#include <iostream>
#include <cstdlib>

namespace pozdnyakov {

  size_t string_length(const char* str) {
    const char* p = str;
    while (*p) {
      ++p;
    }
    return p - str;
  }

  void string_copy(const char* source, char* destination, size_t dest_size) {
    if (source == nullptr || destination == nullptr || dest_size == 0) {
      return;
    }

    size_t i = 0;
    while (source[i] && i < dest_size - 1) {
      destination[i] = source[i];
      ++i;
    }
    destination[i] = '\0';
  }

  int is_alpha_char(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
  }
}
