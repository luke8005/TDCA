#include <cstdlib>
#include <iostream>
#include <string>
//#include <regex>
#include <dirent.h>
#include <algorithm>
#include <string>

std::string exec(const char* cmd);

bool genomeGetter(std::string s_dir, std::string s_genome, int i_fileNumber) 
{
/**
	DIR *directory = opendir(s_dir.c_str());

	struct dirent *entry;
	std::string s_file;

	std::regex e (s_genome);

	bool b_found = false;

	for (int i = 0; i < i_fileNumber; i++) {

		entry = readdir(directory);
		s_file = entry->d_name;

		if (std::regex_match (s_file,e))
			b_found = true;
	}

	closedir(directory);

	return b_found;
**/
	bool b_found = true;

	std::string s_command = std::string("find ") + s_dir + std::string(" -regex '.*") + s_genome + std::string("'");
	std::string s_file = exec(s_command.c_str());

	// remove newline at end of line that find gives
	s_file.erase(std::remove(s_file.begin(), s_file.end(), '\n'), s_file.end());

	std::string s_intputFile = s_dir + s_genome;	
	
	if (s_intputFile.compare(s_file) != 0)
		b_found = false;


	return b_found;
}

