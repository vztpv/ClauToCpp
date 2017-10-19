// Goal : clautext -> cpp

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <map>

// no fast lib!
#include <wiz/ClauText.h>

#define INLINE inline

wiz::StringBuilder builder(102400);

INLINE std::string _add(const std::string& s1, const std::string& s2)
{
	return std::to_string(std::stoi(s1) + std::stoi(s2)); // change to int, double, ..
}
INLINE bool _COMP_LT_EQ(const std::string& s1, const std::string& s2)
{
	return wiz::load_data::Utility::Compare(s1, s2, &builder) == "< 0";
}
INLINE bool _OR(const bool x, const bool y)
{
	return x || y;
}
INLINE bool _AND(const bool x, const bool y)
{
	return x && y;
}
INLINE bool _EQ(const std::string& x, const std::string& y)
{
	return x == y;
}
// find "/~"
INLINE std::string _Find(wiz::load_data::UserType& global, const std::string& str) {
	return wiz::load_data::Find(&global, str, &builder);
} 
INLINE std::string _concat_all(const std::vector<std::string>& vec) // chk for -> no inline?
{
	std::string result;

	for (int i = 0; i < vec.size(); ++i) {
		result += vec[i];
	}
	return result;
}
// todo - add ExcuteData parameter?
INLINE std::string _make(wiz::load_data::UserType& global, const ExcuteData& data, const std::string& str, const std::string& condition)
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
INLINE std::string _assign(wiz::load_data::UserType& global, const ExcuteData& excuteData, std::map<std::string, std::string>& locals, const std::string& dir, const std::string& value, const std::string& condition)
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
INLINE std::string _insert(wiz::load_data::UserType& global, const ExcuteData& excuteData, const std::string& dir, const std::string& value, const std::string& condition)
{
	wiz::load_data::LoadData::AddData(global, dir, value, condition, excuteData, &builder);

	return "";
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
	wiz::load_data::LoadData::LoadDataFromString(str, global);
	std::cout << __snail(&global, excuteData) << std::endl;
	return 0;
}

INLINE std::string __snail(wiz::load_data::UserType* global, ExcuteData& ExcuteData)
{
	std::map<std::string, std::string> locals;
	std::string result;

}
INLINE std::string __init(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;

}
INLINE std::string __init_Arr(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;

	locals["i"] = "";
}
INLINE std::string __init_Arr2(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;

	locals["row"] = "";
	locals["i"] = "";
	locals["size"] = "";
}
INLINE std::string __init_Arr3(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;

	locals["row"] = "";
	locals["i"] = "";
	locals["size"] = "";
}
INLINE std::string __doing(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;

	locals["x"] = "";
}
INLINE std::string __print(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;

}
INLINE std::string __canMoveRight(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;

}
INLINE std::string __canMoveDown(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;

}
INLINE std::string __canMoveLeft(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;

}
INLINE std::string __canMoveUp(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;

}
INLINE std::string __moveRight(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;

}
INLINE std::string __moveDown(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;

}
INLINE std::string __moveLeft(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;

}
INLINE std::string __moveUp(wiz::load_data::UserType* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters)
{
	std::map<std::string, std::string> locals;
	std::string result;

}
