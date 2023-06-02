#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include <vector>

namespace Utils
{
	namespace Printer
	{
		void print(const std::vector<std::vector<float>>& data);
		void print(const std::vector<std::string>& data);
	}
}

#endif // !PRINTER_H
