#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string exec(const char* cmd);

// Returns a samtools depth double from a specified BAM file 
double samDtotal(std::string s_Bamfile)
{
	std::string s_SamDepth ("samtools depth ");
	std::string s_Awk (" | awk '{sum+=$3} END {print sum}'");		
	std::string s_depth = s_SamDepth + s_Bamfile + s_Awk;

	// Run samtools depth and print to temp file
	// XXX check if s_bamfile has an index file XXX

	std::string s_line;
	try {
		s_line = exec(s_depth.c_str());
	}
	catch(...){
		std::cerr << "Cannot access samtools or bedfile not in standard format" << std::endl;
		std::exit(0);
	}

	// Read temp file and convert to double
	//std::ifstream inBam("tempBam.txt");
	//std::string s_line;
	//std::getline(inBam, s_line);
	double d_line = atof(s_line.c_str());

	// Remove temp file
	//std::remove("tempBam.txt");

	return d_line;
}





/** OLD CODE: HARD CODED FILE

// Returns a samtools depth double from a specified BAM file 
double samDtotal(std::string s_Bamfile)
{
	std::string s_SamDepth ("samtools depth ");
	std::string s_Awk (" | awk '{sum+=$3} END {print sum}' > tempBam.txt");		
	std::string s_depth = s_SamDepth + s_Bamfile + s_Awk;

	// Run samtools depth and print to temp file

	// XXX check if s_bamfile has an index file XXX

	try {
		std::system(s_depth.c_str());
	}
	catch(...){
		std::cerr << "Cannot access samtools or bedfile not in standard format" << std::endl;
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
