#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>

namespace matveev
{
  char* getLine(std::istream& in, size_t& len);
  char* rmLat(char* dest, const char* src);
  int hasRep(const char* str);
}

int main()
{
  size_t len = 0;
  char* str = matveev::getLine(std::cin, len);
  if (str == nullptr) {
    std::cerr << "Error memory\n";
    return 1;
  }

  size_t strLen = 0;
  while (str[strLen] != '\0')
  {
    ++strLen;
  }
  char* res = static_cast< char* >(std::malloc(strLen + 1));
  if (res == nullptr)
  {
    std::free(str);
    std::cerr << "Error memory\n";
    return 1;
  }

  matveev::rmLat(res, str);
  std::cout << res << "\n";
  std::cout << matveev::hasRep(str) << "\n";
  std::free(res);
  std::free(str);
  return 0;
}

char* matveev::getLine(std::istream& in, size_t& len)
{
  size_t cap = 16;
  len = 0;
  char* buf = static_cast< char* >(std::malloc(cap));
  if (buf == nullptr)
  {
    return nullptr;
  }
  bool wasSkip = (in.flags() & std::ios_base::skipws);
  if (wasSkip)
  {
    in >> std::noskipws;
  }
  char c = '\0';
  while (in >> c && c != '\n')
  {
    if (len + 1 >= cap)
    {
      size_t newCap = cap * 2;
      char* newBuf = static_cast< char* >(std::malloc(newCap));
      if (newBuf == nullptr)
      {
        std::free(buf);
        if (wasSkip)
        {
          in >> std::skipws;
        }
        return nullptr;
      }
      std::memcpy(newBuf, buf, cap);
      std::free(buf);
      buf = newBuf;
      cap = newCap;
    }
    buf[len] = c;
    len++;
  }
  buf[len] = '\0';
  if (wasSkip)
  {
    in >> std::skipws;
  }
  return buf;
}

char* matveev::rmLat(char* dest, const char* src)
{
  size_t j = 0;
  for (size_t i = 0; src[i] != '\0'; ++i) {
    if (!std::isalpha(static_cast< unsigned char >(src[i]))) {
      dest[j] = src[i];
      j++;
    }
  }
  dest[j] = '\0';
  return dest;
}

int matveev::hasRep(const char* str)
{
  for (size_t i = 0; str[i] != '\0'; ++i) {
    for (size_t j = i + 1; str[j] != '\0'; ++j) {
      if (str[i] == str[j]) {
        return 1;
      }
    }
  }
  return 0;
}
