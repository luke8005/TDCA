#include <iostream>
#include <fstream>
#include <string>
//#include <regex> 
#include <vector>
#include <algorithm>
using namespace std;

std::string exec(const char* cmd);
// creates ideogram with trunover heatmap
void rIdeomm9(std::string s_rPltsName, int i_bamFiles, int i_peakNumber, std::vector<std::vector<std::string> > &dataArray) 
{
	// write r script
	ofstream rIdeo;
	rIdeo.open (s_rPltsName, std::ios::app);

	int i_goodpeak = 0;
	// count non NAN containing turnover cells and set count to i_goodpeak
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
			//s_chrCell.erase(std::remove(s_chrCell.begin(), s_chrCell.end(), "chr"), s_chrCell.end());

			chrArr[i_iterator] = s_chrCell;

			chrStart[i_iterator] = stoi(dataArray[i][1].c_str());
			chrEnd[i_iterator] = stoi(dataArray[i][2].c_str());
			i_iterator++;
		}
	}


	rIdeo << "#mm9\n";
	rIdeo << "rec=data.frame(ideox1=c(";

	// REQUIRED: chromosome, start, end, turnover, # of valid turnover peaks.
	// VARIABLE PORTION XXX

	// x1 position of band
	for (int i = 0; i < i_goodpeak-1; i++) {
		if (chrArr[i] == "1") {
			rIdeo << "0,";
		} else if (chrArr[i] == "2") {
			rIdeo << "1.5,";
		} else if (chrArr[i] == "3") {
			rIdeo << "3,";
		} else if (chrArr[i] == "4") {
			rIdeo << "4.5,";
		} else if (chrArr[i] == "5") {
			rIdeo << "6,";
		} else if (chrArr[i] == "6") {
			rIdeo << "7.5,";
		} else if (chrArr[i] == "7") {
			rIdeo << "9,";
		} else if (chrArr[i] == "8") {
			rIdeo << "10.5,";
		} else if (chrArr[i] == "9") {
			rIdeo << "12,";
		} else if (chrArr[i] == "10") {
			rIdeo << "13.5,";
		} else if (chrArr[i] == "11") {
			rIdeo << "15,";
		} else if (chrArr[i] == "12") {
			rIdeo << "16.5,";
		} else if (chrArr[i] == "13") {
			rIdeo << "18,";
		} else if (chrArr[i] == "14") {
			rIdeo << "19.5,";
		} else if (chrArr[i] == "15") {
			rIdeo << "21,";
		} else if (chrArr[i] == "16") {
			rIdeo << "22.5,";
		} else if (chrArr[i] == "17") {
			rIdeo << "24,";
		} else if (chrArr[i] == "18") {
			rIdeo << "25.5,";
		} else if (chrArr[i] == "19") {
			rIdeo << "27,";
		} else if (chrArr[i] == "X") {
			rIdeo << "28.5,";
		} else if (chrArr[i] == "Y") {
			rIdeo << "30,";
		} else {rIdeo << "-5,";} // different chromosomes written off grid boundaries
	}

	// x1 end position of band
	if (chrArr[i_goodpeak-1] == "1") {
		rIdeo << "0), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "2") {
		rIdeo << "1.5), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "3") {
		rIdeo << "3), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "4") {
		rIdeo << "4.5), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "5") {
		rIdeo << "6), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "6") {
		rIdeo << "7.5), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "7") {
		rIdeo << "9), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "8") {
		rIdeo << "10.5), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "9") {
		rIdeo << "12), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "10") {
		rIdeo << "13.5), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "11") {
		rIdeo << "15), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "12") {
		rIdeo << "16.5), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "13") {
		rIdeo << "18), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "14") {
		rIdeo << "19.5), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "15") {
		rIdeo << "21), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "16") {
		rIdeo << "22.5), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "17") {
		rIdeo << "24), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "18") {
		rIdeo << "25.5), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "19") {
		rIdeo << "27), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "X") {
		rIdeo << "28.5), ideox2=c(";
	} else if (chrArr[i_goodpeak - 1] == "Y") {
		rIdeo << "30), ideox2=c(";
	} else {rIdeo << "-5), ideox2=c(";} // different chromosomes written off grid boundaries


	// ideox2 position of band
	for (int i = 0; i < i_goodpeak-1; i++) {
		if (chrArr[i] == "1") {
			rIdeo << "1,";
		} else if (chrArr[i] == "2") {
			rIdeo << "2.5,";
		} else if (chrArr[i] == "3") {
			rIdeo << "4,";
		} else if (chrArr[i] == "4") {
			rIdeo << "5.5,";
		} else if (chrArr[i] == "5") {
			rIdeo << "7,";
		} else if (chrArr[i] == "6") {
			rIdeo << "8.5,";
		} else if (chrArr[i] == "7") {
			rIdeo << "10,";
		} else if (chrArr[i] == "8") {
			rIdeo << "11.5,";
		} else if (chrArr[i] == "9") {
			rIdeo << "13,";
		} else if (chrArr[i] == "10") {
			rIdeo << "14.5,";
		} else if (chrArr[i] == "11") {
			rIdeo << "16,";
		} else if (chrArr[i] == "12") {
			rIdeo << "17.5,";
		} else if (chrArr[i] == "13") {
			rIdeo << "19,";
		} else if (chrArr[i] == "14") {
			rIdeo << "20.5,";
		} else if (chrArr[i] == "15") {
			rIdeo << "22,";
		} else if (chrArr[i] == "16") {
			rIdeo << "23.5,";
		} else if (chrArr[i] == "17") {
			rIdeo << "25,";
		} else if (chrArr[i] == "18") {
			rIdeo << "26.5,";
		} else if (chrArr[i] == "19") {
			rIdeo << "28,";
		} else if (chrArr[i] == "X") {
			rIdeo << "29.5,";
		} else if (chrArr[i] == "Y") {
			rIdeo << "31,";
		} else {rIdeo << "-5,";} // different chromosomes written off grid boundaries
	}

	// ideox2 end position of band
	if (chrArr[i_goodpeak-1] == "1") {
		rIdeo << "1), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "2") {
		rIdeo << "2.5), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "3") {
		rIdeo << "4), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "4") {
		rIdeo << "5.5), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "5") {
		rIdeo << "7), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "6") {
		rIdeo << "8.5), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "7") {
		rIdeo << "10), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "8") {
		rIdeo << "11.5), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "9") {
		rIdeo << "13), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "10") {
		rIdeo << "14.5), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "11") {
		rIdeo << "16), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "12") {
		rIdeo << "17.5), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "13") {
		rIdeo << "19), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "14") {
		rIdeo << "20.5), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "15") {
		rIdeo << "22), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "16") {
		rIdeo << "23.5), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "17") {
		rIdeo << "25), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "18") {
		rIdeo << "26.5), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "19") {
		rIdeo << "28), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "X") {
		rIdeo << "29.5), ideoy1=c(";
	} else if (chrArr[i_goodpeak - 1] == "Y") {
		rIdeo << "31), ideoy1=c(";
	} else {rIdeo << "-5), ideoy1=c(";} // different chromosomes written off grid boundaries
	



	// band normalized from center to 50,000 bp XXX

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

	rIdeo << "ch=data.frame(chx=c(0.5,2,3.5,5,6.5,8,9.5,11,12.5,14,15.5,17,18.5,20,21.5,23,24.5,26,27.5,29,30.5), t=c(\"1\",\"2\",\"3\",\"4\",\"5\",\"6\",\"7\",\"8\",\"9\",\"10\",\"11\",\"12\",\"13\",\"14\",\"15\",\"16\",\"17\",\"18\",\"19\",\"X\",\"Y\"))\n";
	rIdeo << "d=data.frame(x=c(0.5,0,0,1,1,0.5, 2,1.5,1.5,2.5,2.5,2, 3.5,3,3,4,4,3.5, 5,4.5,4.5,5.5,5.5,5, 6.5,6,6,7,7,6.5, 8,7.5,7.5,8.5,8.5,8, 9.5,9,9,10,10,9.5, 11,10.5,10.5,11.5,11.5,11, 12.5,12,12,13,13,12.5, 14,13.5,13.5,14.5,14.5,14, 15.5,15,15,16,16,15.5, 17,16.5,16.5,17.5,17.5,17, 18.5,18,18,19,19,18.5, 20,19.5,19.5,20.5,20.5,20, 21.5,21,21,22,22,21.5, 23,22.5,22.5,23.5,23.5,23, 24.5,24,24,25,25,24.5, 26,25.5,25.5,26.5,26.5,26, 27.5,27,27,28,28,27.5, 29,28.5,28.5,29.5,29.5,29, 30,31,31,30,30,31,31,30), y=c(0,3000000,197195432,197195432,3000000,0, 0,3000000,181748087,181748087,3000000,0, 0,3000000,159599783,159599783,3000000,0, 0,3000000,155630120,155630120,3000000,0, 0,3000000,152537259,152537259,3000000,0, 0,3000000,149517037,149517037,3000000,0, 0,3000000,152524553,152524553,3000000,0, 0,3000000,131738871,131738871,3000000,0, 0,3000000,124076172,124076172,3000000,0, 0,3000000,129993255,129993255,3000000,0, 0,3000000,121843856,121843856,3000000,0, 0,3000000,121257530,121257530,3000000,0, 0,3000000,120284312,120284312,3000000,0, 0,3000000,125194864,125194864,3000000,0, 0,3000000,103494974,103494974,3000000,0, 0,3000000,98319150,98319150,3000000,0, 0,3000000,95272651,95272651,3000000,0, 0,3000000,90772031,90772031,3000000,0, 0,3000000,61342430,61342430,3000000,0, 0,3000000,166650296,166650296,3000000,0, 2902555,5902555,15902555,15902555,5902555,2902555,0,0), t=c('1', '1', '1', '1', '1', '1', '2', '2', '2', '2', '2', '2', '3', '3', '3', '3', '3', '3', '4', '4', '4', '4', '4', '4', '5', '5', '5', '5', '5', '5', '6', '6', '6', '6', '6', '6', '7', '7', '7', '7', '7', '7', '8', '8', '8', '8', '8', '8', '9', '9', '9', '9', '9', '9', '10', '10', '10', '10', '10', '10', '11', '11', '11', '11', '11', '11', '12', '12', '12', '12', '12', '12', '13', '13', '13', '13', '13', '13', '14', '14', '14', '14', '14', '14', '15', '15', '15', '15', '15', '15', '16', '16', '16', '16', '16', '16', '17', '17', '17', '17', '17', '17', '18', '18', '18', '18', '18', '18', '19', '19', '19', '19', '19', '19', 'X', 'X', 'X', 'X', 'X', 'X', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y'))\n";

	// this is same for all except the scale_x_continuous(limits = c(0, 32)) - 32 is variable

	rIdeo << "#y=c(cenS,cenE,chrE,chrE,cenE,cenS,0,0,\n";
	rIdeo << "ide <- ggplot() +\n";
	rIdeo << "  scale_x_continuous(limits = c(0, 32)) +\n";
	rIdeo << "  scale_y_continuous(limits = c(-5000000, 200000000)) +\n";
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











