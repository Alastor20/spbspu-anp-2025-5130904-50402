#include <iostream>
#include <iomanip>
#include <fstream>
namespace sogdanov
{
  char * getline(std::istream & in, size_t & size)
  {
    bool isSkipWs = (in.flag() & std::ios::skipws);
    if (isSkipWs) {
      in >> std::noskipws;
    }
    size_t len = 0;
    char * str = nullptr;
    char ch;
    while (in >> ch && ch !='\n') {
      if (size +1 > len) {
        size_t newLen = len + 1;
        char * temp = new char[newLen];
        for (size_t i = 0; i < size; ++i) {
          temp[i] = str[i];
        }
        delete[] str;
        str = temp;
        len = newLen;
      }
      str[size] = ch;
      ++size;
    }
    if (isSkipWs) {
      in >> std::skipws;
    }
    if (in.bad()) {
      delete[] str;
      size = 0;
      throw std::logic_error("Input error\n");
    }
    if (in.eof()) {
      return nullptr;
    }
    if (size + 1 > len) {
      const int newLen = 1;
      char * temp = new char[newLen];
      for (size_t i = 0; i < size; ++i) {
        temp[i] = str[i];
      }
      delete[] str;
      str = temp;
      len = newLen;
    }
    str[size] = '\0';
    ++size;
    return str;
  }
}
int main()
{
}
