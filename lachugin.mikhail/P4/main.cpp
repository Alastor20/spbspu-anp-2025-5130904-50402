#include <iostream>
#include <cctype>

namespace lachugin
{
  const size_t startSize = 10;

  bool res1(const char* frsLine, size_t frsSize, const char* scnLine, size_t scnSize)
  {
    size_t min = (frsSize < scnSize) ? frsSize : scnSize;
    size_t max = (frsSize > scnSize) ? frsSize : scnSize;
    const char* minLine = (min == frsSize) ? frsLine : scnLine;
    const char* maxLine = (max == frsSize) ? frsLine : scnLine;
    for (size_t i = 0; i < min; i++)
    {
      if (minLine[i] == ' ')
      {
        continue;
      }
      for (size_t j = 0; j < max; j++)
      {
        if (minLine[i] == maxLine[j])
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
    char* newLine = reinterpret_cast<char*>(malloc((s) * sizeof(char)));
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

  char* latRmv(const char* str, size_t& s)
  {
    char* newLine = reinterpret_cast<char*>(malloc(s * sizeof(char)));
    if (!newLine)
    {
      return nullptr;
    }
    size_t k = 0;
    bool lastSpace = false;
    for (size_t i = 0; i < s; i++)
    {
      unsigned char ch = static_cast<unsigned char>(str[i]);
      if (std::isdigit(ch))
      {
        newLine[k++] = str[i];
        lastSpace = false;
      }
      else if (std::isspace(ch))
      {
        if (!lastSpace)
        {
          newLine[k++] = ' ';
          lastSpace = true;
        }
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

  char* expand(char* oldLine, size_t& oldSize)
  {
    size_t newSize = oldSize + startSize;
    char* newLine = reinterpret_cast<char*>(malloc(newSize * sizeof(char)));
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
    char* data = reinterpret_cast<char*>(malloc(s * sizeof(char)));
    if (!data)
    {
      return nullptr;
    }
    bool is_skip = in.flags() & std::ios_base::skipws;
    if (is_skip)
    {
      in >> std::noskipws;
    }
    size_t i = 0;
    bool input = true;
    while (input)
    {
      if (i >= s)
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
      in >> data[i];
      if (data[i] == '\n')
      {
        input = false;
      }
      if (in.eof())
      {
        input = false;
      }
      i++;
    }
    data[i] = '\0';
    s = i;
    char* temp = nullptr;
    temp = cut(data, s);
    free(data);
    data = temp;
    if (!is_skip)
    {
      in >> std::skipws;
    }
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
  const size_t len = 3;
  char* res2 = lachugin::latRmv(str, s);
  if (!res2)
  {
    free(str);
    std::cerr << "Not enough memory for string input.\n";
    return 1;
  }
  bool res1 = lachugin::res1(str, s, string, len);
  std::cout << res1 << '\n';
  std::cout << res2 << '\n';
  free(str);
  free(res2);
}
