#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <regex>
#include <algorithm>
#include <cmath>
#include <math.h> 
using namespace std;

std::string exec(const char* cmd);

int exonNumber(std::string s_gene, std::string s_genelistFile)
{
	std::string s_command ="grep '" + s_gene + "[[:space:]]' " + s_genelistFile + " | cut -f 6";

	// remove newline at end of line that find gives
	std::string s_exons = exec(s_command.c_str());
	s_exons.erase(std::remove(s_exons.begin(), s_exons.end(), '\n'), s_exons.end());

	return stoi(s_exons);

}

std::string exonStartString(std::string s_gene, std::string s_genelistFile, int i_exons)
{

	std::string s_command ="grep '" + s_gene + "[[:space:]]' " + s_genelistFile + " | cut -f 7";

	// remove newline at end of line that find gives
	std::string s_startExons = exec(s_command.c_str());
	s_startExons.erase(std::remove(s_startExons.begin(), s_startExons.end(), '\n'), s_startExons.end());

	return s_startExons;

}

std::string exonEndString(std::string s_gene, std::string s_genelistFile, int i_exons)
{

	std::string s_command ="grep '" + s_gene + "[[:space:]]' " + s_genelistFile + " | cut -f 8";

	// remove newline at end of line that find gives
	std::string s_endExons = exec(s_command.c_str());
	s_endExons.erase(std::remove(s_endExons.begin(), s_endExons.end(), '\n'), s_endExons.end());

	return s_endExons;

}

//gives an exon from a string
int exons(std::string s_exonString)
{
/**
	int i_anExon;
	std::regex e ("(\\d*)\\,(.*)");
	if (std::regex_match (s_exonString,e)) {
		std::smatch sm;  
		std::regex_match (s_exonString,sm,e);
		i_anExon = stoi(sm[1]);
		return i_anExon;		
	}
**/
	std::string s_command = "echo '" + s_exonString + "' | grep -o '^[[:digit:]]*'";

	// remove newline at end of line that find gives
	std::string s_anExon = exec(s_command.c_str());
	s_anExon.erase(std::remove(s_anExon.begin(), s_anExon.end(), '\n'), s_anExon.end());

	return stoi(s_anExon);
}


// snips an exon off a string
std::string exonStringSnipper(std::string s_exonString)
{
/**
	std::string s_snipped;
	std::regex e ("([[:digit:]])\\,(.*)");
	if (std::regex_match (s_exonString,e)) {
		std::smatch sm;  
		std::regex_match (s_exonString,sm,e);
		s_snipped = sm[2];
		return s_snipped;		
	}
**/

	std::string s_command = "echo '" + s_exonString + "' | grep -o ',.*' | grep -o '[[:digit:]].*'";
	std::string s_snipped = exec(s_command.c_str());
	s_snipped.erase(std::remove(s_snipped.begin(), s_snipped.end(), '\n'), s_snipped.end());

	return s_snipped;

}




// return firt or last exon of a gene
double startEnd(std::string s_gene, std::string s_genelistFile, std::string s_str)
{
/**
	std::string s_grep = "grep '" + s_gene + "' " + s_genelistFile + " > grep.gene.txt";
	try {
		std::system(s_grep.c_str());
	}
	catch(...){
		std::cerr << "Grep not functioning." << std::endl;
		std::exit(0);
	}
	std::ifstream inList("grep.gene.txt"); 
	std::string s_line;
	std::string s_foundGene;	
	std::regex e ("(.*)+\t+(chr.*)+\t+(\\d*)+\t+(\\d*)+\t+(\\+)\t+(\\d*)+\t+(.*)+\t+(.*)");
	std::regex n ("(.*)+\t+(chr.*)+\t+(\\d*)+\t+(\\d*)+\t+(\\-)\t+(\\d*)+\t+(.*)+\t+(.*)");
	while (std::getline(inList, s_line, '\n')) {
		if (std::regex_match (s_line,e)) {
			std::smatch sm;  
			std::regex_match (s_line,sm,e);
			std::string s_start;
			std::string s_end;
			s_foundGene = sm[1];
			s_start = sm[3];
			s_end = sm[4];
			if (s_foundGene == s_gene) {
				std::remove("grep.gene.txt");
				if (s_str == "start") {
					return stod(s_start);	
				} else {
					return stod(s_end);
				}
			}	
		}
		if (std::regex_match (s_line,n)) {
			std::smatch sm;  
			std::regex_match (s_line,sm,n);
			std::string s_start;
			std::string s_end;
			s_foundGene = sm[1];
			s_start = sm[3];
			s_end = sm[4];
			if (s_foundGene == s_gene) {
				std::remove("grep.gene.txt");
				if (s_str == "start") {
					return stod(s_start);	
				} else {
					return stod(s_end);
				}
			}			
		}
	}
	std::remove("grep.gene.txt");
**/


	std::string s_commandFE = "grep '" + s_gene + "[[:space:]]' " + s_genelistFile + " | cut -f 7 | grep -o '^[[:digit:]]*'";

	std::string s_commandLE = "grep '" + s_gene + "[[:space:]]' " + s_genelistFile + " | cut -f 8 | grep -o '[[:digit:]]*,$' | grep -o '[[:digit:]]*'";

	if (s_str == "start") {
		std::string s_firstExon = exec(s_commandFE.c_str());
		s_firstExon.erase(std::remove(s_firstExon.begin(), s_firstExon.end(), '\n'), s_firstExon.end());
		return stod(s_firstExon);	
	} else {
		std::string s_lastExon = exec(s_commandLE.c_str());
		s_lastExon.erase(std::remove(s_lastExon.begin(), s_lastExon.end(), '\n'), s_lastExon.end());
		return stod(s_lastExon);
	}


}


// get strand
std::string strand(std::string s_gene, std::string s_genelistFile)
{

	std::string s_command ="grep '" + s_gene + "[[:space:]]' " + s_genelistFile + " | cut -f 5";

	// remove newline at end of line that find gives
	std::string s_strand = exec(s_command.c_str());
	s_strand.erase(std::remove(s_strand.begin(), s_strand.end(), '\n'), s_strand.end());

	return s_strand;

}

double yAxisMax(double d_mantissaMax, int i_exp)
{

	double d_yAxisMantissa = 0;
	if (d_mantissaMax < 1.2) {
		d_yAxisMantissa = 1.2;
	} else if (d_mantissaMax < 2.5) {
		d_yAxisMantissa = 2.5;
	} else if (d_mantissaMax < 3) {
		d_yAxisMantissa = 3;
	} else if (d_mantissaMax < 4.1) {
		d_yAxisMantissa = 4.1;
	} else if (d_mantissaMax < 5) {
		d_yAxisMantissa = 5;
	} else if (d_mantissaMax < 6) {
		d_yAxisMantissa = 6;
	} else if (d_mantissaMax < 8.1) {
		d_yAxisMantissa = 8.1;
	} else if (d_mantissaMax < 9) {
		d_yAxisMantissa = 9;
	} else {
		d_yAxisMantissa = 1.2;
		i_exp++;
	}

	double d_yAxisMax	= d_yAxisMantissa*pow(10, i_exp);
	return d_yAxisMax;

}


void r3Dadjusted(std::string s_genelistFile, std::string s_rGenePltsName, int i_bamFiles, int turnoverTimes[], int i_validgenes, std::vector<double> &normGeneVector, std::vector<std::string> &validGeneVector) 
{

	ofstream r3D;
	r3D.open (s_rGenePltsName); // XXX

	r3D <<  "# 3d grids from:\n";
	r3D <<  "# https://gist.githubusercontent.com/agstudy/7908344/raw/81f8ff237b78f1ebea4f149479aa03025cfaabdf/gistfile1.r\n";
	r3D <<  "suppressMessages(library(plot3D))\n";
	r3D <<  "suppressMessages(library(rgl))\n";
	r3D <<  "suppressMessages(library(scatterplot3d))\n";
	r3D << "options(warn=-1)\n";
	r3D <<  "sactter.grid <- function (x, y = NULL, z = NULL, color = par(\"col\"), pch = NULL, \n";
	r3D <<  "                          main = NULL, sub = NULL, xlim = NULL, ylim = NULL, zlim = NULL, \n";
	r3D <<  "                          xlab = NULL, ylab = NULL, zlab = NULL, scale.y = 1, angle = 40, \n";
	r3D <<  "                          axis = TRUE, tick.marks = TRUE, label.tick.marks = TRUE, \n";
	r3D <<  "                          x.ticklabs = NULL, y.ticklabs = NULL, z.ticklabs = NULL, \n";
	r3D <<  "                          y.margin.add = 0, grid = TRUE, box = TRUE, lab = par(\"lab\"), \n";
	r3D <<  "                          lab.z = mean(lab[1:2]), type = \"p\", highlight.3d = FALSE, \n";
	r3D <<  "                          mar = c(5, 3, 4, 3) + 0.1, bg = par(\"bg\"), col.axis = par(\"col.axis\"), \n";
	r3D <<  "                          col.grid = \"grey\", col.lab = par(\"col.lab\"), cex.symbols = par(\"cex\"), \n";
	r3D <<  "                          cex.axis = 0.8 * par(\"cex.axis\"), cex.lab = par(\"cex.lab\"), \n";
	r3D <<  "                          font.axis = par(\"font.axis\"), font.lab = par(\"font.lab\"), \n";
	r3D <<  "                          lty.axis = par(\"lty\"), lty.grid = par(\"lty\"), lty.hide = NULL, \n";
	r3D <<  "                          lty.hplot = par(\"lty\"), log = \"\", ...) \n";
	r3D <<  "{\n";
	r3D <<  "  mem.par <- par(mar = mar)\n";
	r3D <<  "  x.scal <- y.scal <- z.scal <- 1\n";
	r3D <<  "  xlabel <- if (!missing(x)) \n";
	r3D <<  "    deparse(substitute(x))\n";
	r3D <<  "  ylabel <- if (!missing(y)) \n";
	r3D <<  "    deparse(substitute(y))\n";
	r3D <<  "  zlabel <- if (!missing(z)) \n";
	r3D <<  "    deparse(substitute(z))\n";
	r3D <<  "  if (highlight.3d && !missing(color)) \n";
	r3D <<  "    warning(\"color is ignored when highlight.3d = TRUE\")\n";
	r3D <<  "  if (!is.null(d <- dim(x)) && (length(d) == 2) && (d[2] >= \n";
	r3D <<  "                                                    4)) \n";
	r3D <<  "    color <- x[, 4]\n";
	r3D <<  "  else if (is.list(x) && !is.null(x$color)) \n";
	r3D <<  "    color <- x$color\n";
	r3D <<  "  xyz <- xyz.coords(x = x, y = y, z = z, xlab = xlabel, ylab = ylabel, \n";
	r3D <<  "                    zlab = zlabel, log = log)\n";
	r3D <<  "  if (is.null(xlab)) {\n";
	r3D <<  "    xlab <- xyz$xlab\n";
	r3D <<  "    if (is.null(xlab)) \n";
	r3D <<  "      xlab <- \"\"\n";
	r3D <<  "  }\n";
	r3D <<  "  if (is.null(ylab)) {\n";
	r3D <<  "    ylab <- xyz$ylab\n";
	r3D <<  "    if (is.null(ylab)) \n";
	r3D <<  "      ylab <- \"\"\n";
	r3D <<  "  }\n";
	r3D <<  "  if (is.null(zlab)) {\n";
	r3D <<  "    zlab <- xyz$zlab\n";
	r3D <<  "    if (is.null(zlab)) \n";
	r3D <<  "      zlab <- \"\"\n";
	r3D <<  "  }\n";
	r3D <<  "  if (length(color) == 1) \n";
	r3D <<  "    color <- rep(color, length(xyz$x))\n";
	r3D <<  "  else if (length(color) != length(xyz$x)) \n";
	r3D <<  "    stop(\"length(color) \", \"must be equal length(x) or 1\")\n";
	r3D <<  "  angle <- (angle%%360)/90\n";
	r3D <<  "  yz.f <- scale.y * abs(if (angle < 1) angle else if (angle > \n";
	r3D <<  "                                                      3) angle - 4 else 2 - angle)\n";
	r3D <<  "  yx.f <- scale.y * (if (angle < 2) \n";
	r3D <<  "    1 - angle\n";
	r3D <<  "    else angle - 3)\n";
	r3D <<  "  if (angle > 2) {\n";
	r3D <<  "    temp <- xyz$x\n";
	r3D <<  "    xyz$x <- xyz$y\n";
	r3D <<  "    xyz$y <- temp\n";
	r3D <<  "    temp <- xlab\n";
	r3D <<  "    xlab <- ylab\n";
	r3D <<  "    ylab <- temp\n";
	r3D <<  "    temp <- xlim\n";
	r3D <<  "    xlim <- ylim\n";
	r3D <<  "    ylim <- temp\n";
	r3D <<  "  }\n";
	r3D <<  "  angle.1 <- (1 < angle && angle < 2) || angle > 3\n";
	r3D <<  "  angle.2 <- 1 <= angle && angle <= 3\n";
	r3D <<  "  dat <- cbind(as.data.frame(xyz[c(\"x\", \"y\", \"z\")]), col = color)\n";
	r3D <<  "  if (!is.null(xlim)) {\n";
	r3D <<  "    xlim <- range(xlim)\n";
	r3D <<  "    dat <- dat[xlim[1] <= dat$x & dat$x <= xlim[2], , drop = FALSE]\n";
	r3D <<  "  }\n";
	r3D <<  "  if (!is.null(ylim)) {\n";
	r3D <<  "    ylim <- range(ylim)\n";
	r3D <<  "    dat <- dat[ylim[1] <= dat$y & dat$y <= ylim[2], , drop = FALSE]\n";
	r3D <<  "  }\n";
	r3D <<  "  if (!is.null(zlim)) {\n";
	r3D <<  "    zlim <- range(zlim)\n";
	r3D <<  "    dat <- dat[zlim[1] <= dat$z & dat$z <= zlim[2], , drop = FALSE]\n";
	r3D <<  "  }\n";
	r3D <<  "  n <- nrow(dat)\n";
	r3D <<  "  if (n < 1) \n";
	r3D <<  "    stop(\"no data left within (x|y|z)lim\")\n";
	r3D <<  "  y.range <- range(dat$y[is.finite(dat$y)])\n";
	r3D <<  "  if (type == \"p\" || type == \"h\") {\n";
	r3D <<  "    y.ord <- rev(order(dat$y))\n";
	r3D <<  "    dat <- dat[y.ord, ]\n";
	r3D <<  "    if (length(pch) > 1) \n";
	r3D <<  "      if (length(pch) != length(y.ord)) \n";
	r3D <<  "        stop(\"length(pch) \", \"must be equal length(x) or 1\")\n";
	r3D <<  "    else pch <- pch[y.ord]\n";
	r3D <<  "    if (length(bg) > 1) \n";
	r3D <<  "      if (length(bg) != length(y.ord)) \n";
	r3D <<  "        stop(\"length(bg) \", \"must be equal length(x) or 1\")\n";
	r3D <<  "    else bg <- bg[y.ord]\n";
	r3D <<  "    if (length(cex.symbols) > 1) \n";
	r3D <<  "      if (length(cex.symbols) != length(y.ord)) \n";
	r3D <<  "        stop(\"length(cex.symbols) \", \"must be equal length(x) or 1\")\n";
	r3D <<  "    else cex.symbols <- cex.symbols[y.ord]\n";
	r3D <<  "    daty <- dat$y\n";
	r3D <<  "    daty[!is.finite(daty)] <- mean(daty[is.finite(daty)])\n";
	r3D <<  "    if (highlight.3d && !(all(diff(daty) == 0))) \n";
	r3D <<  "      dat$col <- rgb(red = seq(0, 1, length = n) * (y.range[2] - \n";
	r3D <<  "                                                      daty)/diff(y.range), green = 0, blue = 0)\n";
	r3D <<  "  }\n";
	r3D <<  "  p.lab <- par(\"lab\")\n";
	r3D <<  "  y.range <- range(dat$y[is.finite(dat$y)], ylim)\n";
	r3D <<  "  y.prty <- pretty(y.range, n = lab[2], min.n = max(1, min(0.5 * \n";
	r3D <<  "                                                             lab[2], p.lab[2])))\n";
	r3D <<  "  y.scal <- round(diff(y.prty[1:2]), digits = 12)\n";
	r3D <<  "  y.add <- min(y.prty)\n";
	r3D <<  "  dat$y <- (dat$y - y.add)/y.scal\n";
	r3D <<  "  y.max <- (max(y.prty) - y.add)/y.scal\n";
	r3D <<  "  if (!is.null(ylim)) \n";
	r3D <<  "    y.max <- max(y.max, ceiling((ylim[2] - y.add)/y.scal))\n";
	r3D <<  "  x.range <- range(dat$x[is.finite(dat$x)], xlim)\n";
	r3D <<  "  x.prty <- pretty(x.range, n = lab[1], min.n = max(1, min(0.5 * \n";
	r3D <<  "                                                             lab[1], p.lab[1])))\n";
	r3D <<  "  x.scal <- round(diff(x.prty[1:2]), digits = 12)\n";
	r3D <<  "  dat$x <- dat$x/x.scal\n";
	r3D <<  "  x.range <- range(x.prty)/x.scal\n";
	r3D <<  "  x.max <- ceiling(x.range[2])\n";
	r3D <<  "  x.min <- floor(x.range[1])\n";
	r3D <<  "  if (!is.null(xlim)) {\n";
	r3D <<  "    x.max <- max(x.max, ceiling(xlim[2]/x.scal))\n";
	r3D <<  "    x.min <- min(x.min, floor(xlim[1]/x.scal))\n";
	r3D <<  "  }\n";
	r3D <<  "  x.range <- range(x.min, x.max)\n";
	r3D <<  "  z.range <- range(dat$z[is.finite(dat$z)], zlim)\n";
	r3D <<  "  z.prty <- pretty(z.range, n = lab.z, min.n = max(1, min(0.5 * \n";
	r3D <<  "                                                            lab.z, p.lab[2])))\n";
	r3D <<  "  z.scal <- round(diff(z.prty[1:2]), digits = 12)\n";
	r3D <<  "  dat$z <- dat$z/z.scal\n";
	r3D <<  "  z.range <- range(z.prty)/z.scal\n";
	r3D <<  "  z.max <- ceiling(z.range[2])\n";
	r3D <<  "  z.min <- floor(z.range[1])\n";
	r3D <<  "  if (!is.null(zlim)) {\n";
	r3D <<  "    z.max <- max(z.max, ceiling(zlim[2]/z.scal))\n";
	r3D <<  "    z.min <- min(z.min, floor(zlim[1]/z.scal))\n";
	r3D <<  "  }\n";
	r3D <<  "  z.range <- range(z.min, z.max)\n";
	r3D <<  "  plot.new()\n";
	r3D <<  "  if (angle.2) {\n";
	r3D <<  "    x1 <- x.min + yx.f * y.max\n";
	r3D <<  "    x2 <- x.max\n";
	r3D <<  "  }\n";
	r3D <<  "  else {\n";
	r3D <<  "    x1 <- x.min\n";
	r3D <<  "    x2 <- x.max + yx.f * y.max\n";
	r3D <<  "  }\n";
	r3D <<  "  plot.window(c(x1, x2), c(z.min, z.max + yz.f * y.max))\n";
	r3D <<  "  temp <- strwidth(format(rev(y.prty))[1], cex = cex.axis/par(\"cex\"))\n";
	r3D <<  "  if (angle.2) \n";
	r3D <<  "    x1 <- x1 - temp - y.margin.add\n";
	r3D <<  "  else x2 <- x2 + temp + y.margin.add\n";
	r3D <<  "  plot.window(c(x1, x2), c(z.min, z.max + yz.f * y.max))\n";
	r3D <<  "  if (angle > 2) \n";
	r3D <<  "    par(usr = par(\"usr\")[c(2, 1, 3:4)])\n";
	r3D <<  "  usr <- par(\"usr\")\n";
	r3D <<  "  title(main, sub, ...)\n";
	r3D <<  "  if (\"xy\" %in% grid || grid) {\n";
	r3D <<  "    i <- x.min:x.max\n";
	r3D <<  "    segments(i, z.min, i + (yx.f * y.max), yz.f * y.max + \n";
	r3D <<  "               z.min, col = col.grid, lty = lty.grid)\n";
	r3D <<  "    i <- 0:y.max\n";
	r3D <<  "    segments(x.min + (i * yx.f), i * yz.f + z.min, x.max + \n";
	r3D <<  "               (i * yx.f), i * yz.f + z.min, col = col.grid, lty = lty.grid)\n";
	r3D <<  "  }\n";
	r3D <<  "  if (\"xz\" %in% grid) {\n";
	r3D <<  "    i <- x.min:x.max\n";
	r3D <<  "    segments(i + (yx.f * y.max), yz.f * y.max + z.min, \n";
	r3D <<  "             i + (yx.f * y.max), yz.f * y.max + z.max, \n";
	r3D <<  "             col = col.grid, lty = lty.grid)\n";
	r3D <<  "    temp <- yx.f * y.max\n";
	r3D <<  "    temp1 <- yz.f * y.max\n";
	r3D <<  "    i <- z.min:z.max\n";
	r3D <<  "    segments(x.min + temp,temp1 + i, \n";
	r3D <<  "             x.max + temp,temp1 + i , col = col.grid, lty = lty.grid)\n";
	r3D <<  "  }\n";
	r3D <<  "  if (\"yz\" %in% grid) {\n";
	r3D <<  "    i <- 0:y.max\n";
	r3D <<  "    segments(x.min + (i * yx.f), i * yz.f + z.min,  \n";
	r3D <<  "             x.min + (i * yx.f) ,i * yz.f + z.max,  \n";
	r3D <<  "             col = col.grid, lty = lty.grid)\n";
	r3D <<  "    temp <- yx.f * y.max\n";
	r3D <<  "    temp1 <- yz.f * y.max\n";
	r3D <<  "    i <- z.min:z.max\n";
	r3D <<  "    segments(x.min + temp,temp1 + i, \n";
	r3D <<  "             x.min, i , col = col.grid, lty = lty.grid)\n";
	r3D <<  "  }\n";
	r3D <<  "  if (axis) {\n";
	r3D <<  "    xx <- if (angle.2) \n";
	r3D <<  "      c(x.min, x.max)\n";
	r3D <<  "    else c(x.max, x.min)\n";
	r3D <<  "    if (tick.marks) {\n";
	r3D <<  "      xtl <- (z.max - z.min) * (tcl <- -par(\"tcl\"))/50\n";
	r3D <<  "      ztl <- (x.max - x.min) * tcl/50\n";
	r3D <<  "      mysegs <- function(x0, y0, x1, y1) segments(x0, \n";
	r3D <<  "                                                  y0, x1, y1, col = col.axis, lty = lty.axis)\n";
	r3D <<  "      i.y <- 0:y.max\n";
	r3D <<  "      mysegs(yx.f * i.y - ztl + xx[1], yz.f * i.y + z.min, \n";
	r3D <<  "             yx.f * i.y + ztl + xx[1], yz.f * i.y + z.min)\n";
	r3D <<  "      i.x <- x.min:x.max\n";
	r3D <<  "      mysegs(i.x, -xtl + z.min, i.x, xtl + z.min)\n";
	r3D <<  "      i.z <- z.min:z.max\n";
	r3D <<  "      mysegs(-ztl + xx[2], i.z, ztl + xx[2], i.z)\n";
	r3D <<  "      if (label.tick.marks) {\n";
	r3D <<  "        las <- par(\"las\")\n";
	r3D <<  "        mytext <- function(labels, side, at, ...) mtext(text = labels, \n";
	r3D <<  "                                                        side = side, at = at, line = -0.5, col = col.lab, \n";
	r3D <<  "                                                        cex = cex.axis, font = font.lab, ...)\n";
	r3D <<  "        if (is.null(x.ticklabs)) \n";
	r3D <<  "          x.ticklabs <- format(i.x * x.scal)\n";
	r3D <<  "        mytext(x.ticklabs, side = 1, at = i.x)\n";
	r3D <<  "        if (is.null(z.ticklabs)) \n";
	r3D <<  "          z.ticklabs <- format(i.z * z.scal)\n";
	r3D <<  "        mytext(z.ticklabs, side = if (angle.1) \n";
	r3D <<  "          4\n";
	r3D <<  "          else 2, at = i.z, adj = if (0 < las && las < \n";
	r3D <<  "                                      3) \n";
	r3D <<  "            1\n";
	r3D <<  "          else NA)\n";
	r3D <<  "        temp <- if (angle > 2) \n";
	r3D <<  "          rev(i.y)\n";
	r3D <<  "        else i.y\n";
	r3D <<  "        if (is.null(y.ticklabs)) \n";
	r3D <<  "          y.ticklabs <- format(y.prty)\n";
	r3D <<  "        else if (angle > 2) \n";
	r3D <<  "          y.ticklabs <- rev(y.ticklabs)\n";
	r3D <<  "        text(i.y * yx.f + xx[1], i.y * yz.f + z.min, \n";
	r3D <<  "             y.ticklabs, pos = if (angle.1) \n";
	r3D <<  "               2\n";
	r3D <<  "             else 4, offset = 1, col = col.lab, cex = cex.axis/par(\"cex\"), \n";
	r3D <<  "             font = font.lab)\n";
	r3D <<  "      }\n";
	r3D <<  "    }\n";
	r3D <<  "    mytext2 <- function(lab, side, line, at) mtext(lab, \n";
	r3D <<  "                                                   side = side, line = line, at = at, col = col.lab, \n";
	r3D <<  "                                                   cex = cex.lab, font = font.axis, las = 0)\n";
	r3D <<  "    lines(c(x.min, x.max), c(z.min, z.min), col = col.axis, \n";
	r3D <<  "          lty = lty.axis)\n";
	r3D <<  "    mytext2(xlab, 1, line = 1.5, at = mean(x.range))\n";
	r3D <<  "    lines(xx[1] + c(0, y.max * yx.f), c(z.min, y.max * yz.f + \n";
	r3D <<  "                                          z.min), col = col.axis, lty = lty.axis)\n";
	r3D <<  "    mytext2(ylab, if (angle.1) \n";
	r3D <<  "      2\n";
	r3D <<  "      else 4, line = 0.5, at = z.min + y.max * yz.f)\n";
	r3D <<  "    lines(xx[c(2, 2)], c(z.min, z.max), col = col.axis, \n";
	r3D <<  "          lty = lty.axis)\n";
	r3D <<  "    mytext2(zlab, if (angle.1) \n";
	r3D <<  "      4\n";
	r3D <<  "      else 2, line = 1.5, at = mean(z.range))\n";
	r3D <<  "    if (box) {\n";
	r3D <<  "      if (is.null(lty.hide)) \n";
	r3D <<  "        lty.hide <- lty.axis\n";
	r3D <<  "      temp <- yx.f * y.max\n";
	r3D <<  "      temp1 <- yz.f * y.max\n";
	r3D <<  "      lines(c(x.min + temp, x.max + temp), c(z.min + temp1, \n";
	r3D <<  "                                             z.min + temp1), col = col.axis, lty = lty.hide)\n";
	r3D <<  "      lines(c(x.min + temp, x.max + temp), c(temp1 + z.max, \n";
	r3D <<  "                                             temp1 + z.max), col = col.axis, lty = lty.axis)\n";
	r3D <<  "      temp <- c(0, y.max * yx.f)\n";
	r3D <<  "      temp1 <- c(0, y.max * yz.f)\n";
	r3D <<  "      lines(temp + xx[2], temp1 + z.min, col = col.axis, \n";
	r3D <<  "            lty = lty.hide)\n";
	r3D <<  "      lines(temp + x.min, temp1 + z.max, col = col.axis, \n";
	r3D <<  "            lty = lty.axis)\n";
	r3D <<  "      temp <- yx.f * y.max\n";
	r3D <<  "      temp1 <- yz.f * y.max\n";
	r3D <<  "      lines(c(temp + x.min, temp + x.min), c(z.min + temp1, \n";
	r3D <<  "                                             z.max + temp1), col = col.axis, lty = if (!angle.2) \n";
	r3D <<  "                                               lty.hide\n";
	r3D <<  "            else lty.axis)\n";
	r3D <<  "      lines(c(x.max + temp, x.max + temp), c(z.min + temp1, \n";
	r3D <<  "                                             z.max + temp1), col = col.axis, lty = if (angle.2) \n";
	r3D <<  "                                               lty.hide\n";
	r3D <<  "            else lty.axis)\n";
	r3D <<  "    }\n";
	r3D <<  "  }\n";
	r3D <<  "  x <- dat$x + (dat$y * yx.f)\n";
	r3D <<  "  z <- dat$z + (dat$y * yz.f)\n";
	r3D <<  "  col <- as.character(dat$col)\n";
	r3D <<  "  if (type == \"h\") {\n";
	r3D <<  "    z2 <- dat$y * yz.f + z.min\n";
	r3D <<  "    segments(x, z, x, z2, col = col, cex = cex.symbols, \n";
	r3D <<  "             lty = lty.hplot, ...)\n";
	r3D <<  "    points(x, z, type = \"p\", col = col, pch = pch, bg = bg, \n";
	r3D <<  "           cex = cex.symbols, ...)\n";
	r3D <<  "  }\n";
	r3D <<  "  else points(x, z, type = type, col = col, pch = pch, bg = bg, \n";
	r3D <<  "              cex = cex.symbols, ...)\n";
	r3D <<  "  if (axis && box) {\n";
	r3D <<  "    lines(c(x.min, x.max), c(z.max, z.max), col = col.axis, \n";
	r3D <<  "          lty = lty.axis)\n";
	r3D <<  "    lines(c(0, y.max * yx.f) + x.max, c(0, y.max * yz.f) + \n";
	r3D <<  "            z.max, col = col.axis, lty = lty.axis)\n";
	r3D <<  "    lines(xx[c(1, 1)], c(z.min, z.max), col = col.axis, \n";
	r3D <<  "          lty = lty.axis)\n";
	r3D <<  "  }\n";
	r3D <<  "  ob <- ls()\n";
	r3D <<  "  rm(list = ob[!ob %in% c(\"angle\", \"mar\", \"usr\", \"x.scal\", \n";
	r3D <<  "                          \"y.scal\", \"z.scal\", \"yx.f\", \"yz.f\", \"y.add\", \"z.min\", \n";
	r3D <<  "                          \"z.max\", \"x.min\", \"x.max\", \"y.max\", \"x.prty\", \"y.prty\", \n";
	r3D <<  "                          \"z.prty\")])\n";
	r3D <<  "  rm(ob)\n";
	r3D <<  "  invisible(list(xyz.convert = function(x, y = NULL, z = NULL) {\n";
	r3D <<  "    xyz <- xyz.coords(x, y, z)\n";
	r3D <<  "    if (angle > 2) {\n";
	r3D <<  "      temp <- xyz$x\n";
	r3D <<  "      xyz$x <- xyz$y\n";
	r3D <<  "      xyz$y <- temp\n";
	r3D <<  "    }\n";
	r3D <<  "    y <- (xyz$y - y.add)/y.scal\n";
	r3D <<  "    return(list(x = xyz$x/x.scal + yx.f * y, y = xyz$z/z.scal + \n";
	r3D <<  "                  yz.f * y))\n";
	r3D <<  "  }, points3d = function(x, y = NULL, z = NULL, type = \"p\", \n";
	r3D <<  "                         ...) {\n";
	r3D <<  "    xyz <- xyz.coords(x, y, z)\n";
	r3D <<  "    if (angle > 2) {\n";
	r3D <<  "      temp <- xyz$x\n";
	r3D <<  "      xyz$x <- xyz$y\n";
	r3D <<  "      xyz$y <- temp\n";
	r3D <<  "    }\n";
	r3D <<  "    y2 <- (xyz$y - y.add)/y.scal\n";
	r3D <<  "    x <- xyz$x/x.scal + yx.f * y2\n";
	r3D <<  "    y <- xyz$z/z.scal + yz.f * y2\n";
	r3D <<  "    mem.par <- par(mar = mar, usr = usr)\n";
	r3D <<  "    on.exit(par(mem.par))\n";
	r3D <<  "    if (type == \"h\") {\n";
	r3D <<  "      y2 <- z.min + yz.f * y2\n";
	r3D <<  "      segments(x, y, x, y2, ...)\n";
	r3D <<  "      points(x, y, type = \"p\", ...)\n";
	r3D <<  "    } else points(x, y, type = type, ...)\n";
	r3D <<  "  }, plane3d = function(Intercept, x.coef = NULL, y.coef = NULL, \n";
	r3D <<  "                        lty = \"dashed\", lty.box = NULL, ...) {\n";
	r3D <<  "    if (!is.atomic(Intercept) && !is.null(coef(Intercept))) Intercept <- coef(Intercept)\n";
	r3D <<  "    if (is.null(lty.box)) lty.box <- lty\n";
	r3D <<  "    if (is.null(x.coef) && length(Intercept) == 3) {\n";
	r3D <<  "      x.coef <- Intercept[if (angle > 2) 3 else 2]\n";
	r3D <<  "      y.coef <- Intercept[if (angle > 2) 2 else 3]\n";
	r3D <<  "      Intercept <- Intercept[1]\n";
	r3D <<  "    }\n";
	r3D <<  "    mem.par <- par(mar = mar, usr = usr)\n";
	r3D <<  "    on.exit(par(mem.par))\n";
	r3D <<  "    x <- x.min:x.max\n";
	r3D <<  "    ltya <- c(lty.box, rep(lty, length(x) - 2), lty.box)\n";
	r3D <<  "    x.coef <- x.coef * x.scal\n";
	r3D <<  "    z1 <- (Intercept + x * x.coef + y.add * y.coef)/z.scal\n";
	r3D <<  "    z2 <- (Intercept + x * x.coef + (y.max * y.scal + y.add) * \n";
	r3D <<  "             y.coef)/z.scal\n";
	r3D <<  "    segments(x, z1, x + y.max * yx.f, z2 + yz.f * y.max, \n";
	r3D <<  "             lty = ltya, ...)\n";
	r3D <<  "    y <- 0:y.max\n";
	r3D <<  "    ltya <- c(lty.box, rep(lty, length(y) - 2), lty.box)\n";
	r3D <<  "    y.coef <- (y * y.scal + y.add) * y.coef\n";
	r3D <<  "    z1 <- (Intercept + x.min * x.coef + y.coef)/z.scal\n";
	r3D <<  "    z2 <- (Intercept + x.max * x.coef + y.coef)/z.scal\n";
	r3D <<  "    segments(x.min + y * yx.f, z1 + y * yz.f, x.max + y * \n";
	r3D <<  "               yx.f, z2 + y * yz.f, lty = ltya, ...)\n";
	r3D <<  "  }, box3d = function(...) {\n";
	r3D <<  "    mem.par <- par(mar = mar, usr = usr)\n";
	r3D <<  "    on.exit(par(mem.par))\n";
	r3D <<  "    lines(c(x.min, x.max), c(z.max, z.max), ...)\n";
	r3D <<  "    lines(c(0, y.max * yx.f) + x.max, c(0, y.max * yz.f) + \n";
	r3D <<  "            z.max, ...)\n";
	r3D <<  "    lines(c(0, y.max * yx.f) + x.min, c(0, y.max * yz.f) + \n";
	r3D <<  "            z.max, ...)\n";
	r3D <<  "    lines(c(x.max, x.max), c(z.min, z.max), ...)\n";
	r3D <<  "    lines(c(x.min, x.min), c(z.min, z.max), ...)\n";
	r3D <<  "    lines(c(x.min, x.max), c(z.min, z.min), ...)\n";
	r3D <<  "  }))\n";
	r3D <<  "}\n";

	// rows and columns
	r3D <<  "times=4\n";
	r3D <<  "bins=150\n";


	// depth recorded as a ratio of time 0 - reorint for forward vs. reverse;
	for (int i = 0; i < i_validgenes; i++) {
		r3D <<  "gene" << i << " = matrix(c(\n";

		std::vector<double> depthVector;

		if (i_bamFiles > 4) {
			for (int k = 1; k < 4; k++) {
				for (int j = 0; j < 150; j++) {	
					double d = normGeneVector[j+(k*150)+(i*5*150)] - normGeneVector[j+(i*5*150)];
					if (d > 0) {
						r3D << d << ", ";
						depthVector.push_back(d);
					} else {
						r3D << "0, ";
						depthVector.push_back(0);
					}
				}
			}
			for (int j = 0; j < 149; j++) {	
				double d = normGeneVector[j+((4)*150)+(i*5*150)] - normGeneVector[j+(i*5*150)];
				if (d > 0) {
					r3D << d << ", ";
					depthVector.push_back(d);
				} else {
					r3D << "0, ";
					depthVector.push_back(0);
				}
			}
			double d = normGeneVector[149+((4)*150)+(i*5*150)] - normGeneVector[149+(i*5*150)];
			if (d > 0) {
				r3D << d;
				depthVector.push_back(d);
			} else {
				r3D << "0";
				depthVector.push_back(0);
			}
		} else { // if 4 bam files
			for (int k = 0; k < 3; k++) {
				for (int j = 0; j < 150; j++) {	
					double d = normGeneVector[j+(k*150)+(i*4*150)] - normGeneVector[j+(i*4*150)];
					if (d > 0) {
						r3D << d << ", ";
						depthVector.push_back(d);
					} else {
						r3D << "0, ";
						depthVector.push_back(0);
					}
				}
			}
			for (int j = 0; j < 149; j++) {	
				double d = normGeneVector[j+((3)*150)+(i*4*150)] - normGeneVector[j+(i*4*150)];
				if (d > 0) {
					r3D << d << ", ";
					depthVector.push_back(d);
				} else {
					r3D << "0, ";
					depthVector.push_back(0);
				}
			}
			double d = normGeneVector[149+((3)*150)+(i*4*150)] - normGeneVector[149+(i*4*150)];
			if (d > 0) {
				r3D << d;
				depthVector.push_back(d);
			} else {
				r3D << "0";  
				depthVector.push_back(0);
			}
		}


		r3D << "), nrow=150, ncol=4)\n";
		r3D << "x <- rep(1:bins,times)\n";
		r3D << "y <- rep(1:times,each=bins)\n";
		r3D << "z <- as.vector(gene" << i << ")\n";

		r3D << "graph" << i << "=sactter.grid(x,y,z, #highlight.3d=TRUE,\n";
		r3D << "	 col.axis=\"black\", main=\"Time Dependent Read Profile of Gene " << validGeneVector[i] << "\", xlab=\"\", ylab=\"\", zlab=\"\",\n";
		r3D << "	# x.ticklabs = '',\n";

		// figure out y axis max
		double d_max = 0;
		
		for (int i = 0; i < depthVector.size(); i++) {			
			double d_temp = depthVector[i];
			if (d_temp > d_max)
				d_max = d_temp;
		}

		int i_exp = log10(d_max); // get exponent
		std::string s_divisor = "1";

		for (int i = 0; i < i_exp; i++) 
			s_divisor += "0";

		double d_mantissaMax = d_max/stod(s_divisor);
		double d_yAxisMax = yAxisMax(d_mantissaMax, i_exp);	
		depthVector.clear();

		r3D << "	 ylim=1:4, xlim=0:150, zlim=0:" << d_yAxisMax << ",\n";

		r3D << "	 tick.marks=FALSE,type=\"h\",\n";
		r3D << "	 grid=c('xy','xz','yz'),\n";
		r3D << "	 col.grid=\"grey80\",box = FALSE, cex.symbols=0.001,color=\"grey60\")\n";


		// draw lines
		r3D << "for(j in 4:4){\n";
		r3D << "  for(i in 1:(bins-1)){\n";
		r3D << "    pts=graph" << i << "$xyz.convert(x=c(i,i+1),y=c(j,j),z=c(gene" << i << "[i,j],gene" << i << "[i+1,j]))\n";
		r3D << "    segments(pts$x[1],pts$y[1],pts$x[2],pts$y[2], col= 'black', lwd=2)\n";
		r3D << "  }}\n";
		r3D << "for(j in 3:3){\n";
		r3D << "  for(i in 1:(bins-1)){\n";
		r3D << "    pts=graph" << i << "$xyz.convert(x=c(i,i+1),y=c(j,j),z=c(gene" << i << "[i,j],gene" << i << "[i+1,j]))\n";
		r3D << "    segments(pts$x[1],pts$y[1],pts$x[2],pts$y[2], col= 'dodgerblue4', lwd=2)\n";
		r3D << "  }}\n";
		r3D << "for(j in 2:2){\n";
		r3D << "  for(i in 1:(bins-1)){\n";
		r3D << "    pts=graph" << i << "$xyz.convert(x=c(i,i+1),y=c(j,j),z=c(gene" << i << "[i,j],gene" << i << "[i+1,j]))\n";
		r3D << "    segments(pts$x[1],pts$y[1],pts$x[2],pts$y[2], col= 'forestgreen', lwd=2)\n";
		r3D << "  }}\n";
		r3D << "for(j in 1:1){\n";
		r3D << "  for(i in 1:(bins-1)){\n";
		r3D << "    pts=graph" << i << "$xyz.convert(x=c(i,i+1),y=c(j,j),z=c(gene" << i << "[i,j],gene" << i << "[i+1,j]))\n";
		r3D << "    segments(pts$x[1],pts$y[1],pts$x[2],pts$y[2], col= 'firebrick', lwd=2)\n";
		r3D << "  }}\n";


		//r3D << "rect(0.5, -0.3, 2.5, -0.1, density = 100, col = \"green4\", border = \"black\", xpd = TRUE)\n";

		// draw exons
		std::string s_geneName = validGeneVector[i];
		//r3D << "rect(0.5, -0.3, 2.5, -0.1, density = 100, col = \"green4\", border = \"black\", xpd = TRUE)\n";

		int i_exons = exonNumber(s_geneName, s_genelistFile);

		std::string s_exonStartString = exonStartString(s_geneName, s_genelistFile, i_exons);
		std::string s_exonEndString = exonEndString(s_geneName, s_genelistFile, i_exons);

		std::vector<double> exonStartVector(0);
		std::vector<double> exonEndVector(0);

		// start exon vector
		for (int i = 0; i < i_exons-1; i++) { 
			int i_anExon = exons(s_exonStartString);
			exonStartVector.push_back(i_anExon);
			s_exonStartString = exonStringSnipper(s_exonStartString);
		}	
		exonStartVector.push_back(stoi(s_exonStartString));

		// end exon vector
		for (int i = 0; i < i_exons-1; i++) { 
			int i_anExon = exons(s_exonEndString);
			exonEndVector.push_back(i_anExon);
			s_exonEndString = exonStringSnipper(s_exonEndString);
		}	
		exonEndVector.push_back(stoi(s_exonEndString));

		std::string s_strand = strand(s_geneName, s_genelistFile);

		double d_start = startEnd(s_geneName, s_genelistFile, std::string ("start"));
		double d_end = startEnd(s_geneName, s_genelistFile, std::string ("end"));

		double d_length = d_end-d_start;
		if (s_strand == "+") { // strand is positive
			for (int i = 0; i < i_exons; i++) { 
				double d_boxStart = 0.5 + (2 * (exonStartVector[i] - d_start) / d_length); 
				double d_boxEnd = 0.5 + (2 * (exonEndVector[i] - d_start) / d_length);
				r3D << "rect(" << d_boxStart << ", -0.3, " << d_boxEnd << ", -0.1, density = 100, col = \"black\", border = \"black\", xpd = TRUE)\n";	
			} 
		} else { // strand is negtive
			for (int i = i_exons-1; i > -1; i--) { 
				double d_boxStart = 0.5 + (2 * (d_end - exonEndVector[i]) / d_length); 
				double d_boxEnd = 0.5 + (2 * (d_end - exonStartVector[i]) / d_length);
				r3D << "rect(" << d_boxStart << ", -0.3, " << d_boxEnd << ", -0.1, density = 100, col = \"black\", border = \"black\", xpd = TRUE)\n";	
			}
		}
		exonStartVector.clear();
		exonEndVector.clear();




		r3D << "# draw upstream and downstream gene\n";
		r3D << "arrows(0.5, -0.2, 2.5, -0.2,length = 0,lwd=2)\n";
		r3D << "arrows(2.5, -0.2, 3, -0.2,length = 0,lwd=0.9)\n";
		r3D << "arrows(0, -0.2, 0.15, -0.2,length = 0.05,lwd=0.9)\n";
		r3D << "arrows(0, -0.2, 0.35, -0.2,length = 0.05,lwd=0.9)\n";
		r3D << "arrows(0, -0.2, 0.5, -0.2,length = 0,lwd=0.9)\n";
		r3D << "arrows(2.5, -0.2, 2.65, -0.2,length = 0.05,lwd=0.9)\n";
		r3D << "arrows(2.5, -0.2, 2.85, -0.2,length = 0.05,lwd=0.9)\n";

		r3D << "# y axis (depth)\n";
		r3D << "arrows(-0.2, 2.6, -0.2, 3.5,length = 0.1, xpd = TRUE)\n";
		r3D << "arrows(-0.2, 2.4, -0.2, 1.5,length = 0.1, xpd = TRUE)\n";
		r3D << "text(c(-0.2,-0.2),c(4,1),labels=c(\"high\",\"low\"),cex = 0.8, srt=90, xpd = TRUE)\n";
		r3D << "text(c(-0.5),c(2.5),labels=c(\"Depth\"), srt=90, xpd = TRUE)\n";

		r3D << "# z axis (time)\n";
		r3D << "arrows(4.9, 1.25, 5.5, 1.75,length = 0.1, xpd = TRUE)\n";
		r3D << "arrows(4.7, 1.1, 4.1, 0.6,length = 0.1, xpd = TRUE)\n";
		r3D << "text(c(5.8,3.9),c(1.95,0.4),labels=c(\"high\",\"low\"),cex = 0.8, srt=38, xpd = TRUE)\n";
		r3D << "text(c(4.95),c(0.95),labels=c(\"Time\"), srt=38, xpd = TRUE)\n";

	}

	r3D.close();
}




