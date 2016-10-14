#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


void rBoxRes(std::string s_rPltsName, int i_peakNumber, int i_bamFiles, std::vector<std::string> &truncLinResVector, std::vector<std::string> &linResVector, std::vector<std::vector<std::string> > &dataArray)
{

	// write rthon script
	ofstream rBoxplotPlt;
	rBoxplotPlt.open(s_rPltsName, std::ios::app);

	rBoxplotPlt << "value <- c(";

	int i_linPeaks = 0;
	int i_truncLinPeaks = 0;
	int i_sigPeaks = 0;
	int i_truncSigPeaks = 0;

	for (int i = 0; i < i_peakNumber; i++) {
		std::string s_line = linResVector[i];
		if ((s_line.find(std::string("NaN")) == string::npos) && (s_line.find(std::string("Inf")) == string::npos)) {
			rBoxplotPlt << s_line << ", ";
			i_linPeaks++;
		}
	}
	for (int i = 0; i < i_peakNumber; i++) {
		std::string s_line = truncLinResVector[i];
		if ((s_line.find(std::string("NaN")) == string::npos) && (s_line.find(std::string("Inf")) == string::npos)) {
			rBoxplotPlt << s_line << ", ";
			i_truncLinPeaks++;
		}
	}

	for (int i = 0; i < i_peakNumber; i++) {
		std::string s_line = dataArray[i+1][2*i_bamFiles + 6];
		if ((s_line.find(std::string("NaN")) == string::npos) && (s_line.find(std::string("Inf")) == string::npos)) {
			rBoxplotPlt << s_line << ", ";
			i_sigPeaks++;
		}
	}
	for (int i = 0; i < i_peakNumber; i++) {
		std::string s_line = dataArray[i+1][2*i_bamFiles + 8];
		if ((s_line.find(std::string("NaN")) == string::npos) && (s_line.find(std::string("Inf")) == string::npos)) {
			i_truncSigPeaks++;
		}
	}
	int i_iterator = 0;
	for (int i = 0; i < i_peakNumber; i++) {
		std::string s_line = dataArray[i+1][2*i_bamFiles + 8];
		if ((s_line.find(std::string("NaN")) == string::npos) && (s_line.find(std::string("Inf")) == string::npos)) {
			if (i_iterator == i_truncSigPeaks-1) { // last data value
				rBoxplotPlt << s_line << ")\n";
				i_iterator++;
			}
			if (i_iterator < i_truncSigPeaks-1) { // last data value
				rBoxplotPlt << s_line << ", ";
				i_iterator++;
			}			
		}
	}


	rBoxplotPlt << "id <- c (";
	for (int i = 0; i < i_linPeaks; i++) 
		rBoxplotPlt << "\"linear\",";
	for (int i = 0; i < i_truncLinPeaks; i++) 
		rBoxplotPlt << "\"adjusted linear\",";
	for (int i = 0; i < i_sigPeaks; i++) 
		rBoxplotPlt << "\"sigmoidal\",";
	for (int i = 0; i < i_truncSigPeaks-1; i++) 
		rBoxplotPlt << "\"adjusted sigmoidal\",";
	rBoxplotPlt << "\"adjusted sigmoidal\")\n";

	//std::cout << "i_linPeaks = " << i_linPeaks << std::endl;			//XXX
	//std::cout << "i_truncLinPeaks = " << i_truncLinPeaks << std::endl;	//XXX
	//std::cout << "i_sigPeaks = " << i_sigPeaks << std::endl;			//XXX
	//std::cout << "i_truncSigPeaks = " << i_truncSigPeaks << std::endl;	//XXX


	rBoxplotPlt << "dat1<- data.frame(id,value)\n";

	rBoxplotPlt << "resbox <- ggplot(dat1, aes(id,value, fill=id)) +\n";
	rBoxplotPlt << "	geom_boxplot(outlier.shape = NA) +\n";
	rBoxplotPlt << "	scale_fill_manual(values=c(\"cornsilk4\", \"chartreuse4\", \"cornsilk2\", \"chartreuse2\")) +\n";
	rBoxplotPlt << "	ggtitle(\"Distribution of Residuals from Different Curve Fits\") +\n";
	rBoxplotPlt << "	labs(y = \"Residuals\n\n\n\",size = 14) +\n";
	rBoxplotPlt << "	labs(x = \"Type of Curve Fit\",size = 14) +\n";
	rBoxplotPlt << "	coord_cartesian(ylim = range(boxplot(dat1$value, plot=FALSE)$stats)*c(.9, 1.5)) +\n";
	rBoxplotPlt << "	theme(\n";
	rBoxplotPlt << "		axis.text = element_text(size = 8, colour = \"black\"),\n";
	rBoxplotPlt << "		axis.text.x=element_blank(),\n";
	rBoxplotPlt << "		legend.key = element_rect(fill = \"white\"),\n";
	rBoxplotPlt << "		legend.background = element_rect(fill = \"white\"),\n";
	rBoxplotPlt << "		legend.position = (\"bottom\"),\n";
	rBoxplotPlt << "		plot.title=element_text(size=10),\n";
	rBoxplotPlt << "       	axis.title=element_text(size=8),\n";
	rBoxplotPlt << "		legend.text = element_text(size = 7),\n";
	rBoxplotPlt << "		legend.title=element_blank(),\n";
	rBoxplotPlt << "		panel.grid.major = element_line(colour = \"white\"),\n";
	rBoxplotPlt << "		panel.grid.minor = element_blank(),\n";
	rBoxplotPlt << "		panel.background = element_rect(fill = \"white\"),\n";
	rBoxplotPlt << "		axis.line.x = element_line(colour = \"black\"),\n";
	rBoxplotPlt << "		axis.line.y = element_line(colour = \"black\")\n";
	rBoxplotPlt << "	)\n";


	rBoxplotPlt.close();
}




