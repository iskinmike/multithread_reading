
#include <iostream>
#include <string>
#include <fstream>
#include "StatAggregator.h"


int main(int argc, char *argv[])
{
	if (argc != 4) {
		std::cout << "usage: " << argv[0] << " path_to_folder amount_of_files amount_of_threads" << std::endl;
		return 0;
	}

	std::string path_to_folder(argv[1]);
	std::string amount_of_files_str(argv[2]);
	std::string amount_of_threads_str(argv[3]);

#ifdef TEST
	std::uint64_t start_time = time(NULL);
	std::cout << time(NULL) << std::endl;
#endif // TEST

	StatAggregator stat_aggregator(path_to_folder, std::stoi(amount_of_files_str), std::stoi(amount_of_threads_str));
	stat_aggregator.generateStat();
	stat_aggregator.writeTo("agr.txt");

#ifdef TEST
	std::uint64_t end_time = time(NULL);
	std::cout << end_time << "|" << end_time - start_time << std::endl;
#endif // TEST

    return 0;
}

