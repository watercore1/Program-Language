#include "util.h"

// precision of double
const double eps = 1e-10;

int GenerateId()
{
    static int id = 0;
    return id++;
}


int Compare(double a, double b)
{
    if ((a-b) > eps)
        return 1;
    else if ((b-a) > eps)
        return -1;
    else
        return 0;
}

std::string DoubleToString(const double n){
    char* chCode;
    chCode = new char[20];
    sprintf(chCode, "%.2lf", n);
    std::string str(chCode);
    delete[]chCode;
    return str;
}