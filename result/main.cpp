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

INLINE std::string __expr___add(const std::string& s1, const std::string& s2)
{
	return std::to_string(std::stoi(s1) + std::stoi(s2)); // change to int, double, ..
}

INLINE std::string __expr___divide(const std::string& s1, const std::string& s2)
{
	return wiz::_toString(std::stoi(s1) / std::stoi(s2));
}

INLINE std::string __expr___modular(const std::string& s1, const std::string& s2)
{
	return wiz::_toString(std::stoi(s1) % std::stoi(s2));
}


INLINE bool __expr___COMP_LT_EQ(const std::string& s1, const std::string& s2)
{
	auto x = wiz::load_data::Utility::Compare(s1, s2, &builder);
	return x == "== 0" || x == "< 0";
}
INLINE bool __expr___COMP_GT_EQ(const std::string& s1, const std::string& s2)
{
	auto x = wiz::load_data::Utility::Compare(s1, s2, &builder);
	return x == "== 0" || x == "> 0";
}

INLINE bool __expr___OR(const bool x, const bool y)
{
	return x || y;
}
INLINE bool __expr___AND(const bool x, const bool y)
{
	return x && y;
}
INLINE bool __expr___EQ(const std::string& x, const std::string& y)
{
	return wiz::load_data::Utility::Compare(x, y, &builder) == "== 0";
}
// find "/~"
INLINE std::string _Find(wiz::load_data::UserType& global, const std::string& str) {
	std::string x = wiz::load_data::Find(&global, str, &builder);
	if (x.empty()) { return str; }
	return x;
}
INLINE std::string __expr___concat_all(const std::vector<std::string>& vec) // chk for -> no inline?
{
	std::string result;

	for (int i = 0; i < vec.size(); ++i) {
		result += vec[i];
	}
	return result;
}
INLINE std::string __expr___concat(const std::string& str1, const std::string& str2)
{
	return str1 + str2;
}

// todo - add ExcuteData parameter?
INLINE std::string __func___make(wiz::load_data::UserType& global, const ExcuteData& data, const std::string& str, const std::string& condition)
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
INLINE std::string __func___assign(wiz::load_data::UserType& global, const ExcuteData& excuteData, std::map<std::string, std::string>& locals, const std::string& dir, const std::string& value, const std::string& condition)
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

INLINE std::string __func___assign2(wiz::load_data::UserType& global, const ExcuteData& excuteData, std::map<std::string, std::string>& locals,
	const std::string& _dir, const std::string& value, const std::string& condition)
{
	std::pair<std::string, std::string> dir = Find2(&global, _dir);

	{
		if (dir.first == "" && wiz::String::startsWith(dir.second, "$local."))
		{
			locals[wiz::String::substring(dir.second, 7)] = value;
		}
		else {
			wiz::load_data::LoadData::SetData(global, dir.first, dir.second, value, "TRUE", excuteData, &builder);
		}
	}

	return "";
}


INLINE std::string __func___insert(wiz::load_data::UserType& global, const ExcuteData& excuteData, const std::string& dir, const std::string& value, const std::string& condition)
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

INLINE bool __expr___NOTEQ(const std::string x, const std::string y)
{
	return !(wiz::load_data::Utility::Compare(x, y, &builder) == "== 0");
}

INLINE bool __expr___AND_ALL(const std::vector<bool>& vec)
{
	bool result = true;

	for (int i = 0; i < vec.size(); ++i) {
		result = result && vec[i];
		if (vec[i] == false) {
			break;
		}
	}

	return result;
}

INLINE bool __expr___COMP_GT_(const std::string& x, const std::string& y)
{
	return wiz::load_data::Utility::Compare(x, y, &builder) == "> 0";
}
INLINE bool __expr___COMP_LT_(const std::string& x, const std::string& y)
{
	return wiz::load_data::Utility::Compare(x, y, &builder) == "< 0";
}

#define __expr___return_value() result 

INLINE std::string __expr___element(wiz::load_data::UserType& global, const std::string& dir, const std::string& idx_str) {
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

INLINE std::string __func___setElement(wiz::load_data::UserType& global, const ExcuteData& excuteData, const std::string& dir, const std::string& idx, const std::string& value)
{
	int _idx = stoi(idx);
	wiz::load_data::UserType::Find(&global, dir, &builder).second[0]->SetItem(_idx, value);

	return "";
}

INLINE std::string __expr___size(wiz::load_data::UserType* global, std::string& dir)
{
	auto x = wiz::load_data::UserType::Find(global, dir, &builder);

	if (x.first) {
		return wiz::_toString(x.second[0]->GetItemListSize());
	}
	else {
		throw "error in __expr___size function.";
	}
}

//// todo - now.~ !
INLINE std::string __expr___get(wiz::load_data::UserType* global, std::string data, std::map<std::string, std::string>& locals, std::map<std::string, std::string>& parameters)
{
	std::string result;

	// /./dir
	try {
		if (data.size() > 1 && data[0] == '/') {
			std::string x = wiz::load_data::Find(global, data, &builder);
			if (!x.empty()) {
				return x;
			}
		}
	}
	catch (...) {

	}
	// $local.
	try {
		std::string x = wiz::load_data::FindLocals(locals, data);
		if (!x.empty()) {
			return x;
		}
	}
	catch (...) {

	}
	// $parameter.
	try {
		std::string x = wiz::load_data::FindParameters(parameters, data);
		if (!x.empty()) {
			return x;
		}
	}
	catch (...) {

	}

	return data;
}

INLINE bool __expr___NOT(const bool x) {
	return !x;
}

INLINE std::string __expr___rand(const std::string& first, const std::string& last) {
	int x = stoi(first);
	int y = stoi(last);
	int istart = std::min<int>(x, y), ilast = std::max<int>(x, y);

	return wiz::_toString(rand() % (ilast - istart + 1) + istart);
}

INLINE std::string __expr___pop_back(wiz::load_data::UserType* global, const std::string& dir)
{
	std::string result;

	wiz::load_data::UserType* ut = nullptr;
	auto finded = wiz::load_data::UserType::Find(global, dir, &builder);
	ut = finded.second[0];

	if (ut->IsItemList(ut->GetIListSize() - 1))
	{
		auto x = ut->GetItemList(ut->GetItemListSize() - 1);
		result = (x.Get(0));
		ut->RemoveItemList(ut->GetItemListSize() - 1);
	}
	else {
		auto x = ut->GetUserTypeList(ut->GetUserTypeListSize() - 1);
		result = (x->ToString()); // chk!!
		ut->RemoveUserTypeList(ut->GetUserTypeListSize() - 1);
	}

	return result;
}


INLINE std::string __func___swap(wiz::load_data::UserType* global, const ExcuteData& excuteData,
	const std::string& dir, const std::string& value1, const std::string& value2)
{
	if (value1 != value2) {
		int x = atoi(value1.c_str());
		int y = atoi(value2.c_str());

		std::string temp = wiz::load_data::UserType::Find(global, dir, &builder).second[0]->GetItemList(x).Get(0);
		std::string temp2 = wiz::load_data::UserType::Find(global, dir, &builder).second[0]->GetItemList(y).Get(0);

		wiz::load_data::LoadData::SetData(*global, dir, x, temp2, "TRUE", excuteData, &builder);
		wiz::load_data::LoadData::SetData(*global, dir, y, temp, "TRUE", excuteData, &builder);
	}
	return "";
}


INLINE std::string __func___findIndex(wiz::load_data::UserType* global, const ExcuteData& excuteData, const std::string& dir, const std::string& value)
{
	wiz::load_data::UserType ut;
	wiz::load_data::LoadData::LoadDataFromString(wiz::load_data::UserType::Find(global, dir, &builder).second[0]->ToString(), ut);

	for (int i = 0; i < ut.GetItemListSize(); ++i) {
		if (ut.GetItemList(i).Get(0) == value) {
			return wiz::toStr(i);
		}
	}

	return "";
}



INLINE std::string __func___remove3(wiz::load_data::UserType* global, const ExcuteData& excuteData, const std::string& dir, const std::string& value, const std::string& condition)
{
	int idx = atoi(value.c_str());  // long long -> int?

	wiz::load_data::LoadData::Remove(*global, dir, idx, condition, excuteData, &builder);

	return "";
}

INLINE std::pair<bool, std::string> __event__0(wiz::load_data::UserType* global, ExcuteData& excuteData);
INLINE std::pair<bool, std::string> __event__1(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> _module4_Test_4_Main(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> _module4_Test_4_0(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> _module4_Test_4_1(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);

int main(void)
{
	ExcuteData excuteData;
	wiz::load_data::UserType global;
	srand(time(NULL));
	std::string fileName = "test_call_by_data.txt_test.txt";
	wiz::load_data::LoadData::LoadDataFromFile("test_call_by_data.txt_test.txt", global);
	std::cout << __event__0(&global, excuteData).second << std::endl;
	return 0;
}

INLINE std::pair<bool, std::string> __event__0(wiz::load_data::UserType* global, ExcuteData& excuteData)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	std::cout << "Hello World A";

	std::cout << "\n";

	{
		std::map<std::string, std::string> param;

		auto x = _module4_Test_4_Main(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}
	std::cout << CONCAT_ALL(std::vector<std::string>{ 	(([&]() -> std::string { 	std::map<std::string, std::string> param;
	param["x"] = CONCAT_ALL(std::vector<std::string>{ "3"});

	auto x = __event__1(global, excuteData, param);
	if (x.first) { return x.second; }
	else { return ""; }}) ())});

	std::cout << CONCAT_ALL(std::vector<std::string>{ __expr___return_value()});


	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__1(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	result_change = true;
	return { result_change, CONCAT_ALL(std::vector<std::string>{ "Hello_World!"}) };

	return { result_change, result };
}
INLINE std::pair<bool, std::string> _module4_Test_4_Main(wiz::load_data::UserType* _global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	wiz::load_data::UserType* global = _global->GetUserTypeItem("Test")[0];
	std::string option;


	{
		std::map<std::string, std::string> param;

		auto x = _module4_Test_4_0(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> _module4_Test_4_0(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	{
		std::map<std::string, std::string> param;

		auto x = _module4_Test_4_1(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}
	result_change = true;
	return { result_change, CONCAT_ALL(std::vector<std::string>{ "end"}) };

	return { result_change, result };
}
INLINE std::pair<bool, std::string> _module4_Test_4_1(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	std::cout << "Hello World B";

	std::cout << "\n";

	__func___assign(*global, excuteData, locals, "/./x", CONCAT_ALL(std::vector<std::string>{ "356"}), "TRUE");
	std::cout << CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/./x")});

	std::cout << "\n";


	return { result_change, result };
}
