#include <string>
#include <iostream>
#include <vector>
//#include <regex>
#include <fstream> 
#include <algorithm>

std::string exec(const char* cmd);

std::string geneToCoordinates(std::string s_gene, std::string s_genelistFile)
{

	std::string s_grep = "grep '" + s_gene + "' " + s_genelistFile + " > grep.gene.txt";

	try {
		std::system(s_grep.c_str());
	}
	catch(...){
		std::cerr << "Grep not functioning." << std::endl;
		std::exit(0);
	}

	std::ifstream inList("grep.gene.txt"); 
	std::string s_line;

	//std::string s_foundGene;
	//std::string s_chr;
	//std::string s_start;
	//std::string s_end;
	//std::string s_strand;	

	std::string s_coordinates;

/**
	std::regex e ("(.*)+\t+(chr.*)+\t+(\\d*)+\t+(\\d*)+\t+(\\+)\t+.*");
	std::regex n ("(.*)+\t+(chr.*)+\t+(\\d*)+\t+(\\d*)+\t+(\\-)\t+.*");

	while (std::getline(inList, s_line, '\n')) {
		if (std::regex_match (s_line,e)) {
			std::smatch sm;  
			std::regex_match (s_line,sm,e);
			std::string s_chr;
			std::string s_start;
			std::string s_end;
			s_foundGene = sm[1];
			s_chr = sm[2];
			s_start = sm[3];
			s_end = sm[4];
			s_strand = "+";
			s_coordinates = s_chr + "\t" + s_start + "\t" + s_end + "\t" + s_strand;
			if (s_foundGene == s_gene)
				std::remove("grep.gene.txt");
				return s_coordinates;		
		}
		if (std::regex_match (s_line,n)) {
			std::smatch sm;  
			std::regex_match (s_line,sm,n);
			std::string s_chr;
			std::string s_start;
			std::string s_end;
			s_foundGene = sm[1];
			s_chr = sm[2];
			s_start = sm[3];
			s_end = sm[4];
			s_strand = "-";
			s_coordinates = s_chr + "\t" + s_start + "\t" + s_end + "\t" + s_strand;
			if (s_foundGene == s_gene)
				std::remove("grep.gene.txt");
				return s_coordinates;		
		}
	}
**/

	while (std::getline(inList, s_line, '\n')) {
		
		std::string s_command = std::string("printf '") + s_line + std::string("' | cut -f 2,3,4,5");
		s_coordinates = exec(s_command.c_str());
		s_coordinates.erase(std::remove(s_coordinates.begin(), s_coordinates.end(), '\n'), s_coordinates.end());
		if (s_coordinates != "") {
			std::remove("grep.gene.txt");
			return s_coordinates;	
		}
	}

	std::remove("grep.gene.txt");
}
























