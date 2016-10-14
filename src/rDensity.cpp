#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


void rDensity(std::string s_rPltsName, int i_peakNumber, std::vector<std::string> drcInflectionVector, int i_bamFiles, int turnoverTimes[], std::string s_name) 
{
	// write rthon script
	ofstream rDensityPlt;
	rDensityPlt.open(s_rPltsName, std::ios::app);

	int i_valid = 0; // non-NaNs
	int i_count = 0; 

	rDensityPlt << "values <- c(";

	for (int i = 0; i < i_peakNumber; i++) {
		if (drcInflectionVector[i] != "NaN")
			i_valid++;
	}

	for (int i = 0; i < i_peakNumber; i++) {
		if (drcInflectionVector[i] != "NaN" && i_count < (i_valid - 1)) {
			rDensityPlt << drcInflectionVector[i] << ",";
			i_count++;
		}
		if (drcInflectionVector[i] != "NaN" && i_count == (i_valid - 1)) {
			rDensityPlt << drcInflectionVector[i] << ")\n";
			i_count++;
		}
	}

	rDensityPlt << "id <- c(";

	for (int i = 0; i < i_valid - 1; i++) 
		rDensityPlt << "\"" << s_name << "\",";
	rDensityPlt << "\"" << s_name << "\")\n";

	rDensityPlt << "dfvalue <- data.frame(values, id)\n";

	rDensityPlt << s_name << " <- ggplot(dfvalue, aes(values, fill = id)) +\n";	
	rDensityPlt << "	geom_density(adjust = 1/5, alpha = 0.2) +\n";
	rDensityPlt << "	scale_y_continuous(expand = c(0,0)) +\n";
	rDensityPlt << "	ggtitle(\"Distribution of Inflection Points from Sigmoidal Curve Fit\") +\n";
	rDensityPlt << "	labs(x = \"Inflection Points\",size = 14) +\n";
	rDensityPlt << "	labs(y = \"Density\",size = 14) +\n";
	rDensityPlt << "	labs(fill = \"\") +\n";
	rDensityPlt << "	scale_fill_manual( values = c(\"grey20\")) +\n";
	rDensityPlt << "	scale_x_continuous(limits = c(0, NA)) +\n";
	rDensityPlt << "	theme(\n";
	rDensityPlt << "		axis.text = element_text(size = 8, colour = \"black\"),\n";
	rDensityPlt << "		#legend.key = element_rect(fill = \"white\"),\n";
	rDensityPlt << "		#legend.background = element_rect(fill = \"white\"),\n";
	rDensityPlt << "		legend.position=(\"none\"),\n";
	rDensityPlt << "		panel.grid.major = element_line(colour = \"white\"),\n";
	rDensityPlt << "		panel.grid.minor = element_blank(),\n";
	rDensityPlt << "		panel.background = element_rect(fill = \"white\"),\n";
	rDensityPlt << "		axis.line.x = element_line(colour = \"black\"),\n";
	rDensityPlt << "		axis.line.y = element_line(colour = \"black\")\n";
	rDensityPlt << "	)\n";

	rDensityPlt.close();
}




