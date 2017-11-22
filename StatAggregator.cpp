#include "stdafx.h"
#include "StatAggregator.h"

#include <fstream>
#include "StatElement.h"


StatAggregator::StatAggregator()
{
}


void StatAggregator::statAggregationThread()
{
	while (true) {
		file_counter_mutex.lock();
		std::string file_name("");
		bool exit_flag = (m_last_opened_file >= m_log_files_count);
		if (!exit_flag) {
			++m_last_opened_file;
			file_name = generateFileName();
		}
		file_counter_mutex.unlock();

		if (exit_flag) {
			break;
		}

		std::ifstream log_file;
		log_file.open(file_name);

		if (!log_file.is_open()) {
#ifdef VERBOSE
			std::cout << "Can't open" << file_name << std::endl;			
#endif // VERBOSE
			continue;
		} 
#ifdef VERBOSE
		else {
			std::cout << "Success to open" << file_name << std::endl;
		}
#endif // VERBOSE

		while (!log_file.eof()) {
			std::string line;
			std::getline(log_file, line);

			StatElement elem(line);

			stat_gatherer.addElement(elem);
		}
	}
}

std::string StatAggregator::generateFileName()
{
	std::string name("");
	name.append(m_path_to_log_folder);
	name.append("file");
	name.append(std::to_string(m_last_opened_file));
	name.append(".log");

	std::size_t found = name.find("//");
	if (found != std::string::npos) {
		name.replace(found,2, "/");
	}
	return name;
}

StatAggregator::StatAggregator(std::string path_to_log_folder, uint log_files_count, uint thread_counts)
: m_path_to_log_folder(path_to_log_folder), 
  m_log_files_count(log_files_count),
  m_thread_counts(thread_counts),
  m_last_opened_file(0) {}

StatAggregator::~StatAggregator()
{
}

void StatAggregator::generateStat()
{
	uint amount_threads_to_start = m_thread_counts;
	if (m_log_files_count < m_thread_counts) {
		amount_threads_to_start = m_log_files_count;
	}

	for (uint i = 1; i <= amount_threads_to_start; ++i) {
		threads.emplace_back(std::thread([this] {return this->statAggregationThread(); }));
	}

	for (auto tr = threads.begin(); tr != threads.end(); ++tr) {
		if (tr->joinable()) {
			tr->join();
		}
	}
}

void StatAggregator::writeTo(std::string output_file_path)
{
}

std::string StatAggregator::getFormattedStat()
{
	return stat_gatherer.getStat();
}
