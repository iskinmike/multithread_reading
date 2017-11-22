#pragma once
#include <map>
#include <unordered_map>
#include <string>
#include <mutex>
#include "StatElement.h"

typedef std::string Date;
typedef std::uint64_t Props;
typedef std::string Fact;

typedef std::unordered_map<Props, std::uint64_t> PropsValue;
typedef std::unordered_map<Fact, PropsValue> FactValue;
typedef std::unordered_map<Date, FactValue> DateValue;

class StatGatherer
{
	std::mutex gatherer_mtx;
	std::mutex invalid_mtx;
	std::uint64_t invalid_count;
	void increaseInvalidCounter();
	std::string gatherPropsFormat(PropsBits bits);
public:
	DateValue gathered_data;
	StatGatherer();
	~StatGatherer();

	void addElement(const StatElement& element);
	void addData(const Date& date,const Fact& fact, const Props& props);

	std::string getStat();
};

