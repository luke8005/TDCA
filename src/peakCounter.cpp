#include <fstream> 
#include <string>

int peakCounter(std::string s_bed) 
{
	int i_peakNumber = 0;
	
	std::ifstream inBed(s_bed); // user specified bed file
	std::string line;

	while (std::getline(inBed, line, '\n')) {
		i_peakNumber++;
	}

	return i_peakNumber;
}
