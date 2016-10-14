#include <iostream>
#include <string>
#include <dirent.h>

// count number of files in a directory
int fileCount(std::string s_dir)
{
	DIR *directory = opendir(s_dir.c_str());
	if( directory == NULL ) //check if directory is real
	{
		perror(s_dir.c_str());
		exit(0);
	}
	struct dirent *entry;
	int i_fileNumber = 0;
	while( NULL != ( entry = readdir(directory) ) )
	{
		i_fileNumber++;
	}
	return i_fileNumber;
}
