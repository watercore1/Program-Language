/**
 * @File   :rlc_binary.h
 * @author :watercore email:1900012476@pku.edu.cn
 * @Date   :2022-06-02
 * @brief  :RLC 的显式具体化，使用 unsigned char 类型，即字节读取二进制文件
 *
 */
#ifndef RLC_BINARY_H_
#define RLC_BINARY_H_
#include "run_length_coder.h"

template <>
RunLengthCoder<unsigned char>::RunLengthCoder() {
  symbols.push_back(RepeatSymbol<unsigned char>('\0', 0, true));
}

//由于这两个函数被下面的函数调用，所以要把模板化放在前面，否则会调用隐式模板化

template <>
bool RunLengthCoder<unsigned char>::IsEqual(unsigned char cur,
                                            unsigned char next) {
  return cur == next;
}

template <>
void RunLengthCoder<unsigned char>::PrintCompressionInfo() {
  cout << "encode file size: " << encode_file_size << " bytes" << endl;
  cout << "decode file size: " << decode_file_size << " bytes" << endl;
  cout << "compression ratio: " << double(encode_file_size) / decode_file_size
       << endl
       << endl;
};

template <>
void RunLengthCoder<unsigned char>::ReadDecodedFile(string filename) {
  //以二进制格式打开文件
  ifstream fin(filename, ios::binary);
  unsigned char read_next;
  while (fin >> noskipws >> read_next) {
    /*在两种情况下都要在编码数组中添加一个新元素：
    1.遇到一个不同的元素
    2.当前是访问的是文件中第一个元素，等价于当前编码列表中只有我们初始化的一个元素。
    */
    if (!IsEqual(symbols.back().value, read_next) || symbols.back().is_head) {
      symbols.push_back(RepeatSymbol<unsigned char>(read_next, 1, false));
    } else {
      symbols.back().count++;
    }
  }
  fin.close();
  cout << "Read " << filename << " successfully." << endl << endl;

  //获取原始文件大小
  decode_file_size = GetFileSize(filename);
}

template <>
void RunLengthCoder<unsigned char>::OutputEncodedFile(string filename) {
  //以二进制格式打开文件
  ofstream fout(filename, ios::binary);
  for (auto symbol : symbols)
    if (!symbol.is_head) {
      //如果重复数大于255，则要进行拆分
      if (symbol.count > 255) {
        int remain = symbol.count;
        while (remain >= 255) {
          fout << symbol.value << (unsigned char)255;
          remain -= 255;
        }
        //此时可能的剩余值为0-254，如果为0，则不用再输出了
        if (remain != 0) fout << symbol.value << (unsigned char)remain;
      } else
        fout << symbol.value << (unsigned char)symbol.count;
    }
  fout.close();
  cout << "Output to " << filename << " successfully." << endl << endl;

  //获取编码后文件大小
  encode_file_size = GetFileSize(filename);
  PrintCompressionInfo();
}

template <>
void RunLengthCoder<unsigned char>::ReadEncodedFile(string filename) {
  //以文本格式打开文件
  ifstream fin(filename, ios::binary);
  unsigned char read_next;
  unsigned char count;
  while (fin >> noskipws >> read_next>>count) {
			symbols.push_back(RepeatSymbol<unsigned char>(read_next, int(count) , false));
  }
  fin.close();
  cout << "Read " << filename << " successfully." << endl << endl;

  //获取编码文件大小
  encode_file_size = GetFileSize(filename);
}

template <>
void RunLengthCoder<unsigned char>::OutputDecodedFile(string filename) {
  //以二进制格式打开文件
  ofstream fout(filename, ios::binary);

  for (auto symbol : symbols) {
    if (!symbol.is_head) {
      for (int j = 0; j < symbol.count; j++) {
        fout << symbol.value;
      }
    }
  }
  fout.close();
  cout << "Output to " << filename << " successfully." << endl << endl;

  //获取解码后文件大小
  decode_file_size = GetFileSize(filename);
}



#endif