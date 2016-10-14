#include <fstream>  

void rBegin(std::string s_rPltsName, std::string s_rPltsPDF, std::string s_args) 
{
	std::ofstream rPlts;
	rPlts.open(s_rPltsName);

	rPlts << "# tdca command line arguments: " << s_args << std::endl;
	rPlts << "suppressMessages(library(ggplot2))\n";
	rPlts << "suppressMessages(library(scales))\n";
	rPlts << "suppressMessages(library(grid))\n";
	rPlts << "options(warn=-1)\n";



	rPlts << "# Multiple plot function\n";
	rPlts << "#\n";
	rPlts << "# ggplot objects can be passed in ..., or to plotlist (as a list of ggplot objects)\n";
	rPlts << "# - cols:   Number of columns in layout\n";
	rPlts << "# - layout: A matrix specifying the layout. If present, 'cols' is ignored.\n";
	rPlts << "#\n";
	rPlts << "# If the layout is something like matrix(c(1,2,3,3), nrow=2, byrow=TRUE),\n";
	rPlts << "# then plot 1 will go in the upper left, 2 will go in the upper right, and\n";
	rPlts << "# 3 will go all the way across the bottom.\n";
	rPlts << "#\n";
	rPlts << "multiplot <- function(..., plotlist=NULL, file, cols=1, layout=NULL) {\n";
	rPlts << "  library(grid)\n";

	rPlts << "  # Make a list from the ... arguments and plotlist\n";
	rPlts << "  plots <- c(list(...), plotlist)\n";

	rPlts << "  numPlots = length(plots)\n";

	rPlts << "  # If layout is NULL, then use 'cols' to determine layout\n";
	rPlts << "  if (is.null(layout)) {\n";
	rPlts << "    # Make the panel\n";
	rPlts << "    # ncol: Number of columns of plots\n";
	rPlts << "    # nrow: Number of rows needed, calculated from # of cols\n";
	rPlts << "    layout <- matrix(seq(1, cols * ceiling(numPlots/cols)),\n";
	rPlts << "                    ncol = cols, nrow = ceiling(numPlots/cols))\n";
	rPlts << "  }\n";

	rPlts << " if (numPlots==1) {\n";
	rPlts << "    print(plots[[1]])\n";

	rPlts << "  } else {\n";
	rPlts << "    # Set up the page\n";
	rPlts << "    grid.newpage()\n";
	rPlts << "    pushViewport(viewport(layout = grid.layout(nrow(layout), ncol(layout))))\n";

	rPlts << "    # Make each plot, in the correct location\n";
	rPlts << "    for (i in 1:numPlots) {\n";
	rPlts << "      # Get the i,j matrix positions of the regions that contain this subplot\n";
	rPlts << "      matchidx <- as.data.frame(which(layout == i, arr.ind = TRUE))\n";

	rPlts << "      print(plots[[i]], vp = viewport(layout.pos.row = matchidx$row,\n";
	rPlts << "                                      layout.pos.col = matchidx$col))\n";
	rPlts << "    }\n";
	rPlts << "  }\n";
	rPlts << "}\n";






	rPlts.close();
}
