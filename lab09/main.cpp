#include "run_length_coder.h"
#include "rlc_binary.h"

using namespace std;
int main() {
  int option = GetOption();

  while (option != 9) {
    switch (option) {
      case 1: {
        RunLengthCoder<int> rlc_int;
        //rlc_int.ReadDecodedFile(GetFilename("origin input"));
        //rlc_int.OutputEncodedFile(GetFilename("encode output"));
        rlc_int.ReadDecodedFile("input-int.txt");
        rlc_int.OutputEncodedFile("encode-int.txt");
        break;
      }

      case 2: {
        RunLengthCoder<int> rlc_int;
        //rlc_int.ReadEncodedFile(GetFilename("encode input"));
        //rlc_int.OutputDecodedFile(GetFilename("decode output"));
        rlc_int.ReadEncodedFile("encode-int.txt");
        rlc_int.OutputDecodedFile("decode-int.txt");
        break;
      }

      case 3: {
        RunLengthCoder<char> rlc_char;
        //rlc_char.ReadDecodedFile(GetFilename("origin input"));
        //rlc_char.OutputEncodedFile(GetFilename("encode output"));
        rlc_char.ReadDecodedFile("input-char.txt");
        rlc_char.OutputEncodedFile("encode-char.txt");
        break;
      }

      case 4: {
        RunLengthCoder<char> rlc_char;
        //rlc_char.ReadEncodedFile(GetFilename("encode input"));
        //rlc_char.OutputDecodedFile(GetFilename("decode output"));
        rlc_char.ReadEncodedFile("encode-char.txt");
        rlc_char.OutputDecodedFile("decode-char.txt");
        break;
      }

      case 5: {
        RunLengthCoder<float> rlc_float;
        //rlc_float.ReadDecodedFile(GetFilename("origin input"));
        //rlc_float.OutputEncodedFile(GetFilename("encode output"));
        rlc_float.ReadDecodedFile("input-float.txt");
        rlc_float.OutputEncodedFile("encode-float.txt");
        break;
      }

      case 6: {
        RunLengthCoder<float> rlc_float;
        //rlc_float.ReadEncodedFile(GetFilename("encode input"));
        //rlc_float.OutputDecodedFile(GetFilename("decode output"));
        rlc_float.ReadEncodedFile("encode-float.txt");
        rlc_float.OutputDecodedFile("decode-float.txt");
        break;
      }

      case 7: {
        RunLengthCoder<unsigned char> rlc_binary;
        //rlc_binary.ReadDecodedFile(GetFilename("origin input"));
        //rlc_binary.OutputEncodedFile(GetFilename("encode output"));
        rlc_binary.ReadDecodedFile("input-binary.bmp");
        rlc_binary.OutputEncodedFile("encode-binary");
        break;
      }

      case 8: {
        RunLengthCoder<unsigned char> rlc_binary;
        //rlc_binary.ReadEncodedFile(GetFilename("encode input"));
        //rlc_binary.OutputDecodedFile(GetFilename("decode output"));
        rlc_binary.ReadEncodedFile("encode-binary");
        rlc_binary.OutputDecodedFile("decode-binary.bmp");
        break;
      }

      default:
        break;
    }
    option = GetOption();
  }

  return 0;
}
