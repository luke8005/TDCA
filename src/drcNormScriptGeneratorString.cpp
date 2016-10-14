#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <vector>
using namespace std;

// ===============================
// INCORPORATE LINEAR RESIDUALS !!
// ===============================

void drcNormScriptGeneratorString(int i_loopNumber, int i_bamFiles, int i_truncDiff, int turnoverTimes[], std::vector<std::vector<std::string> > &normReadsVector, bool b_real, int i_minIndex, int i_bamRep, int i_peakNumber) 
{

	// write R script
	ofstream drcInflection;
	drcInflection.open ("drcInflection.R", std::ios::app);

	if (b_real == true) {
		// time table
		drcInflection << "time" << i_loopNumber << " <- c(";
		std::cout << "In drcNormScriptGeneratorString" << std::endl;	// DELETE XXX
		std::cout << "time" << i_loopNumber << " <- c(";	// DELETE XXX

		for (int i = 0; i < (i_bamFiles - 1 - i_truncDiff); i++) {
			for (int j = 0; j < i_bamRep; j++) {
				drcInflection << turnoverTimes[i] << ",";	
				std::cout << turnoverTimes[i] << ",";	// DELETE XXX
			}
		}
		for (int j = 0; j < i_bamRep-1; j++) {
			drcInflection << turnoverTimes[(i_bamFiles - 1 - i_truncDiff)] << ",";
			std::cout << turnoverTimes[(i_bamFiles - 1 - i_truncDiff)] << ",";	// DELETE XXX
		}
		drcInflection << turnoverTimes[(i_bamFiles - 1 - i_truncDiff)] << ")\n";
		std::cout << turnoverTimes[(i_bamFiles - 1 - i_truncDiff)] << ")\n";	// DELETE XXX

		// depth table
		drcInflection << "depth" << i_loopNumber << " <- c(";
		std::cout << "depth" << i_loopNumber << " <- c(";	// DELETE XXX

		for (int i = 0; i < (i_bamFiles - 1 - i_truncDiff); i++)  {
			for (int j = 0; j < i_bamRep; j++) {
				drcInflection << atof(normReadsVector[i_loopNumber+1+(i_peakNumber*j)][i+1].c_str()) - atof(normReadsVector[i_loopNumber+1+(i_peakNumber*j)][i_minIndex+1].c_str()) << ",";


				std::cout << atof(normReadsVector[i_loopNumber+1+(i_peakNumber*j)][i+1].c_str()) - atof(normReadsVector[i_loopNumber+1+(i_peakNumber*j)][i_minIndex+1].c_str()) << ","; /// DELETE XXX
			}
		}

		for (int j = 0; j < i_bamRep-1; j++) {
			drcInflection << atof(normReadsVector[i_loopNumber+1+(i_peakNumber*j)][(i_bamFiles - 1 - i_truncDiff)+1].c_str()) - atof(normReadsVector[i_loopNumber+1+(i_peakNumber*j)][i_minIndex+1].c_str()) << ",";	

			std::cout << atof(normReadsVector[i_loopNumber+1+(i_peakNumber*j)][(i_bamFiles - 1 - i_truncDiff)+1].c_str()) - atof(normReadsVector[i_loopNumber+1+(i_peakNumber*j)][i_minIndex+1].c_str()) << ",";
		}

		drcInflection << atof(normReadsVector[i_loopNumber+1+(i_peakNumber*(i_bamRep-1))][(i_bamFiles - 1 - i_truncDiff)+1].c_str()) - atof(normReadsVector[i_loopNumber+1+(i_peakNumber*(i_bamRep-1))][i_minIndex+1].c_str()) << ")\n";
		
		std::cout << atof(normReadsVector[i_loopNumber+1+(i_peakNumber*(i_bamRep-1))][(i_bamFiles - 1 - i_truncDiff)+1].c_str()) - atof(normReadsVector[i_loopNumber+1+(i_peakNumber*(i_bamRep-1))][i_minIndex+1].c_str()) << ")\n";

		drcInflection << "peak" << i_loopNumber << " <- data.frame(time" << i_loopNumber << ",depth" << i_loopNumber << ")\n";
		drcInflection << "suppressMessages(library(drc))\n";






		drcInflection << "try(peak" << i_loopNumber << ".L.3 <- drm(depth" << i_loopNumber << " ~ time" << i_loopNumber << ", data = peak" << i_loopNumber << ", fct = L.3()))\n";








		drcInflection << "tryCatch(suppressWarnings(summary(peak" << i_loopNumber << ".L.3)),error = function(e) {print(paste(\"e:(Intercept) ERROR\")); print(paste(\"d:(Intercept) ERROR\"));  print(paste(\" NaN (-1 degrees of freedom)\")); NaN})\n";
	} else {
		drcInflection << "print(paste(\"e:(Intercept) ERROR\"))\n";
		drcInflection << "print(paste(\"d:(Intercept) ERROR\"))\n";
		drcInflection << "print(paste(\" NaN (-1 degrees of freedom)\"))\n";
	}


}
