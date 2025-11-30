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
    size_t capacity = 0;
    char * str = nullptr;
    char ch;
    while (in >> ch && ch != '\n') {
      if (size + 1 > capacity) {
        size_t newCap = capacity == 0 ? 16 : capacity * 2;
        char * temp = new char[newCap];
        for (size_t i = 0; i < size; ++i) {
          temp[i] = str[i];
        }
        delete[] str;
        str = temp;
        capacity = newCap;
      }
      str[size] = ch;
      ++size;
    }
    if (isSkipWs) {
      in >> std::skipws;
    }
    if (in.fail()) {
      delete[] str;
      size = 0;
      return nullptr;
    }
    str[size] = '\0';
    return str;
  }
  char * excSnd(char * str, const char * mask, char * res)
  {
    size_t k = 0;
    for (size_t i = 0; str[i] != '\0'; ++i) {
      bool isFound = false;
      for (size_t j = 0; mask[j] != '\0'; ++j) {
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
  char * rmvVow(char * str, char * res)
  {
    const char * vowels = "AEIOUaeiou";
    size_t k = 0;
    for (size_t i = 0; str[i] != '\0'; ++i) {
      bool isFound = false;
      for (size_t j = 0; vowels[j] != '\0'; ++j) {
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
  char * str = nullptr;
  char * k1 = nullptr;
  char * k2 = nullptr;
  try {
    size_t size = 0;
    str = sogdanov::getLine(std::cin, size);
    if (!str) {
      return 1;
    }
    const char * mask = "abc";
    k1 = new char[size + 1];
    k2 = new char[size + 1];
    char * res1 = sogdanov::excSnd(str, mask, k1);
    char * res2 = sogdanov::rmvVow(str, k2);
    std::cout << res1 << '\n' << res2 << '\n';
    delete[] k1;
    delete[] k2;
    delete[] str;
  } catch (const std::bad_alloc &) {
    delete[] k1;
    delete[] k2;
    delete[] str;
    std::cerr << "Memory allocation failed\n";
    return 1;
  }
}
