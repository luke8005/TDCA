#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// creates a bar chart of absolute min and max values for all loci
void rScat(std::string s_rPltsName, int i_bamFiles, int i_peakNumber, std::vector<std::vector<std::string> > &dataArray, std::vector<std::string> &drcUpperAsymVector) 
{

	// write python script
	ofstream rScat;
	rScat.open (s_rPltsName, std::ios::app);

	int i_truncSigPeaks = 0;

	for (int i = 0; i < i_peakNumber; i++) {
		std::string s_line = dataArray[i+1][2*i_bamFiles + 7];
		if ((s_line.find(std::string("NaN")) == string::npos) && (s_line.find(std::string("Inf")) == string::npos)) {
			i_truncSigPeaks++;
		}
	}

	int i_iterator = 0;
	rScat << "turn <- c(";
	for (int i = 0; i < i_peakNumber; i++) {
		std::string s_line = dataArray[i+1][2*i_bamFiles + 7]; // trunc inflction point
		if ((s_line.find(std::string("NaN")) == string::npos) && (s_line.find(std::string("Inf")) == string::npos)) {
			if (i_iterator == i_truncSigPeaks-1) { // last data value
				rScat << s_line << ")\n";
				i_iterator++;
			}
			if (i_iterator < i_truncSigPeaks-1) { // last data value
				rScat << s_line << ", ";
				i_iterator++;
			}			
		}
	}

	i_iterator = 0;
	rScat << "upass <- c(";
	for (int i = 0; i < i_peakNumber; i++) {
		std::string s_line = dataArray[i+1][2*i_bamFiles + 7]; // trunc inflction point
		if ((s_line.find(std::string("NaN")) == string::npos) && (s_line.find(std::string("Inf")) == string::npos)) {
			if (i_iterator == i_truncSigPeaks-1) { // last data value
				rScat << drcUpperAsymVector[i] << ")\n";
				i_iterator++;
			}
			if (i_iterator < i_truncSigPeaks-1) { // last data value
				rScat << drcUpperAsymVector[i] << ", ";
				i_iterator++;
			}			
		}
	}

	rScat << "d3<- data.frame(upass,turn)\n"; 

	rScat << "scat <- ggplot(d3, aes(upass,turn)) + \n"; 
	rScat << "	geom_point(size = 0.3) +\n"; 
	rScat << "	ggtitle(\"Inflection Point against Upper Asymptote\") +\n"; 
	rScat << "	labs(x = \"Upper Asymptote (normalized reads)\",size = 10) +\n"; 
	rScat << "	labs(y = \"Inflection Points (minutes)\",size = 10) +\n"; 
	rScat << "	scale_y_continuous(expand = c(0,0), limits = c(0, NA)) +\n"; 
	rScat << "	scale_x_continuous(expand = c(0,0), limits = c(0, NA)) +\n"; 
	rScat << "	theme(\n"; 
	rScat << "		axis.text = element_text(size = 8, colour = \"black\"),\n"; 
	rScat << "		legend.key = element_rect(fill = \"white\"),\n"; 
	rScat << "		legend.background = element_rect(fill = \"white\"),\n"; 
	rScat << "		panel.grid.major = element_line(colour = \"white\"),\n"; 
	rScat << "		panel.grid.minor = element_blank(),\n"; 
	rScat << "		panel.background = element_rect(fill = \"white\"),\n"; 
	rScat << "		axis.line.x = element_line(colour = \"black\"),\n"; 
	rScat << "		axis.line.y = element_line(colour = \"black\")\n"; 
	rScat << "	)\n"; 

	rScat.close();

}
