#include <iostream>
#include <fstream>
#include <string>
#include <sys\stat.h>


using namespace std;

//用户输入要处理的文件类型
int GetOption();
//获取文件名
string GetFilename(string filetype);
//获取文件大小
int GetFileSize(string filename);