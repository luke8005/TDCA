#include <iostream>
#include <fstream>
#include <string>
//#include <regex> 
#include <vector>
#include <algorithm>
using namespace std;

std::string exec(const char* cmd);

// creates ideogram with trunover heatmap
void rIdeodm3(std::string s_rPltsName, int i_bamFiles, int i_peakNumber, std::vector<std::vector<std::string> > &dataArray) 
{
	// write r script
	ofstream rIdeo;
	rIdeo.open (s_rPltsName, std::ios::app);

	int i_goodpeak = 0;
	// count non NAN containing turnover cells
	for (int i = 1; i < i_peakNumber + 1; i++) {
		std::string s = dataArray[i][2*i_bamFiles + 7];
		if ( s != "NaN")
			i_goodpeak++;		
	}


/**
	std::regex p1 ("chr+(.*)");

	// create array of non NAN containing turnover chromosomes and their start and end sites
	std::string chrArr[i_goodpeak];
	int chrStart[i_goodpeak];
	int chrEnd[i_goodpeak];

	int i_iterator = 0;
	for (int i = 1; i < i_peakNumber + 1; i++) {
		std::string s_trunover = dataArray[i][2*i_bamFiles + 7];
		if ( s_trunover != "NaN") {
			std::string s_chrCell = dataArray[i][0];		
			if (std::regex_match (s_chrCell,p1)) {
				std::smatch sm;  
				std::regex_match (s_chrCell,sm,p1);
				std::string s_chrNumber = sm[1];
				chrArr[i_iterator] = s_chrNumber;
			}
			chrStart[i_iterator] = stoi(dataArray[i][1].c_str());
			chrEnd[i_iterator] = stoi(dataArray[i][2].c_str());
			i_iterator++;
		}
	}
**/


	// create array of non NAN containing turnover chromosomes and their start and end sites
	std::string chrArr[i_goodpeak];
	int chrStart[i_goodpeak];
	int chrEnd[i_goodpeak];

	int i_iterator = 0;
	for (int i = 1; i < i_peakNumber + 1; i++) {
		std::string s_trunover = dataArray[i][2*i_bamFiles + 7];
		if ( s_trunover != "NaN") {
			std::string s_chrCell = dataArray[i][0];		
		
			s_chrCell.erase(0, 3);
			chrArr[i_iterator] = s_chrCell;

			chrStart[i_iterator] = stoi(dataArray[i][1].c_str());
			chrEnd[i_iterator] = stoi(dataArray[i][2].c_str());
			i_iterator++;
		}
	}





	rIdeo << "#dm3\n";
	rIdeo << "rec=data.frame(ideox1=c(";

	// REQUIRED: chromosome, start, end, turnover, # of valid turnover peaks.
	// VARIABLE PORTION XXX

	// ideox1 position of band
	for (int i = 0; i < i_goodpeak-1; i++) {
		if (chrArr[i] == "2L") {
			rIdeo << "0,";
		} else if (chrArr[i] == "2LHet") {
			rIdeo << "1.5,";
		} else if (chrArr[i] == "2R") {
			rIdeo << "3,";
		} else if (chrArr[i] == "2RHet") {
			rIdeo << "4.5,";
		} else if (chrArr[i] == "3L") {
			rIdeo << "6,";
		} else if (chrArr[i] == "3LHet") {
			rIdeo << "7.5,";
		} else if (chrArr[i] == "3R") {
			rIdeo << "9,";
		} else if (chrArr[i] == "3RHet") {
			rIdeo << "10.5,";
		} else if (chrArr[i] == "4") {
			rIdeo << "12,";
		} else if (chrArr[i] == "U") {
			rIdeo << "13.5,";
		} else if (chrArr[i] == "Uextra") {
			rIdeo << "15,";
		} else if (chrArr[i] == "X") {
			rIdeo << "16.5,";
		} else if (chrArr[i] == "XHet") {
			rIdeo << "18,";
		} else if (chrArr[i] == "YHet") {
			rIdeo << "19.5,";
		} else {rIdeo << "-5,";} // different chromosomes written off grid boundaries
	}

	// ideox1 end position of band
	if (chrArr[i_goodpeak-1] == "2L") {
		rIdeo << "0), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "2LHet") {
		rIdeo << "1.5), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "2R") {
		rIdeo << "3), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "2RHet") {
		rIdeo << "4.5), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "3L") {
		rIdeo << "6), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "3LHet") {
		rIdeo << "7.5), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "3R") {
		rIdeo << "9), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "3RHet") {
		rIdeo << "10.5), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "4") {
		rIdeo << "12), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "U") {
		rIdeo << "13.5), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "Uextra") {
		rIdeo << "15), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "X") {
		rIdeo << "16.5), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "XHet") {
		rIdeo << "18), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "YHet") {
		rIdeo << "19.5), ideox2=c(";
	} else {rIdeo << "-5), ideox2=c(";} // different chromosomes written off grid boundaries

	// ideox2 position of band
	for (int i = 0; i < i_goodpeak-1; i++) {
		if (chrArr[i] == "2L") {
			rIdeo << "1,";
		} else if (chrArr[i] == "2LHet") {
			rIdeo << "2.5,";
		} else if (chrArr[i] == "2R") {
			rIdeo << "4,";
		} else if (chrArr[i] == "2RHet") {
			rIdeo << "5.5,";
		} else if (chrArr[i] == "3L") {
			rIdeo << "7,";
		} else if (chrArr[i] == "3LHet") {
			rIdeo << "8.5,";
		} else if (chrArr[i] == "3R") {
			rIdeo << "10,";
		} else if (chrArr[i] == "3RHet") {
			rIdeo << "11.5,";
		} else if (chrArr[i] == "4") {
			rIdeo << "13,";
		} else if (chrArr[i] == "U") {
			rIdeo << "14.5,";
		} else if (chrArr[i] == "Uextra") {
			rIdeo << "16,";
		} else if (chrArr[i] == "X") {
			rIdeo << "17.5,";
		} else if (chrArr[i] == "XHet") {
			rIdeo << "19,";
		} else if (chrArr[i] == "YHet") {
			rIdeo << "20.5,";
		} else {rIdeo << "-5,";} // different chromosomes written off grid boundaries
	}

	// ideox2 end position of band
	if (chrArr[i_goodpeak-1] == "2L") {
		rIdeo << "1), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "2LHet") {
		rIdeo << "2.5), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "2R") {
		rIdeo << "4), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "2RHet") {
		rIdeo << "5.5), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "3L") {
		rIdeo << "7), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "3LHet") {
		rIdeo << "8.5), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "3R") {
		rIdeo << "10), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "3RHet") {
		rIdeo << "11.5), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "4") {
		rIdeo << "13), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "U") {
		rIdeo << "14.5), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "Uextra") {
		rIdeo << "16), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "X") {
		rIdeo << "17.5), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "XHet") {
		rIdeo << "19), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "YHet") {
		rIdeo << "20.5), ideoy1=c(";
	} else {rIdeo << "-5), ideoy1=c(";} // different chromosomes written off grid boundaries
	
	// band normalized from center to 500,000 bp XXX

	// ideoy1 position of band
	int i_mid = 0;
	for (int i = 0; i < i_goodpeak-1; i++) {
		i_mid = (chrEnd[i] - chrStart[i])/2;
		rIdeo << chrStart[i] + i_mid - 50000 << ",";
	}
	i_mid = (chrEnd[i_goodpeak] - chrStart[i_goodpeak])/2;
	rIdeo << chrStart[i_goodpeak] + i_mid - 50000 << "), ideoy2=c(";

	// ideoy2 position of band
	i_mid = 0;
	for (int i = 0; i < i_goodpeak-1; i++) {
		i_mid = (chrEnd[i] - chrStart[i])/2;
		rIdeo << chrStart[i] + i_mid + 50000 << ",";
	}
	i_mid = (chrEnd[i_goodpeak] - chrStart[i_goodpeak])/2;
	rIdeo << chrStart[i_goodpeak] + i_mid + 50000 << "), t=c(";

	i_iterator = 0;
	// t values of bands
	for (int i = 1; i < i_peakNumber + 1; i++) {
		std::string s_trunover = dataArray[i][2*i_bamFiles + 7];
		if ( s_trunover != "NaN" && i_iterator == i_goodpeak-1) {
			rIdeo << s_trunover << "))\n";
		}
		if ( s_trunover != "NaN" && i_iterator != i_goodpeak-1) {
			rIdeo << s_trunover << ",";
			i_iterator++;
		}
	}


	// Draw all chromosomes

	rIdeo << "ch=data.frame(chx=c(0.5,2,3.5,5,6.5,8,9.5,11,12.5,14,15.5,17,18.5,20), t=c(\"2L\",\"2LHet\",\"2R\",\"2RHet\",\"3L\",\"3LHet\",\"3R\",\"3RHet\",\"4\",\"U\",\"Uextra\",\"X\",\"XHet\",\"YHet\"))\n";
	rIdeo << "d=data.frame(x=c(0,1,1,0, 1.5,2.5,2.5,1.5, 3,4,4,3, 4.5,5.5,5.5,4.5, 6,7,7,6, 7.5,8.5,8.5,7.5, 9,10,10,9, 10.5,11.5,11.5,10.5, 12,13,13,12, 13.5,14.5,14.5,13.5, 15,16,16,15, 16.5,17.5,17.5,16.5, 18,19,19,18, 19.5,20.5,20.5,19.5), y=c(0,0,23011544,23011544, 0,0,368872,368872, 0,0,21146708,21146708, 0,0,3288761,3288761, 0,0,24543557,24543557, 0,0,2555491,2555491, 0,0,27905053,27905053, 0,0,2517507,2517507, 0,0,1351857,1351857, 0,0,10049037,10049037, 0,0,29004656,29004656, 0,0,22422827,22422827, 0,0,204112,204112, 0,0,347038,347038), t=c('1', '1', '1', '1', '2', '2', '2', '2', '3', '3', '3', '3', '4', '4', '4', '4', '5', '5', '5', '5', '6', '6', '6', '6', '7', '7', '7', '7','8', '8', '8', '8', '9', '9', '9', '9', '10', '10', '10', '10', '11', '11', '11', '11', '12', '12', '12', '12', '13', '13', '13', '13', '14', '14', '14', '14'))\n";

	// this is same for all except the scale_x_continuous(limits = c(0, 32)) - 32 is variable

	rIdeo << "#y=c(cenS,cenE,chrE,chrE,cenE,cenS,0,0,\n";
	rIdeo << "ide <- ggplot() +\n";
	rIdeo << "  scale_x_continuous(limits = c(0, 21)) +\n";
	rIdeo << "  scale_y_continuous(limits = c(-5000000, 33000000)) +\n";
	rIdeo << "  geom_polygon(data=d, mapping=aes(x=x, y=y, group=t), colour=\"black\", fill=\"white\") + \n";
	rIdeo << "  geom_rect(data=rec, mapping=aes(xmin=ideox1, xmax=ideox2, ymin=ideoy1, ymax=ideoy2, fill=t)) +\n";
	rIdeo << "  geom_polygon(data=d, mapping=aes(x=x, y=y, group=t), colour=\"black\", alpha=0) +\n";
	rIdeo << "  scale_fill_gradientn(trans = \"log10\",colours=rainbow(14)) +\n";
	rIdeo << "  geom_text(data=ch, aes(x=chx, y=-5000000, label=t), size=4) +\n";
	rIdeo << "  ggtitle(\"Ideogram Heat Map of Turnover Inflection Points\") +\n";
	rIdeo << "  labs(x = \"Chromosome\",size = 14) +\n";
	rIdeo << "  labs(y = \"Size (bp)\",size = 14) +\n";
	rIdeo << "  labs(fill = \"\") +\n";
	rIdeo << "  theme(\n";
	rIdeo << "    axis.text = element_text(size = 8, colour = \"black\"),\n";
	rIdeo << "    legend.key = element_rect(fill = \"white\"),\n";
	rIdeo << "    legend.background = element_rect(fill = \"white\"),\n";
	rIdeo << "    panel.grid.major = element_line(colour = \"white\"),\n";
	rIdeo << "    panel.grid.minor = element_blank(),\n";
	rIdeo << "    panel.background = element_rect(fill = \"grey95\"),\n";
	rIdeo << "    legend.key.height=unit(2,\"cm\"),\n";
	rIdeo << "    axis.text.x = element_blank(),\n";
	rIdeo << "    axis.ticks.x = element_blank(),\n";
	rIdeo << "    #axis.line.x = element_line(colour = \"black\"),\n";
	rIdeo << "    axis.line.y = element_line(colour = \"black\")\n";
	rIdeo << "  )\n";


	rIdeo.close();

}











