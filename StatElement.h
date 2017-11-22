#pragma once
#include <rapidjson\document.h>
#include <rapidjson\rapidjson.h>
#include <string>
#include <vector> 
#include <bitset>

typedef std::bitset<10> PropsBits;

struct StatData {
	std::string date;
	std::string fact_name;
	std::uint64_t props;
};

class StatElement
{
	rapidjson::Document m_doc;
	bool is_valid;
	bool parseDocument();
	std::string getDateFromTimestamp(std::uint64_t time_stamp);
public:
	StatData m_data;
	bool isValid() const;
	StatElement(const std::string& json_string);
	~StatElement();
};
