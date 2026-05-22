#include "Utils.h"


std::string read_file(const char* path)
{
	std::ifstream file(path);
	std::string line, contents;

	if (!file.is_open())
	{
		return "";
	}

	while (std::getline(file, line))
	{

		contents += line + "\n";
	}
	return contents;
}