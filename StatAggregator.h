#pragma once

#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <iostream>
#include "StatGatherer.h"


typedef unsigned int uint;

class StatAggregator
{
	StatAggregator();

	StatGatherer stat_gatherer;

	std::string m_path_to_log_folder;
	uint m_log_files_count;
	uint m_thread_counts;

	void statAggregationThread();
	uint m_last_opened_file;
	std::mutex file_counter_mutex;

	std::vector<std::thread> threads;
	std::string generateFileName();

public:
	StatAggregator(std::string path_to_log_folder, uint log_files_count, uint thread_counts);
	~StatAggregator();

	void generateStat();
	void writeTo(std::string output_file_path);
	std::string getFormattedStat();
};

