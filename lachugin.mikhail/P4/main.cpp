#include <iostream>
#include <cctype>
#include <cstring>

namespace lachugin
{
  const size_t startSize = 10;

  void fopy(const char* src, size_t n, char* dst)
  {
    for (size_t i = 0; i < n; i++)
    {
      dst[i] = src[i];
    }
  }

  char* expand(char* oldLine, size_t oldCap, size_t& newCap)
  {
    newCap = oldCap + startSize;
    char* newLine =
      reinterpret_cast<char*>(malloc(newCap));

    if (!newLine)
    {
      return nullptr;
    }

    fopy(oldLine, oldCap, newLine);
    free(oldLine);
    return newLine;
  }

  char* getline(std::istream& in, size_t& len)
  {
    size_t cap = startSize;
    char* data =
      reinterpret_cast<char*>(malloc(cap));

    if (!data)
    {
      return nullptr;
    }

    len = 0;
    char c;

    while (in.get(c))
    {
      if (c == '\n')
      {
        break;
      }
      if (len + 1 >= cap)
      {
        char* tmp = expand(data, cap, cap);
        if (!tmp)
        {
          free(data);
          return nullptr;
        }
        data = tmp;
      }
      data[len++] = c;
    }
    if (len == 0 && in.eof())
    {
      free(data);
      return nullptr;
    }
    data[len] = '\0';
    return data;
  }

  char* latRmv(const char* str, size_t len)
  {
    char* tmp = reinterpret_cast<char*>(malloc(len + 1));

    if (!tmp)
    {
      return nullptr;
    }

    size_t k = 0;
    for (size_t i = 0; i < len; i++)
    {
      if (!std::isalpha(static_cast<unsigned char>(str[i])))
      {
        tmp[k++] = str[i];
      }
    }

    tmp[k] = '\0';
    return tmp;
  }

  bool res1(const char* a, size_t as, const char* b, size_t bs)
  {
    for (size_t i = 0; i < as; i++)
    {
      if (a[i] == ' ')
      {
        continue;
      }

      for (size_t j = 0; j < bs; j++)
      {
        if (a[i] == b[j])
        {
          return true;
        }
      }
    }
    return false;
  }
}

int main()
{
  size_t len = 0;
  char* str = lachugin::getline(std::cin, len);

  if (!str)
  {
    std::cerr << "Error: no input.\n";
    return 1;
  }

  const char* pattern = "acb";
  bool found = lachugin::res1(str, len, pattern, 3);

  char* filtered = lachugin::latRmv(str, len);
  if (!filtered)
  {
    free(str);
    return 2;
  }

  std::cout << found << '\n';
  std::cout << filtered << '\n';

  free(str);
  free(filtered);
}
