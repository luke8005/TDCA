#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void rEnd(std::string s_rPltsName,std::string s_rPltsPDF, bool b_genomeFlagCall, int i_bamRep) 
{
	std::ofstream rPlts;
	rPlts.open(s_rPltsName, std::ios::app);

	rPlts << "pdf(\"" << s_rPltsPDF << "\")\n";
	//rPlts << "print(resbox)\n";
	//rPlts << "print(pie)\n";
	rPlts << "gA <- ggplotGrob(pie)\n";
	rPlts << "gB <- ggplotGrob(resbox)\n";
	rPlts << "g = rbind(gA, gB, size = \"first\")\n";
	rPlts << "grid.draw(g)\n";
	rPlts << "print(bar)\n";


	if (i_bamRep > 1) {
	rPlts << "layout1 <- matrix(c(1, 2, 3, 3), nrow = 2, byrow = TRUE)\n";
	rPlts << "multiplot(s1,s2,stdevBox, layout = layout1)\n";
	rPlts << "print(s3)\n";
	} else {
		rPlts << "print(scat)\n";
	}


	//rPlts << "print(non_truncated)\n";
	rPlts << "print(truncated)\n";

	if ( b_genomeFlagCall == true ) {
		rPlts << "print(box)\n";
		rPlts << "print(ide)\n";
	}

	// OTHER CHARTS
	rPlts << "invisible(dev.off())\n";
	rPlts.close();

	// run rthon script
	std::string s_rscript = "Rscript " + s_rPltsName; // temp file
	
	try {
		std::system(s_rscript.c_str());
	}
	catch(...){
		std::cerr << "Cannot access R" << std::endl;
		std::exit(0);
	}
}
