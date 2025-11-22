#include <iostream>

namespace pozdnyakov {

  size_t string_length(const char* str) {
    const char* p = str;
    while (*p != '\0') {
      ++p;
    }
    return p - str;
  }
}
