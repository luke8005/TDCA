#include <fstream>
#include <iostream>
#include <string>
//#include <regex>
#include <vector>
using namespace std;

void drcScriptGenerator(int i_loopNumber, int i_bamFiles, int i_truncDiff, int turnoverTimes[], std::vector<double> &turnoverArr, bool b_real, bool b_turnoverDirection, double d_overallMax) 
{

	// write R script
	ofstream drcInflection;
	drcInflection.open ("drcInflection.R", std::ios::app);

	ofstream linearResiduals;
	linearResiduals.open ("linearResiduals.R", std::ios::app);

	if (b_real == true) {
		// time table
		drcInflection << "time" << i_loopNumber << " <- c(";
		for (int i = 0; i < (i_bamFiles - 1 - i_truncDiff); i++)  
			drcInflection << turnoverTimes[i] << ",";	

		drcInflection << turnoverTimes[(i_bamFiles - 1 - i_truncDiff)] << ")\n";

		// depth table
		drcInflection << "depth" << i_loopNumber << " <- c(";
		for (int i = 0; i < (i_bamFiles - 1 - i_truncDiff); i++)  
			drcInflection << turnoverArr[i] << ",";	
		drcInflection << turnoverArr[(i_bamFiles - 1 - i_truncDiff)] << ")\n";

		drcInflection << "peak" << i_loopNumber << " <- data.frame(time" << i_loopNumber << ",depth" << i_loopNumber << ")\n";

		drcInflection << "print(paste(\"peak" << i_loopNumber << "\"));\n";

		drcInflection << "suppressMessages(library(drc))\n";

		if (b_turnoverDirection) { // forward
			drcInflection << "try(peak" << i_loopNumber << ".L.3 <- drm(depth" << i_loopNumber << " ~ time" << i_loopNumber << ", data = peak" << i_loopNumber << ", fct = L.3()))\n"; 
		} else { // reverse
			drcInflection << "try(peak" << i_loopNumber << ".L.3 <- drm(depth" << i_loopNumber << " ~ time" << i_loopNumber << ", data = peak" << i_loopNumber << ", fct = l3u(upper=" << d_overallMax << ")))\n";

		}


		drcInflection << "tryCatch(suppressWarnings(summary(peak" << i_loopNumber << ".L.3)),error = function(e) {print(paste(\"e:(Intercept) ERROR\")); print(paste(\"d:(Intercept) ERROR\"));  print(paste(\" NaN (-1 degrees of freedom)\")); NaN})\n"; // forces an error to be printed

		// linear	
		linearResiduals << "suppressMessages(library(MASS))\n";
		// time table
		// time table
		linearResiduals << "time" << i_loopNumber << " <- c(";
		for (int i = 0; i < (i_bamFiles - 1 - i_truncDiff); i++)  
			linearResiduals << turnoverTimes[i] << ",";	
		linearResiduals << turnoverTimes[(i_bamFiles - 1 - i_truncDiff)] << ")\n";

		// depth table
		linearResiduals << "depth" << i_loopNumber << " <- c(";
		for (int i = 0; i < (i_bamFiles - 1 - i_truncDiff); i++)  
			linearResiduals << turnoverArr[i] << ",";	
		linearResiduals << turnoverArr[(i_bamFiles - 1 - i_truncDiff)] << ")\n";

		linearResiduals << "fit" << i_loopNumber << " <- lm(depth" << i_loopNumber << " ~ time" << i_loopNumber << ")\n";
		linearResiduals << "summary(fit" << i_loopNumber << ")\n";


	} else {
		drcInflection << "print(paste(\"e:(Intercept) ERROR\"))\n";
		drcInflection << "print(paste(\"d:(Intercept) ERROR\"))\n";
		drcInflection << "print(paste(\" NaN (-1 degrees of freedom)\"))\n";

		// linear		
		linearResiduals << "print(paste(\"Residual standard error: NaN on 0 degrees of freedom\"))\n";
	}





}
