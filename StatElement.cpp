

#include "StatElement.h"
#include <time.h>
#include <iostream>
#include <algorithm>


// prepare keywords
std::string ts_word("ts_fact");
std::string fact_word("fact_name");
std::string props_word("props");

bool StatElement::parseDocument()
{
	if (!m_doc.HasMember(ts_word.c_str()) || !m_doc.HasMember(fact_word.c_str()) || !m_doc.HasMember(props_word.c_str())){
		return false;
	}

	const rapidjson::Value& ts = m_doc[ts_word.c_str()];
	const rapidjson::Value& fact = m_doc[fact_word.c_str()];
	const rapidjson::Value& props = m_doc[props_word.c_str()];

	if  (!ts.IsInt64() || !fact.IsString() || !props.IsObject()) {
		return false;
	}

	m_data.date.assign(getDateFromTimestamp(ts.GetInt64()));
	m_data.fact_name.assign(fact.GetString());

	std::string props_str("");
	for (rapidjson::Value::ConstMemberIterator itr = props.MemberBegin();
		itr != props.MemberEnd(); ++itr)
	{
		props_str.append(std::string(itr->name.GetString()).erase(0,4));
		props_str.append(",");
	}
	if (!props_str.empty()) {
		props_str.pop_back();
	}
	m_data.props = props_str;

	return true;
}


std::string StatElement::getDateFromTimestamp(const std::uint64_t& time_stamp)
{
	time_t t = time_stamp;
	char date[20];
#ifndef WIN32
	struct tm *tm = gmtime(&t);
	strftime(date, sizeof(date), "%Y-%m-%d", tm);
#else
	struct tm tm;
	gmtime_s(&tm, &t);
	strftime(date, sizeof(date), "%Y-%m-%d", &tm);
#endif // !WIN32
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
