#include <iostream>
#include <string>
//#include <regex>
#include <dirent.h>
#include <iostream>  
#include <algorithm>

std::string exec(const char* cmd);

// count number of files with a certain type of extention in a directory
int extFileCount(std::string s_dir, int i_fileNumber, std::string s_extension)
{
	int i_Files = 0;
	DIR *directory = opendir(s_dir.c_str());

	struct dirent *entry;
	std::string FileArr[i_fileNumber];

	for (int i=0; i < i_fileNumber; i++) {
		entry = readdir(directory);
		FileArr[i] = entry->d_name;
	}

/**
	for (int i=0; i < i_fileNumber; i++) {
		std::string s (FileArr[i]);
		std::regex e (".*" + s_extension);

		if (std::regex_match (s,e)) {
			i_Files++;
		}
	}
**/

	std::string s_reg1 = "echo ";
	std::string s_reg2 = " | grep -o '";
	std::string s_reg3 = "'";

	for (int i=0; i < i_fileNumber; i++) {
		std::string s_command = s_reg1 + FileArr[i] + s_reg2 + s_extension + s_reg3;
		std::string s = exec(s_command.c_str());
		s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
		if (s != "") 
			i_Files++;
	}



	return i_Files;
}

