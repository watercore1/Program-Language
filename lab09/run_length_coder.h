#ifndef RLC_LENGTH_H_
#define RLC_LENGTH_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "util.h"

using namespace std;

template <class T>
struct RepeatSymbol {
  T value;
  int count;
  bool is_head;  //头元素只是一个占位元素，用来初始化第一个元素
  RepeatSymbol(T v, int c, bool h) : value(v), count(c), is_head(h) {}
};

template <class T>
class RunLengthCoder {
 private:
  //文件内容的行数和列数，用于解码时还原文本文件
  int rows, columns;
  //原始文件和编码文件的大小，以字节为单位
  int decode_file_size, encode_file_size;
  //编码数组
  vector<RepeatSymbol<T>> symbols;

 public:
  //构造函数
  RunLengthCoder();
  //从原始文件中读取数据并储存
  void ReadDecodedFile(string filename);
  //编码后写入文件
  void OutputEncodedFile(string filename);
  //从编码文件中读取数据并储存
  void ReadEncodedFile(string filename);
  //解码后写入文件
  void OutputDecodedFile(string filename);
  //判断两个元素是否相等
  bool IsEqual(T cur, T next);
  //写入文件后，输出压缩信息
  void PrintCompressionInfo();
};

template <class T>
RunLengthCoder<T>::RunLengthCoder(){
  symbols.push_back(RepeatSymbol<T>(T(0),0,true));
}

template <class T>
void RunLengthCoder<T>::ReadDecodedFile(string filename){
  //以文本格式打开文件
  ifstream fin(filename);
  T read_next;
  //行列数
  fin >> rows >> columns;
  while(fin >> read_next){
    /*在两种情况下都要在编码数组中添加一个新元素：
    1.遇到一个不同的元素
    2.当前是访问的是文件中第一个元素，等价于当前编码列表中只有我们初始化的一个元素。    
    */
    if(!IsEqual(symbols.back().value,read_next) || symbols.back().is_head){
      symbols.push_back(RepeatSymbol<T>(read_next,1,false));
    }
    else{
      symbols.back().count++;
    }
  }
	fin.close();
  cout<<"Read "<<filename <<" successfully."<<endl<<endl;

  //获取原始文件大小
  decode_file_size=GetFileSize(filename);

}

template <class T>
void RunLengthCoder<T>::OutputEncodedFile(string filename) {
  //以文本格式打开文件
  ofstream fout(filename);
  fout << rows <<" "<< columns<<endl;
  for(auto symbol:symbols)
    if(!symbol.is_head){
      fout<<symbol.value<<" "<<symbol.count<<endl;
  }
  fout.close();
  cout<<"Output to "<<filename <<" successfully."<<endl<<endl;

  //获取编码后文件大小
  encode_file_size = GetFileSize(filename);
  PrintCompressionInfo();
}

template <class T>
void RunLengthCoder<T>::ReadEncodedFile(string filename){
  //以文本格式打开文件
  ifstream fin(filename);
  T read_next;
  int count;
  //行列数
  fin >> rows >> columns;
  while(fin >> read_next >> count){
    symbols.push_back(RepeatSymbol<T>(read_next,count,false));
  }
	fin.close();
  cout<<"Read "<<filename <<" successfully."<<endl<<endl;

  //获取编码文件大小
  encode_file_size=GetFileSize(filename);
}

template <class T>
void RunLengthCoder<T>::OutputDecodedFile(string filename) {
  //以文本格式打开文件
  ofstream fout(filename);
  fout << rows <<" "<< columns<<endl;
  int count=0;  //已经输出了多少个字符
  for(auto symbol:symbols){
    if(!symbol.is_head){
      for(int j=0;j<symbol.count;j++){
        count++;
        fout<<symbol.value<<" ";
        //注意换行
        if(count % columns==0) fout<<endl;
      }
    }
  }
  fout.close();
  cout<<"Output to "<<filename <<" successfully."<<endl<<endl;

  //获取解码后文件大小
  decode_file_size = GetFileSize(filename);
}

template <class T>
bool RunLengthCoder<T>::IsEqual(T cur, T next){
  if(std::is_same<T,float>::value){
    double eps = 1e-6;
    return abs(cur-next)<eps;
  }
  else return cur==next;
}

template <class T>
void RunLengthCoder<T>::PrintCompressionInfo() {
    cout << "encode file size: " << encode_file_size << " bytes" << endl;
    cout << "decode file size: " << decode_file_size << " bytes" << endl;
    cout << "compression ratio: " << double(encode_file_size) / decode_file_size
         << endl
         << endl;
  };


#endif