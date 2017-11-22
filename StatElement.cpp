#include "stdafx.h"
#include "StatElement.h"
#include <time.h>
#include <iostream>
#include <algorithm>

// prepare keywords
std::string ts_word("ts_fact");
std::string fact_word("fact_name");
std::string props_word("props");
std::vector<std::string> props_words = { "prop1", "prop2", "prop3", "prop4", "prop5",
									     "prop6", "prop7", "prop8", "prop9", "prop10" };

bool StatElement::parseDocument()
{
	if (m_doc.HasMember(ts_word.c_str())) {
		const rapidjson::Value& ts = m_doc[ts_word.c_str()];
		if (ts.IsInt64()) {
			m_data.date.assign(getDateFromTimestamp(ts.GetInt64()));
		} else {
			return false;
		}
	}
	else {
		return false;
	}

	if (m_doc.HasMember(fact_word.c_str())) {
		const rapidjson::Value& fact = m_doc[fact_word.c_str()];
		if (fact.IsString()) {
			m_data.fact_name.assign(fact.GetString());
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}

	if (m_doc.HasMember(props_word.c_str())) {
		const rapidjson::Value& props = m_doc[props_word.c_str()];
		if (props.IsObject()) {
			int counter = 0;
			PropsBits props_bits;
			for (auto& el : props_words) {
				if (props.HasMember(el.c_str())) {
					props_bits.set(counter);
				}
				++counter;
			}
			m_data.props = props_bits.to_ullong();
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	return true;
}


std::string StatElement::getDateFromTimestamp(std::uint64_t time_stamp)
{
	time_t t = time_stamp;
#ifndef WIN32
	struct tm *tm = localtime(&t);
#else
	struct tm tm;
	localtime_s(&tm, &t);
#endif // !WIN32
	char date[20];
	strftime(date, sizeof(date), "%Y-%m-%d", &tm);
	return std::string(date);
}

bool StatElement::isValid() const
{
	return is_valid;
}

StatElement::StatElement(const std::string& json_string) : is_valid(false)
{
	m_doc.Parse(json_string.c_str());
	if (m_doc.IsObject()) {
		is_valid = parseDocument();
	}
}

StatElement::~StatElement()
{
}
