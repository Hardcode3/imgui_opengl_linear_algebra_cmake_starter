#include <csv.h>


CSV::CSV(const std::string& filename, const char separator, bool has_header)
	: filename_(filename), separator_(separator), has_header_(has_header) {}


CSV::CSV(const char* filename, const char separator, bool has_header)
	: filename_(std::string(filename)), separator_(separator), has_header_(has_header) {}

bool CSV::read(std::vector < std::vector < float >>& data, std::vector<std::string>& header)
{
	std::ifstream file(filename_);
	if (!file.is_open())
		return false;

	std::string line;
	// read the header part
	if (has_header_)
	{
		if (std::getline(file, line))
		{
			line_count_++;
			std::istringstream iss(line);
			std::string token;
			while (std::getline(iss, token, separator_))
			{
				header.push_back(token);
			}
		}
	}

	// read the rest of the file
	while (std::getline(file, line))
	{
		line_count_++;
		std::vector<float> row;
		std::istringstream iss(line);
		std::string token;
		while (std::getline(iss, token, separator_))
		{
			float value;
			std::istringstream(token) >> value;
			row.push_back(value);
		}
		data.push_back(row);
	}
	return true;
}

bool CSV::write(std::vector < std::vector < float >>& data, std::vector<std::string>& header)
{
	std::ofstream file(filename_, 'w');
	if (!file.is_open())
		return false;

	if (has_header_)
	{
		for (std::string column_name : header)
		{
			file << column_name << separator_;
		}
		file << std::endl;
	}

	for (std::vector<float> row : data)
	{
		for (size_t i = 0; i < row.size(); i++)
		{
			file << row[i];
			if (i != row.size() - 1)
				file << separator_;
		}
		file << std::endl;
	}
	file.close();
}



