#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// creates a bar chart of absolute min and max values for all loci
void rBar(std::string s_rPltsName, int i_bamFiles, int turnoverTimes[], int maxIndexArray[], int minIndexArray[], int i_peakNumber) 
{

	// write python script
	ofstream rBar;
	rBar.open (s_rPltsName, std::ios::app);

	rBar << "time <- c(";
	for (int i = 0; i < i_bamFiles; i++)
		rBar << "\"" << turnoverTimes[i] << "\", ";
	for (int i = 0; i < i_bamFiles - 1; i++)
		rBar << "\"" << turnoverTimes[i] << "\", ";
	rBar <<  "\"" << turnoverTimes[i_bamFiles - 1] << "\")\n";



	rBar << "value <- c("; // min first
	for (int i = 0; i < i_bamFiles; i++)
		rBar << (double(minIndexArray[i]) / i_peakNumber * 100) << ", ";
	for (int i = 0; i < i_bamFiles - 1; i++)
		rBar << (double(maxIndexArray[i]) / i_peakNumber * 100) << ", ";
	rBar << (double(maxIndexArray[i_bamFiles - 1]) / i_peakNumber * 100) << ")\n";


	rBar << "id <- c(";
	for (int i = 0; i < i_bamFiles; i++)
		rBar << "\"min\", ";
	for (int i = 0; i < i_bamFiles - 1; i++)
		rBar << "\"max\", ";
	rBar << "\"max\")\n";

	rBar << "dat1<- data.frame(time,value,id)\n";
	rBar << "dat1$time <- factor(dat1$time, levels = dat1$time)\n";
	rBar << "bar <- ggplot(dat1, aes(x=time, y=value, fill=id)) +\n";
	rBar << "	geom_bar(stat=\"identity\", position=position_dodge(), colour=\"black\") +\n";
	rBar << "	scale_fill_manual(values=c(\"lemonchiffon3\", \"grey30\")) +\n";
	rBar << "	scale_y_continuous(limits = c(0, 100), expand = c(0,0)) +\n";
	rBar << "	geom_text(data=dat1, aes(label=paste0(round(value,2),\"%\")), position=position_dodge(width=0.9), vjust=-0.25, size=2) +\n";
	rBar << "	labs(title = \"Distribution of normalized absolute minimum and maximum depths\") +\n";
	rBar << "	labs(x = \"Turnover Time (minutes)\",size = 10) +\n";
	rBar << "	labs(y = \"Percent Occurence\",size = 10) +\n";
	rBar << "	labs(fill = \"\") +\n";
	rBar << "	theme(\n";
	rBar << "		axis.text = element_text(size = 8, colour = \"black\"),\n";
	rBar << "		legend.key = element_rect(fill = \"white\"),\n";
	rBar << "		legend.background = element_rect(fill = \"white\"),\n";
	rBar << "		panel.grid.major = element_line(colour = \"white\"),\n";
	rBar << "		panel.grid.minor = element_blank(),\n";
	rBar << "		plot.title=element_text(size=14),\n";
	rBar << "		legend.key.size = unit(0.4, \"cm\"),\n";
	rBar << "		legend.text = element_text(size = 8),\n";
	rBar << "		panel.background = element_rect(fill = \"white\"),\n";
	rBar << "		axis.line.x = element_line(colour = \"black\"),\n";
	rBar << "		axis.line.y = element_line(colour = \"black\")\n";
	rBar << "	)\n";


	rBar.close();

}


















