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
INLINE std::pair<bool, std::string> __event__200(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__201(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__101(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__3(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__103(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__104(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__100(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__4(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__5(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__6(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__7(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__11(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__12(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__13(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__20(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__21(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__22(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__1000(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__1001(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__1005(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__1006(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__1007(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__1008(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__1015(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__1016(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__1017(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__1010(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__1011(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__1100(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__1200(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__3003(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__3002(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__3001(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__3000(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__8(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__9(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__52(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__51(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__50(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__4001(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__4000(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__4015(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__4014(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__4013(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__4012(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__4011(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);
INLINE std::pair<bool, std::string> __event__4010(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters);

int main(void)
{
	ExcuteData excuteData;
	wiz::load_data::UserType global;
	srand(time(NULL));
	std::string data =
		"Info =  { NUM_NUM = 13 SHA_NUM = 4 CARDNUM = 52 TOTAL_CARD_NUM = 54 PLAYER_NUM = 4 FIRST_CARD_NUM = 5 GAME_OVER_CARD_NUM = 15 ONE_CARD_FAIL_CARD_NUM = 5  } Mode =  { JUMP_MODE = 6 BACK_MODE = 7 MORE_ONE_MODE = 8 CHANGE_SHA_MODE = 3 GAME_END_MODE = 4 GAME_OVER_MODE = 5 ATTACK_MODE = 1 GENERAL_MODE = 0  } Turn =  { dir = true start = 1 end = 4 n = 4 now = 4  } CardStringImage =  { num =  { K A 2 3 4 5 6 7 8 9 10 J Q  } sha =  { sha_image =  { spade dia heart clover  } sha_name =  { spade dia heart clover  }  } blackJoker =  { ��  } colorJoker =  { ��  }  } PutCard =  { cardId = NONE  } FunctionNo =  {   } Functions =  {   } AttackPoint =  { total_point = 0 now_point = 0  } ChangeSha =  { sha = NONE  } State =  {   } Person =  {   } Computer =  {   } PlayerNameList =  {   } PlayerGameOverList =  {   } Temp =  { count = 0  }";
	wiz::load_data::LoadData::LoadDataFromString(data, global);
	std::cout << __event__0(&global, excuteData).second << std::endl;
	return 0;
}

INLINE std::pair<bool, std::string> __event__1(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	if (__expr___EQ(_Find(*global, "/Turn/dir"), "true")) {
		__func___assign(*global, excuteData, locals, "/Turn/now", CONCAT_ALL(std::vector<std::string>{ __expr___add(__expr___modular(_Find(*global, "/Turn/now"), _Find(*global, "/Turn/n")), "1")}), "TRUE");

	}
	else {
		__func___assign(*global, excuteData, locals, "/Turn/now", CONCAT_ALL(std::vector<std::string>{ __expr___add(__expr___modular(__expr___add(_Find(*global, "/Turn/now"), __expr___add(_Find(*global, "/Turn/n"), "-2")), _Find(*global, "/Turn/n")), "1")}), "TRUE");

	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__200(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	if (__expr___EQ(_Find(*global, "/Turn/dir"), "true")) {
		__func___assign(*global, excuteData, locals, "/Turn/dir", CONCAT_ALL(std::vector<std::string>{ "false"}), "TRUE");

	}
	else {
		__func___assign(*global, excuteData, locals, "/Turn/dir", CONCAT_ALL(std::vector<std::string>{ "true"}), "TRUE");

	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__201(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	__func___assign(*global, excuteData, locals, "/Turn/dir", CONCAT_ALL(std::vector<std::string>{ "true"}), "TRUE");
	__func___assign(*global, excuteData, locals, "/Turn/start", CONCAT_ALL(std::vector<std::string>{ "1"}), "TRUE");
	__func___assign(*global, excuteData, locals, "/Turn/end", CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Info/PLAYER_NUM")}), "TRUE");
	__func___assign(*global, excuteData, locals, "/Turn/n", CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Info/PLAYER_NUM")}), "TRUE");
	__func___assign(*global, excuteData, locals, "/Turn/now", CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Info/PLAYER_NUM")}), "TRUE");

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__101(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	if (__expr___COMP_LT_(parameters["i"], _Find(*global, "/Info/CARDNUM"))) {
		if (__expr___EQ(parameters["i"], "0")) {
			__func___make(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Card")}), "TRUE");

		}
		__func___make(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ __expr___concat_all(std::vector<std::string>{ _Find(*global, "/Card/"), parameters["i"]})}), "TRUE");
		__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ __expr___concat_all(std::vector<std::string>{ _Find(*global, "/Card/"), parameters["i"]})}), CONCAT_ALL(std::vector<std::string>{ "sha = ", __expr___divide(parameters["i"], "13"), "num = ", __expr___modular(parameters["i"], "13"), "isBlackJoker = no", "isColorJoker = no"}), "TRUE");
		{
			std::map<std::string, std::string> param;
			param["i"] = __expr___add(parameters["i"], "1");

			auto x = __event__101(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}

	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__3(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	{
		std::map<std::string, std::string> param;
		param["i"] = CONCAT_ALL(std::vector<std::string>{ "0"});

		auto x = __event__101(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}
	__func___make(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Card"), __expr___concat("/", _Find(*global, "/Info/CARDNUM"))}), "TRUE");
	__func___make(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Card"), __expr___concat("/", __expr___add(_Find(*global, "/Info/CARDNUM"), "1"))}), "TRUE");
	__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ __expr___concat(_Find(*global, "/Card"), __expr___concat("/", _Find(*global, "/Info/CARDNUM")))}), CONCAT_ALL(std::vector<std::string>{ "sha = -1", "num = -1", "isBlackJoker = yes", "isColorJoker = no"}), "TRUE");
	__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ __expr___concat(_Find(*global, "/Card"), __expr___concat("/", __expr___add(_Find(*global, "/Info/CARDNUM"), "1")))}), CONCAT_ALL(std::vector<std::string>{ "sha = -2", "num = -2", "isBlackJoker = no", "isColorJoker = yes"}), "TRUE");

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__103(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	result_change = true;
	return { result_change, CONCAT_ALL(std::vector<std::string>{ __expr___divide(parameters["card"] , "13")}) };

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__104(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	result_change = true;
	return { result_change, CONCAT_ALL(std::vector<std::string>{ __expr___modular(parameters["card"] , "13")}) };

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__100(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	if (__expr___EQ("yes", parameters["isBlackJoker"])) {
		{
			auto x = wiz::load_data::UserType::Find(global, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/CardStringImage/blackJoker")}), &builder);
			if (x.first) {
				wiz::load_data::UserType* ut = x.second[0];
				std::cout << ut->ToString();
			}
			else {
				std::cout << CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/CardStringImage/blackJoker")});
			}
		}


	}
	if (__expr___EQ("yes", parameters["isColorJoker"])) {
		{
			auto x = wiz::load_data::UserType::Find(global, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/CardStringImage/colorJoker")}), &builder);
			if (x.first) {
				wiz::load_data::UserType* ut = x.second[0];
				std::cout << ut->ToString();
			}
			else {
				std::cout << CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/CardStringImage/colorJoker")});
			}
		}


	}
	if (__expr___COMP_LT_("-1", parameters["num"])) {
		{
			int _start = (stoi(CONCAT_ALL(std::vector<std::string>{ parameters["sha"]})));
			int _last = (stoi(CONCAT_ALL(std::vector<std::string>{ parameters["sha"]})));
			wiz::load_data::UserType* ut = wiz::load_data::UserType::Find(global, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/CardStringImage/sha/sha_image")}), &builder).second[0];
			for (int i = _start; i <= _last; ++i)
			{
				if (i != _start) { std::cout << " "; }
				std::cout << ut->GetItemList(i).Get(0);
			}
		}

		{
			int _start = (stoi(CONCAT_ALL(std::vector<std::string>{ parameters["num"]})));
			int _last = (stoi(CONCAT_ALL(std::vector<std::string>{ parameters["num"]})));
			wiz::load_data::UserType* ut = wiz::load_data::UserType::Find(global, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/CardStringImage/num")}), &builder).second[0];
			for (int i = _start; i <= _last; ++i)
			{
				if (i != _start) { std::cout << " "; }
				std::cout << ut->GetItemList(i).Get(0);
			}
		}


	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__4(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	if (__expr___COMP_LT_(parameters["i"], __expr___add("2", _Find(*global, "/Info/CARDNUM")))) {
		if (__expr___EQ(parameters["i"], "0")) {
			__func___make(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/CardList")}), "TRUE");

		}
		__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/CardList")}), CONCAT_ALL(std::vector<std::string>{ parameters["i"]}), "TRUE");
		{
			auto x = wiz::load_data::UserType::Find(global, CONCAT_ALL(std::vector<std::string>{ parameters["i"]}), &builder);
			if (x.first) {
				wiz::load_data::UserType* ut = x.second[0];
				std::cout << ut->ToString();
			}
			else {
				std::cout << CONCAT_ALL(std::vector<std::string>{ parameters["i"]});
			}
		}

		{
			auto x = wiz::load_data::UserType::Find(global, CONCAT_ALL(std::vector<std::string>{ "\n"}), &builder);
			if (x.first) {
				wiz::load_data::UserType* ut = x.second[0];
				std::cout << ut->ToString();
			}
			else {
				std::cout << CONCAT_ALL(std::vector<std::string>{ "\n"});
			}
		}

		{
			std::map<std::string, std::string> param;
			param["i"] = __expr___add(parameters["i"], "1");

			auto x = __event__4(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
			return { result_change, result };
		}

	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__5(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	{
		std::map<std::string, std::string> param;
		param["i"] = CONCAT_ALL(std::vector<std::string>{ "0"});

		auto x = __event__4(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__6(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	if (__expr___COMP_GT_(parameters["n"], "0")) {
		__func___swap(global, excuteData, "/CardList", CONCAT_ALL(std::vector<std::string>{ __expr___rand("0", __expr___add(parameters["n"], "-1"))}), CONCAT_ALL(std::vector<std::string>{ __expr___add(parameters["n"], "-1")}));

		{
			std::map<std::string, std::string> param;
			param["n"] = __expr___add(parameters["n"], "-1");

			auto x = __event__6(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}

	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__7(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	{
		std::map<std::string, std::string> param;
		param["n"] = __expr___size(global, _Find(*global, "/CardList"));

		auto x = __event__6(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__11(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	{
		std::map<std::string, std::string> param;
		param["i"] = CONCAT_ALL(std::vector<std::string>{ "0"});

		auto x = __event__12(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__12(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	if (__expr___COMP_LT_(parameters["i"], _Find(*global, "/Info/PLAYER_NUM"))) {
		{
			std::map<std::string, std::string> param;
			param["i"] = CONCAT_ALL(std::vector<std::string>{ "0"});
			param["j"] = CONCAT_ALL(std::vector<std::string>{ parameters["i"]});

			auto x = __event__13(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		{
			std::map<std::string, std::string> param;
			param["i"] = __expr___add(parameters["i"], "1");

			auto x = __event__12(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}

	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__13(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	if (__expr___COMP_LT_(parameters["i"], _Find(*global, "/Info/FIRST_CARD_NUM"))) {
		__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ __expr___concat_all(std::vector<std::string>{ _Find(*global, "/PlayerCardList/"), parameters["j"]})}), CONCAT_ALL(std::vector<std::string>{ __expr___pop_back(global, _Find(*global, "/CardList"))}), "TRUE");
		{
			std::map<std::string, std::string> param;
			param["i"] = __expr___add(parameters["i"], "1");
			param["j"] = CONCAT_ALL(std::vector<std::string>{ parameters["j"]});

			auto x = __event__13(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}

	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__20(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	__func___assign(*global, excuteData, locals, "/PutCard/cardId", CONCAT_ALL(std::vector<std::string>{ parameters["card_id"]}), "TRUE");

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__21(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	__func___assign(*global, excuteData, locals, "/PutCard/cardId", CONCAT_ALL(std::vector<std::string>{ "NONE"}), "TRUE");

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__22(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/CardList")}), CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/PutCard/cardId")}), "TRUE");
	{
		std::map<std::string, std::string> param;

		auto x = __event__21(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__1000(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	if (__expr___COMP_LT_(parameters["i"], _Find(*global, "/Info/TOTAL_CARD_NUM"))) {
		if (__expr___EQ(__expr___get(global, __expr___concat(__expr___concat(_Find(*global, "/Card"), __expr___concat("/", parameters["i"])), _Find(*global, "/isBlackJoker")), locals, parameters), "yes")) {
			__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/FunctionNo")}), CONCAT_ALL(std::vector<std::string>{ "3"}), "TRUE");

		}
		else {
			if (__expr___EQ(__expr___get(global, __expr___concat(__expr___concat(_Find(*global, "/Card"), __expr___concat("/", parameters["i"])), _Find(*global, "/isColorJoker")), locals, parameters), "yes")) {
				__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/FunctionNo")}), CONCAT_ALL(std::vector<std::string>{ "4"}), "TRUE");

			}
			else {
				if (__expr___AND(__expr___EQ(__expr___get(global, __expr___concat(__expr___concat(_Find(*global, "/Card"), __expr___concat("/", parameters["i"])), _Find(*global, "/sha")), locals, parameters), "0"), __expr___EQ(__expr___get(global, __expr___concat(__expr___concat(_Find(*global, "/Card"), __expr___concat("/", parameters["i"])), _Find(*global, "/num")), locals, parameters), "1"))) {
					__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/FunctionNo")}), CONCAT_ALL(std::vector<std::string>{ "9"}), "TRUE");

				}
				else {
					if (__expr___EQ(__expr___get(global, __expr___concat(__expr___concat(_Find(*global, "/Card"), __expr___concat("/", parameters["i"])), _Find(*global, "/num")), locals, parameters), "0")) {
						__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/FunctionNo")}), CONCAT_ALL(std::vector<std::string>{ "8"}), "TRUE");
						{
							std::map<std::string, std::string> param;
							param["i"] = __expr___add(parameters["i"], "1");

							auto x = __event__1000(global, excuteData, param);
							if (x.first) { result_change = true; result = x.second; }
						}
						result_change = true;
						return { result_change, CONCAT_ALL(std::vector<std::string>{ }) };

					}
					if (__expr___EQ(__expr___get(global, __expr___concat(__expr___concat(_Find(*global, "/Card"), __expr___concat("/", parameters["i"])), _Find(*global, "/num")), locals, parameters), "1")) {
						__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/FunctionNo")}), CONCAT_ALL(std::vector<std::string>{ "1"}), "TRUE");
						{
							std::map<std::string, std::string> param;
							param["i"] = __expr___add(parameters["i"], "1");

							auto x = __event__1000(global, excuteData, param);
							if (x.first) { result_change = true; result = x.second; }
						}
						result_change = true;
						return { result_change, CONCAT_ALL(std::vector<std::string>{ }) };

					}
					if (__expr___EQ(__expr___get(global, __expr___concat(__expr___concat(_Find(*global, "/Card"), __expr___concat("/", parameters["i"])), _Find(*global, "/num")), locals, parameters), "2")) {
						__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/FunctionNo")}), CONCAT_ALL(std::vector<std::string>{ "2"}), "TRUE");
						{
							std::map<std::string, std::string> param;
							param["i"] = __expr___add(parameters["i"], "1");

							auto x = __event__1000(global, excuteData, param);
							if (x.first) { result_change = true; result = x.second; }
						}
						result_change = true;
						return { result_change, CONCAT_ALL(std::vector<std::string>{ }) };

					}
					if (__expr___EQ(__expr___get(global, __expr___concat(__expr___concat(_Find(*global, "/Card"), __expr___concat("/", parameters["i"])), _Find(*global, "/num")), locals, parameters), "7")) {
						__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/FunctionNo")}), CONCAT_ALL(std::vector<std::string>{ "5"}), "TRUE");
						{
							std::map<std::string, std::string> param;
							param["i"] = __expr___add(parameters["i"], "1");

							auto x = __event__1000(global, excuteData, param);
							if (x.first) { result_change = true; result = x.second; }
						}
						result_change = true;
						return { result_change, CONCAT_ALL(std::vector<std::string>{ }) };

					}
					if (__expr___EQ(__expr___get(global, __expr___concat(__expr___concat(_Find(*global, "/Card"), __expr___concat("/", parameters["i"])), _Find(*global, "/num")), locals, parameters), "11")) {
						__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/FunctionNo")}), CONCAT_ALL(std::vector<std::string>{ "6"}), "TRUE");
						{
							std::map<std::string, std::string> param;
							param["i"] = __expr___add(parameters["i"], "1");

							auto x = __event__1000(global, excuteData, param);
							if (x.first) { result_change = true; result = x.second; }
						}
						result_change = true;
						return { result_change, CONCAT_ALL(std::vector<std::string>{ }) };

					}
					if (__expr___EQ(__expr___get(global, __expr___concat(__expr___concat(_Find(*global, "/Card"), __expr___concat("/", parameters["i"])), _Find(*global, "/num")), locals, parameters), "12")) {
						__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/FunctionNo")}), CONCAT_ALL(std::vector<std::string>{ "7"}), "TRUE");
						{
							std::map<std::string, std::string> param;
							param["i"] = __expr___add(parameters["i"], "1");

							auto x = __event__1000(global, excuteData, param);
							if (x.first) { result_change = true; result = x.second; }
						}
						result_change = true;
						return { result_change, CONCAT_ALL(std::vector<std::string>{ }) };

					}
					__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/FunctionNo")}), CONCAT_ALL(std::vector<std::string>{ "0"}), "TRUE");

				}

			}

		}
		{
			std::map<std::string, std::string> param;
			param["i"] = __expr___add(parameters["i"], "1");

			auto x = __event__1000(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}

	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__1001(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	{
		std::map<std::string, std::string> param;
		param["i"] = CONCAT_ALL(std::vector<std::string>{ "0"});

		auto x = __event__1000(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__1005(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	if (__expr___EQ(parameters["Mode"], _Find(*global, "/Mode/ATTACK_MODE"))) {
		if (__expr___OR(__expr___EQ(parameters["Old"], "3"), __expr___EQ(parameters["Old"], "4"))) {
			if (__expr___EQ(parameters["New"], "3")) {
				result_change = true;
				return { result_change, CONCAT_ALL(std::vector<std::string>{ "TRUE"}) };

			}
			if (__expr___EQ(parameters["New"], "4")) {
				result_change = true;
				return { result_change, CONCAT_ALL(std::vector<std::string>{ "TRUE"}) };

			}
			if (__expr___EQ(parameters["New"], "9")) {
				result_change = true;
				return { result_change, CONCAT_ALL(std::vector<std::string>{ "TRUE"}) };

			}
			result_change = true;
			return { result_change, CONCAT_ALL(std::vector<std::string>{ "FALSE"}) };

		}
		if (__expr___OR(__expr___EQ(parameters["Old"], "1"), __expr___EQ(parameters["Old"], "9"))) {
			if (__expr___OR(__expr___EQ(parameters["New"], "1"), __expr___EQ(parameters["New"], "9"))) {
				result_change = true;
				return { result_change, CONCAT_ALL(std::vector<std::string>{ "TRUE"}) };

			}
			if (__expr___AND(__expr___EQ(parameters["Old_sha"], parameters["New_sha"]), __expr___EQ(parameters["New"], "2"))) {
				result_change = true;
				return { result_change, CONCAT_ALL(std::vector<std::string>{ "TRUE"}) };

			}
			if (__expr___EQ(parameters["New"], "3")) {
				result_change = true;
				return { result_change, CONCAT_ALL(std::vector<std::string>{ "TRUE"}) };

			}
			if (__expr___EQ(parameters["New"], "4")) {
				result_change = true;
				return { result_change, CONCAT_ALL(std::vector<std::string>{ "TRUE"}) };

			}
			result_change = true;
			return { result_change, CONCAT_ALL(std::vector<std::string>{ "FALSE"}) };

		}
		if (__expr___EQ(parameters["Old"], "2")) {
			if (__expr___EQ(parameters["New"], "2")) {
				result_change = true;
				return { result_change, CONCAT_ALL(std::vector<std::string>{ "TRUE"}) };

			}
			if (__expr___AND(__expr___EQ(parameters["Old_sha"], parameters["New_sha"]), __expr___EQ(parameters["New"], "1"))) {
				result_change = true;
				return { result_change, CONCAT_ALL(std::vector<std::string>{ "TRUE"}) };

			}
			if (__expr___AND(__expr___EQ(parameters["Old_sha"], parameters["New_sha"]), __expr___EQ(parameters["New"], "9"))) {
				result_change = true;
				return { result_change, CONCAT_ALL(std::vector<std::string>{ "TRUE"}) };

			}
			if (__expr___EQ(parameters["New"], "3")) {
				result_change = true;
				return { result_change, CONCAT_ALL(std::vector<std::string>{ "TRUE"}) };

			}
			if (__expr___EQ(parameters["New"], "4")) {
				result_change = true;
				return { result_change, CONCAT_ALL(std::vector<std::string>{ "TRUE"}) };

			}
			result_change = true;
			return { result_change, CONCAT_ALL(std::vector<std::string>{ "FALSE"}) };

		}

	}
	else {
		if (__expr___EQ(parameters["New"], "3")) {
			result_change = true;
			return { result_change, CONCAT_ALL(std::vector<std::string>{ "TRUE"}) };

		}
		if (__expr___EQ(parameters["New"], "4")) {
			result_change = true;
			return { result_change, CONCAT_ALL(std::vector<std::string>{ "TRUE"}) };

		}
		if (__expr___OR(__expr___NOT(__expr___AND(__expr___NOTEQ(parameters["Old_sha"], parameters["New_sha"]), __expr___NOTEQ(parameters["Old_num"], parameters["New_num"]))), __expr___AND(__expr___NOTEQ(parameters["Mode"], _Find(*global, "/Mode/ATTACK_MODE")), __expr___OR(__expr___EQ(parameters["Old"], "3"), __expr___EQ(parameters["Old"], "4"))))) {
			result_change = true;
			return { result_change, CONCAT_ALL(std::vector<std::string>{ "TRUE"}) };

		}

	}
	result_change = true;
	return { result_change, CONCAT_ALL(std::vector<std::string>{ "FALSE"}) };

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__1006(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;

	locals["Old_num"] = "";
	locals["New_num"] = "";
	locals["Old_sha"] = "";
	locals["New_sha"] = "";
	locals["Old"] = "";
	locals["New"] = "";

	{
		std::map<std::string, std::string> param;
		param["card"] = CONCAT_ALL(std::vector<std::string>{ parameters["put_card"]});

		auto x = __event__103(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}
	__func___assign(*global, excuteData, locals, "$local.Old_sha", CONCAT_ALL(std::vector<std::string>{ __expr___return_value()}), "TRUE");
	if (__expr___EQ(parameters["mode"], _Find(*global, "/Mode/CHANGE_SHA_MODE"))) {
		__func___assign(*global, excuteData, locals, "$local.Old_sha", CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/ChangeSha/sha")}), "TRUE");

	}
	{
		std::map<std::string, std::string> param;
		param["card"] = CONCAT_ALL(std::vector<std::string>{ parameters["put_card"]});

		auto x = __event__104(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}
	__func___assign(*global, excuteData, locals, "$local.Old_num", CONCAT_ALL(std::vector<std::string>{ __expr___return_value()}), "TRUE");
	{
		std::map<std::string, std::string> param;
		param["card"] = CONCAT_ALL(std::vector<std::string>{ parameters["card"]});

		auto x = __event__103(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}
	__func___assign(*global, excuteData, locals, "$local.New_sha", CONCAT_ALL(std::vector<std::string>{ __expr___return_value()}), "TRUE");
	{
		std::map<std::string, std::string> param;
		param["card"] = CONCAT_ALL(std::vector<std::string>{ parameters["card"]});

		auto x = __event__104(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}
	__func___assign(*global, excuteData, locals, "$local.New_num", CONCAT_ALL(std::vector<std::string>{ __expr___return_value()}), "TRUE");
	__func___assign(*global, excuteData, locals, "$local.Old", CONCAT_ALL(std::vector<std::string>{ __expr___element(*global, _Find(*global, "/FunctionNo"), parameters["put_card"])}), "TRUE");
	__func___assign(*global, excuteData, locals, "$local.New", CONCAT_ALL(std::vector<std::string>{ __expr___element(*global, _Find(*global, "/FunctionNo"), parameters["card"])}), "TRUE");
	{
		std::map<std::string, std::string> param;
		param["Mode"] = parameters["mode"];
		param["New"] = locals["New"];
		param["New_num"] = locals["New_num"];
		param["New_sha"] = locals["New_sha"];
		param["Old"] = locals["Old"];
		param["Old_num"] = locals["Old_num"];
		param["Old_sha"] = locals["Old_sha"];

		auto x = __event__1005(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}
	result_change = true;
	return { result_change, CONCAT_ALL(std::vector<std::string>{ __expr___return_value()}) };

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__1007(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;

	locals["Attack_A1"] = "";
	locals["KK1"] = "";
	locals["Attack_A2"] = "";
	locals["Attack_A3"] = "";
	locals["Attack_A4"] = "";
	locals["Attack_A5"] = "";
	locals["Change_Sha1"] = "";
	locals["Jump1"] = "";
	locals["Back1"] = "";

	__func___make(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Functions/0")}), "TRUE");
	__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Functions/0")}), CONCAT_ALL(std::vector<std::string>{ "attack_point = 0", "kk = no", "change_sha = no", "jump = no", "back = no"}), "TRUE");
	__func___assign(*global, excuteData, locals, "$local.Attack_A2", CONCAT_ALL(std::vector<std::string>{ "attack_point = 1", "kk = no", "change_sha = no", "jump = no", "back = no"}), "TRUE");
	__func___make(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Functions/1")}), "TRUE");
	__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Functions/1")}), CONCAT_ALL(std::vector<std::string>{ locals["Attack_A2"]}), "TRUE");
	__func___assign(*global, excuteData, locals, "$local.Attack_A3", CONCAT_ALL(std::vector<std::string>{ "attack_point = 2", "kk = no", "change_sha = no", "jump = no", "back = no"}), "TRUE");
	__func___make(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Functions/2")}), "TRUE");
	__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Functions/2")}), CONCAT_ALL(std::vector<std::string>{ locals["Attack_A3"]}), "TRUE");
	__func___assign(*global, excuteData, locals, "$local.Attack_A4", CONCAT_ALL(std::vector<std::string>{ "attack_point = 5", "kk = no", "change_sha = no", "jump = no", "back = no"}), "TRUE");
	__func___make(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Functions/3")}), "TRUE");
	__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Functions/3")}), CONCAT_ALL(std::vector<std::string>{ locals["Attack_A4"]}), "TRUE");
	__func___assign(*global, excuteData, locals, "$local.Attack_A5", CONCAT_ALL(std::vector<std::string>{ "attack_point = 7", "kk = no", "change_sha = no", "jump = no", "back = no"}), "TRUE");
	__func___make(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Functions/4")}), "TRUE");
	__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Functions/4")}), CONCAT_ALL(std::vector<std::string>{ locals["Attack_A5"]}), "TRUE");
	__func___assign(*global, excuteData, locals, "$local.Change_Sha1", CONCAT_ALL(std::vector<std::string>{ "attack_point = 0", "kk = no", "change_sha = yes", "jump = no", "back = no"}), "TRUE");
	__func___make(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Functions/5")}), "TRUE");
	__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Functions/5")}), CONCAT_ALL(std::vector<std::string>{ locals["Change_Sha1"]}), "TRUE");
	__func___assign(*global, excuteData, locals, "$local.Jump1", CONCAT_ALL(std::vector<std::string>{ "attack_point = 0", "kk = no", "change_sha = no", "jump = yes", "back = no"}), "TRUE");
	__func___make(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Functions/6")}), "TRUE");
	__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Functions/6")}), CONCAT_ALL(std::vector<std::string>{ locals["Jump1"]}), "TRUE");
	__func___assign(*global, excuteData, locals, "$local.Back1", CONCAT_ALL(std::vector<std::string>{ "attack_point = 0", "kk = no", "change_sha = no", "jump = no", "back = yes"}), "TRUE");
	__func___make(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Functions/7")}), "TRUE");
	__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Functions/7")}), CONCAT_ALL(std::vector<std::string>{ locals["Back1"]}), "TRUE");
	__func___assign(*global, excuteData, locals, "$local.KK1", CONCAT_ALL(std::vector<std::string>{ "attack_point = 0", "kk = yes", "change_sha = no", "jump = no", "back = no"}), "TRUE");
	__func___make(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Functions/8")}), "TRUE");
	__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Functions/8")}), CONCAT_ALL(std::vector<std::string>{ locals["KK1"]}), "TRUE");
	__func___assign(*global, excuteData, locals, "$local.Attack_A1", CONCAT_ALL(std::vector<std::string>{ "attack_point = 3", "kk = no", "change_sha = no", "jump = no", "back = no"}), "TRUE");
	__func___make(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Functions/9")}), "TRUE");
	__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Functions/9")}), CONCAT_ALL(std::vector<std::string>{ locals["Attack_A1"]}), "TRUE");

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__1008(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;

	locals["card_function_no"] = "";
	locals["function_dir"] = "";

	{
		auto x = wiz::load_data::UserType::Find(global, CONCAT_ALL(std::vector<std::string>{ parameters["card"]}), &builder);
		if (x.first) {
			wiz::load_data::UserType* ut = x.second[0];
			std::cout << ut->ToString();
		}
		else {
			std::cout << CONCAT_ALL(std::vector<std::string>{ parameters["card"]});
		}
	}

	__func___assign(*global, excuteData, locals, "$local.card_function_no", CONCAT_ALL(std::vector<std::string>{ __expr___element(*global, _Find(*global, "/FunctionNo"), parameters["card"])}), "TRUE");
	__func___assign(*global, excuteData, locals, "$local.function_dir", CONCAT_ALL(std::vector<std::string>{ __expr___concat(_Find(*global, "/Functions"), __expr___concat("/", locals["card_function_no"]))}), "TRUE");
	{
		auto x = wiz::load_data::UserType::Find(global, CONCAT_ALL(std::vector<std::string>{ locals["function_dir"]}), &builder);
		if (x.first) {
			wiz::load_data::UserType* ut = x.second[0];
			std::cout << ut->ToString();
		}
		else {
			std::cout << CONCAT_ALL(std::vector<std::string>{ locals["function_dir"]});
		}
	}

	if (__expr___COMP_GT_(__expr___get(global, __expr___concat(locals["function_dir"], __expr___concat("/", "attack_point")), locals, parameters), "0")) {
		{
			std::map<std::string, std::string> param;
			param["point"] = __expr___get(global, __expr___concat(locals["function_dir"], __expr___concat("/", "attack_point")), locals, parameters);

			auto x = __event__1010(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}

	}
	if (__expr___EQ(__expr___get(global, __expr___concat(locals["function_dir"], __expr___concat("/", "change_sha")), locals, parameters), "yes")) {
		{
			std::map<std::string, std::string> param;

			auto x = __event__1015(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}

	}
	if (__expr___EQ(__expr___get(global, __expr___concat(locals["function_dir"], __expr___concat("/", "jump")), locals, parameters), "yes")) {
		{
			std::map<std::string, std::string> param;
			param["i"] = CONCAT_ALL(std::vector<std::string>{ "0"});

			auto x = __event__1016(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}

	}
	if (__expr___EQ(__expr___get(global, __expr___concat(locals["function_dir"], __expr___concat("/", "back")), locals, parameters), "yes")) {
		{
			std::map<std::string, std::string> param;

			auto x = __event__1017(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}

	}
	if (__expr___EQ(__expr___get(global, __expr___concat(locals["function_dir"], __expr___concat("/", "kk")), locals, parameters), "yes")) {
		{
			std::map<std::string, std::string> param;

			auto x = __event__1017(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		{
			std::map<std::string, std::string> param;
			param["i"] = CONCAT_ALL(std::vector<std::string>{ "0"});

			auto x = __event__1016(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		{
			std::map<std::string, std::string> param;

			auto x = __event__1017(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}

	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__1015(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	if (__expr___EQ(_Find(*global, "/Turn/now"), _Find(*global, "/State/person_stream"))) {

	}
	else {
		__func___assign(*global, excuteData, locals, "/ChangeSha/sha", CONCAT_ALL(std::vector<std::string>{ __expr___rand("0", "3")}), "TRUE");
		__func___assign(*global, excuteData, locals, "/State/mode", CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Mode/CHANGE_SHA_MODE")}), "TRUE");
		{
			auto x = wiz::load_data::UserType::Find(global, CONCAT_ALL(std::vector<std::string>{ "\"change sha : \""}), &builder);
			if (x.first) {
				wiz::load_data::UserType* ut = x.second[0];
				std::cout << ut->ToString();
			}
			else {
				std::cout << CONCAT_ALL(std::vector<std::string>{ "\"change sha : \""});
			}
		}

		{
			auto x = wiz::load_data::UserType::Find(global, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/ChangeSha/sha")}), &builder);
			if (x.first) {
				wiz::load_data::UserType* ut = x.second[0];
				std::cout << ut->ToString();
			}
			else {
				std::cout << CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/ChangeSha/sha")});
			}
		}

		{
			auto x = wiz::load_data::UserType::Find(global, CONCAT_ALL(std::vector<std::string>{ "\n"}), &builder);
			if (x.first) {
				wiz::load_data::UserType* ut = x.second[0];
				std::cout << ut->ToString();
			}
			else {
				std::cout << CONCAT_ALL(std::vector<std::string>{ "\n"});
			}
		}


	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__1016(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	{
		std::map<std::string, std::string> param;

		auto x = __event__1(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}
	if (__expr___EQ(__expr___element(*global, _Find(*global, "/PlayerGameOverList"), __expr___add(_Find(*global, "/Turn/now"), "-1")), "no")) {
		result_change = true;
		return { result_change, CONCAT_ALL(std::vector<std::string>{ }) };

	}
	else {
		{
			std::map<std::string, std::string> param;
			param["i"] = __expr___add(parameters["i"], "1");

			auto x = __event__1016(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}

	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__1017(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	{
		std::map<std::string, std::string> param;

		auto x = __event__200(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__1010(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	__func___assign(*global, excuteData, locals, "/AttackPoint/now_point", CONCAT_ALL(std::vector<std::string>{ parameters["point"]}), "TRUE");
	__func___assign(*global, excuteData, locals, "/AttackPoint/total_point", CONCAT_ALL(std::vector<std::string>{ __expr___add(_Find(*global, "/AttackPoint/total_point"), parameters["point"])}), "TRUE");
	__func___assign(*global, excuteData, locals, "/State/mode", CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Mode/ATTACK_MODE")}), "TRUE");

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__1011(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	__func___assign(*global, excuteData, locals, "/AttackPoint/now_point", CONCAT_ALL(std::vector<std::string>{ "0"}), "TRUE");
	__func___assign(*global, excuteData, locals, "/AttackPoint/total_point", CONCAT_ALL(std::vector<std::string>{ "0"}), "TRUE");

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__1100(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/State")}), CONCAT_ALL(std::vector<std::string>{ "mode = ", _Find(*global, "/Mode/GENERAL_MODE")}), "TRUE");
	__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/State")}), CONCAT_ALL(std::vector<std::string>{ "action_state = NONE"}), "TRUE");
	__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/State")}), CONCAT_ALL(std::vector<std::string>{ "action_card = NONE"}), "TRUE");
	__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/State")}), CONCAT_ALL(std::vector<std::string>{ "person_stream = -1"}), "TRUE");

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__1200(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;



	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__3003(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	{
		std::map<std::string, std::string> param;
		param["i"] = CONCAT_ALL(std::vector<std::string>{ "0"});

		auto x = __event__3002(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__3002(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	if (__expr___COMP_LT_(parameters["i"], _Find(*global, "/Info/PLAYER_NUM"))) {
		__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/PlayerGameOverList")}), CONCAT_ALL(std::vector<std::string>{ "no"}), "TRUE");
		{
			std::map<std::string, std::string> param;
			param["i"] = __expr___add(parameters["i"], "1");

			auto x = __event__3002(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}

	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__3001(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	{
		std::map<std::string, std::string> param;
		param["i"] = CONCAT_ALL(std::vector<std::string>{ "0"});
		param["j"] = CONCAT_ALL(std::vector<std::string>{ "1"});

		auto x = __event__3000(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__3000(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	if (__expr___COMP_LT_(parameters["i"], _Find(*global, "/Info/PLAYER_NUM"))) {
		if (__expr___NOTEQ(parameters["i"], _Find(*global, "/State/person_stream"))) {
			__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/PlayerNameList")}), CONCAT_ALL(std::vector<std::string>{ __expr___concat("computer", "j")}), "TRUE");
			{
				std::map<std::string, std::string> param;
				param["i"] = __expr___add(parameters["i"], "1");
				param["j"] = __expr___add(parameters["j"], "1");

				auto x = __event__3000(global, excuteData, param);
				if (x.first) { result_change = true; result = x.second; }
			}

		}
		else {
			__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/PlayerNameList")}), CONCAT_ALL(std::vector<std::string>{ "person"}), "TRUE");
			{
				std::map<std::string, std::string> param;
				param["i"] = __expr___add(parameters["i"], "1");
				param["j"] = CONCAT_ALL(std::vector<std::string>{ parameters["j"]});

				auto x = __event__3000(global, excuteData, param);
				if (x.first) { result_change = true; result = x.second; }
			}

		}

	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__8(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	{
		std::map<std::string, std::string> param;
		param["i"] = CONCAT_ALL(std::vector<std::string>{ "0"});

		auto x = __event__9(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__9(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	if (__expr___COMP_LT_(parameters["i"], _Find(*global, "/Info/PLAYER_NUM"))) {
		if (__expr___EQ(parameters["i"], "0")) {
			__func___make(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/PlayerCardList")}), "TRUE");

		}
		__func___make(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ __expr___concat_all(std::vector<std::string>{ _Find(*global, "/PlayerCardList/"), parameters["i"]})}), "TRUE");
		{
			std::map<std::string, std::string> param;
			param["i"] = __expr___add(parameters["i"], "1");

			auto x = __event__9(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}

	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__52(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	{
		std::map<std::string, std::string> param;
		param["isBlackJoker"] = __expr___get(global, __expr___concat(__expr___concat(_Find(*global, "/Card"), __expr___concat("/", parameters["card"])), _Find(*global, "/isBlackJoker")), locals, parameters);
		param["isColorJoker"] = __expr___get(global, __expr___concat(__expr___concat(_Find(*global, "/Card"), __expr___concat("/", parameters["card"])), _Find(*global, "/isColorJoker")), locals, parameters);
		param["num"] = __expr___get(global, __expr___concat(__expr___concat(_Find(*global, "/Card"), __expr___concat("/", parameters["card"])), _Find(*global, "/num")), locals, parameters);
		param["sha"] = __expr___get(global, __expr___concat(__expr___concat(_Find(*global, "/Card"), __expr___concat("/", parameters["card"])), _Find(*global, "/sha")), locals, parameters);

		auto x = __event__100(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__51(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	if (__expr___COMP_LT_(parameters["j"], __expr___size(global, __expr___concat_all(std::vector<std::string>{ _Find(*global, "/PlayerCardList/"), parameters["i"]})))) {
		{
			std::map<std::string, std::string> param;
			param["isBlackJoker"] = __expr___get(global, __expr___concat(__expr___concat(_Find(*global, "/Card"), __expr___concat("/", __expr___element(*global, __expr___concat_all(std::vector<std::string>{ _Find(*global, "/PlayerCardList/"), parameters["i"]}), parameters["j"]))), _Find(*global, "/isBlackJoker")), locals, parameters);
			param["isColorJoker"] = __expr___get(global, __expr___concat(__expr___concat(_Find(*global, "/Card"), __expr___concat("/", __expr___element(*global, __expr___concat_all(std::vector<std::string>{ _Find(*global, "/PlayerCardList/"), parameters["i"]}), parameters["j"]))), _Find(*global, "/isColorJoker")), locals, parameters);
			param["num"] = __expr___get(global, __expr___concat(__expr___concat(_Find(*global, "/Card"), __expr___concat("/", __expr___element(*global, __expr___concat_all(std::vector<std::string>{ _Find(*global, "/PlayerCardList/"), parameters["i"]}), parameters["j"]))), _Find(*global, "/num")), locals, parameters);
			param["sha"] = __expr___get(global, __expr___concat(__expr___concat(_Find(*global, "/Card"), __expr___concat("/", __expr___element(*global, __expr___concat_all(std::vector<std::string>{ _Find(*global, "/PlayerCardList/"), parameters["i"]}), parameters["j"]))), _Find(*global, "/sha")), locals, parameters);

			auto x = __event__100(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		{
			auto x = wiz::load_data::UserType::Find(global, CONCAT_ALL(std::vector<std::string>{ "\"/\""}), &builder);
			if (x.first) {
				wiz::load_data::UserType* ut = x.second[0];
				std::cout << ut->ToString();
			}
			else {
				std::cout << CONCAT_ALL(std::vector<std::string>{ "\"/\""});
			}
		}

		{
			std::map<std::string, std::string> param;
			param["i"] = CONCAT_ALL(std::vector<std::string>{ parameters["i"]});
			param["j"] = __expr___add(parameters["j"], "1");

			auto x = __event__51(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}

	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__50(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	if (__expr___COMP_LT_(parameters["i"], _Find(*global, "/Info/PLAYER_NUM"))) {
		{
			std::map<std::string, std::string> param;
			param["i"] = CONCAT_ALL(std::vector<std::string>{ parameters["i"]});
			param["j"] = CONCAT_ALL(std::vector<std::string>{ "0"});

			auto x = __event__51(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		{
			auto x = wiz::load_data::UserType::Find(global, CONCAT_ALL(std::vector<std::string>{ "\n"}), &builder);
			if (x.first) {
				wiz::load_data::UserType* ut = x.second[0];
				std::cout << ut->ToString();
			}
			else {
				std::cout << CONCAT_ALL(std::vector<std::string>{ "\n"});
			}
		}

		{
			std::map<std::string, std::string> param;
			param["i"] = __expr___add(parameters["i"], "1");

			auto x = __event__50(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}

	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__0(wiz::load_data::UserType* global, ExcuteData& excuteData)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;

	locals["result"] = "";

	if (false) {

	}
	else {
		{
			std::map<std::string, std::string> param;

			auto x = __event__201(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		{
			std::map<std::string, std::string> param;

			auto x = __event__3(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		{
			std::map<std::string, std::string> param;

			auto x = __event__5(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		{
			std::map<std::string, std::string> param;

			auto x = __event__7(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		{
			std::map<std::string, std::string> param;

			auto x = __event__8(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		{
			std::map<std::string, std::string> param;

			auto x = __event__11(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		{
			std::map<std::string, std::string> param;

			auto x = __event__21(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		__func___assign(*global, excuteData, locals, "/PutCard/cardId", CONCAT_ALL(std::vector<std::string>{ __expr___pop_back(global, _Find(*global, "/CardList"))}), "TRUE");
		{
			std::map<std::string, std::string> param;
			param["i"] = CONCAT_ALL(std::vector<std::string>{ "0"});

			auto x = __event__50(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		{
			std::map<std::string, std::string> param;

			auto x = __event__1001(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		{
			std::map<std::string, std::string> param;
			param["card"] = CONCAT_ALL(std::vector<std::string>{ "0"});
			param["mode"] = _Find(*global, "/Mode/GENERAL_MODE");
			param["put_card"] = CONCAT_ALL(std::vector<std::string>{ "0"});

			auto x = __event__1006(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		__func___assign(*global, excuteData, locals, "$local.result", CONCAT_ALL(std::vector<std::string>{ __expr___return_value()}), "TRUE");
		{
			auto x = wiz::load_data::UserType::Find(global, CONCAT_ALL(std::vector<std::string>{ locals["result"]}), &builder);
			if (x.first) {
				wiz::load_data::UserType* ut = x.second[0];
				std::cout << ut->ToString();
			}
			else {
				std::cout << CONCAT_ALL(std::vector<std::string>{ locals["result"]});
			}
		}

		{
			std::map<std::string, std::string> param;

			auto x = __event__1100(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		{
			std::map<std::string, std::string> param;

			auto x = __event__1011(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		{
			std::map<std::string, std::string> param;

			auto x = __event__3001(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		{
			std::map<std::string, std::string> param;

			auto x = __event__3003(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		{
			std::map<std::string, std::string> param;

			auto x = __event__1007(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		{
			std::map<std::string, std::string> param;

			auto x = __event__4001(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}

	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__4001(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	{
		std::map<std::string, std::string> param;

		auto x = __event__4000(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}
	if (__expr___NOTEQ(__expr___return_value(), _Find(*global, "/Mode/GAME_END_MODE"))) {
		{
			std::map<std::string, std::string> param;

			auto x = __event__4001(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
			return { result_change, result };
		}

	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__4000(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;

	locals["card"] = "";
	locals["idx"] = "";

	{
		auto x = wiz::load_data::UserType::Find(global, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Turn/now")}), &builder);
		if (x.first) {
			wiz::load_data::UserType* ut = x.second[0];
			std::cout << ut->ToString();
		}
		else {
			std::cout << CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Turn/now")});
		}
	}

	{
		auto x = wiz::load_data::UserType::Find(global, CONCAT_ALL(std::vector<std::string>{ "\n"}), &builder);
		if (x.first) {
			wiz::load_data::UserType* ut = x.second[0];
			std::cout << ut->ToString();
		}
		else {
			std::cout << CONCAT_ALL(std::vector<std::string>{ "\n"});
		}
	}

	{
		auto x = wiz::load_data::UserType::Find(global, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/State/mode")}), &builder);
		if (x.first) {
			wiz::load_data::UserType* ut = x.second[0];
			std::cout << ut->ToString();
		}
		else {
			std::cout << CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/State/mode")});
		}
	}

	{
		auto x = wiz::load_data::UserType::Find(global, CONCAT_ALL(std::vector<std::string>{ "\n"}), &builder);
		if (x.first) {
			wiz::load_data::UserType* ut = x.second[0];
			std::cout << ut->ToString();
		}
		else {
			std::cout << CONCAT_ALL(std::vector<std::string>{ "\n"});
		}
	}

	{
		std::map<std::string, std::string> param;
		param["i"] = CONCAT_ALL(std::vector<std::string>{ "0"});

		auto x = __event__50(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}
	{
		std::map<std::string, std::string> param;
		param["card"] = CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/PutCard/cardId")});

		auto x = __event__52(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}
	{
		auto x = wiz::load_data::UserType::Find(global, CONCAT_ALL(std::vector<std::string>{ "\n"}), &builder);
		if (x.first) {
			wiz::load_data::UserType* ut = x.second[0];
			std::cout << ut->ToString();
		}
		else {
			std::cout << CONCAT_ALL(std::vector<std::string>{ "\n"});
		}
	}

	if (__expr___NOTEQ(_Find(*global, "/Turn/now"), _Find(*global, "/State/person_stream"))) {
		__func___assign(*global, excuteData, locals, "/State/action_state", CONCAT_ALL(std::vector<std::string>{ "EAT"}), "TRUE");
		{
			std::map<std::string, std::string> param;
			param["i"] = CONCAT_ALL(std::vector<std::string>{ "0"});
			param["n"] = CONCAT_ALL(std::vector<std::string>{ "20"});

			auto x = __event__4010(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		if (__expr___EQ(_Find(*global, "/State/action_state"), "PUT")) {
			__func___assign(*global, excuteData, locals, "$local.card", CONCAT_ALL(std::vector<std::string>{ __expr___return_value()}), "TRUE");
			{
				std::map<std::string, std::string> param;
				param["card"] = CONCAT_ALL(std::vector<std::string>{ locals["card"]});

				auto x = __event__52(global, excuteData, param);
				if (x.first) { result_change = true; result = x.second; }
			}
			{
				auto x = wiz::load_data::UserType::Find(global, CONCAT_ALL(std::vector<std::string>{ "\n"}), &builder);
				if (x.first) {
					wiz::load_data::UserType* ut = x.second[0];
					std::cout << ut->ToString();
				}
				else {
					std::cout << CONCAT_ALL(std::vector<std::string>{ "\n"});
				}
			}


		}

	}
	else {

	}
	{
		auto x = wiz::load_data::UserType::Find(global, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/State/action_state")}), &builder);
		if (x.first) {
			wiz::load_data::UserType* ut = x.second[0];
			std::cout << ut->ToString();
		}
		else {
			std::cout << CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/State/action_state")});
		}
	}

	if (__expr___EQ(_Find(*global, "/State/action_state"), "PUT")) {
		__func___assign(*global, excuteData, locals, "/State/action_state", CONCAT_ALL(std::vector<std::string>{ "-1"}), "TRUE");
		{
			std::map<std::string, std::string> param;
			param["card"] = CONCAT_ALL(std::vector<std::string>{ locals["card"]});
			param["mode"] = CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/State/mode")});
			param["put_card"] = CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/PutCard/cardId")});

			auto x = __event__1006(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		if (__expr___EQ("FALSE", __expr___return_value())) {
			result_change = true;
			return { result_change, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/State/mode")}) };

		}
		if (__expr___EQ("2", __expr___size(global, __expr___concat(_Find(*global, "/PlayerCardList"), __expr___concat("/", __expr___add("-1", _Find(*global, "/Turn/now"))))))) {
			{
				std::map<std::string, std::string> param;
				param["card"] = CONCAT_ALL(std::vector<std::string>{ locals["card"]});

				auto x = __event__4011(global, excuteData, param);
				if (x.first) { result_change = true; result = x.second; }
			}
			{
				std::map<std::string, std::string> param;
				param["i"] = CONCAT_ALL(std::vector<std::string>{ "0"});

				auto x = __event__1016(global, excuteData, param);
				if (x.first) { result_change = true; result = x.second; }
			}
			result_change = true;
			return { result_change, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/State/mode")}) };

		}
		__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/CardList")}), CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/PutCard/cardId")}), "TRUE");
		{
			std::map<std::string, std::string> param;

			auto x = __event__7(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		__func___findIndex(global, excuteData, CONCAT_ALL(std::vector<std::string>{ __expr___concat(_Find(*global, "/PlayerCardList"), __expr___concat("/", __expr___add(_Find(*global, "/Turn/now"), "-1")))}), CONCAT_ALL(std::vector<std::string>{ locals["card"]}));

		__func___assign(*global, excuteData, locals, "$local.idx", CONCAT_ALL(std::vector<std::string>{ __expr___return_value()}), "TRUE");
		__func___assign(*global, excuteData, locals, "/PutCard/cardId", CONCAT_ALL(std::vector<std::string>{ __expr___element(*global, __expr___concat(_Find(*global, "/PlayerCardList"), __expr___concat("/", __expr___add(_Find(*global, "/Turn/now"), "-1"))), locals["idx"])}), "TRUE");
		__func___remove3(global, excuteData, CONCAT_ALL(std::vector<std::string>{ __expr___concat(_Find(*global, "/PlayerCardList"), __expr___concat("/", __expr___add(_Find(*global, "/Turn/now"), "-1")))}), CONCAT_ALL(std::vector<std::string>{ locals["idx"]}), "TRUE");

		if (__expr___EQ("0", __expr___size(global, __expr___concat(_Find(*global, "/PlayerCardList"), __expr___concat("/", __expr___add("-1", _Find(*global, "/Turn/now"))))))) {
			__func___assign(*global, excuteData, locals, "/State/mode", CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Mode/GAME_END_MODE")}), "TRUE");
			result_change = true;
			return { result_change, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/State/mode")}) };

		}
		if (__expr___EQ(_Find(*global, "/State/mode"), _Find(*global, "/Mode/CHANGE_SHA_MODE"))) {
			__func___assign(*global, excuteData, locals, "/State/mode", CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Mode/GENERAL_MODE")}), "TRUE");

		}
		{
			std::map<std::string, std::string> param;
			param["card"] = CONCAT_ALL(std::vector<std::string>{ locals["card"]});

			auto x = __event__1008(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}

	}
	if (__expr___EQ(_Find(*global, "/State/action_state"), "EAT")) {
		__func___assign(*global, excuteData, locals, "/State/action_state", CONCAT_ALL(std::vector<std::string>{ "-1"}), "TRUE");
		if (__expr___EQ(_Find(*global, "/State/mode"), _Find(*global, "/Mode/ATTACK_MODE"))) {
			{
				std::map<std::string, std::string> param;
				param["i"] = CONCAT_ALL(std::vector<std::string>{ "0"});
				param["n"] = CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/AttackPoint/total_point")});

				auto x = __event__4013(global, excuteData, param);
				if (x.first) { result_change = true; result = x.second; }
			}
			__func___assign(*global, excuteData, locals, "/State/mode", CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Mode/GENERAL_MODE")}), "TRUE");
			{
				std::map<std::string, std::string> param;

				auto x = __event__1011(global, excuteData, param);
				if (x.first) { result_change = true; result = x.second; }
			}

		}
		else {
			{
				std::map<std::string, std::string> param;
				param["i"] = CONCAT_ALL(std::vector<std::string>{ "0"});
				param["n"] = CONCAT_ALL(std::vector<std::string>{ "1"});

				auto x = __event__4013(global, excuteData, param);
				if (x.first) { result_change = true; result = x.second; }
			}

		}
		if (__expr___COMP_LT_(__expr___add(_Find(*global, "/Info/GAME_OVER_CARD_NUM"), "-1"), __expr___size(global, __expr___concat(_Find(*global, "/PlayerCardList"), __expr___concat("/", __expr___add(_Find(*global, "/Turn/now"), "-1")))))) {
			__func___assign(*global, excuteData, locals, "/Temp/count", CONCAT_ALL(std::vector<std::string>{ "0"}), "TRUE");
			{
				std::map<std::string, std::string> param;
				param["i"] = CONCAT_ALL(std::vector<std::string>{ "0"});
				param["n"] = CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Info/PLAYER_NUM")});

				auto x = __event__4014(global, excuteData, param);
				if (x.first) { result_change = true; result = x.second; }
			}
			if (__expr___EQ(_Find(*global, "/Temp/count"), "2")) {
				__func___assign(*global, excuteData, locals, "/State/mode", CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Mode/GAME_END_MODE")}), "TRUE");
				result_change = true;
				return { result_change, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/State/mode")}) };

			}
			__func___assign(*global, excuteData, locals, "/Temp/count", CONCAT_ALL(std::vector<std::string>{ "0"}), "TRUE");
			__func___setElement(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/PlayerGameOverList")}), CONCAT_ALL(std::vector<std::string>{ __expr___add("-1", _Find(*global, "/Turn/now"))}), CONCAT_ALL(std::vector<std::string>{ "yes"}));
			{
				std::map<std::string, std::string> param;

				auto x = __event__4015(global, excuteData, param);
				if (x.first) { result_change = true; result = x.second; }
			}
			{
				std::map<std::string, std::string> param;

				auto x = __event__7(global, excuteData, param);
				if (x.first) { result_change = true; result = x.second; }
			}

		}

	}
	{
		std::map<std::string, std::string> param;
		param["i"] = CONCAT_ALL(std::vector<std::string>{ "0"});

		auto x = __event__1016(global, excuteData, param);
		if (x.first) { result_change = true; result = x.second; }
	}
	result_change = true;
	return { result_change, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/State/mode")}) };

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__4015(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;

	locals["index"] = "";
	locals["card"] = "";

	if (__expr___COMP_LT_("0", __expr___size(global, __expr___concat(_Find(*global, "/PlayerCardList"), __expr___concat("/", __expr___add("-1", _Find(*global, "/Turn/now"))))))) {
		__func___assign(*global, excuteData, locals, "$local.index", CONCAT_ALL(std::vector<std::string>{ __expr___add("-1", __expr___size(global, __expr___concat(_Find(*global, "/PlayerCardList"), __expr___concat("/", __expr___add("-1", _Find(*global, "/Turn/now"))))))}), "TRUE");
		__func___assign(*global, excuteData, locals, "$local.card", CONCAT_ALL(std::vector<std::string>{ __expr___element(*global, __expr___concat(_Find(*global, "/PlayerCardList"), __expr___concat("/", __expr___add("-1", _Find(*global, "/Turn/now")))), locals["index"])}), "TRUE");
		__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/CardList")}), CONCAT_ALL(std::vector<std::string>{ locals["card"]}), "TRUE");
		__func___remove3(global, excuteData, CONCAT_ALL(std::vector<std::string>{ __expr___concat(_Find(*global, "/PlayerCardList"), __expr___concat("/", __expr___add("-1", _Find(*global, "/Turn/now"))))}), CONCAT_ALL(std::vector<std::string>{ locals["index"]}), "TRUE");

		{
			std::map<std::string, std::string> param;

			auto x = __event__4015(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}

	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__4014(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	if (__expr___COMP_LT_(parameters["i"], parameters["n"])) {
		if (__expr___EQ("no", __expr___element(*global, _Find(*global, "/PlayerGameOverList"), parameters["i"]))) {
			__func___assign(*global, excuteData, locals, "/Temp/count", CONCAT_ALL(std::vector<std::string>{ __expr___add(_Find(*global, "/Temp/count"), "1")}), "TRUE");

		}
		{
			std::map<std::string, std::string> param;
			param["i"] = __expr___add(parameters["i"], "1");
			param["n"] = CONCAT_ALL(std::vector<std::string>{ parameters["n"]});

			auto x = __event__4014(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}

	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__4013(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;


	if (__expr___COMP_LT_(parameters["i"], parameters["n"])) {
		{
			std::map<std::string, std::string> param;

			auto x = __event__4012(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		{
			std::map<std::string, std::string> param;
			param["i"] = __expr___add(parameters["i"], "1");
			param["n"] = CONCAT_ALL(std::vector<std::string>{ parameters["n"]});

			auto x = __event__4013(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}

	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__4012(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;

	locals["card"] = "";

	if (__expr___EQ("0", __expr___size(global, _Find(*global, "/CardList")))) {
		result_change = true;
		return { result_change, CONCAT_ALL(std::vector<std::string>{ "\"ERROR_cardList_is_empty\""}) };

	}
	__func___assign(*global, excuteData, locals, "$local.card", CONCAT_ALL(std::vector<std::string>{ __expr___pop_back(global, _Find(*global, "/CardList"))}), "TRUE");
	__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ __expr___concat(_Find(*global, "/PlayerCardList"), __expr___concat("/", __expr___add(_Find(*global, "/Turn/now"), "-1")))}), CONCAT_ALL(std::vector<std::string>{ locals["card"]}), "TRUE");

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__4011(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;

	locals["select"] = "";
	locals["idx"] = "";

	if (__expr___NOTEQ(_Find(*global, "/Turn/now"), _Find(*global, "/State/person_stream"))) {
		__func___assign(*global, excuteData, locals, "$local.select", CONCAT_ALL(std::vector<std::string>{ __expr___rand("1", "3")}), "TRUE");

	}
	if (__expr___NOTEQ(locals["select"], __expr___rand("1", "3"))) {
		{
			std::map<std::string, std::string> param;
			param["i"] = CONCAT_ALL(std::vector<std::string>{ "0"});
			param["n"] = CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Info/ONE_CARD_FAIL_CARD_NUM")});

			auto x = __event__4013(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		__func___assign(*global, excuteData, locals, "/Temp/count", CONCAT_ALL(std::vector<std::string>{ "0"}), "TRUE");
		{
			std::map<std::string, std::string> param;
			param["i"] = CONCAT_ALL(std::vector<std::string>{ "0"});
			param["n"] = CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Info/PLAYER_NUM")});

			auto x = __event__4014(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		if (__expr___EQ(_Find(*global, "/Temp/count"), "2")) {
			__func___assign(*global, excuteData, locals, "/State/mode", CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Mode/GAME_END_MODE")}), "TRUE");
			result_change = true;
			return { result_change, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/State/mode")}) };

		}
		__func___assign(*global, excuteData, locals, "/Temp/count", CONCAT_ALL(std::vector<std::string>{ "0"}), "TRUE");

	}
	else {
		if (__expr___EQ(_Find(*global, "/State/mode"), _Find(*global, "/Mode/CHANGE_SHA_MODE"))) {
			__func___assign(*global, excuteData, locals, "/State/mode", CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Mode/GENERAL_MODE")}), "TRUE");

		}
		__func___insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/CardList")}), CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/PutCard/cardId")}), "TRUE");
		{
			std::map<std::string, std::string> param;

			auto x = __event__7(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		__func___findIndex(global, excuteData, CONCAT_ALL(std::vector<std::string>{ __expr___concat(_Find(*global, "/PlayerCardList"), __expr___concat("/", __expr___add(_Find(*global, "/Turn/now"), "-1")))}), CONCAT_ALL(std::vector<std::string>{ parameters["card"]}));

		__func___assign(*global, excuteData, locals, "$local.idx", CONCAT_ALL(std::vector<std::string>{ __expr___return_value()}), "TRUE");
		__func___assign(*global, excuteData, locals, "/PutCard/cardId", CONCAT_ALL(std::vector<std::string>{ __expr___element(*global, __expr___concat(_Find(*global, "/PlayerCardList"), __expr___concat("/", __expr___add(_Find(*global, "/Turn/now"), "-1"))), locals["idx"])}), "TRUE");
		__func___remove3(global, excuteData, CONCAT_ALL(std::vector<std::string>{ __expr___concat(_Find(*global, "/PlayerCardList"), __expr___concat("/", __expr___add(_Find(*global, "/Turn/now"), "-1")))}), CONCAT_ALL(std::vector<std::string>{ locals["idx"]}), "TRUE");

		if (__expr___EQ(_Find(*global, "/State/mode"), _Find(*global, "/Mode/CHANGE_SHA_MODE"))) {
			__func___assign(*global, excuteData, locals, "/State/mode", CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/Mode/GENERAL_MODE")}), "TRUE");

		}
		{
			std::map<std::string, std::string> param;
			param["card"] = CONCAT_ALL(std::vector<std::string>{ parameters["card"]});

			auto x = __event__1008(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}

	}

	return { result_change, result };
}
INLINE std::pair<bool, std::string> __event__4010(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	bool result_change = false;
	std::string option;

	locals["index"] = "";
	locals["card"] = "";

	if (__expr___COMP_LT_(parameters["i"], parameters["n"])) {
		__func___assign(*global, excuteData, locals, "$local.index", CONCAT_ALL(std::vector<std::string>{ __expr___rand("0", __expr___add("-1", __expr___size(global, __expr___concat(_Find(*global, "/PlayerCardList"), __expr___concat("/", __expr___add(_Find(*global, "/Turn/now"), "-1"))))))}), "TRUE");
		__func___assign(*global, excuteData, locals, "$local.card", CONCAT_ALL(std::vector<std::string>{ __expr___element(*global, __expr___concat(_Find(*global, "/PlayerCardList"), __expr___concat("/", __expr___add(_Find(*global, "/Turn/now"), "-1"))), locals["index"])}), "TRUE");
		{
			std::map<std::string, std::string> param;
			param["card"] = CONCAT_ALL(std::vector<std::string>{ locals["card"]});
			param["mode"] = CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/State/mode")});
			param["put_card"] = CONCAT_ALL(std::vector<std::string>{ _Find(*global, "/PutCard/cardId")});

			auto x = __event__1006(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		if (__expr___EQ("TRUE", __expr___return_value())) {
			__func___assign(*global, excuteData, locals, "/State/action_card", CONCAT_ALL(std::vector<std::string>{ locals["card"]}), "TRUE");
			__func___assign(*global, excuteData, locals, "/State/action_state", CONCAT_ALL(std::vector<std::string>{ "PUT"}), "TRUE");
			result_change = true;
			return { result_change, CONCAT_ALL(std::vector<std::string>{ locals["card"]}) };

		}
		{
			std::map<std::string, std::string> param;
			param["i"] = __expr___add(parameters["i"], "1");
			param["n"] = parameters["n"];

			auto x = __event__4010(global, excuteData, param);
			if (x.first) { result_change = true; result = x.second; }
		}
		result_change = true;
		return { result_change, CONCAT_ALL(std::vector<std::string>{ __expr___return_value()}) };

	}

	return { result_change, result };
}
