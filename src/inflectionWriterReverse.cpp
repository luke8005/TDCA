#include <fstream>
#include <iostream>
#include <string>
#include <vector>
//#include <regex>
#include <algorithm>
#include <cmath>
#include <math.h> 
using namespace std;


void inflectionWriterReverse(std::vector<std::string> &drcInflectionVector, std::vector<std::string> &drcResidualsVector, std::vector<std::string> &linResVector) 
{
	std::string s_drcScript = "Rscript drcInflection.R > drcInflections.txt";
	std::string s_linearScript = "Rscript linearResiduals.R > linearResiduals.txt";

	try {
		std::system(s_drcScript.c_str());
		std::system(s_linearScript.c_str());
	}
	catch(...){
		std::cerr << "Cannot access R" << std::endl;
		std::exit(0);
	}


/**
	std::ifstream inFile("drcInflections.txt");
	std::string s_line;
	std::regex p1 ("e:\\(Intercept\\)+\\s*+(\\d*\\.\\d*e\\+\\d*)+.*");
	std::regex n1 ("e:\\(Intercept\\)+\\s*+(-\\d*\\.\\d*e\\+\\d*)+.*");
	std::regex p2 ("e:\\(Intercept\\)+\\s*+(\\d*\\.\\d*e\\-\\d*)+.*");
	std::regex n2 ("e:\\(Intercept\\)+\\s*+(-\\d*\\.\\d*e\\-\\d*)+.*");
	std::regex p3 ("e:\\(Intercept\\)+\\s*+(\\d*\\.\\d*)+.*");
	std::regex n3 ("e:\\(Intercept\\)+\\s*+(-\\d*\\.\\d*)+.*");
	std::regex e (".*+(e:\\(Intercept\\) ERROR)+.*");

	int i_matchCount = 0;

	while (std::getline(inFile, s_line)) {
		if (std::regex_match (s_line,p1)) {
			std::smatch sm;  
			std::regex_match (s_line,sm,p1);
			std::string s_line = sm[1];
			std::cout << std::fixed;
			double d = std::stod(s_line);
			drcInflectionVector[i_matchCount] = std::to_string(d);
			i_matchCount++;
		} else if (std::regex_match (s_line,n1)) {
			std::smatch sm;  
			std::regex_match (s_line,sm,n1);
			std::string s_line = sm[1];
			std::cout << std::fixed;
			double d = std::stod(s_line);
			drcInflectionVector[i_matchCount] = std::to_string(d);
			i_matchCount++;
		} else if (std::regex_match (s_line,p2)) {
			std::smatch sm;  
			std::regex_match (s_line,sm,p2);
			std::string s_line = sm[1];
			std::cout << std::fixed;
			double d = std::stod(s_line);
			drcInflectionVector[i_matchCount] = std::to_string(d);
			i_matchCount++;
		} else if (std::regex_match (s_line,n2)) {
			std::smatch sm;  
			std::regex_match (s_line,sm,n2);
			std::string s_line = sm[1];
			std::cout << std::fixed;
			double d = std::stod(s_line);
			drcInflectionVector[i_matchCount] = std::to_string(d);
			i_matchCount++;
		} else if (std::regex_match (s_line,p3)) {
			std::smatch sm;  
			std::regex_match (s_line,sm,p3);
			std::string s_line = sm[1];
			drcInflectionVector[i_matchCount] = s_line;
			i_matchCount++;
		} else if (std::regex_match (s_line,n3)) {
			std::smatch sm;  
			std::regex_match (s_line,sm,n3);
			std::string s_line = sm[1];
			drcInflectionVector[i_matchCount] = s_line;
			i_matchCount++;
		} else if (std::regex_match (s_line,e)) {
			std::smatch sm;  
			std::regex_match (s_line,sm,e);
			std::string s_line = "NaN";
			drcInflectionVector[i_matchCount] = s_line;
			i_matchCount++;
		} else {
		}
	}
**/


	// sigmoidal inflections
	std::remove("inflections.txt");
	std::string s_inflectionsScript = "grep -o 'e:(Intercept)[[:space:]]*[^[:space:]]*' drcInflections.txt | grep -o '[[:space:]]*[^[:space:]]*' | grep -o '[^[:space:]]*' > inflections.txt";

	try {
		std::system(s_inflectionsScript.c_str());
		std::system(s_inflectionsScript.c_str());
	} catch(...){
		std::cerr << "s_inflectionsScript not working." << std::endl;
		std::exit(0);
	}

	std::ifstream inflecFile("inflections.txt");	
	int i_matchCount = 0;
	std::string s_line;	
			
	while (std::getline(inflecFile, s_line)) {
		std::getline(inflecFile, s_line);
		s_line.erase(std::remove(s_line.begin(), s_line.end(), '\n'), s_line.end());
		try {
			std::cout << std::fixed;
			double d = std::stod(s_line);
			if ( (std::isinf(d)) || (std::isnan(d)) ) {
				drcInflectionVector[i_matchCount] = std::string("NaN");
			} else {
				drcInflectionVector[i_matchCount] = std::to_string(d);
			}
		} catch(...){
			drcInflectionVector[i_matchCount] = std::string("NaN");
		}
		i_matchCount++;
	}
	std::remove("inflections.txt");








/**
	// get residuals
	inFile.clear();
	inFile.seekg(0, ios::beg);

	std::regex rp1 ("\\s*+(\\d*\\.\\d*)+\\s*\\(\\d+ degrees of freedom\\)");
	std::regex re (" NaN \\(-1 degrees of freedom\\)");
	std::regex ro (" Inf \\(0 degrees of freedom\\)");
	std::regex rs (".*+ NaN \\(-1 degrees of freedom\\)+.*");

	i_matchCount = 0;
	std::getline(inFile, s_line);
	while (std::getline(inFile, s_line)) {
		if (std::regex_match (s_line,rp1)) {
			std::smatch sm;  
			std::regex_match (s_line,sm,rp1);
			std::string s_line = sm[1];
			std::cout << std::fixed;
			double d = std::stod(s_line);
			drcResidualsVector[i_matchCount] = std::to_string(d);
			i_matchCount++;
		} else if (std::regex_match (s_line,re)) {
			std::smatch sm;  
			std::regex_match (s_line,sm,re);
			std::string s_line = "NaN";
			drcResidualsVector[i_matchCount] = s_line;
			i_matchCount++;
		} else if (std::regex_match (s_line,ro)) {
			std::smatch sm;  
			std::regex_match (s_line,sm,ro);
			std::string s_line = "Inf";
			drcResidualsVector[i_matchCount] = s_line;
			i_matchCount++;
		} else if (std::regex_match (s_line,rs)) {
			std::smatch sm;  
			std::regex_match (s_line,sm,rs);
			std::string s_line = "Inf";
			drcResidualsVector[i_matchCount] = s_line;
			i_matchCount++;
		} else {
		}
	}
**/


	// sygmoidal residuals
	i_matchCount = 0;
	std::remove("asymres.txt");
	std::string s_arScript = "grep 'degrees of freedom' drcInflections.txt | grep -o '[^[:space:]]*[[:space:]]*(' | grep -o '[^[:space:]]*' > asymres.txt";

	try {
		std::system(s_arScript.c_str());
		std::system(s_arScript.c_str());
	} catch(...){
		std::cerr << "s_arScript not working." << std::endl;
		std::exit(0);
	}

	std::ifstream arFile("asymres.txt");	

	while (std::getline(arFile, s_line)) {
		s_line.erase(std::remove(s_line.begin(), s_line.end(), '\n'), s_line.end());
		try {
			std::cout << std::fixed;
			double d = std::stod(s_line);
			if ( (std::isinf(d)) || (std::isnan(d)) ) {
				drcResidualsVector[i_matchCount] = std::string("NaN");
			} else {
				drcResidualsVector[i_matchCount] = std::to_string(d);
			}
		} catch(...){
			drcResidualsVector[i_matchCount] = std::string("NaN");
		}
		std::getline(arFile, s_line);
		i_matchCount++;
	}
	std::remove("asymres.txt");



/**
	// linear residuals
	std::ifstream linFile("linearResiduals.txt");
	std::regex lr1 ("Residual standard error: +(\\d*\\.\\d*)+.*");
	std::regex lr2 ("Residual standard error: +(\\d*)+.*");
	std::regex lr3 (".*+Residual standard error: +(NaN)+ on 0 degrees of freedom+.*");

	i_matchCount = 0;

	while (std::getline(linFile, s_line)) {
		if (std::regex_match (s_line,lr3)) {
			std::smatch sm;  
			std::regex_match (s_line,sm,lr3);
			std::string s_line = sm[1];
			linResVector[i_matchCount] = s_line;
			i_matchCount++;
		} else if (std::regex_match (s_line,lr1)) {
			std::smatch sm;  
			std::regex_match (s_line,sm,lr1);
			std::string s_line = sm[1];
			std::cout << std::fixed;
			double d = std::stod(s_line);
			linResVector[i_matchCount] = std::to_string(d);
			i_matchCount++;
		} else if (std::regex_match (s_line,lr2)) {
			std::smatch sm;  
			std::regex_match (s_line,sm,lr2);
			std::string s_line = sm[1];
			std::cout << std::fixed;
			double d = std::stod(s_line);
			linResVector[i_matchCount] = std::to_string(d);
			i_matchCount++;
		} else {
		}
	}
**/

	// linear residuals
	i_matchCount = 0;
	std::remove("linres.txt");
	std::string s_lrScript = "grep 'Residual standard error:' linearResiduals.txt | grep -o '[^[:space:]]*[[:space:]]*on' | grep -o '[^[:space:]]*' > linres.txt";

	try {
		std::system(s_lrScript.c_str());
		std::system(s_lrScript.c_str());
	} catch(...){
		std::cerr << "s_lrScript not working." << std::endl;
		std::exit(0);
	}
	std::ifstream lrFile("linres.txt");	
	while (std::getline(lrFile, s_line)) {
		s_line.erase(std::remove(s_line.begin(), s_line.end(), '\n'), s_line.end());

		try {
			std::cout << std::fixed;
			double d = std::stod(s_line);
			if ( (std::isinf(d)) || (std::isnan(d)) ) {
				linResVector[i_matchCount] = std::string("NaN");
			} else {
				linResVector[i_matchCount] = std::to_string(d);
			}
		} catch(...){
			linResVector[i_matchCount] = std::string("NaN");
		}
		i_matchCount++;
		std::getline(lrFile, s_line);
	}
	std::remove("linres.txt");


	std::remove("drcInflections.txt");
	std::remove("drcInflection.R");

	std::remove("linearResiduals.txt");
	std::remove("linearResiduals.R");



}

