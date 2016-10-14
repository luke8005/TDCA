#include <cstdlib>
#include <iostream>
#include <string>
#include <regex>
#include <dirent.h>


std::string bedGetter(std::string s_dir, int i_iterator) 
{
	DIR *directory = opendir(s_dir.c_str());

	struct dirent *entry;
	std::string s_file;
	
	std::regex e (".*\\.bed");

	bool b_parseFiles = true;
	int i_counter = 0;

	while (b_parseFiles) {

		entry = readdir(directory);
		s_file = entry->d_name;

		if (std::regex_match (s_file,e))
			i_counter++;
		if (i_counter == (i_iterator + 1))
			b_parseFiles = false;
	}

	closedir(directory);

	return s_file;
}
