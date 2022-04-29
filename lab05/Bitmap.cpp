#include "Bitmap.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <cmath>

uint32_t BYTE_PER_PIX;
Bitmap::FileHeader::FileHeader(const char *path)
{
    // 检查源文件路径是否为*.bmp
    std::regex checkBmp(".*\\.bmp", std::regex_constants::icase);
    if (!std::regex_match(path, checkBmp))
        throw FILE_ERROR::SRC_NOT_VALID;

    std::ifstream ifs(path, std::ios::binary);
    if (ifs.fail())
        throw FILE_ERROR::OPEN_ERROR;

    // 读取与检查 Magic Number
    ifs.read(data, 14);
    if (bfType[0] != 'B' || bfType[1] != 'M')
        throw FILE_ERROR::SRC_NOT_VALID;

    ifs.close();
}

Bitmap::DibHeader::DibHeader(const char *path, int skip)
{
    std::ifstream ifs(path, std::ios::binary);
    ifs.seekg(skip);
    ifs.read(data, 40);
    switch (biBitCount)
    {
    case 24:
        BYTE_PER_PIX = 3;
        break;
    case 32:
        BYTE_PER_PIX = 4;
        break;
    default:
        throw FILE_ERROR::SRC_NOT_VALID;
    }
    // 每行的补零数
    uint32_t padding{(4 - ((biWidth * BYTE_PER_PIX) & 0x3)) & 0x3};
    biSizeImage = (biWidth * BYTE_PER_PIX + padding) * biHeight;
    // 其他信息
    if (biSize > 40)
    {
        others = new char[biSize - 40];
        ifs.read(others, biSize - 40);
    }
    else
        others = nullptr;
    ifs.close();
}
Bitmap::DibHeader::~DibHeader()
{
    if (others)
        delete[] others;
}
Bitmap::Matrix::Matrix(const char *path, uint32_t offset, uint32_t imageSize, uint32_t width, uint32_t height,
                       uint32_t padding)
    : pix{new unsigned char[imageSize]}, mWidth{width}, mHeight{height}, mPadding{padding}
{
    std::ifstream ifs(path, std::ios::binary);
    ifs.seekg(offset);
    ifs.read(reinterpret_cast<char *>(pix), imageSize);
}
Bitmap::Matrix::Matrix(uint32_t imageSize, uint32_t width, uint32_t height, uint32_t padding)
    : pix{new unsigned char[imageSize]}, mWidth{width}, mHeight{height}, mPadding{padding}
{
}
unsigned char *Bitmap::Matrix::operator()(uint32_t x, uint32_t y)
{
    return pix + (mWidth * BYTE_PER_PIX + mPadding) * y + x * BYTE_PER_PIX;
}
Bitmap::Bitmap(const char *path)
    : fileHeader(path), dibHeader(path, Bitmap::FileHeader::FILE_HEADER_SIZE),
      matrix(path, fileHeader.bfOffsetBits, dibHeader.biSizeImage, dibHeader.biWidth, dibHeader.biHeight,
             (4 - ((dibHeader.biWidth * BYTE_PER_PIX) & 0x3)) & 0x3),
      iccConfigSize{fileHeader.bfSize - fileHeader.bfOffsetBits - dibHeader.biSizeImage}
{
    if (iccConfigSize)
    {
        iccConfig = new char[iccConfigSize];
        std::ifstream ifs(path);
        ifs.seekg(fileHeader.bfOffsetBits + dibHeader.biSizeImage);
        ifs.read(iccConfig, iccConfigSize);
    }
    else
        iccConfig = nullptr;
}

Bitmap::~Bitmap()
{
    if (matrix.pix)
        delete[] matrix.pix;
}

void Bitmap::Rotate(double angle)
{
    // 修改头文件信息
    uint32_t original_width = dibHeader.biWidth;
    uint32_t original_height = dibHeader.biHeight;
    double width1 = abs(original_width * cos(angle) + original_height * sin(angle));
    double width2 = abs(original_width * cos(angle) - original_height * sin(angle));
    double height1 = abs(original_height * cos(angle) + original_width * sin(angle));
    double height2 = abs(original_height * cos(angle) - original_width * sin(angle));
    dibHeader.biWidth = std::max(width1, width2);
    dibHeader.biHeight = std::max(height1, height2);

    uint32_t newPadding{(4 - ((dibHeader.biWidth * BYTE_PER_PIX) & 0x3)) & 0x3};
    uint32_t desSize{(dibHeader.biWidth * BYTE_PER_PIX + newPadding) * dibHeader.biHeight};
    uint32_t difference{desSize - dibHeader.biSizeImage};
    fileHeader.bfSize += difference;
    dibHeader.biSizeImage = desSize;

    // 位图原始数据
    Matrix tmp(dibHeader.biSizeImage, dibHeader.biWidth, dibHeader.biHeight, newPadding);
    // 遍历新位图中的每一个像素
    for (uint32_t x{0}; x < tmp.mWidth; x++)
    {
        for (uint32_t y{0}; y < tmp.mHeight; y++)
        {
            double original_x =
                (x - tmp.mWidth / 2.0) * cos(angle) - (y - tmp.mHeight / 2.0) * sin(angle) + original_width / 2.0;
            double original_y =
                (x - tmp.mWidth / 2.0) * sin(angle) + (y - tmp.mHeight / 2.0) * cos(angle) + original_height / 2.0;
            if (original_x < 0 || original_x >= original_width - 1 || original_y < 0 ||
                original_y >= original_height - 1)
            {
                std::memset(tmp(x, y), 0, BYTE_PER_PIX);
            }
            else
            {
                uint32_t original_x0 = original_x;
                uint32_t original_y0 = original_y;
                double x_diff = original_x - original_x0;
                double y_diff = original_y - original_y0;
                for (uint32_t i{0}; i < BYTE_PER_PIX; i++)
                {
                    tmp(x, y)[i] = (1 - x_diff) * (1 - y_diff) * matrix(original_x0, original_y0)[i] +
                                   (1 - x_diff) * y_diff * matrix(original_x0, original_y0 + 1)[i] +
                                   x_diff * (1 - y_diff) * matrix(original_x0 + 1, original_y0)[i] +
                                   x_diff * y_diff * matrix(original_x0 + 1, original_y0 + 1)[i];
                }
            }
        }
    }
    if (matrix.pix)
        delete[] matrix.pix;
    matrix.pix = tmp.pix;
}

void Bitmap::Resize(uint32_t newWidth, uint32_t newHeight)
{
    // 修改头文件信息
    uint32_t original_width = dibHeader.biWidth;
    uint32_t original_height = dibHeader.biHeight;
    dibHeader.biWidth = newWidth;
    dibHeader.biHeight = newHeight;

    uint32_t newPadding{(4 - ((dibHeader.biWidth * BYTE_PER_PIX) & 0x3)) & 0x3};
    uint32_t desSize{(dibHeader.biWidth * BYTE_PER_PIX + newPadding) * dibHeader.biHeight};
    uint32_t difference{desSize - dibHeader.biSizeImage};
    fileHeader.bfSize += difference;
    dibHeader.biSizeImage = desSize;

    // 位图原始数据
    Matrix tmp(dibHeader.biSizeImage, dibHeader.biWidth, dibHeader.biHeight, newPadding);
    // 遍历新位图中的每一个像素
    for (uint32_t x{0}; x < tmp.mWidth; x++)
    {
        for (uint32_t y{0}; y < tmp.mHeight; y++)
        {
            double original_x = double(x) / tmp.mWidth * original_width;
            double original_y = double(y) / tmp.mHeight * original_height;
            uint32_t original_x0 = original_x;
            uint32_t original_y0 = original_y;
            double x_diff = original_x - original_x0;
            double y_diff = original_y - original_y0;
            for (uint32_t i{0}; i < BYTE_PER_PIX; i++)
            {
                tmp(x, y)[i] = (1 - x_diff) * (1 - y_diff) * matrix(original_x0, original_y0)[i] +
                               (1 - x_diff) * y_diff * matrix(original_x0, original_y0 + 1)[i] +
                               x_diff * (1 - y_diff) * matrix(original_x0 + 1, original_y0)[i] +
                               x_diff * y_diff * matrix(original_x0 + 1, original_y0 + 1)[i];
            }
        }
    }
    if (matrix.pix)
        delete[] matrix.pix;
    matrix.pix = tmp.pix;
}

void Bitmap::HorizontalFlip()
{
    // 位图原始数据
    Matrix tmp(dibHeader.biSizeImage, dibHeader.biWidth, dibHeader.biHeight, matrix.mPadding);
    // 遍历新位图中的每一个像素
    for (uint32_t x{0}; x < tmp.mWidth; x++)
    {
        for (uint32_t y{0}; y < tmp.mHeight; y++)
        {
            memcpy(tmp(x,y),matrix(dibHeader.biWidth-1-x,y),BYTE_PER_PIX);
        }
    }
    if (matrix.pix)
        delete[] matrix.pix;
    matrix.pix = tmp.pix;
}
void Bitmap::VerticalFlip()
{
    // 位图原始数据
    Matrix tmp(dibHeader.biSizeImage, dibHeader.biWidth, dibHeader.biHeight, matrix.mPadding);
    // 遍历新位图中的每一个像素
    for (uint32_t x{0}; x < tmp.mWidth; x++)
    {
        for (uint32_t y{0}; y < tmp.mHeight; y++)
        {
            memcpy(tmp(x,y),matrix(x,dibHeader.biHeight-1-y),BYTE_PER_PIX);
        }
    }
    if (matrix.pix)
        delete[] matrix.pix;
    matrix.pix = tmp.pix;
}

void Bitmap::Save(const char *path)
{
    // 检查保存路径是否为*.bmp
    std::regex checkBmp(".*\\.bmp", std::regex_constants::icase);
    if (!std::regex_match(path, checkBmp))
        throw FILE_ERROR::SAVE_NOT_BMP;

    std::ofstream ofs(path, std::ios::binary);
    ofs.write(fileHeader.data, 14);
    ofs.write(dibHeader.data, 40);
    if (dibHeader.others)
        ofs.write(dibHeader.others, dibHeader.biSize - 40);
    if (ofs.fail())
        throw FILE_ERROR::SAVE_ERROR;
    ofs.seekp(fileHeader.bfOffsetBits);
    ofs.write(reinterpret_cast<char *>(matrix.pix), dibHeader.biSizeImage);
    if (iccConfig)
        ofs.write(iccConfig, iccConfigSize);
    ofs.close();
}
