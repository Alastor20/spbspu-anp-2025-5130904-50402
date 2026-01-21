#include <iostream>
#include <iomanip>
namespace chernikov {
  char* getline(std::istream& in, size_t& size);
  size_t hasSam(const char* str1, const char* str2);
  void uniTwo(char* uni_two, const char* str1, const char* str2, size_t size1, size_t size2);
}
int main()
{
  char* str1 = nullptr;
  char* str2 = nullptr;
  size_t size1 = 0;
  size_t size2 = 0;
  try {
    str1 = chernikov::getline(std::cin, size1);
    if (size1 == 1 && str1[0] == '\0') {
      std::cerr << "Memory allocation or string allocation error";
      delete[] str1;
      return 1;
    }
    str2 = chernikov::getline(std::cin, size2);
  } catch (const std::bad_alloc& e) {
    std::cerr << "Memory allocation or string allocation error" << e.what() << "\n";
    delete[] str1;
    delete[] str2;
    return 1;
  }
  size_t has_sam = chernikov::hasSam(str1, str2);
  char* uni_two = nullptr;
  size_t max_size = size1 + size2;
  try {
    uni_two = new char[size1 + size2 + 1];
    uni_two[0] = '\0';
  } catch (const std::bad_alloc& e) {
    std::cerr << "Memory allocation failed: " << e.what() << "\n";
    delete[] str1;
    delete[] str2;
    return 1;
  }
  chernikov::uniTwo(uni_two, str1, str2, size1, size2);
  std::cout << "HAS-SAM: " << has_sam << '\n';
  std::cout << "UNI_TWO: " << uni_two << '\n';

  std::cout << "\n";
  delete[] str1;
  delete[] str2;
  delete[] uni_two;
  return 0;
}

char* chernikov::getline(std::istream& in, size_t& size) {
  if (in.eof()) {
    size = 0;
    char* data = new char[1];
    data[0] = '\0';
    return data;
  }
  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws) {
    in >> std::noskipws;
  }
  char ch;
  size = 0;
  char* data = nullptr;
  try{
    while (in >> ch && ch != '\n') {
      char* new_data = new char[size + 2];
      for (size_t i = 0; i < size; ++i) {
        new_data[i] = data[i];
      }
      new_data[size] = ch;
      new_data[size + 1] = '\0';
      delete[] data;
      data = new_data;
      size++;
    }
  } catch (const std::bad_alloc& e) {
    delete[] data;
    if (is_skipws) {
      in >> std::skipws;
    }
    throw;
  }
  if (size == 0) {
    delete[] data;
    data = new char[1];
    data[0] = '\0';
    size = 0;
  }
  if (is_skipws) {
    in >> std::skipws;
  }
  return data;
}
size_t chernikov::hasSam(const char* str1, const char* str2) {
  for (size_t i = 0; str1[i] != '\0'; ++i) {
    for (size_t j = 0; str2[j] != '\0'; ++j) {
      if (str1[i] == str2[j]) {
        return 1;
      }
    }
  }
  return 0;
}
void chernikov::uniTwo(char* uni_two, const char* str1, const char* str2, size_t size1, size_t size2) {
  size_t len1 = (size1 > 0) ? size1 - 1 : 0;
  size_t len2 = (size2 > 0) ? size2 - 1 : 0;
  size_t min_len = (len1 < len2) ? len1 : len2;
  size_t diff = 0;
  const char* longer_str = nullptr;
  if (len1 > len2) {
    diff = len1 - len2;
    longer_str = str1;
  } else if (len2 > len1) {
    diff = len2 - len1;
    longer_str = str2;
  }
  size_t uni_index = 0;
  for (size_t i = 0; i < min_len; ++i) {
    uni_two[uni_index++] = str1[i];
    uni_two[uni_index++] = str2[i];
  }
  if (diff > 0 && longer_str != nullptr) {
    for (size_t i = 0; i < diff; ++i) {
      uni_two[uni_index++] = longer_str[min_len + i];
    }
  }
  uni_two[uni_index] = '\0';
}
