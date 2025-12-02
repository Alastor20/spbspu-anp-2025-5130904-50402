#include <iostream>
#include <iomanip>
namespace chernikov{
  char * getline(std::istream& in, char * data, size_t & size);
  size_t hasSam(const char * str1, const char * str2, const size_t size1, const size_t size2);
  void uniTwo(char * uni_two,const char * str1, const char * str2, size_t size1, size_t size2, size_t & size_ut);
  size_t min(size_t size1, size_t size2, size_t& diff, size_t& flag);
}

int main(){
  char * str1 = nullptr;
  char * str2 = nullptr;
  size_t size1 = 0;
  size_t size2 = 0;
  try {
    str1 = chernikov::getline(std::cin, str1, size1);
    str2 = chernikov::getline(std::cin, str2, size2);
  }
  catch (...) {
    std::cerr << "Memory allocation or string allocation error";
    delete[] str1;
    delete[] str2;
    return 1;
  }
  size_t has_sam = chernikov::hasSam(str1, str2, size1, size2);
  char* uni_two = nullptr;
  size_t size_uni_two = 0;
  try {
    uni_two = new char[size1 + size2 + 1];
  }
  catch (...) {
    std::cerr << "Memory allocation or string allocation error";
    delete[] str1;
    delete[] str2;
    return 1;
  }
  chernikov::uniTwo(uni_two, str1, str2, size1, size2, size_uni_two);
  std::cout << "HAS-SAM: " << has_sam << '\n';
  std::cout << "UNI_TWO: " << '\n';
  for (size_t i = 0; i < size_uni_two; ++i) {
    std::cout << uni_two[i];
  }

  std::cout << std::endl;
  delete[] str1;
  delete[] str2;
  delete[] uni_two;
  return 0;
}

char * chernikov::getline(std::istream& in, char* data, size_t & size) {
  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws) {
    in >> std::noskipws;
  }
  char ch;
  size = 0;
  while (in >> ch && ch != '\n') {
    size++;
    char * new_data = new char[size + 1];
    if (new_data == nullptr) {
      throw std::bad_alloc();
    }
    for (size_t i = 0; i < size; ++i) {
      new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    in >> data[size];
  }
  size++;
  char * new_data = new char[size];
  if (new_data == nullptr) {
    throw std::bad_alloc();
  }
  for (size_t i = 0; i < size - 1; ++i) {
    new_data[i] = data[i];
  }
  new_data[size] = '\0';
  delete[] data;
  data = new_data;
  if (is_skipws) {
    in >> std::skipws;
  }
  return data;
}
size_t chernikov::hasSam(const char * str1, const char * str2, const size_t size1, const size_t size2) {
  for (size_t i = 0; i < size1; ++i) {
    if (str1[i] == '\0') {
      break;
    }
    for (size_t j = 0; j < size2; ++j) {
      if (str2[j] == '\0') {
        break;
      }
      if (str1[i] == str2[j]) {
        return 1;
      }
    }
  }
  return 0;
}
void chernikov::uniTwo(char * uni_two, const char * str1, const char * str2, size_t size1, size_t size2, size_t & size_ut) {
  size_t diff = 0;
  size_t str_flag = 0;
  if (size1 > 0 && str1[size1 - 1] == '\0') {
    size1--;
  }
  if (size1 > 0 && str2[size2 - 1] == '\0') {
    size2--;
  }
  size_t size = min(size1, size2, diff, str_flag);
  size_t uni_index = 0;
  for (size_t i = 0; i < size;) {
    uni_two[uni_index++] = str1[i];
    uni_two[uni_index++] = str2[i];
  }
  if (diff > 0) {
    if (str_flag == 1) {
      for (size_t i = 0; i < diff; ++i) {
        uni_two[uni_index++] = str1[size + i];
      }
    }
    else {
      for (size_t i = 0; i < diff; ++i) {
        uni_two[uni_index++] = str2[size + i];
      }
    }
  }
  uni_two[uni_index] = '\0';
  size_ut = uni_index;
}
size_t chernikov::min(size_t size1, size_t size2, size_t & diff, size_t & flag) {
  if (size1 < size2) {
    flag = 2;
    diff = size2 - size1;
    return size1;
  }
  else if (size2 < size1) {
    flag = 1;
    diff = size1 - size2;
    return size2;
  }
  else {
    diff = 0;
    return size2;
  }
}
