#include <cstdlib>
#include <iostream>
#include <string>
//#include <regex>
//#include <dirent.h>
#include <algorithm>

std::string exec(const char* cmd);

std::string bamGetter(std::string s_dir, int i_turnoverTime) 
{

/**
	DIR *directory = opendir(s_dir.c_str());

	struct dirent *entry;
	std::string s_bamFile;
	
	std::regex e (".*_" + s_turnoverTime + "\\.bam");

	bool b_parseFiles = true;



	while (b_parseFiles) {

		entry = readdir(directory);
		s_bamFile = entry->d_name;

		if (std::regex_match (s_bamFile,e))
			b_parseFiles = false;
	}

	closedir(directory);
	return s_bamFile;
**/

	std::string s_turnoverTime = std::to_string(i_turnoverTime);

	std::string s_reg1 = "find ";
	std::string s_reg2 = " -regex '.*_";
	std::string s_reg3 = ".bam'";

	std::string s_command = s_reg1 + s_dir + s_reg2 + std::to_string(i_turnoverTime) + s_reg3;

	// remove newline at end of line that find gives
	std::string s_bamFile = exec(s_command.c_str());
	s_bamFile.erase(std::remove(s_bamFile.begin(), s_bamFile.end(), '\n'), s_bamFile.end());

	return s_bamFile;


}
