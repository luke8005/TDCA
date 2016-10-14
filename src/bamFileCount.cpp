#include <iostream>
#include <string>
//#include <regex>
#include <dirent.h>

std::string exec(const char* cmd);

// count number of bam files in a directory
int bamFileCount(std::string s_dir, int i_fileNumber)
{
	int i_bamFiles = 0;
	DIR *directory = opendir(s_dir.c_str());

	struct dirent *entry;
	std::string bamFileArr[i_fileNumber];

	for (int i=0; i < i_fileNumber; i++)
	{
		entry = readdir(directory);
		bamFileArr[i] = entry->d_name;
	}
/**
	for (int i=0; i < i_fileNumber; i++) {
		std::string s (bamFileArr[i]);
		std::regex e (".*+_(\\d*)+\\.bam");

		if (std::regex_match (s,e)) {
			i_bamFiles++;
		}
	}
**/
	
	std::string s_reg1 = "echo ";
	std::string s_reg2 = " | grep -o '_[0-9]*.bam$' | grep -o '[0-9]*'";

	for (int i=0; i < i_fileNumber; i++) {
		std::string s_command = s_reg1 + bamFileArr[i] + s_reg2;
		std::string s = exec(s_command.c_str());
		if (s != "") 
			i_bamFiles++;
	}

	return i_bamFiles;
}
