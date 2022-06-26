#include "util.h"


int GetOption() {
  cout << "Choose the type of input file:\n"
          "1) original integer    2)encode integer\n"   
          "3) original char       4)encode char\n"   
          "5) original float      6)encode float\n"   
          "7) original binary     8)encode binary\n"   
          "9) quit\n"
          "please enter 1-9: ";
  unsigned int option;
  while (!(cin >> option) || option > 9) {
    //跳过错误输入，清空缓冲区
    cin.clear();
    cin.sync();
    cout << "please enter 1-9: ";
  }
  cin.clear();
  cin.sync();
  return option;
}

string GetFilename(string filetype){
  cout << "Please enter " << filetype << " file name: ";
  string filename;
  getline(cin,filename);

  ifstream fin(filename);
  while(!fin.is_open()){
    cout <<"Can't open "<< filename <<". Please enter again: ";
    getline(cin,filename);
    fin.open(filename);
  }

  fin.close();
  return filename;
}

int GetFileSize(string filename){
  struct _stat info;
	_stat(filename.c_str(), &info);
	return info.st_size;
}

