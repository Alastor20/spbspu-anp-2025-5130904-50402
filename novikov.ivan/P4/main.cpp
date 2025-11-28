#include <cstddef>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <istream>

const char literal[] = "aBS_ABC";

size_t countLatin(const char * str, size_t size);
size_t countSameChars(const char * str, size_t size, const char * literal);

void extend(char ** str, size_t size, size_t & capacity)
{
  char * temp = nullptr;
  if (size == capacity) {
    capacity *= 2;
    temp = static_cast< char * >(malloc(capacity));
    if (temp == nullptr) {
      * str = nullptr;
      return;
    }
    for (size_t i = 0; i < size; ++i) {
      temp[i] = (* str)[i];
    }
  }
  free(* str);
  * str = temp;
}

char * getline(std::istream & in, size_t & size)
{
  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws) {
    in >> std::noskipws;
  }

  size_t capacity = 1;
  char * str = static_cast< char * >(malloc(capacity * sizeof(char)));

  if (str == nullptr) {
    return nullptr;
  }
  while (in) {
    extend(& str, size, capacity);
    if (str == nullptr) {
      return nullptr;
    }
    in >> str[size];
    if (in.eof()) {
      break;
    }
    ++size;
  }
  if (in.bad() || size == 0) {
    free(str);
    return nullptr;
  }

  str[size] = '\0';

  if (is_skipws) {
    in >> std::skipws;
  }
  return str;
}

int main()
{
  size_t size = 0;
  char * str = getline(std::cin, size);

  if (str == nullptr) {
    free(str);
    std::cerr << "Reading failed\n";
    return 1;
  }

  size_t result1 = countLatin(str, size);
  size_t result2 = countSameChars(str, size, literal);

  std::cout << result1 << "\n";
  std::cout << result2 << "\n";
  free(str);
}
