#include <iostream>
#include <iomanip>
#include <cctype>

namespace dirko
{
  const char *find(const char *start, const char *end, char target)
  {
    for (const char *ch = start; ch < end; ++ch)
    {
      if (*ch == target)
      {
        return ch;
      }
    }
    return end;
  }
  char *getLine(std::istream &in, size_t &size)
  {
    bool isSkipWp = in.flags() & std::ios::skipws;
    if (isSkipWp)
    {
      in >> std::noskipws;
    }
    char *str = nullptr;
    char ch = 0;
    while (in >> ch && ch != '\n')
    {
      char *temp = reinterpret_cast< char * >(malloc(size + 1));
      if (temp == nullptr)
      {
        free(str);
        throw std::bad_alloc();
      }
      for (size_t i = 0; i < size; ++i)
      {
        temp[i] = str[i];
      }
      free(str);
      str = temp;
      str[size] = ch;
      ++size;
    }
    if (in.fail())
    {
      free(str);
      throw std::logic_error("Cant read");
    }
    if (isSkipWp)
    {
      in >> std::skipws;
    }
    char *temp = reinterpret_cast< char * >(malloc(size + 1));
    if (temp == nullptr)
    {
      free(str);
      throw std::bad_alloc();
    }
    for (size_t i = 0; i < size; ++i)
    {
      temp[i] = str[i];
    }
    free(str);
    str = temp;
    str[size] = '\0';
    ++size;
    return str;
  }
  size_t doDifLat(const char *str, size_t size)
  {
    size_t count = 0;
    char seen[26] = {};
    for (size_t i = 0; i < size; ++i)
    {
      if (std::isalpha(str[i]))
      {
        if (dirko::find(seen, seen + count, std::tolower(str[i])) == seen + count)
        {
          seen[count] = std::tolower(str[i]);
          ++count;
        }
      }
    }
    return count;
  }
  char *doUppLow(const char *source, char *distention, size_t size)
  {
    for (size_t i = 0; i < size; ++i)
    {
      distention[i] = std::tolower(source[i]);
    }
    return distention;
  }
}
int main()
{
  char *str = nullptr;
  size_t size = 0;
  try
  {
    str = dirko::getLine(std::cin, size);
  }
  catch (const std::bad_alloc &e)
  {
    std::cerr << "Cant alloc\n";
    return 1;
  }
  catch (const std::logic_error &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  size_t result1 = dirko::doDifLat(str, size);
  char *result2 = reinterpret_cast< char * >(malloc(sizeof(char) * size));
  if (result2 == nullptr)
  {
    free(str);
    std::cerr << "Cant alloc\n";
    return 1;
  }
  dirko::doUppLow(str, result2, size);
  std::cout << result1 << '\n';
  std::cout << result2 << '\n';
  free(str);
  free(result2);
}
