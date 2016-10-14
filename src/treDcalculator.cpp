#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <string>
//#include <regex>
#include <algorithm>

std::string exec(const char* cmd);
double samDregion(std::string s_Bamfile, std::string s_PeakCoordinates);

// call within writeReadsToVector.cpp after depthArr[] has been established 
void treDcalculator(double transferArr[][150], std::string s_bamPath, std::string s_geneinfo, double d_minDepth, double depthArr[], int j) 
{

/**
	std::string s_chr;
	std::string s_start;
	std::string s_end;
	std::string s_strand;

	// break down s_geneinfo string
	std::regex p ("(chr.*)+\t+(\\d*)+\t+(\\d*)+\t+(.*)");
	if (std::regex_match (s_geneinfo,p)) {
		std::smatch sm;  
		std::regex_match (s_geneinfo,sm,p);
		s_chr = sm[1];
		s_start = sm[2];
		s_end = sm[3];
		s_strand = sm[4];
	} else {}
**/


	std::string s_chrCommand = std::string("printf '") + s_geneinfo + std::string("' | cut -f 1");
	std::string s_startCommand = std::string("printf '") + s_geneinfo + std::string("' | cut -f 2");
	std::string s_endCommand = std::string("printf '") + s_geneinfo + std::string("' | cut -f 3");
	std::string s_strandCommand = std::string("printf '") + s_geneinfo + std::string("' | cut -f 4");

	std::string s_chr = exec(s_chrCommand.c_str());
	std::string s_start = exec(s_startCommand.c_str());
	std::string s_end = exec(s_endCommand.c_str());
	std::string s_strand = exec(s_strandCommand.c_str());

	// remove newline at end of line that find gives
	s_chr.erase(std::remove(s_chr.begin(), s_chr.end(), '\n'), s_chr.end());
	s_start.erase(std::remove(s_start.begin(), s_start.end(), '\n'), s_start.end());
	s_end.erase(std::remove(s_end.begin(), s_end.end(), '\n'), s_end.end());
	s_strand.erase(std::remove(s_strand.begin(), s_strand.end(), '\n'), s_strand.end());


	double d_genelength = atof(s_end.c_str()) - atof(s_start.c_str()); 
	double i_onepercent = d_genelength/100;

	int i_regionstart;
	int i_regionend;
	int i_upstart;
	int i_upend;
	int i_downstart;
	int i_downend;
	int i_flank = 1000;

	double geneArr[100] = {0}; 	// lowest index is TSS
	double upArr[25] = {0}; 	// lowest index is farthest from gene
	double downArr[25] = {0}; 	// lowest index is TES

	std::string s_geneCoordinates;
	std::string s_upCoordinates;
	std::string s_downCoordinates;
	
	double d_depth = 0;

	for (int i = 0; i < 25; i++) { // upstream
		if (s_strand == "-") {
			i_upstart = atoi(s_end.c_str()) + i_flank - (i_flank/25*i);
			i_upend = atoi(s_end.c_str()) + i_flank - (i_flank/25*(i+1));
			s_upCoordinates = s_chr + ":" + std::to_string(i_upend) + "-" + std::to_string(i_upstart);

			// CALCULATE DEPTH
			d_depth = (samDregion(s_bamPath, s_upCoordinates) / depthArr[j] * d_minDepth);
		}
		if (s_strand == "+") {
			i_upstart = atoi(s_start.c_str()) - i_flank + (i_flank/25*i);
			i_upend = atoi(s_start.c_str()) - i_flank + (i_flank/25*(i+1));
			s_upCoordinates = s_chr + ":" + std::to_string(i_upstart) + "-" + std::to_string(i_upend);

			// CALCULATE DEPTH
			d_depth = (samDregion(s_bamPath, s_upCoordinates) / depthArr[j] * d_minDepth);
		}
		upArr[i] = d_depth;
	}

	for (int i = 0; i < 25; i++) { // downstream
		if (s_strand == "-") {
			i_downstart = atoi(s_start.c_str()) - (i_flank/100*i);
			i_downend = atoi(s_start.c_str()) - (i_flank/100*(i+1));
			s_downCoordinates = s_chr + ":" + std::to_string(i_downend) + "-" + std::to_string(i_downstart);

			// CALCULATE DEPTH
			d_depth = (samDregion(s_bamPath, s_downCoordinates) / depthArr[j] * d_minDepth);
		}
		if (s_strand == "+") {
			i_downstart = atoi(s_end.c_str()) + (i_flank/100*i);
			i_downend = atoi(s_end.c_str()) + (i_flank/100*(i+1));
			s_downCoordinates = s_chr + ":" + std::to_string(i_downstart) + "-" + std::to_string(i_downend);

			// CALCULATE DEPTH
			d_depth = (samDregion(s_bamPath, s_downCoordinates) / depthArr[j] * d_minDepth);
		}
		downArr[i] = d_depth;
	}

	for (int i = 0; i < 100; i++) { // gene body
		if (s_strand == "-") {
			i_regionstart = atoi(s_end.c_str()) - i*i_onepercent;
			i_regionend = atoi(s_end.c_str()) - (i+1)*i_onepercent;
			s_geneCoordinates = s_chr + ":" + std::to_string(i_regionend) + "-" + std::to_string(i_regionstart);

			// CALCULATE DEPTH
			d_depth = (samDregion(s_bamPath, s_geneCoordinates) / depthArr[j] * d_minDepth);
		}	
		if (s_strand == "+") {
			i_regionstart = atoi(s_start.c_str()) + i*i_onepercent;
			i_regionend = atoi(s_start.c_str()) + (i+1)*i_onepercent;
			s_geneCoordinates = s_chr + ":" + std::to_string(i_regionstart) + "-" + std::to_string(i_regionend);

			// CALCULATE DEPTH
			d_depth = (samDregion(s_bamPath, s_geneCoordinates) / depthArr[j] * d_minDepth);			
		}
		geneArr[i] = d_depth;
	}

/** OLD XXX
	// write to normGeneVector
	for (int i = 0; i < 24; i++) // upstream
		normGeneVector.push_back(upArr[i]); 
	normGeneVector.push_back(upArr[24]); 

	for (int i = 0; i < 99; i++) // gene body
		normGeneVector.push_back(geneArr[i]); 
	normGeneVector.push_back(geneArr[99]); 

	for (int i = 0; i < 24; i++) // downstream
		normGeneVector.push_back(downArr[i]); 
	normGeneVector.push_back(downArr[24]); 
**/



	// write to normGeneVector
	for (int i = 0; i < 25; i++) // upstream
		transferArr[j][i] = upArr[i]; 

	for (int i = 0; i < 100; i++) // gene body
		transferArr[j][i+25] = geneArr[i]; 

	for (int i = 0; i < 25; i++) // downstream
		transferArr[j][i+125] = downArr[i]; 




}



