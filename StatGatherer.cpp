#include "StatGatherer.h"
#include <iostream>
#include <sstream>

void StatGatherer::increaseInvalidCounter()
{
	invalid_mtx.lock();
	invalid_count++;
	invalid_mtx.unlock();
}

std::string StatGatherer::gatherPropsFormat(PropsBits bits)
{
	std::string result("");
	for (int i = 0; i < 10; ++i) {
		if (bits[i]) {
			result.append(std::to_string(i + 1));
			result.append(",");
		}
	}
	if (!result.empty()) {
		result.pop_back();
	}
	return result;
}

StatGatherer::StatGatherer() : invalid_count(0)
{
}


StatGatherer::~StatGatherer()
{
}

void StatGatherer::addElement(const StatElement & element)
{
	if (element.isValid()) {
		addData(element.m_data.date, element.m_data.fact_name, element.m_data.props);
	}
	else {
		increaseInvalidCounter();
	}
}

void StatGatherer::addData(const Date & date, const Fact & fact, const Props & props)
{
	gatherer_mtx.lock();
	gathered_data[date][fact][props]++;
	gatherer_mtx.unlock();
}

std::string StatGatherer::getStat()
{
	std::stringstream ss;

	ss << "{\n";
	for (auto& date : gathered_data) {
		ss << "\t\"" << date.first << "\" : {\n";
		for (auto& fact : date.second) {
			ss << "\t\t\"" << fact.first << "\" : {\n";
			for (auto& props : fact.second) {
				ss << "\t\t\t\"" << gatherPropsFormat(props.first) << "\" : " << props.second << "\n";
			}
			ss << "\t\t}\n";;
		}
		ss << "\t}\n";;
	}
	ss << "}";
#ifdef VERBOSE
	std::cout <<"Invalid lines: "<< invalid_count << std::endl;
#endif // VERBOSE
	std::string result = ss.str();
	return result;
}
