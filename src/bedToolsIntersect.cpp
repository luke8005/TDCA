#include <string>
#include <iostream>
#include <vector>
#include <regex>
#include <fstream> 

std::string exec(const char* cmd);

// gets fourth column (1 or 0; hit or no hit) after bedtools intersect -c
void bedToolsIntersect(std::string s_genomePath, std::string s_bed, std::vector<std::string> &featureVector, int i_loop)
{

	std::string s_bedI ("bedtools intersect -a ");
	std::string s_dashB (" -b ");	
	std::string s_bedToolsCommand = s_bedI + s_bed + s_dashB + s_genomePath + " -c > bedToolsTemp" + std::to_string(i_loop) + ".bed";

	try {
		std::system(s_bedToolsCommand.c_str());
	}
	catch(...){
		std::cerr << "Cannot access bedtools or issue with input" << std::endl;
		std::exit(0);
	}

	
	std::ifstream inFeature("bedToolsTemp" + std::to_string(i_loop) + ".bed"); 
	std::string line;
	int i_iterator = 0;

	while (std::getline(inFeature, line, '\n')) {

		std::string s_command = std::string("printf '") + line + std::string("' | cut -f 4");
		std::string s_hit = exec(s_command.c_str());

		s_hit.erase(std::remove(s_hit.begin(), s_hit.end(), '\n'), s_hit.end());

		featureVector[i_iterator] = s_hit;
		i_iterator++;

	}
	std::string s_tempfile = "bedToolsTemp" + std::to_string(i_loop) + ".bed";
	std::remove(s_tempfile.c_str());
}














