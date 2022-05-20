#include "util.h"

const double eps = 1e-8;

int GetId()
{
    static int id = 0;
    return id++;
}


int Compare(double a, double b = 0.)
{
    if ((a-b) > eps)
        return 1;
    else if ((b-a) > eps)
        return -1;
    else
        return 0;
}
