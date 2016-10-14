#include <cstdlib>
#include <iostream>
#include <string>
//#include <regex>
#include <algorithm>

std::string exec(const char* cmd);

// converts a line in a bed file to a chromosome coordinate readable by samtools depth
std::string bedToCoordinates(std::string bedLine)
{

/**
	std::string s_Chr;
	std::string s_Start;
	std::string s_End;

	try {
		std::regex e ("(chr.*)+\t+(\\d*)+\t+(\\d*)");
		if (std::regex_match (bedLine,e))
		{
			std::smatch sm;  
			std::regex_match (bedLine,sm,e);
			s_Chr = sm[1];
			s_Start = sm[2];
			s_End = sm[3];
		}
	}
	catch(...){
		std::cerr << "Bed file doesn't seem to be in standard format." << std::endl;
		std::exit(0);
	}

	std::string s_PeakCoordinates = s_Chr + ":" + s_Start + "-" + s_End;
	return s_PeakCoordinates;
**/

	std::string s_chrCommand = std::string("printf '") + bedLine + std::string("' | cut -f 1");
	std::string s_startCommand = std::string("printf '") + bedLine + std::string("' | cut -f 2");
	std::string s_endCommand = std::string("printf '") + bedLine + std::string("' | cut -f 3");

	std::string s_Chr = exec(s_chrCommand.c_str());
	std::string s_Start = exec(s_startCommand.c_str());
	std::string s_End = exec(s_endCommand.c_str());

	// remove newline at end of line that find gives
	s_Chr.erase(std::remove(s_Chr.begin(), s_Chr.end(), '\n'), s_Chr.end());
	s_Start.erase(std::remove(s_Start.begin(), s_Start.end(), '\n'), s_Start.end());
	s_End.erase(std::remove(s_End.begin(), s_End.end(), '\n'), s_End.end());

	std::string s_PeakCoordinates = s_Chr + ":" + s_Start + "-" + s_End;
	return s_PeakCoordinates;
}












