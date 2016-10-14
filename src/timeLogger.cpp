#include <iostream>
#include <string>
//#include <regex>
#include <dirent.h>
#include <algorithm>

std::string exec(const char* cmd);

// make an array of turnover times used based on regex bam file names
int timeLogger(int *arr, std::string s_dir, int i_fileNumber)
{
	DIR *directory = opendir(s_dir.c_str());
	struct dirent *entry;
	std::string bamFileArr[i_fileNumber];

	for (int i=0; i < i_fileNumber; i++)
	{
		entry = readdir(directory);
		bamFileArr[i] = entry->d_name;
	}

/**
	int k = 0;
	for (int i=0; i < i_fileNumber; i++) {
		std::string s (bamFileArr[i]);
		std::regex e (".*+_(\\d*)+\\.bam");

		if (std::regex_match (s,e))
		{
			std::smatch sm;  
			std::regex_match (s,sm,e);
			std::string s = sm[1];
			int j = atoi(s.c_str());
			arr[k] = j;
			k++;
		}
	}
	return 0;
**/

	int k = 0;
	for (int i=0; i < i_fileNumber; i++) {
		std::string s_command = std::string("echo ") + bamFileArr[i] + std::string(" | grep -o '_[0-9]*.bam$' | grep -o '[0-9]*'");
		std::string s_time = exec(s_command.c_str());
		// remove newline at end of line that find gives
		s_time.erase(std::remove(s_time.begin(), s_time.end(), '\n'), s_time.end());

		try {

			if (s_time != "") {
				int j = atoi(s_time.c_str());
				arr[k] = j;
				k++;
			}
		} catch(...) {
			std::cerr << "Bam file: " << bamFileArr[i] << "is not in proper name format." << std::endl;
			std::exit(0);
		}
	}
	return 0;








}
