#include <iostream>

namespace lachugin
{
  const size_t startSize = 10;
  bool hasSam(const char* frsLine, const char* scnLine)
  {
    for (size_t i = 0; frsLine[i] != '\0'; i++)
    {
      if (frsLine[i] == ' ')
      {
        continue;
      }
      for (size_t j = 0; scnLine[j] != '\0'; j++)
      {
        if (frsLine[i] == scnLine[j])
        {
          return true;
        }
      }
    }
    return false;
  }

  void fopy(const char* oldLine, size_t s, char* newLine)
  {
    for (size_t i = 0; i < s; i++)
    {
      newLine[i] = oldLine[i];
    }
  }

  char* cut(const char* str, size_t& s)
  {
    char* newLine = reinterpret_cast < char* >(malloc((s + 1) * sizeof(char)));
    if (!newLine)
    {
      return nullptr;
    }

    for (size_t i = 0; i < s; i++)
    {
      newLine[i] = str[i];
    }
    newLine[s] = '\0';
    return newLine;
  }

  char* latRmv(const char* str, size_t& s, char* newLine)
  {
    size_t k = 0;
    for (size_t i = 0; str[i] != '\0'; i++)
    {
      unsigned char ch = static_cast<unsigned char>(str[i]);
      if (!std::isalpha(ch))
      {
        newLine[k++] = str[i];
      }
    }
    newLine[k] = '\0';
    s = k;
    char* temp = cut(newLine, s);
    free(newLine);

    if (!temp)
    {
      return nullptr;
    }

    return temp;
  }

  char* expand(char* oldLine, size_t& oldSize) {
    size_t newSize = oldSize + startSize;
    char* newLine = reinterpret_cast < char* >(malloc(newSize * sizeof(char)));
    if (!newLine)
    {
      return nullptr;
    }
    fopy(oldLine, oldSize, newLine);
    oldSize = newSize;
    return newLine;
  }

  char* getline(std::istream& in, size_t& s)
  {
    char* data = reinterpret_cast< char* >(malloc(s * sizeof(char)));
    if (!data) return nullptr;

    bool is_skip = in.flags() & std::ios_base::skipws;
    if (is_skip)
      in >> std::noskipws;

    size_t i = 0;
    char hlpChar;
    while (!(hlpChar == '\n'))
    {
      if (i + 1 >= s)
      {
        char* helpLine = expand(data, s);
        if (!helpLine)
        {
          free(data);
          return nullptr;
        }
        free(data);
        data = helpLine;
      }
      if (!(in >> hlpChar))
        break;
      data[i++] = hlpChar;
    }
    data[i] = '\0';
    char* helpLine =  cut (data, s);
    data = helpLine;

    if (is_skip)
      in >> std::skipws;

    return data;
  }
}

int main()
{
  size_t s = lachugin::startSize;
  char* str = lachugin::getline(std::cin, s);
  if (!str || s == 0)
  {
    free(str);
    std::cerr << "Error: no input.\n";
    return 2;
  }
  const char* string = "acb";
  char* newLine = reinterpret_cast<char*>(malloc(s * sizeof(char)));
  if (!newLine)
  {
    free(newLine);
    std::cerr << "Error: no input.\n";
    return 2;
  }
  char* res2 = lachugin::latRmv(str, s, newLine);
  if (!res2)
  {
    free(str);
    std::cerr << "Not enough memory for string input.\n";
    return 1;
  }
  bool res1 = lachugin::hasSam(str, string);
  std::cout << res1 << '\n';
  std::cout << res2 << '\n';
  free(str);
  free(res2);
}
