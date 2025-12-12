#include <iostream>
#include <cctype>
#include <new>

namespace pozdnyakov
{

  char* readString(std::istream& in, unsigned int& outLen)
  {
    unsigned int capacity = 256;
    unsigned int size = 0;

    char* str = new char[capacity];
    str[0] = '\0';

    char ch;
    while (in.get(ch) && ch != '\n')
    {
      if (size + 1 >= capacity)
      {
        unsigned int newCapacity = capacity * 2;
        char* newStr = new char[newCapacity];

        for (unsigned int i = 0; i < size; ++i)
        {
          newStr[i] = str[i];
        }
        newStr[size] = '\0';

        delete[] str;
        str = newStr;
        capacity = newCapacity;
      }

      str[size++] = ch;
      str[size] = '\0';
    }

    outLen = size;
    return str;
  }


  void replaceChars(const char* input, char* output, unsigned int len, char oldChar, char newChar)
  {
    for (unsigned int i = 0; i < len; ++i)
    {
      output[i] = (input[i] == oldChar) ? newChar : input[i];
    }
    output[len] = '\0';
  }


  unsigned int mergeLatinLetters(const char* s1, const char* s2, char* output, 
    unsigned int outputCapacity)
  {
    int present[26];
    for (int i = 0; i < 26; ++i)
    {
      present[i] = 0;
    }

    auto feed = [&present](const char* s)
      {
        for (unsigned int i = 0; s[i] != '\0'; ++i)
        {
          unsigned char uc = static_cast< unsigned char >(s[i]);
          if (std::isalpha(uc))
          {
            char lowered = static_cast< char >(std::tolower(uc));
            if (lowered >= 'a' && lowered <= 'z')
            {
              present[lowered - 'a'] = 1;
            }
          }
        }
      };

    feed(s1);
    feed(s2);

    unsigned int outIdx = 0;
    for (int i = 0; i < 26 && outIdx + 1 < outputCapacity; ++i)
    {
      if (present[i])
      {
        output[outIdx++] = static_cast< char >('a' + i);
      }
    }

    output[outIdx] = '\0';
    return outIdx;
  }

}


int main()
{
  using namespace pozdnyakov;

  const char OLD_CHAR = 'c';
  const char NEW_CHAR = 'b';
  const char* SECOND_STRING = "def_ghk";

  try
  {
    unsigned int inputLen = 0;
    char* inputStr = readString(std::cin, inputLen);

    if (inputLen == 0)
    {
      std::cerr << "Empty input error\n";
      delete[] inputStr;
      return 1;
    }

    char* result1 = new char[inputLen + 1];
    replaceChars(inputStr, result1, inputLen, OLD_CHAR, NEW_CHAR);
    std::cout << result1 << '\n';
    delete[] result1;

    const unsigned int BUFF2 = 27;
    char result2[BUFF2];
    mergeLatinLetters(inputStr, SECOND_STRING, result2, BUFF2);
    std::cout << result2 << '\n';

    delete[] inputStr;
    return 0;
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Memory allocation error\n";
    return 1;
  }
}
