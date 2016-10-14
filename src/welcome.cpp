#include <iostream>
#include <sstream>
#include <string>

int welcome()
{
	std::cout << "Welcome to TDCA. For user manual and detailed usage see: https://github.com/luke8005/TDCA" << std::endl;
	std::cout << "Usage: tdca <-bed peaks.bed> <-bam folder/> [options]" << std::endl;
	std::cout << "Example: tdca -bed ChIP-seq.peaks.bed -bam bamFolder/ -i bamInputFolder/ -g mm9 -n exp-name" <<
		std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "    -v			Display program version and exit program." << std::endl;
	std::cout << "    -h			Display this page and exit program." << std::endl;
	std::cout << "    -bam 		User specified folder containing sorted bam turnover files " <<
							"including index files." << std::endl;
	std::cout << "    -i 			User specified folder containing sorted input bam turnover " << 
							"files including index files." << std::endl;
	std::cout << "    -bed 		User specified bed file containing loci of interest." << std::endl;
	std::cout << "    -g 			Genome name." << std::endl;
	std::cout << "    -3d 		User specified gene file containing RefSeq gene names." << std::endl;
	std::cout << "    -s 			Saturation threshold (allowable range from 0.5-0.95)." << std::endl;
	std::cout << "    -n	 		User specified name for output files." << std::endl;
	return 0;
}
