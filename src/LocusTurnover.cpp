#include <iostream>
#include<string>
//#include <regex>
#include <vector>
#include "LocusTurnover.h"
#include <algorithm>

std::string exec(const char* cmd);

// constructor for LocusTurnover class, takes the loci name with the preset chr:bp-bp format as well as number of time pts
LocusTurnover::LocusTurnover(std::string l, int t)
{
	//allocates the appropriate amount of elements to the vectors so no need for push_back
	i_numTimePts = t;
	turnoverArr.reserve(i_numTimePts);
	s_locus = l;

/**
	std::regex e ("(chr.*)+\\:+(\\d*)+\\-+(\\d*)");
	//std::regex e ("(*) + \\: + (*) + \\- + (*)");
	std::smatch sm;
	std::regex_match (s_locus,sm,e);
	s_chr = sm[1];
	s_start = sm[2];
	s_end = sm[3]; 
**/

	std::string s_chrCommand = std::string("echo ") + s_locus + std::string(" | grep -o 'chr.*:'");
	std::string s_startCommand = std::string("echo ") + s_locus + std::string(" | grep -o ':.*-'");
	std::string s_endCommand = std::string("echo ") + s_locus + std::string(" | grep -o '\\-.*'");

	std::string s_chrTemp = exec(s_chrCommand.c_str());
	std::string s_startTemp = exec(s_startCommand.c_str());
	std::string s_endTemp = exec(s_endCommand.c_str());

	// remove newline at end of line that find gives
	s_chrTemp.erase(std::remove(s_chrTemp.begin(), s_chrTemp.end(), '\n'), s_chrTemp.end());
	s_startTemp.erase(std::remove(s_startTemp.begin(), s_startTemp.end(), '\n'), s_startTemp.end());
	s_endTemp.erase(std::remove(s_endTemp.begin(), s_endTemp.end(), '\n'), s_endTemp.end());

	// remove first and/or last characters of retreived strings
	s_chr = s_chrTemp.substr(0, s_chrTemp.size()-1);
	s_startTemp.erase(0, 1);
	s_start = s_startTemp.substr(0, s_startTemp.size()-1);
	s_end = s_endTemp.erase(0, 1); 



}

//must pass an array with the reads at different time pts as well as number of time pts
void LocusTurnover::analysis(void)
{
	//for simple last timepoint and first timepoint difference 
	d_overallTurnoverStartEnd = abs(turnoverArr[(i_numTimePts-1)] - turnoverArr[0]); 

	//determines if turnover is forward or reverse based on first and last time pt reads
	if (turnoverArr[(i_numTimePts-1)] > turnoverArr[0]) {
		b_forw_rvrs = 1;
      } else {
		b_forw_rvrs = 0;
	}  

	//gives the overall min as the first time pt just as a starting point for comparison during the loop
	d_overallMin = turnoverArr[0]; 
	i_overallMinIndex = 0;
	d_overallMax = turnoverArr[(i_numTimePts - 1)]; //same but for the max
	i_overallMaxIndex = i_numTimePts - 1;
	d_maxTurnover = abs(turnoverArr[1] - turnoverArr[0]); //same but for the maxTurnover
     
	//iterates the reads of the time pts to find max and min num of reads and max turnover between two time points
	for (int i = 0; i < i_numTimePts; i++) {
		if (turnoverArr[i] > d_overallMax) { 
			d_overallMax = turnoverArr[i];
			i_overallMaxIndex = i;
		}
		if(turnoverArr[i] < d_overallMin) { 
			d_overallMin = turnoverArr[i];
			i_overallMinIndex = i;
		}
		if  (i != 1 && abs(turnoverArr[i] - turnoverArr[i-1]) > d_maxTurnover) {
			d_maxTurnover = abs(turnoverArr[i] - turnoverArr[(i-1)]);
		}
	}
     
	//gives the overall turnover using the overall max and min
	d_overallTurnoverMaxMin = d_overallMax - d_overallMin; 
} 







 
