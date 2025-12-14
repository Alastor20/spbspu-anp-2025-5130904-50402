#include <iostream>
namespace lachugin
{
	const size_t startSize = 10;
	bool res1 (const char* frsLine, size_t frsSize, const char* scnLine, size_t scnSize)
	{
		size_t min = (frsSize < scnSize) ? frsSize : scnSize;
		size_t max = (frsSize > scnSize) ? frsSize : scnSize;
		const char* minLine = (min == frsSize) ? frsLine : scnLine;
		const char* maxLine = (max == frsSize) ? frsLine : scnLine;
		for (size_t i = 0; i < min; i++)
		{
			for (size_t j = 0; j < max; j++)
			{
				if (minLine[i] == maxLine[j])
				{
					if (i == ' ')
					{
						continue;
					}
					return true;
				}
			}
		}
		return false;
	}
	void fopy (const char* oldLine, size_t s, char* newLine)
	{
		for (size_t i = 0; i < s; i++)
		{
			newLine[i] = oldLine[i];
		}
	}

	char* cut (const char* str, size_t& s)
	{
		char* newLine = reinterpret_cast< char* >(malloc(s* sizeof(char)));
		if (!newLine)
		{
			return nullptr;
		}
		for (size_t i = 0; i < s; i++)
		{
			newLine[i] = str[i];
		}
		return newLine;
	}

  char* latRmv (const char* str, size_t& s)
	{
		char* newLine = reinterpret_cast< char* >(malloc(s* sizeof(char)));
		if (!newLine)
		{
			return nullptr;
		}
		size_t k = 0;
		for (size_t i = 0; i < s; i++)
		{
			if (!std::isalpha(str[i]))
			{
				newLine[k] = str[i];
				k++;
			}
		}
		char* temp = cut(newLine, k);
		free(newLine);
		if (!temp)
		{
			free(temp);
			return nullptr;
		}
		newLine = temp;
		return newLine;
	}

	char* expand (char* oldLine, size_t& oldSize)
	{
		size_t newSize = oldSize + startSize;
		char* newLine = reinterpret_cast< char* >(malloc(newSize* sizeof(char)));
		if (!newLine)
		{
			return nullptr;
		}
		fopy (oldLine, newSize, newLine);
		oldSize = newSize;
		return newLine;
	}
	char* getline (std::istream& in, size_t& s)
	{
		char* helpLine = nullptr;
		char* data = reinterpret_cast< char* >(malloc(startSize * sizeof(char)));
		if (!data)
		{
			return nullptr;
		}
		bool is_skip = in.flags()& std::ios_base::skipws;
		if(is_skip)
		{
			in >> std::noskipws;
		}
		size_t i = 0;
		bool input = true;
		while (input)
		{
			if (i>=s)
			{
				helpLine = expand (data, s);
				if (!helpLine)
				{
					free(data);
					return nullptr;
				}
				free(data);
				data = helpLine;
			}
			in >> data[i];
			if (data[i] == '\n')
			{
				data[i] = 0;
				input = false;
			}
			++i;
		}
		helpLine = cut(data, s);
		if (!helpLine)
		{
			free(data);
			return nullptr;
		}
		free(data);
		data = helpLine;
		if (!is_skip)
		{
			in >> std::skipws;
		}
		return data;
	}
}

int main()
{
	size_t s = lachugin::startSize;
	char* str = nullptr;
	str = lachugin::getline(std::cin, s);
	if (!str)
	{
		std::cerr << "Not enough memory for string input.\n";\
		free(str);
		return 10;
	}
	if (std::strlen(str) == 0)
	{
		free(str);
		std::cerr << "Error: no input.\n";
		return 2;
	}
	char* res2 = nullptr;
	const char* string = "acb";
	const size_t len = 3;
	res2 = lachugin::latRmv(str, s);
	if (!res2)
	{
		std::cerr << "Not enough memory for string input.\n";
		free(str);
		return 3;
	}
	bool res1 = lachugin::res1(str, s, string, len);
  std::cout << res1 << '\n';
	std::cout << res2 << '\n';
	free(str);
}
