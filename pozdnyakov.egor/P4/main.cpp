#include <iostream>
#include <cctype>
#include <new>
#include <cstring>

namespace pozdnyakov
{
  char* readString(std::istream& in, size_t& size)
  {
    size_t capacity = 256;
    size = 0;
    char* str = new char[capacity];
    char ch;

    while (in.get(ch) && ch != '\n')
    {
      if (size + 1 >= capacity)
      {
        size_t newCapacity = capacity * 2;
        char* newStr = new char[newCapacity];

        for (size_t i = 0; i < size; ++i)
        {
          newStr[i] = str[i];
        }

        delete[] str;
        str = newStr;
        capacity = newCapacity;
      }

      str[size++] = ch;
    }

    str[size] = '\0';

    if (size == 0)
    {
      delete[] str;
      throw std::runtime_error("Empty input");
    }

    return str;
  }

  void replaceChars(const char* input, char* output, char oldChar, char newChar)
  {
    size_t i = 0;
    while (input[i] != '\0')
    {
      output[i] = (input[i] == oldChar) ? newChar : input[i];
      ++i;
    }
    output[i] = '\0';
  }

  char* mergeLatinLetters(const char* s1, const char* s2)
  {
    bool present[26] = { false };

    auto feed = [&present](const char* s)
      {
        for (size_t i = 0; s[i] != '\0'; ++i)
        {
          char ch = s[i];
          if (std::isalpha(static_cast< unsigned char >(ch)))
          {
            present[std::tolower(static_cast< unsigned char >(ch)) - 'a'] = true;
          }
        }
      };

    feed(s1);
    feed(s2);

    size_t resultSize = 0;
    for (bool p : present)
    {
      if (p) ++resultSize;
    }

    char* result = new char[resultSize + 1];
    size_t idx = 0;
    for (size_t i = 0; i < 26; ++i)
    {
      if (present[i])
      {
        result[idx++] = static_cast< char >('a' + i);
      }
    }
    result[idx] = '\0';

    return result;
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
    result1 = new char[inputSize + 1];

    replaceChars(inputStr, result1, OLD_CHAR, NEW_CHAR);
    std::cout << result1 << '\n';

    result2 = mergeLatinLetters(inputStr, SECOND_STRING);
    std::cout << result2 << '\n';

    delete[] result1;
    delete[] result2;
    delete[] inputStr;

    return 0;
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Memory allocation error\n";

    if (result1) delete[] result1;
    if (result2) delete[] result2;
    if (inputStr) delete[] inputStr;

    return 1;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';

    if (result1) delete[] result1;
    if (result2) delete[] result2;
    if (inputStr) delete[] inputStr;

    return 1;
  }
}
