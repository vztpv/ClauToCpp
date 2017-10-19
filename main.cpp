

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

// no fast lib!
#include <wiz/ClauText.h>

// " -> \"
std::string ToStr(const std::string& str)
{
	std::string result;

	wiz::load_data::Utility::ChangeStr(str, std::vector<std::string>{"\""}, std::vector<std::string>{"\\\""}, result);

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
				<< "\twiz::load_data::LoadData::LoadDataFromString(str, global);\n"
				<< "\tstd::cout << " << "__" << MainUT.GetUserTypeItem("$call")[0]->GetItem("id")[0].Get(0) << "(&global, excuteData) << std::endl;\n"
				<< "\treturn 0;\n"
				<< "}\n\n";
		}

		{ // part E
			const std::string main_name = MainUT.GetUserTypeItem("$call")[0]->GetItem("id")[0].Get(0);

			for (int i = 0; i < EventUT.size(); ++i) {
				const std::string event_name = EventUT[i]->GetItem("id")[0].Get(0);
				
				outFile << "INLINE std::string " << "__" << event_name << "(wiz::load_data::UserType"
					<< "* global, ExcuteData& ExcuteData";
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
