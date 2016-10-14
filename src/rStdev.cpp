#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// 
void rStdev(std::string s_rPltsName, int i_bamFiles, int i_peakNumber, std::vector<std::vector<std::string> > &dataArray, std::vector<std::string> &drcUpperAsymVector, int turnoverTimes[]) 
{

	// write python script
	ofstream rStdev;
	rStdev.open (s_rPltsName, std::ios::app);

	int i_truncSigPeaks = 0;

	for (int i = 0; i < i_peakNumber; i++) {
		std::string s_line = dataArray[i+1][2*i_bamFiles + 7];
		if ((s_line.find(std::string("NaN")) == string::npos) && (s_line.find(std::string("Inf")) == string::npos)) {
			i_truncSigPeaks++;
		}
	}

	int i_iterator = 0;
	rStdev << "turn <- c(";
	for (int i = 0; i < i_peakNumber; i++) {
		std::string s_line = dataArray[i+1][2*i_bamFiles + 7]; // trunc inflction point
		if ((s_line.find(std::string("NaN")) == string::npos) && (s_line.find(std::string("Inf")) == string::npos)) {
			if (i_iterator == i_truncSigPeaks-1) { // last data value
				rStdev << s_line << ")\n";
				i_iterator++;
			}
			if (i_iterator < i_truncSigPeaks-1) { // not last data value
				rStdev << s_line << ", ";
				i_iterator++;
			}			
		}
	}


	i_iterator = 0;
	rStdev << "upass <- c(";
	for (int i = 0; i < i_peakNumber; i++) {
		std::string s_line = dataArray[i+1][2*i_bamFiles + 7]; // trunc inflction point
		if ((s_line.find(std::string("NaN")) == string::npos) && (s_line.find(std::string("Inf")) == string::npos)) {
			if (i_iterator == i_truncSigPeaks-1) { // last data value
				rStdev << drcUpperAsymVector[i] << ")\n";
				i_iterator++;
			}
			if (i_iterator < i_truncSigPeaks-1) { // last data value
				rStdev << drcUpperAsymVector[i] << ", ";
				i_iterator++;
			}			
		}
	}

	i_iterator = 0;
	rStdev << "stdev <- c(";
	for (int i = 0; i < i_peakNumber; i++) {
		std::string s_line = dataArray[i+1][2*i_bamFiles + 7]; // trunc inflction point
		if ((s_line.find(std::string("NaN")) == string::npos) && (s_line.find(std::string("Inf")) == string::npos)) {
			double d_sum = 0;
			if (i_iterator == i_truncSigPeaks-1) { // last data value
				for (int k = 0; k < i_bamFiles; k++) { 	// for each time point
					d_sum += stod(dataArray[i+1][3 + i_bamFiles + k]);
				}
				rStdev << d_sum/i_bamFiles << ")\n"; 
				i_iterator++;
			}
			if (i_iterator < i_truncSigPeaks-1) { // not last data value
				for (int k = 0; k < i_bamFiles; k++) { 	// for each time point
					d_sum += stod(dataArray[i+1][3 + i_bamFiles + k]);
				}
				rStdev << d_sum/i_bamFiles << ","; 
				i_iterator++;
			}			
		}
	}




	rStdev << "d1<- data.frame(stdev,upass)\n"; 
	rStdev << "d2<- data.frame(stdev,turn)\n"; 
	rStdev << "d3<- data.frame(upass,turn,stdev)\n"; 

	rStdev << "s1 <- ggplot(d1, aes(upass,stdev)) +\n";  
	rStdev << "	geom_point(size = 0.3) +\n"; 
	rStdev << "	ggtitle(\"Standard Deviation and Upper Asymptote\") +\n"; 
	rStdev << "	labs(x = \"Upper Asymptote (reads)\",size = 8) +\n"; 
	rStdev << "	labs(y = \"Standard Deviation (reads)\",size = 8) +\n"; 
	rStdev << "	scale_y_continuous(expand = c(0,0), limits = c(0, NA)) +\n"; 
	rStdev << "	scale_x_continuous(expand = c(0,0), limits = c(0, NA)) +\n";
	rStdev << "	theme(\n"; 
	rStdev << "		axis.title.x=element_text(size=8),\n"; 
	rStdev << "		axis.title.y=element_text(size=8),\n"; 
	rStdev << "		plot.title=element_text(size=10),\n"; 
	rStdev << "		axis.text = element_text(size = 8, colour = \"black\"),\n"; 
	rStdev << "		legend.key = element_rect(fill = \"white\"),\n"; 
	rStdev << "		legend.background = element_rect(fill = \"white\"),\n"; 
	rStdev << "		panel.grid.major = element_line(colour = \"white\"),\n"; 
	rStdev << "		panel.grid.minor = element_blank(),\n"; 
	rStdev << "		panel.background = element_rect(fill = \"white\"),\n"; 
	rStdev << "		axis.line.x = element_line(colour = \"black\"),\n"; 
	rStdev << "		axis.line.y = element_line(colour = \"black\")\n"; 
	rStdev << "	)\n"; 

	rStdev << "s2 <- ggplot(d2, aes(turn,stdev)) + \n"; 
	rStdev << "	geom_point(size = 0.3) +\n"; 
	rStdev << "	ggtitle(\"Standard Deviation and Inflection Points\") +\n"; 
	rStdev << "	labs(x = \"Inflection Points (minutes)\",size = 8) +\n"; 
	rStdev << "	labs(y = \"Standard Deviation (reads)\",size = 8) +\n"; 
	rStdev << "	scale_y_continuous(expand = c(0,0), limits = c(0, NA)) +\n"; 
	rStdev << "	scale_x_continuous(expand = c(0,0), limits = c(0, NA)) +\n";
	rStdev << "	theme(\n"; 
	rStdev << "		axis.title.x=element_text(size=8),\n"; 
	rStdev << "		axis.title.y=element_text(size=8),\n"; 
	rStdev << "		plot.title=element_text(size=10),\n"; 
	rStdev << "		axis.text = element_text(size = 8, colour = \"black\"),\n"; 
	rStdev << "		legend.key = element_rect(fill = \"white\"),\n"; 
	rStdev << "		legend.background = element_rect(fill = \"white\"),\n"; 
	rStdev << "		panel.grid.major = element_line(colour = \"white\"),\n"; 
	rStdev << "		panel.grid.minor = element_blank(),\n"; 
	rStdev << "		panel.background = element_rect(fill = \"white\"),\n"; 
	rStdev << "		axis.line.x = element_line(colour = \"black\"),\n"; 
	rStdev << "		axis.line.y = element_line(colour = \"black\")\n"; 
	rStdev << "	)\n"; 

	rStdev << "s3 <- ggplot(d3, aes(upass,turn,colour=stdev)) + \n"; 
	rStdev << "	geom_point(size = 0.3) +\n"; 
	rStdev << "	scale_fill_hue(c=45, l=80) +\n"; 
	rStdev << "	ggtitle(\"Standard Deviation and Upper Asymptotes\") +\n"; 
	rStdev << "	labs(x = \"Upper Asymptote (normalized reads)\",size = 8) +\n"; 
	rStdev << "	labs(y = \"Inflection Points (minutes)\",size = 8) +\n"; 
	rStdev << "	scale_y_continuous(expand = c(0,0), limits = c(0, NA)) +\n"; 
	rStdev << "	scale_x_continuous(expand = c(0,0), limits = c(0, NA)) +\n";
	rStdev << "	theme(\n"; 
	rStdev << "		plot.title=element_text(size=14),\n"; 
	rStdev << "		axis.text = element_text(size = 8, colour = \"black\"),\n"; 
	rStdev << "		legend.key = element_rect(fill = \"white\"),\n"; 
	rStdev << "		legend.background = element_rect(fill = \"white\"),\n"; 
	rStdev << "		panel.grid.major = element_line(colour = \"white\"),\n"; 
	rStdev << "		panel.grid.minor = element_blank(),\n"; 
	rStdev << "		panel.background = element_rect(fill = \"white\"),\n"; 
	rStdev << "		axis.line.x = element_line(colour = \"black\"),\n"; 
	rStdev << "		axis.line.y = element_line(colour = \"black\")\n"; 
	rStdev << "	)\n"; 




	rStdev << "stdevvalues <- c(";
	for (int i = 1; i < i_peakNumber; i++) { 		// for each peak
		for (int k = 0; k < i_bamFiles; k++) { 	// for each time point
			rStdev << dataArray[i][3 + i_bamFiles + k] << ",";
		}
	}
	for (int k = 0; k < i_bamFiles-1; k++)  		// last peak
		rStdev << dataArray[i_peakNumber][3 + i_bamFiles + k] << ",";
	rStdev << dataArray[i_peakNumber][3 + i_bamFiles + i_bamFiles-1] << ")\n";

	rStdev << "time <- c (";
	for (int i = 1; i < i_peakNumber; i++) { 		// for each peak
		for (int k = 0; k < i_bamFiles; k++) { 	// for each time point
			rStdev << "\"" << turnoverTimes[k] << "\",";
		}
	}
	for (int k = 0; k < i_bamFiles-1; k++)  		// last peak
		rStdev << "\"" << turnoverTimes[k] << "\",";
	rStdev << "\"" << turnoverTimes[i_bamFiles-1] << "\")\n";


	rStdev << "dat1<- data.frame(time,stdevvalues)\n";
	rStdev << "dat1$time <- factor(dat1$time, levels = dat1$time)\n";
	rStdev << "stdevBox <- ggplot(dat1, aes(time,stdevvalues, fill=time)) +\n";
	rStdev << "	geom_boxplot(outlier.shape = NA) +\n";
	rStdev << "	scale_fill_brewer(palette=\"GnBu\") +\n";
	rStdev << "	ggtitle(\"Standard Deviation Ranges of Time Points\") +\n";
	rStdev << "	labs(y = \"Standard Deviation (reads)\",size = 8) +\n";
	rStdev << "	labs(x = \"Time Points (minutes)\",size = 8) +\n";
	rStdev << "	coord_cartesian(ylim = range(boxplot(dat1$stdevvalues, plot=FALSE)$stats)*c(.9, 1.5)) +\n";
	rStdev << "	theme(\n";
	rStdev << "		axis.title.x=element_text(size=8),\n"; 
	rStdev << "		axis.title.y=element_text(size=8),\n"; 
	rStdev << "		plot.title=element_text(size=10),\n"; 
	rStdev << "		axis.text = element_text(size = 8, colour = \"black\"),\n";
	rStdev << "		legend.position=(\"none\"),\n";
	rStdev << "		panel.grid.major = element_line(colour = \"white\"),\n";
	rStdev << "		panel.grid.minor = element_blank(),\n";
	rStdev << "		panel.background = element_rect(fill = \"white\"),\n";
	rStdev << "		axis.line.x = element_line(colour = \"black\"),\n";
	rStdev << "		axis.line.y = element_line(colour = \"black\")\n";
	rStdev << "	)\n";

	rStdev.close();

}
