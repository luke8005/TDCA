#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


void rPie(std::string s_rPltsName, int i_peakNumber, int i_tuncSat, int i_tuncNotSat, int i_notTuncSat, int i_notTuncNotSat, int i_eliminated)
{

	// write rthon script
	ofstream rPiePlt;
	rPiePlt.open(s_rPltsName, std::ios::app);

	double d_el = double(i_eliminated)/double(i_peakNumber)*100;
	double d_ts = double(i_tuncSat)/double(i_peakNumber)*100;
	double d_tns = double(i_tuncNotSat)/double(i_peakNumber)*100;
	double d_nts = double(i_notTuncSat)/double(i_peakNumber)*100;
	double d_ntns = double(i_notTuncNotSat)/double(i_peakNumber)*100;
	
	//std::cout << "d_el = " << d_el << std::endl;
	//std::cout << "d_ts = " << d_ts << std::endl;
	//std::cout << "d_tns = " << d_tns << std::endl;
	//std::cout << "d_nts = " << d_nts << std::endl;
	//std::cout << "d_ntns = " << d_ntns << std::endl;


	rPiePlt << "values <- c(" << d_el << "," << d_ts << "," << d_tns << "," << d_nts << "," << d_ntns << ")\n";
	rPiePlt << "id <- c(\"elim\", \"trunc; sat\", \"trunc; not-sat\", \"not-trunc; sat\", \"not-trunc; not-sat\")\n";
	rPiePlt << "dfvalue <- data.frame(values, id)\n";

	rPiePlt << "bp<- ggplot(dfvalue, aes(x=\"\", y=values, fill=id))+\n";
	rPiePlt << "  geom_bar(width = 1, stat = \"identity\", color='black')\n";
	rPiePlt << "pie <- bp + coord_polar(\"y\", start=0)\n";

	rPiePlt << "# coordinate midpoints\n";
	rPiePlt << "y.breaks <- cumsum(dfvalue$values) - dfvalue$values/2\n";


	rPiePlt << "blank_theme <- theme_minimal()+\n";
	rPiePlt << "	theme(\n";
	rPiePlt << "		axis.title.x = element_blank(),\n";
	rPiePlt << "		axis.title.y = element_blank(),\n";
	rPiePlt << "		panel.border = element_blank(),\n";
	rPiePlt << "		axis.text.x = element_text(size=6),\n";
	rPiePlt << "		panel.grid=element_blank(),\n";
	rPiePlt << "		axis.ticks = element_blank(),\n";
	rPiePlt << "		plot.title=element_text(size=10),\n";		
	rPiePlt << "		legend.key.size = unit(0.25, \"cm\"),\n";	
	rPiePlt << "		legend.position=\"bottom\",\n";		
	rPiePlt << "		legend.text = element_text(size = 7)\n";
	rPiePlt << "	)\n";

	rPiePlt << "lbls <- paste(round(values,1),\"%\",sep=\"\")\n";
	rPiePlt << "pie <- pie + scale_fill_manual(values=c(\"firebrick2\", \"khaki3\", \"khaki2\", \"seashell3\", \"seashell2\")) + blank_theme +\n";
	rPiePlt << "	theme(axis.text.x=element_text(color='black')) +\n";
	rPiePlt << "	labs(fill=\"\") +\n";
	rPiePlt << "	guides(fill=guide_legend(nrow=2,byrow=TRUE)) +\n";
	rPiePlt << "	scale_y_continuous(breaks=y.breaks, labels=lbls) +\n";
	rPiePlt << "	ggtitle(\"Peak Characteristics\")\n";


	rPiePlt.close();

}
