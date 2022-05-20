#include "Bitmap.h"
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
enum class PARAM_ERROR
{
    TOO_MANY_PARAM,
    TOO_FEW_PARAM,
    UNKNOWN_PARAM,
    INVALID_PARAM
};
inline constexpr double pi()
{
    return std::atan(1) * 4;
}
inline void checkArgCount(unsigned int actual_num, unsigned int expected_num)
{
    if (actual_num < expected_num)
        throw PARAM_ERROR::TOO_FEW_PARAM;
    else if (actual_num > expected_num)
        throw PARAM_ERROR::TOO_MANY_PARAM;
}
void paramErrMsg(const char *param, const char *message);
int main(int argc, char *argv[])
{
    try
    {
        Bitmap bitmap(argv[1]);
        if (strcmp(argv[2], "rotate") == 0)
        {
            checkArgCount(argc, 5);
            double angle = std::stod(std::string(argv[3]));
            bitmap.Rotate(angle / 180 * pi());
        }
        else if (strcmp(argv[2], "resize") == 0)
        {
            checkArgCount(argc, 6);
            int newWidth = std::atoi(argv[3]);
            int newHeight = std::atoi(argv[4]);
            bitmap.Resize(newWidth, newHeight);
        }
        else if (strcmp(argv[2], "h_flip") == 0)
        {
            checkArgCount(argc, 4);
            bitmap.HorizontalFlip();
        }
        else if (strcmp(argv[2], "v_flip") == 0)
        {
            checkArgCount(argc, 4);
            bitmap.VerticalFlip();
        }
        else
        {
            throw PARAM_ERROR::UNKNOWN_PARAM;
        }
        bitmap.Save(argv[argc-1]);
    } 
    catch (PARAM_ERROR error)
    {
        switch (error)
        {
        case PARAM_ERROR::TOO_FEW_PARAM:
            std::cout << "\033[31m"
                      << "Too few parameters."
                      << "\033[0m" << std::endl;
            break;
        case PARAM_ERROR::TOO_MANY_PARAM:
            std::cout << "\033[31m"
                      << "Too Many parameters."
                      << "\033[0m" << std::endl;
            break;
        case PARAM_ERROR::UNKNOWN_PARAM:
            paramErrMsg(argv[2], "is unknown parameters.");
            break;
        }
        return EXIT_FAILURE;
    }
    catch (std::invalid_argument error){
        std::cout << "\033[31m"
                      << "There is invalid integer or double number."
                      << "\033[0m" << std::endl;
    }
    catch (FILE_ERROR error)
    {
        switch (error)
        {
        case FILE_ERROR::SRC_NOT_VALID:
            paramErrMsg(argv[1], "File is NOT a valid 24-bit or 32-bit .bmp bitmap.");
            break;
        case FILE_ERROR::OPEN_ERROR:
            paramErrMsg(argv[1], "File does NOT exist or does NOT have permission.");
            break;
        case FILE_ERROR::SAVE_NOT_BMP:
            paramErrMsg(argv[argc - 1], "Destination path is NOT a .bmp file.");
            break;
        case FILE_ERROR::SAVE_ERROR:
            paramErrMsg(argv[argc - 1], "Destination path is NOT valid. Maybe no permission.");
            break;
        }
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
void paramErrMsg(const char *arg, const char *message)
{
    std::cout << arg << std::endl;
    std::cout << "\033[32m" << std::setiosflags(std::ios::left) << std::setfill('~') << std::setw(strlen(arg)) << "^"
              << std::endl;
    std::cout << "|\n|\n";
    std::cout << "\033[31m" << message << "\033[0m" << std::endl;
}
