#ifndef BITMAP_H
#define BITMAP_H
#include <cstdint>

enum class FILE_ERROR
{
    SRC_NOT_VALID,
    OPEN_ERROR,
    SAVE_NOT_BMP,
    SAVE_ERROR
};

class Bitmap
{
private:
    struct FileHeader
    {
        static constexpr int FILE_HEADER_SIZE{14};

        char data[14];
        char *bfType{data};
        // 整个 bmp 文件的大小
        uint32_t &bfSize{*reinterpret_cast<uint32_t *>(data + 2)};
        // 预留字段，通常为 0
        uint16_t &bfReserved1{*reinterpret_cast<uint16_t *>(data + 6)};
        // 预留字段，通常为 0
        uint16_t &bfReserved2{*reinterpret_cast<uint16_t *>(data + 8)};
        // 图片信息的开始位置，通常为 54
        uint32_t &bfOffsetBits{*reinterpret_cast<uint32_t *>(data + 10)};
        FileHeader(const char *path);
    };
    struct DibHeader
    {
        char data[40];
        // Dib header 的大小，通常为 40
        uint32_t &biSize{*reinterpret_cast<uint32_t *>(data)};
        // 图像宽度，单位为像素
        uint32_t &biWidth{*reinterpret_cast<uint32_t *>(data + 4)};
        // 图像高度，单位为像素
        uint32_t &biHeight{*reinterpret_cast<uint32_t *>(data + 8)};
        // 色彩平面，必须为 1
        uint16_t &biPlanes{*reinterpret_cast<uint16_t *>(data + 12)};
        // 每像素用多少 bit 表示
        uint16_t &biBitCount{*reinterpret_cast<uint16_t *>(data + 14)};
        // 压缩方式，通常不压缩，值为 0
        uint32_t &biCompression{*reinterpret_cast<uint32_t *>(data + 16)};
        // 原始位图数据的大小，不包括文件头
        uint32_t &biSizeImage{*reinterpret_cast<uint32_t *>(data + 20)};
        // 横向分辨率（像素/米）
        uint32_t &biXPelsPerMeter{*reinterpret_cast<uint32_t *>(data + 24)};
        // 纵向分辨率（像素/米）
        uint32_t &biYPelsPerMeter{*reinterpret_cast<uint32_t *>(data + 28)};
        // 调色板中颜色数量
        uint32_t &biClrUsed{*reinterpret_cast<uint32_t *>(data + 32)};
        // 重要颜色的数量
        uint32_t &biClrImportant{*reinterpret_cast<uint32_t *>(data + 36)};
        char *others;
        DibHeader(const char *path, int skip);
        ~DibHeader();
    };
    struct Matrix
    {
        // 注意必须是 unsigned，因为在插值时要与 double 进行运算
        unsigned char *pix;
        uint32_t mWidth, mHeight, mPadding;
        Matrix(const char *path, uint32_t offset, uint32_t imageSize, uint32_t width, uint32_t height, uint32_t padding);
        Matrix(uint32_t imageSize, uint32_t width, uint32_t height, uint32_t padding);

        unsigned char *operator()(uint32_t x, uint32_t y);
    };
    FileHeader fileHeader;
    DibHeader dibHeader;
    Matrix matrix;
    uint32_t iccConfigSize;
    char *iccConfig;

public:
    Bitmap(const char *path);
    ~Bitmap();
    void Rotate(double angle);
    void Resize(uint32_t newWidth,uint32_t newHeight);
    void HorizontalFlip();
    void VerticalFlip();
    void Save(const char *path);
};
#endif // BITMAP_H
