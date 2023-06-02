#include <printer.h>

void Utils::Printer::print(const std::vector<std::vector<float>>& data)
{
	std::string str;
	for (std::vector<float> line : data)
	{
		for (int i = 0; i < line.size(); i++)
		{
			std::cout << line[i] << " ";
		}
		std::cout << "\n";
	}
}

void Utils::Printer::print(const std::vector<std::string>& data)
{
	std::string str;
	for (std::string header : data)
	{
		std::cout << header << " ";
	}
	std::cout << "\n";
}