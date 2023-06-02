#ifndef CSV_H
#define CSV_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>


class CSV
{
public:
	CSV(const std::string& filename, const char separator = ',', bool has_header = true);
	CSV(const char* filename, const char separator = ',', bool has_header = true);
	~CSV() {}

	bool read(std::vector < std::vector < float >> &data, std::vector<std::string>& header);
	bool write(std::vector < std::vector < float >>& data, std::vector<std::string>& header);

	
	unsigned int& get_line_count() { return line_count_; }

private:
	const std::string filename_;
	char separator_;
	bool has_header_ ;
	unsigned int line_count_ = 0;
};

#endif