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

	for (int i = 0; i < vec.size(); ++i) {
		result = result && vec[i];
		if (vec[i] == false) {
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

INLINE std::string __snail(wiz::load_data::UserType* global, ExcuteData& excuteData);
INLINE std::string __init(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters);
INLINE std::string __init_Arr(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters);
INLINE std::string __init_Arr2(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters);
INLINE std::string __init_Arr3(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters);
INLINE std::string __doing(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters);
INLINE std::string __print(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters);
INLINE std::string __canMoveRight(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters);
INLINE std::string __canMoveDown(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters);
INLINE std::string __canMoveLeft(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters);
INLINE std::string __canMoveUp(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters);
INLINE std::string __moveRight(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters);
INLINE std::string __moveDown(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters);
INLINE std::string __moveLeft(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters);
INLINE std::string __moveUp(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters);

int main(void)
{
	ExcuteData excuteData;
	wiz::load_data::UserType global;
	std::string data =
		"COUNT = 0 ROW_MAX = 0 COL_MAX = 0 Pos =  { row = 1 col = 1  } value = 1";
	wiz::load_data::LoadData::LoadDataFromString(data, global);
	std::cout << __snail(&global, excuteData) << std::endl;

	
	return 0;
}

INLINE std::string __snail(wiz::load_data::UserType* global, ExcuteData& excuteData)
{
	std::map<std::string, std::string> locals;
	std::string result;
	std::string option;


	{
		std::map<std::string, std::string> param;
		param["col_max"] = CONCAT_ALL(std::vector<std::string>{ "300" });
		param["row_max"] = CONCAT_ALL(std::vector<std::string>{ "300" });

		__init(global, excuteData, param);
	}

	return result;
}
INLINE std::string __init(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	std::string option;


	__make(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ __concat_all(std::vector<std::string>{ "/", ".", "/", "Arr" })}), "TRUE");
	__assign(*global, excuteData, locals, "/./ROW_MAX", CONCAT_ALL(std::vector<std::string>{ parameters["row_max"]}), "TRUE");
	__assign(*global, excuteData, locals, "/./COL_MAX", CONCAT_ALL(std::vector<std::string>{ parameters["col_max"]}), "TRUE");
	{
		std::map<std::string, std::string> param;
		param["i"] = CONCAT_ALL(std::vector<std::string>{ "0" });

		__init_Arr(global, excuteData, param);
	}

	return result;
}
INLINE std::string __init_Arr(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	std::string option;

	locals["i"] = "";

	__assign(*global, excuteData, locals, "$local.i", CONCAT_ALL(std::vector<std::string>{ parameters["i"]}), "TRUE");
	while (__COMP_LT_EQ(locals["i"], __add("1", _Find(*global, "/./ROW_MAX")))) {
		if (__OR(__EQ("0", locals["i"]), __EQ(__add("1", _Find(*global, "/./ROW_MAX")), locals["i"]))) {
			__make(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ __concat_all(std::vector<std::string>{ "/", ".", "/", "Arr", "/", "_" })}), "TRUE");
			{
				std::map<std::string, std::string> param;
				param["i"] = CONCAT_ALL(std::vector<std::string>{ "0" });
				param["row"] = CONCAT_ALL(std::vector<std::string>{ locals["i"]});
				param["size"] = __add("1", _Find(*global, "/./COL_MAX"));

				__init_Arr2(global, excuteData, param);
			}
			__assign(*global, excuteData, locals, "$local.i", CONCAT_ALL(std::vector<std::string>{ __add("1", locals["i"])}), "TRUE");

		}
		else {
			__make(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ __concat_all(std::vector<std::string>{ "/", ".", "/", "Arr", "/", "_" })}), "TRUE");
			{
				std::map<std::string, std::string> param;
				param["i"] = CONCAT_ALL(std::vector<std::string>{ "0" });
				param["row"] = CONCAT_ALL(std::vector<std::string>{ locals["i"]});
				param["size"] = __add("1", _Find(*global, "/./COL_MAX"));

				__init_Arr3(global, excuteData, param);
			}
			__assign(*global, excuteData, locals, "$local.i", CONCAT_ALL(std::vector<std::string>{ __add("1", locals["i"])}), "TRUE");

		}

	}

	return result;
}
INLINE std::string __init_Arr2(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	std::string option;

	locals["row"] = "";
	locals["i"] = "";
	locals["size"] = "";

	__assign(*global, excuteData, locals, "$local.row", CONCAT_ALL(std::vector<std::string>{ parameters["row"]}), "TRUE");
	__assign(*global, excuteData, locals, "$local.i", CONCAT_ALL(std::vector<std::string>{ parameters["i"]}), "TRUE");
	__assign(*global, excuteData, locals, "$local.size", CONCAT_ALL(std::vector<std::string>{ parameters["size"]}), "TRUE");
	while (__COMP_LT_EQ(locals["i"], locals["size"])) {
		__insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ __concat_all(std::vector<std::string>{ "/", ".", "/", "Arr", "/", "$", "ut", locals["row"]})}), CONCAT_ALL(std::vector<std::string>{ "-1" }), "TRUE");
		__assign(*global, excuteData, locals, "$local.i", CONCAT_ALL(std::vector<std::string>{ __add("1", locals["i"])}), "TRUE");

	}

	return result;
}
INLINE std::string __init_Arr3(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	std::string option;

	locals["row"] = "";
	locals["i"] = "";
	locals["size"] = "";

	__assign(*global, excuteData, locals, "$local.row", CONCAT_ALL(std::vector<std::string>{ parameters["row"]}), "TRUE");
	__assign(*global, excuteData, locals, "$local.i", CONCAT_ALL(std::vector<std::string>{ parameters["i"]}), "TRUE");
	__assign(*global, excuteData, locals, "$local.size", CONCAT_ALL(std::vector<std::string>{ parameters["size"]}), "TRUE");
	while (__COMP_LT_EQ(locals["i"], locals["size"])) {
		if (__OR(__EQ(locals["i"], "0"), __EQ(locals["i"], __add("1", _Find(*global, "/./COL_MAX"))))) {
			__insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ __concat_all(std::vector<std::string>{ "/", ".", "/", "Arr", "/", "$", "ut", locals["row"]})}), CONCAT_ALL(std::vector<std::string>{ "-1" }), "TRUE");
			__assign(*global, excuteData, locals, "$local.i", CONCAT_ALL(std::vector<std::string>{ __add("1", locals["i"])}), "TRUE");

		}
		else {
			__insert(*global, excuteData, CONCAT_ALL(std::vector<std::string>{ __concat_all(std::vector<std::string>{ "/", ".", "/", "Arr", "/", "$", "ut", locals["row"]})}), CONCAT_ALL(std::vector<std::string>{ "0" }), "TRUE");
			__assign(*global, excuteData, locals, "$local.i", CONCAT_ALL(std::vector<std::string>{ __add("1", locals["i"])}), "TRUE");

		}

	}

	return result;
}
INLINE std::string __doing(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	std::string option;

	locals["x"] = "";

	__assign(*global, excuteData, locals, "$local.x", CONCAT_ALL(std::vector<std::string>{ parameters["k"]}), "TRUE");
	if (__EQ(locals["x"], "0")) {
		{
			std::map<std::string, std::string> param;

			__canMoveRight(global, excuteData, param);
		}
		if (("TRUE" == __return_value())) {
			{
				std::map<std::string, std::string> param;

				__moveRight(global, excuteData, param);
			}
			{
				std::map<std::string, std::string> param;
				param["k"] = CONCAT_ALL(std::vector<std::string>{ locals["x"]});

				__doing(global, excuteData, param);
				return result;
			}

		}
		else {
			__assign(*global, excuteData, locals, "$local.x", CONCAT_ALL(std::vector<std::string>{ "1" }), "TRUE");

		}

	}
	if (__EQ("1", locals["x"])) {
		{
			std::map<std::string, std::string> param;

			__canMoveDown(global, excuteData, param);
		}
		if (("TRUE" == __return_value())) {
			{
				std::map<std::string, std::string> param;

				__moveDown(global, excuteData, param);
			}
			{
				std::map<std::string, std::string> param;
				param["k"] = CONCAT_ALL(std::vector<std::string>{ locals["x"]});

				__doing(global, excuteData, param);
				return result;
			}

		}
		else {
			__assign(*global, excuteData, locals, "$local.x", CONCAT_ALL(std::vector<std::string>{ "2" }), "TRUE");

		}

	}
	if (__EQ("2", locals["x"])) {
		{
			std::map<std::string, std::string> param;

			__canMoveLeft(global, excuteData, param);
		}
		if (("TRUE" == __return_value())) {
			{
				std::map<std::string, std::string> param;

				__moveLeft(global, excuteData, param);
			}
			{
				std::map<std::string, std::string> param;
				param["k"] = CONCAT_ALL(std::vector<std::string>{ locals["x"]});

				__doing(global, excuteData, param);
				return result;
			}

		}
		else {
			__assign(*global, excuteData, locals, "$local.x", CONCAT_ALL(std::vector<std::string>{ "3" }), "TRUE");

		}

	}
	if (__EQ("3", locals["x"])) {
		{
			std::map<std::string, std::string> param;

			__canMoveUp(global, excuteData, param);
		}
		if (("TRUE" == __return_value())) {
			{
				std::map<std::string, std::string> param;

				__moveUp(global, excuteData, param);
			}
			{
				std::map<std::string, std::string> param;
				param["k"] = CONCAT_ALL(std::vector<std::string>{ locals["x"]});

				__doing(global, excuteData, param);
				return result;
			}

		}
		else {
			__assign(*global, excuteData, locals, "$local.x", CONCAT_ALL(std::vector<std::string>{ "0" }), "TRUE");
			{
				std::map<std::string, std::string> param;

				__canMoveRight(global, excuteData, param);
			}
			if (("TRUE" == __return_value())) {
				{
					std::map<std::string, std::string> param;
					param["k"] = CONCAT_ALL(std::vector<std::string>{ locals["x"]});

					__doing(global, excuteData, param);
					return result;
				}

			}
			else {

			}

		}

	}

	return result;
}
INLINE std::string __print(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	std::string option;


	if (__AND(__COMP_GT_(parameters["start_row"], _Find(*global, "/./ROW_MAX")), __COMP_GT_EQ(parameters["start_col"], _Find(*global, "/./COL_MAX")))) {

	}
	if (__COMP_LT_EQ(parameters["start_col"], _Find(*global, "/./COL_MAX"))) {


		{
			std::map<std::string, std::string> param;
			param["start_col"] = __add("1", parameters["start_col"]);
			param["start_row"] = parameters["start_row"];

			__print(global, excuteData, param);
			return result;
		}

	}
	if (__COMP_LT_(parameters["start_row"], _Find(*global, "/./ROW_MAX"))) {

		{
			std::map<std::string, std::string> param;
			param["start_col"] = CONCAT_ALL(std::vector<std::string>{ "1" });
			param["start_row"] = __add("1", parameters["start_row"]);

			__print(global, excuteData, param);
			return result;
		}

	}

	return result;
}
INLINE std::string __canMoveRight(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	std::string option;


	if (__AND_ALL(std::vector<bool>{__EQ("0", __element(*global, __concat_all(std::vector<std::string>{ "/", ".", "/", "Arr", "/", "$", "ut", _Find(*global, "/./Pos/row")}), __add("1", _Find(*global, "/./Pos/col")))), __NOTEQ("0", __element(*global, __concat_all(std::vector<std::string>{ "/", ".", "/", "Arr", "/", "$", "ut", __add("-1", _Find(*global, "/./Pos/row"))}), _Find(*global, "/./Pos/col")))})) {

	}

	return result;
}
INLINE std::string __canMoveDown(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	std::string option;


	if (__AND_ALL(std::vector<bool>{__EQ("0", __element(*global, __concat_all(std::vector<std::string>{ _Find(*global, "/."), "/", "Arr", "/", "$", "ut", __add("1", _Find(*global, "/./Pos/row"))}), _Find(*global, "/./Pos/col"))), __NOTEQ("0", __element(*global, __concat_all(std::vector<std::string>{ _Find(*global, "/."), "/", "Arr", "/", "$", "ut", __add("-1", _Find(*global, "/./Pos/row"))}), _Find(*global, "/./Pos/col"))), __NOTEQ("0", __element(*global, __concat_all(std::vector<std::string>{ _Find(*global, "/."), "/", "Arr", "/", "$", "ut", _Find(*global, "/./Pos/row")}), __add("1", _Find(*global, "/./Pos/col"))))})) {

	}

	return result;
}
INLINE std::string __canMoveLeft(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	std::string option;


	if (__EQ("0", __element(*global, __concat_all(std::vector<std::string>{ _Find(*global, "/."), "/", "Arr", "/", "$", "ut", __add("-1", _Find(*global, "/./Pos/row"))}), __add("-1", _Find(*global, "/./Pos/col"))))) {

	}

	return result;
}
INLINE std::string __canMoveUp(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	std::string option;


	if (__AND(__EQ("0", __element(*global, __concat_all(std::vector<std::string>{ _Find(*global, "/."), "/", "Arr", "/", "$", "ut", __add("-1", _Find(*global, "/./Pos/row"))}), _Find(*global, "/./Pos/col"))), __AND(__NOTEQ("0", __element(*global, __concat_all(std::vector<std::string>{ _Find(*global, "/."), "/", "Arr", "/", "$", "ut", __add("1", _Find(*global, "/./Pos/row"))}), _Find(*global, "/./Pos/col"))), __NOTEQ("0", __element(*global, __concat_all(std::vector<std::string>{ _Find(*global, "/."), "/", "Arr", "/", "$", "ut", _Find(*global, "/./Pos/row")}), __add("-1", _Find(*global, "/./Pos/col"))))))) {

	}

	return result;
}
INLINE std::string __moveRight(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	std::string option;



	return result;
}
INLINE std::string __moveDown(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	std::string option;



	return result;
}
INLINE std::string __moveLeft(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	std::string option;



	return result;
}
INLINE std::string __moveUp(wiz::load_data::UserType* global, ExcuteData& excuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;
	std::string option;



	return result;
}
