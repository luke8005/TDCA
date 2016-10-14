#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


std::string exec(const char* cmd);

// Returns a samtools depth double from a specified genome region and BAM file 
double samDregion(std::string s_Bamfile, std::string s_PeakCoordinates)
{
	std::string s_SamDepth ("samtools depth ");
	std::string s_RegionsFlag (" -r ");
	std::string s_Awk (" | awk '{sum+=$3} END {print sum}'");		
	std::string s_PeakDepth = s_SamDepth + s_Bamfile + s_RegionsFlag + s_PeakCoordinates + s_Awk;

	// Run samtools depth at a genome region and print to temp file

	std::string s_line;
	try {
		//std::system(s_PeakDepth.c_str());
		s_line = exec(s_PeakDepth.c_str());
	}
	catch(...){
		std::cerr << "Cannot access samtools" << std::endl;
		std::exit(0);
	}

	// Read temp file and convert to double
	//std::ifstream inBam("tempBam.txt");

	//std::getline(inBam, s_line);
	double d_line = atof(s_line.c_str());

	// Remove temp file
	//std::remove("tempBam.txt");

	return d_line;
}

/** OLD CODE: HARD CODED FILE

// Returns a samtools depth double from a specified genome region and BAM file 
double samDregion(std::string s_Bamfile, std::string s_PeakCoordinates)
{
	std::string s_SamDepth ("samtools depth ");
	std::string s_RegionsFlag (" -r ");
	std::string s_Awk (" | awk '{sum+=$3} END {print sum}' > tempBam.txt");		
	std::string s_PeakDepth = s_SamDepth + s_Bamfile + s_RegionsFlag + s_PeakCoordinates + s_Awk;

	// Run samtools depth at a genome region and print to temp file

	try {
		std::system(s_PeakDepth.c_str());
	}
	catch(...){
		std::cerr << "Cannot access samtools" << std::endl;
		std::exit(0);
	}

	// Read temp file and convert to double
	std::ifstream inBam("tempBam.txt");
	std::string s_line;
	std::getline(inBam, s_line);
	double d_line = atof(s_line.c_str());

	// Remove temp file
	std::remove("tempBam.txt");

	return d_line;
}

**/

