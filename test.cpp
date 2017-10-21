// Goal : clautext -> cpp

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <map>

// no fast lib!
#include <wiz/ClauText.h>

#define INLINE inline

#define NONE 0

wiz::StringBuilder builder(102400);

INLINE std::string __add(const std::string& s1, const std::string& s2)
{
	return std::to_string(std::stoi(s1) + std::stoi(s2)); // change to int, double, ..
}
INLINE bool __COMP_LT_EQ(const std::string& s1, const std::string& s2)
{
	auto x = wiz::load_data::Utility::Compare(s1, s2, &builder);
	return x == "== 0" || x == "< 0";
}
INLINE bool __COMP_GT_EQ(const std::string& s1, const std::string& s2)
{
	auto x = wiz::load_data::Utility::Compare(s1, s2, &builder);
	return x == "== 0" || x == "> 0";
}

INLINE bool __OR(const bool x, const bool y)
{
	return x || y;
}
INLINE bool __AND(const bool x, const bool y)
{
	return x && y;
}
INLINE bool __EQ(const std::string& x, const std::string& y)
{
	return wiz::load_data::Utility::Compare(x, y, &builder) == "== 0";
}
// find "/~"
INLINE std::string _Find(wiz::load_data::UserType& global, const std::string& str) {
	return wiz::load_data::Find(&global, str, &builder);
}
INLINE std::string __concat_all(const std::vector<std::string>& vec) // chk for -> no inline?
{
	std::string result;

	for (int i = 0; i < vec.size(); ++i) {
		result += vec[i];
	}
	return result;
}
// todo - add ExcuteData parameter?
INLINE std::string __make(wiz::load_data::UserType& global, const ExcuteData& data, const std::string& str, const std::string& condition)
{
	std::string dir = str;

	dir = ToBool4(nullptr, global, dir, data, &builder);

	std::string name;
	for (int i = dir.size() - 1; i >= 0; --i)
	{
		if (dir[i] == '/') {
			name = wiz::String::substring(dir, i + 1);
			dir = wiz::String::substring(dir, 0, i - 1);
			break;
		}
	}
	if (dir.empty()) { dir = "."; }

	wiz::load_data::LoadData::AddUserType(global, dir, name, "", condition, data, &builder);

	return "";
}
INLINE std::string __assign(wiz::load_data::UserType& global, const ExcuteData& excuteData, std::map<std::string, std::string>& locals, const std::string& dir, const std::string& value, const std::string& condition)
{
	std::pair<std::string, std::string> _dir = Find2(&global, dir);

	//// todo!! - add locals to parameter.
	if (_dir.first == "" && wiz::String::startsWith(_dir.second, "$local."))
	{
		locals[wiz::String::substring(_dir.second, 7)] = value;
	}
	else
	{
		wiz::load_data::LoadData::SetData(global, _dir.first, _dir.second, value, condition, excuteData, &builder);
	}
	return "";
}
INLINE std::string __insert(wiz::load_data::UserType& global, const ExcuteData& excuteData, const std::string& dir, const std::string& value, const std::string& condition)
{
	wiz::load_data::LoadData::AddData(global, dir, value, condition, excuteData, &builder);

	return "";
}

template <class T>
INLINE std::string ToString(const T& data)
{
	return _toString(data);
}

template <>
INLINE std::string ToString(const std::string& data)
{
	return data;
}


INLINE std::string CONCAT_ALL(const std::vector<std::string>& vec)
{
	std::string result;

	for (int i = 0; i < vec.size(); ++i) {
		result += vec[i];
		if (i < vec.size() - 1) {
			result += " ";
		}
	}

	return result;
}

INLINE bool __NOTEQ(const std::string x, const std::string y)
{
	return !(wiz::load_data::Utility::Compare(x, y, &builder) == "== 0");
}

INLINE bool __AND_ALL(const std::vector<bool>& vec)
{
	bool result = true;

	for(int i=0; i < vec.size(); ++i) {
		result = result && vec[i];
		if( vec[i] == false ) {
			break;
		}
	}

	return result;
}

INLINE bool __COMP_GT_(const std::string& x, const std::string& y)
{
	return wiz::load_data::Utility::Compare(x, y, &builder) == "> 0";
}
INLINE bool __COMP_LT_(const std::string& x, const std::string& y)
{
	return wiz::load_data::Utility::Compare(x, y, &builder) == "< 0";
}

#define __return_value() result 

INLINE std::string __element(wiz::load_data::UserType& global, const std::string& dir, const std::string& idx_str) {
	int idx = atoi(idx_str.c_str());

	if ('/' == dir[0])
	{
		wiz::load_data::UserType* ut = wiz::load_data::UserType::Find(&global, dir, &builder).second[0];
		return ut->GetItemList(idx).Get(0);
	}
	else
	{
		return "NONE";
	}
}

