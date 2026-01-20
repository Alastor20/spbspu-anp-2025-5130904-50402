#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>

namespace pozdnyakov
{
  const size_t MAX_ELEMENTS = 10000;
  const size_t MAX_ROWS = 100;
  const size_t MAX_COLS = 100;

  std::istream& readDimensions(std::istream& in, size_t& rows, size_t& cols)
  {
    if (!(in >> rows))
    {
      return in;
    }
    if (!(in >> cols))
    {
      return in;
    }
    return in;
  }

  std::istream& readMatrix(std::istream& in, int* data, size_t rows, size_t cols)
  {
    size_t total = rows * cols;
    for (size_t i = 0; i < total; i++)
    {
      if (!(in >> data[i]))
      {
        return in;
      }
    }
    return in;
  }

  size_t countDiagonalsWithoutZero(const int* data, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0)
    {
      return 0;
    }

    size_t count = 0;

    for (size_t startRow = 0; startRow < rows; ++startRow)
    {
      bool hasZero = false;
      for (size_t r = startRow, c = 0; r < rows && c < cols; ++r, ++c)
      {
        if (data[r * cols + c] == 0)
        {
          hasZero = true;
          break;
        }
      }
      if (!hasZero)
      {
        count++;
      }
    }

    for (size_t startCol = 1; startCol < cols; ++startCol)
    {
      bool hasZero = false;
      for (size_t r = 0, c = startCol; r < rows && c < cols; ++r, ++c)
      {
        if (data[r * cols + c] == 0)
        {
          hasZero = true;
          break;
        }
      }
      if (!hasZero)
      {
        count++;
      }
    }

    return count;
  }

  void transformMatrixLayers(int* data, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0)
    {
      return;
    }

    size_t minDim = (rows < cols) ? rows : cols;
    size_t layers = (minDim + 1) / 2;

    for (size_t layer = 0; layer < layers; layer++)
    {
      int inc = 1;

      size_t lastRow = rows - 1 - layer;
      size_t lastCol = cols - 1 - layer;

      for (size_t r = layer; r <= lastRow; r++)
      {
        for (size_t c = layer; c <= lastCol; c++)
        {
          data[r * cols + c] += inc;
        }
      }
    }
  }

  std::ostream& writeMatrix(std::ostream& out, const int* data, size_t rows, size_t cols)
  {
    out << rows << ' ' << cols;
    size_t total = rows * cols;
    for (size_t i = 0; i < total; i++)
    {
      out << ' ' << data[i];
    }
    out << '\n';
    return out;
  }

  bool validateArgs(const char* s)
  {
    char* endptr = nullptr;
    long num = std::strtol(s, std::addressof(endptr), 10);
    if (endptr == s || *endptr != '\0')
    {
      return false;
    }
    if (num != 1 && num != 2)
    {
      return false;
    }
    return true;
  }
}

int main(int argc, char* argv[])
{
  using namespace pozdnyakov;

  if (argc != 4)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }

  if (!validateArgs(argv[1]))
  {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }

  long mode = std::strtol(argv[1], nullptr, 10);
  const char* inputFile = argv[2];
  const char* outputFile = argv[3];

  std::ifstream in(inputFile);
  if (!in.is_open())
  {
    std::cerr << "Cannot open input file\n";
    return 2;
  }

  size_t rows = 0;
  size_t cols = 0;

  if (!readDimensions(in, rows, cols))
  {
    std::cerr << "Invalid matrix dimensions\n";
    return 2;
  }

  if (rows == 0 && cols == 0)
  {
    std::ofstream out(outputFile);
    if (!out.is_open())
    {
      std::cerr << "Cannot open output file\n";
      return 3;
    }
    out << 0 << '\n' << 0 << ' ' << 0 << '\n';
    return 0;
  }

  if (mode == 1)
  {
    if (rows * cols > MAX_ELEMENTS || rows > MAX_ROWS || cols > MAX_COLS)
    {
      std::cerr << "Matrix size exceeds limits\n";
      return 2;
    }
  }

  int fixedData[MAX_ROWS * MAX_COLS] = {0};
  int* dataPtr = nullptr;

  if (mode == 1)
  {
    dataPtr = fixedData;
  }
  else
  {
    dataPtr = reinterpret_cast< int* >(std::malloc(rows * cols * sizeof(int)));
    if (dataPtr == nullptr)
    {
      std::cerr << "Memory allocation failed\n";
      return 2;
    }
  }

  if (!readMatrix(in, dataPtr, rows, cols))
  {
    std::cerr << "Invalid matrix data\n";
    if (mode == 2)
    {
      std::free(dataPtr);
    }
    return 2;
  }

  size_t diagCount = countDiagonalsWithoutZero(dataPtr, rows, cols);
  transformMatrixLayers(dataPtr, rows, cols);

  std::ofstream out(outputFile);
  if (!out.is_open())
  {
    std::cerr << "Cannot open output file\n";
    if (mode == 2)
    {
      std::free(dataPtr);
    }
    return 3;
  }

  out << diagCount << '\n';
  writeMatrix(out, dataPtr, rows, cols);

  if (mode == 2)
  {
    std::free(dataPtr);
  }

  return 0;
}
