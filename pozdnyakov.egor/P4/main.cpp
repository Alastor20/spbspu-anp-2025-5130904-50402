#include <iostream>
#include <cctype>
#include <new>

namespace pozdnyakov {

  char* read_string(std::istream& in, unsigned int& out_len) {
    unsigned int capacity = 256;
    unsigned int size = 0;

    char* str = new char[capacity];
    str[0] = '\0';

    char ch;
    while (in.get(ch) && ch != '\n') {
      if (size + 1 >= capacity) {
        unsigned int new_capacity = capacity * 2;
        char* new_str = new char[new_capacity];

        for (unsigned int i = 0; i < size; ++i) {
          new_str[i] = str[i];
        }
        new_str[size] = '\0';

        delete[] str;
        str = new_str;
        capacity = new_capacity;
      }

      str[size++] = ch;
      str[size] = '\0';
    }

    out_len = size;
    return str;
  }


  void replace_chars(const char* input, char* output,
    unsigned int len, char old_ch, char new_ch)
  {
    for (unsigned int i = 0; i < len; ++i) {
      output[i] = (input[i] == old_ch) ? new_ch : input[i];
    }
    output[len] = '\0';
  }


  unsigned int merge_latin_letters(const char* s1, const char* s2,
    char* output, unsigned int output_capacity)
  {
    int present[26];
    for (int i = 0; i < 26; ++i) present[i] = 0;

    auto feed = [&present](const char* s) {
      for (unsigned int i = 0; s[i] != '\0'; ++i) {
        unsigned char uc = static_cast<unsigned char>(s[i]);
        if (std::isalpha(uc)) {
          char lowered = static_cast<char>(std::tolower(uc));
          if (lowered >= 'a' && lowered <= 'z') {
            present[lowered - 'a'] = 1;
          }
        }
      }
      };

    feed(s1);
    feed(s2);

    unsigned int out_idx = 0;
    for (int i = 0; i < 26 && out_idx + 1 < output_capacity; ++i) {
      if (present[i]) {
        output[out_idx++] = static_cast<char>('a' + i);
      }
    }

    output[out_idx] = '\0';
    return out_idx;
  }

}

int main() {
  using namespace pozdnyakov;

  const char OLD_CHAR = 'c';
  const char NEW_CHAR = 'b';
  const char* SECOND_STRING = "def_ghk";

  try {
    unsigned int input_len = 0;
    char* input_str = read_string(std::cin, input_len);

    if (input_len == 0) {
      std::cerr << "Empty input error\n";
      delete[] input_str;
      return 1;
    }

    char* result1 = new char[input_len + 1];
    replace_chars(input_str, result1, input_len, OLD_CHAR, NEW_CHAR);
    std::cout << result1 << '\n';
    delete[] result1;

    const unsigned int BUFF2 = 27;
    char result2[BUFF2];
    merge_latin_letters(input_str, SECOND_STRING, result2, BUFF2);
    std::cout << result2 << '\n';

    delete[] input_str;
    return 0;

  }
  catch (const std::bad_alloc&) {
    std::cerr << "Memory allocation error\n";
    return 1;
  }
}
