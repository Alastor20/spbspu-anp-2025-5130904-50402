#include <iostream>
#include <iomanip>
namespace sogdanov
{
  char * getLine(std::istream & in, size_t & size)
  {
    bool isSkipWs = (in.flags() & std::ios::skipws);
    if (isSkipWs) {
      in >> std::noskipws;
    }
    size_t len = 0;
    char * str = nullptr;
    char ch;
    while (in >> ch && ch !='\n') {
      if (size +1 > len) {
        size_t newLen = len * 2;
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
    char * temp = new char[size + 1];
    for (size_t i = 0; i < size; ++i) {
      temp[i] = str[i];
    }
    delete[] str;
    str = temp;
    str[size] = '\0';
    ++size;
    return str;
  }
  size_t len(const char * a)
  {
    size_t count = 0;
    for (size_t i = 0; a[i] != '\0'; ++i) {
      count++;
    }
    return count;
  }
  char * excSnd(char * str, const char * mask, char * res, size_t size, size_t maskLen)
  {
    size_t k = 0;
    for (size_t i = 0; i < size; ++i) {
      bool isFound = false;
      for (size_t j = 0; j < maskLen; ++j) {
        if (str[i] == mask[j]) {
          isFound = true;
          break;
        }
      }
      if (!isFound) {
        res[k] = str[i];
        k++;
      }
    }
    res[k] = '\0';
    return res;
  }
  char * rmvVow(char * str, char * res, size_t size)
  {
    const char * vowels = "AEIOUaeiou";
    size_t vowelsLen = len(vowels);
    size_t k = 0;
    for (size_t i = 0; i < size; ++i) {
      bool isFound = false;
      for (size_t j = 0; j < vowelsLen; ++j) {
        if (str[i] == vowels[j]) {
          isFound = true;
          break;
        }
      }
      if (!isFound) {
        res[k] = str[i];
        k++;
      }
    }
    res[k] = '\0';
    return res;
  }
}

int main()
{
  try {
    size_t size = 0;
    char * str = sogdanov::getLine(std::cin, size);
    if (!str) {
      return 1;
    }
    const char * mask = "abc";
    size_t maskLen = sogdanov::len(mask);
    char * k1 = new char[size];
    char * k2 = new char[size];
    char * res1 = sogdanov::excSnd(str, mask, k1, size, maskLen);
    char * res2 = sogdanov::rmvVow(str, k2, size);
    std::cout << res1 << '\n' << res2 << '\n';
    delete[] res1;
    delete[] res2;
    delete[] str;
  } catch (const std::bad_alloc &) {
    std::cerr << "Memory allocation failed\n";
    return 1;
  }
}
