

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

// no fast lib!
#include <wiz/ClauText.h>

// " -> \"
inline std::string ToStr(const std::string& str)
{
	std::string result;

	wiz::load_data::Utility::ChangeStr(str, std::vector<std::string>{"\""}, std::vector<std::string>{"\\\""}, result);

	return result;
}

// need to rename!
void Do(const wiz::load_data::UserType& someUT, wiz::load_data::UserType& result)
{
	int it_count = 0;
	int ut_count = 0;
	for (int i = 0; i < someUT.GetIListSize(); ++i) {
		if (someUT.IsItemList(i)) {
			// chk case $concat_all = { x = 3 } => error?
			const std::string data = someUT.GetItemList(it_count).Get(0);

			if (wiz::String::startsWith(data, "$local.")) {
				result.AddItem("", std::string("") + "locals[\"" + ToStr(data.substr(7)) + "\"]");
				result.PushComment("1");
			}
			else if (wiz::String::startsWith(data, "$parameter.")) {
				result.AddItem("", std::string("") + "parameters[\"" + ToStr(data.substr(11)) + "\"]");
				result.PushComment("1");
			}
			else if (wiz::String::startsWith(data, "/") && data.size() > 1) {
				//// todo - chk /./ABC/$parameter.j - do not allow?
				// concat_all("/", ".", "/", "ABC", "/", parameters["j"]) // chk exist?
				result.AddItem("", std::string("") + "_Find(*global, \"" + ToStr(data) + "\")");
				result.PushComment("1");
			}
			else {
				result.AddItem(ToStr(someUT.GetItemList(it_count).GetName()), ToStr(data) );
				result.PushComment("2");
			}
			it_count++;
		}
		else {
			result.AddUserTypeItem(wiz::load_data::UserType(someUT.GetUserTypeList(ut_count)->GetName()));
			result.PushComment("3");

			Do(*someUT.GetUserTypeList(ut_count), *result.GetUserTypeList(ut_count));
			ut_count++;
		}
	}

}

std::string PrintSomeUT(wiz::load_data::UserType& someUT, int depth = 0)
{
	std::string result;

	int it_count = 0;
	int ut_count = 0;
	for (int i = 0; i < someUT.GetIListSize(); ++i) {
		if (someUT.IsItemList(i)) {
			// chk case $concat_all = { x = 3 } => error?
			const std::string data = someUT.GetItemList(it_count).Get(0);
			const std::string name = someUT.GetItemList(it_count).GetName();

			if (name.empty()) {
				if (someUT.GetCommentList(i) != "2") {
					result += data;
				}
				else {
					result += "\"" + (data)+"\"" + " ";
				}
			}
			else {
				if (someUT.GetCommentList(i) != "2") {
					result += data;
				}
				else {
					result += "\"" + (name)+" = " + (data)+"\"";
				}
			}
			
			if (i < someUT.GetIListSize() - 1) {
				result += " , ";
			}

			
			it_count++;	
		}
		else {
			//// todo - $ removal!!
			result += "__" + someUT.GetUserTypeList(ut_count)->GetName() + "(";
			result += PrintSomeUT(*someUT.GetUserTypeList(ut_count), depth + 1);
			result += ")";

			
			if (i < someUT.GetIListSize() - 1) {
				result += " , ";
			}
			ut_count++;
		}		
	}

	return result;
}

std::string ConvertFunction(wiz::load_data::UserType& eventUT)
{
	std::string result;
	
	for (int i = 0; i < eventUT.GetUserTypeListSize(); ++i) {
		const std::string functionName = eventUT.GetUserTypeList(i)->GetName();
		if (functionName == "$local" ||
			functionName == "$parameter" ||
			functionName == "$option")
		{
			continue;
		}

		if (functionName == "$assign") {
			result += "\t__assign(*global, excuteData, locals, \"";
			result += ToStr(eventUT.GetUserTypeList(i)->GetItemList(0).Get(0));
			result += "\"";
			result += ", ";

			//// tobool4? tobool3?
			// chk local
			// chk parameter
			// chk /./test
			// chk functions. $test
			wiz::load_data::UserType* ut = eventUT.GetUserTypeList(i)->GetUserTypeList(0);
			wiz::load_data::UserType resultUT;
			// for item, item in ut->GetUserTypeList(0), ... 
			Do(*ut, resultUT);

			result += "CONCAT_ALL(std::vector<std::string>{ " + PrintSomeUT(resultUT) + "})";

			if (eventUT.GetUserTypeList(i)->GetUserTypeListSize() >= 2) {
				wiz::load_data::UserType* _ut = eventUT.GetUserTypeList(i)->GetUserTypeList(1);
				wiz::load_data::UserType _resultUT;
				// for item, item in ut->GetUserTypeList(0), ... 
				Do(*_ut, _resultUT);

				result += ", CONCAT_ALL(std::vector<std::string>{ " + PrintSomeUT(resultUT) + "})";
			}
			else {
				result += ", \"TRUE\"";
			}
			// chk condition! - defualt "TRUE" ?, chk size!
			result += ");";

			result += "\n";
		}
		else if (functionName == "$while") {
			result += "\twhile(";
			wiz::load_data::UserType* ut = eventUT.GetUserTypeList(i)->GetUserTypeList(0);
			wiz::load_data::UserType resultUT;
			// for item, item in ut->GetUserTypeList(0), ... 
			Do(*ut, resultUT);

			result += "\"TRUE\" == CONCAT_ALL(std::vector<std::string>{ " + PrintSomeUT(resultUT) + "}) ? true : false";
			result += ") {\n";
			result += "\t";
			result += ConvertFunction(*eventUT.GetUserTypeList(i)->GetUserTypeList(1));
			result += "\n";
			result += "\t}\n";
		}

	}

	return result;
}

int main(int argc, char* argv[])
{
	try {
		wiz::load_data::UserType MainUT;
		std::vector<wiz::load_data::UserType*> EventUT;
		wiz::load_data::UserType global;
		std::string name;
		const std::string outputName = "test.cpp";
		std::ofstream outFile;

		outFile.open(outputName);
		if (false == outFile.is_open()) {
			return 1;
		}

		{ // part A
			std::ifstream inFile;
			inFile.open("functionA.txt");
			if (false == outFile.is_open()) {
				outFile.close();
				return 2;
			}

			// copy data from infile to outfile.
			std::string temp;

			while (std::getline(inFile, temp)) {
				outFile << temp << "\n";
			}

			// close
			inFile.close();
		}

		{ // part B
			if (1 == argc) {
				std::cout << "fileName : ";
				std::getline(std::cin, name);
			}
			else {
				name = std::string(argv[1]);
			}
			wiz::load_data::LoadData::LoadDataFromFile(name, global);
		}

		{ // part C
			auto x = global.GetCopyUserTypeItem("Main");
			if (x.size() != 1) {
				return -1; //
			}
			MainUT = *x[0];
			EventUT = global.GetCopyUserTypeItem("Event");

			global.RemoveUserTypeList("Main");
			global.RemoveUserTypeList("Event");

			// user defined functions declaration?
			const std::string main_name = MainUT.GetUserTypeItem("$call")[0]->GetItem("id")[0].Get(0);
			outFile << "INLINE std::string " << "__" << main_name << "(wiz::load_data::UserType"
				<< "* global, ExcuteData& excuteData);" << "\n";
			for (int i = 0; i < EventUT.size(); ++i) {
				const std::string event_name = EventUT[i]->GetItem("id")[0].Get(0);
				if (event_name == main_name) {
					continue;
				}
				outFile << "INLINE std::string " << "__" << event_name << "(wiz::load_data::UserType"
					<< "* global, ExcuteData& ExcuteData, std::map<std::string, std::string>& parameters);" << "\n";
			}
		}

		{ // part D
			outFile << "\n" << "int main(void)\n"
				<< "{\n"
				<< "\tExcuteData excuteData;\n"
				<< "\twiz::load_data::UserType global;\n"
				<< "\tstd::string data =\n"
				<< "\t\"" << global.ToString() << "\"" << ";\n"
				<< "\twiz::load_data::LoadData::LoadDataFromString(data, global);\n"
				<< "\tstd::cout << " << "__" << MainUT.GetUserTypeItem("$call")[0]->GetItem("id")[0].Get(0) << "(&global, excuteData) << std::endl;\n"
				<< "\treturn 0;\n"
				<< "}\n\n";
		}

		{ // part E
			const std::string main_name = MainUT.GetUserTypeItem("$call")[0]->GetItem("id")[0].Get(0);

			for (int i = 0; i < EventUT.size(); ++i) {
				const std::string event_name = EventUT[i]->GetItem("id")[0].Get(0);
				
				outFile << "INLINE std::string " << "__" << event_name << "(wiz::load_data::UserType"
					<< "* global, ExcuteData& excuteData";
				if (event_name != main_name) {
					outFile << ", std::map<std::string, std::string>& parameters";
				}
				outFile << ")" << "\n"
				<< "{\n"
				<< "\tstd::map<std::string, std::string> locals;\n"
				<< "\tstd::string result;\n\n";

				// set locals
				{
					auto locals = EventUT[i]->GetUserTypeItem("$local");
					if (!locals.empty()) {
						for (int j = 0; j < locals[0]->GetItemListSize(); ++j) {
							outFile << "\tlocals[\"" << ToStr(locals[0]->GetItemList(j).Get(0)) << "\"] = \"\";\n";
						}
					}
				}
				// convertedFunction = ConvertFunction(*global, ut, excutedata, locals, parameters);
					// $local = { }, $option = { } $parameter = { } => pass!
				outFile << "\n" << ConvertFunction(*EventUT[i]) << "\n";

				outFile << "}\n";
 			}
		}

		// close
		outFile.close();
	}
	catch (...) {
		std::cout << "no expected result" << std::endl;
	}

	return 0;
}
