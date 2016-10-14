#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


void rBoxplot(std::string s_rPltsName, int i_peakNumber, int i_genomeFileCount, int i_bamFiles, std::vector<std::vector<std::string> > &dataArray) 
{
	// write rthon script
	ofstream rBoxplotPlt;
	rBoxplotPlt.open(s_rPltsName, std::ios::app);

	rBoxplotPlt << "value <- c(";

	int i_arr[i_genomeFileCount]; // valid overlaps per gene feature
	int i_colstart = 2*i_bamFiles + 12;
	int i_colend = 2*i_bamFiles + 12 + i_genomeFileCount;
	int i_loop = 0;

	for (int i = i_colstart; i < i_colend; i++) { // for each gene feature
		int i_iterator = 0;
		for (int j = 1; j < i_peakNumber + 1; j++) { // number of valid turnover values for each gene feature
			std::string s_str = dataArray[j][2*i_bamFiles + 7]; // truncated turnover column
			if ( (atoi(dataArray[j][i].c_str()) > 0) && (s_str.find(std::string("NaN")) == string::npos) ) {
				i_iterator++;
			}
		}
		i_arr[i_loop] = i_iterator;
		i_loop++;
	}

	for (int i = i_colstart; i < i_colend-1; i++) { // for each gene feature except last
		for (int j = 1; j < i_peakNumber + 1; j++) {
			std::string s_str = dataArray[j][2*i_bamFiles + 7]; // truncated turnover column
			if ( (atoi(dataArray[j][i].c_str()) > 0) && (s_str.find(std::string("NaN")) == string::npos) )
				rBoxplotPlt << s_str << ",";
		}
	}

	int i_iterator = 1;
	for (int j = 1; j < i_peakNumber + 1; j++) { // for turnover values of last gene feature
		std::string s_str = dataArray[j][2*i_bamFiles + 7]; // truncated turnover column
	
		// put a 0 value if last genome feature has zero overlaps
		if (i_arr[i_genomeFileCount-1] == 0) {
			rBoxplotPlt << "0)\n";
			break;
		}

		if ( (atoi(dataArray[j][i_colend-1].c_str()) > 0) && (s_str.find(std::string("NaN")) == string::npos) && (i_arr[i_genomeFileCount-1]) > (i_iterator) ) {
			rBoxplotPlt << s_str << ",";
			i_iterator++;
		} else if ( (atoi(dataArray[j][i_colend-1].c_str()) > 0) && (s_str.find(std::string("NaN")) == string::npos) && (i_arr[i_genomeFileCount-1] == (i_iterator)) ) {
			rBoxplotPlt << s_str << ")\n";
		} else {}
	}


	// print array containing number of valid turnover values of each gene feature
/**
	for (int i = 0; i < i_genomeFileCount; i++) {
		std::cout << "i_arr[" << i << "] = " << i_arr[i] << std::endl;
	}
**/




	rBoxplotPlt << "id <- c (";

	for (int i = 0; i < i_genomeFileCount-1; i++) {
		for (int j = 0; j < i_arr[i]; j++) {
			std::string s_feat = dataArray[0][i_colstart+i];
			s_feat = s_feat.substr(0, s_feat.size()-4);
			rBoxplotPlt << "\"" << s_feat << "\",";
		}
	}

	for (int i = 0; i < i_arr[i_genomeFileCount-1]-1; i++) {
		std::string s_feat = dataArray[0][i_colend-1];
		s_feat = s_feat.substr(0, s_feat.size()-4);
		rBoxplotPlt << "\"" << s_feat << "\",";
	}
	std::string s_feat = dataArray[0][i_colend-1];
	s_feat = s_feat.substr(0, s_feat.size()-4);
	rBoxplotPlt << "\"" << s_feat << "\")\n";


	rBoxplotPlt << "dat1<- data.frame(id,value)\n";

	rBoxplotPlt << "box <- ggplot(dat1, aes(id,value, fill=id)) +\n";
	rBoxplotPlt << "	geom_boxplot(outlier.shape = NA) +\n";
	rBoxplotPlt << "	coord_cartesian(ylim = range(boxplot(dat1$value, plot=FALSE)$stats)*c(.9, 2)) + # limit Y range to non outlier data\n";
	rBoxplotPlt << "	scale_fill_brewer(palette=\"Dark2\") +\n";
	rBoxplotPlt << "	ggtitle(\"Inflection Points at Gene Features\") +\n";
	rBoxplotPlt << "	labs(y = \"Inflection Points (minutes)\",size = 14) +\n";
	rBoxplotPlt << "	labs(x = \"Feature\",size = 14) +\n";
	rBoxplotPlt << "	scale_y_continuous(limits = c(0, NA)) +\n";
	rBoxplotPlt << "	theme(\n";
	rBoxplotPlt << "		axis.text = element_text(size = 8, colour = \"black\"),\n";
	rBoxplotPlt << "		axis.text.x=element_blank(),\n";
	rBoxplotPlt << "		legend.key = element_rect(fill = \"white\"),\n";
	rBoxplotPlt << "		legend.background = element_rect(fill = \"white\"),\n";
	rBoxplotPlt << "		legend.position = (\"bottom\"),\n";
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




