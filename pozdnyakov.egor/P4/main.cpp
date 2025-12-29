#include <iostream>
#include <cctype>
#include <cstring>
#include <stdexcept>

namespace pozdnyakov
{
  void fillCharMap(const char* str, bool* map)
  {
    for (size_t i = 0; str[i] != '\0'; ++i)
    {
      if (std::isalpha(static_cast< unsigned char >(str[i])))
      {
        unsigned char uCh = static_cast< unsigned char >(str[i]);
        char lowerCh = static_cast< char >(std::tolower(uCh));
        map[lowerCh - 'a'] = true;
      }
    }
  }

  char* readString(std::istream& in, size_t& size)
  {
    size_t capacity = 256;
    size = 0;
    char* str = new char[capacity];
    char ch;

    while (in.get(ch))
    {
      if (ch == '\n')
      {
        break;
      }

      if (size + 1 >= capacity)
      {
        size_t newCapacity = capacity * 2;
        char* newStr = nullptr;

        try
        {
          newStr = new char[newCapacity];
        }
        catch (const std::bad_alloc&)
        {
          delete[] str;
          throw;
        }

        for (size_t i = 0; i < size; ++i)
        {
          newStr[i] = str[i];
        }

        delete[] str;
        str = newStr;
        capacity = newCapacity;
      }

      str[size] = ch;
      ++size;
    }

    str[size] = '\0';

    if (!in && !in.eof())
    {
      delete[] str;
      throw std::runtime_error("Input stream error");
    }

    return str;
  }

  void replaceChars(const char* input, char* output, char oldChar, char newChar)
  {
    size_t i = 0;

    while (input[i] != '\0')
    {
      if (input[i] == oldChar)
      {
        output[i] = newChar;
      }
      else
      {
        output[i] = input[i];
      }
      ++i;
    }
    output[i] = '\0';
  }

  void mergeLatinLetters(const char* s1, const char* s2, char* dest)
  {
    bool present[26];

    for (size_t k = 0; k < 26; ++k)
    {
      present[k] = false;
    }

    fillCharMap(s1, present);
    fillCharMap(s2, present);
    size_t idx = 0;

    for (size_t i = 0; i < 26; ++i)
    {
      if (present[i])
      {
        dest[idx] = static_cast< char >('a' + i);
        ++idx;
      }
    }
    dest[idx] = '\0';
  }
}

int main()
{
  using namespace pozdnyakov;

  const char OLD_CHAR = 'c';
  const char NEW_CHAR = 'b';
  const char* SECOND_STRING = "def_ghk";

  char* inputStr = nullptr;
  char* result1 = nullptr;
  char* result2 = nullptr;
  size_t inputSize = 0;

  try
  {
    inputStr = readString(std::cin, inputSize);

    if (inputStr[0] == '\0')
    {
      throw std::runtime_error("Empty input");
    }

    result1 = new char[inputSize + 1];
    result1[inputSize] = '\0';
    replaceChars(inputStr, result1, OLD_CHAR, NEW_CHAR);
    std::cout << result1 << '\n';

    result2 = new char[27];
    result2[26] = '\0';
    mergeLatinLetters(inputStr, SECOND_STRING, result2);
    std::cout << result2 << '\n';

    delete[] result1;
    delete[] result2;
    delete[] inputStr;

    return 0;
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Memory allocation error\n";

    delete[] result1;
    delete[] result2;
    delete[] inputStr;

    return 1;
  }
  catch (const std::runtime_error& e)
  {
    std::cerr << "Error: " << e.what() << '\n';

    delete[] inputStr;
    delete[] result1;
    delete[] result2;

    return 1;
  }
}
