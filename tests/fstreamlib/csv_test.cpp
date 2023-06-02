#include <csv.h>
#include <path.h>
#include <printer.h>

int main(int, char**)
{
    const std::string filename = "test_csv.csv";
    CSV csv_reader(filename, ',');

    std::vector<std::string> header;
    std::vector<std::vector<float>> data;
    csv_reader.read(data, header);

    data.push_back(std::vector<float>{6, 6, 6, 6, 9});
    data.push_back(std::vector<float>{7});

    const std::string out_filename = "test_csv_2.csv";
    std::cout << "test_csv_2.csv file exists: " << Utils::Path::file_exists(out_filename) << "\n";
    CSV csv_writer(out_filename, ';', true);
    csv_writer.write(data, header);
    std::cout << "test_csv_2.csv file exists: " << Utils::Path::file_exists(out_filename) << "\n";

    return 0;
}

