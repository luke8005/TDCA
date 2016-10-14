#include <fstream>     // write to file
#include <iostream>    // input/output
#include <string>
#include <vector>
#include <chrono>

using namespace std::chrono;


// forward declaration
double samDregion(std::string s_Bamfile, std::string s_PeakCoordinates);
std::string bedToCoordinates(std::string bedLine);
std::string bamGetter(std::string s_dir, int i_turnoverTime);
double samDtotal(std::string s_Bamfile);
std::string geneToCoordinates(std::string s_gene, std::string s_genelistFile);
void treDcalculatorInput(double transferArr[][150], std::string s_bamPath, std::string s_geneinfo, std::string s_inputBamPath, double d_minDepth, double d_minInputDepth, double depthArr[], double inputDepthArr[], int j);
void treDcalculator(double transferArr[][150], std::string s_bamPath, std::string s_geneinfo, double d_minDepth, double depthArr[], int j);


int writeReadsToVectorParallel(std::string bamFolderArr[], std::string inputBamFolderArr[], bool b_bamInputFlagCall, int i_bamRep, int i_iterator, std::string s_name, int i_bamFiles, int turnoverTimes[], std::string s_bed, std::vector<std::vector<std::string> > &normReadsVector, bool b_genelistFlagCall, std::string s_genelist, std::vector<double> &normGeneVector, std::string s_genelistFile, std::vector<std::string> &validGeneVector, int i_peakNumber)
{

	//variables to read a BED file for samtools depth -r command
	std::ifstream inBed(s_bed); // user specified bed file
	std::string line;

	std::string s_relativePath ("./");
	std::string s_bamDirectory = s_relativePath + bamFolderArr[i_iterator];

	std::string s_inputBamDirectory;
	if (b_bamInputFlagCall)
		s_inputBamDirectory = s_relativePath + inputBamFolderArr[i_iterator];

	// Numbers for total depth normalization
	double d_minDepth; // max samtools depth value in bam folder
	double depthArr[i_bamFiles];

	double d_minInputDepth; // max samtools depth value in input bam folder
	double inputDepthArr[i_bamFiles];



	high_resolution_clock::time_point t1 = high_resolution_clock::now(); // TIME XXX

	if (b_bamInputFlagCall) {
		std::cout << "Calculating max depth for each input bam file in rep " << i_iterator+1 << "." << std::endl;
		#pragma omp parallel for 
		for (int j = 0; j < i_bamFiles; j++) { // for each input bam file

			std::string s_inputBamfile = bamGetter(s_inputBamDirectory, turnoverTimes[j]);
			//std::string s_inputBamPath = s_relativePath + inputBamFolderArr[i_iterator] + s_inputBamfile;
			std::string s_inputBamPath = s_inputBamfile;

			inputDepthArr[j] = samDtotal(s_inputBamPath);
			std::cout << "Input bam file: " << s_inputBamPath << " has depth " << inputDepthArr[j] << std::endl;
		}
		d_minInputDepth = inputDepthArr[0];
		for (int j = 1; j < i_bamFiles; j++) { // for each bam file
			if (inputDepthArr[j] < d_minInputDepth)
				d_minInputDepth = inputDepthArr[j];
		}
	}

	std::cout << "Calculating max depth for each bam file in rep " << i_iterator+1 << "." << std::endl;
	#pragma omp parallel for 
	for (int j = 0; j < i_bamFiles; j++) { // for each bam file

		std::string s_Bamfile = bamGetter(s_bamDirectory, turnoverTimes[j]);
		//std::string s_bamPath = s_relativePath + bamFolderArr[i_iterator] + s_Bamfile;
		std::string s_bamPath = s_Bamfile;

		depthArr[j] = samDtotal(s_bamPath);
		std::cout << "Bam file: " << s_bamPath << " has depth " << depthArr[j] << std::endl;
	}

	d_minDepth = depthArr[0];
	for (int j = 1; j < i_bamFiles; j++) { // for each bam file
		if (depthArr[j] < d_minDepth)
			d_minDepth = depthArr[j];
	}



	high_resolution_clock::time_point t2 = high_resolution_clock::now(); // TIME XXX
	auto samT = duration_cast<seconds>( t2 - t1 ).count(); // TIME XXX
	//std::cout << "samT: " << samT << std::endl; // TIME XXX



	high_resolution_clock::time_point t3 = high_resolution_clock::now(); // TIME XXX

	std::cout << "Min depth for rep " << i_iterator+1 << ": " << d_minDepth << std::endl;
	if (b_bamInputFlagCall) // if input is available 
		std::cout << "Min depth for input rep " << i_iterator+1 << ": " << d_minInputDepth << std::endl;

	std::cout << "Writing normalized read vector." << std::endl;
	std::vector<std::string> lineVector;
	std::string transferArr[i_bamFiles]; 

	// for progress
	float f_progress = 0.0;
	int i_barWidth = 20;
	double d_progiterator = 0;

	// if input is available
	if (b_bamInputFlagCall) {
		while (std::getline(inBed, line, '\n')) {
			std::string s_coordinates = bedToCoordinates(line);
			lineVector.push_back(s_coordinates);
			#pragma omp parallel for 
			for (int j = 0; j < i_bamFiles; j++) { // for each bam file
				std::string s_Bamfile = bamGetter(s_bamDirectory, turnoverTimes[j]);
				std::string s_inputBamfile = bamGetter(s_inputBamDirectory, turnoverTimes[j]);
				//std::string s_bamPath = s_relativePath + bamFolderArr[i_iterator] + s_Bamfile;
				std::string s_bamPath = s_Bamfile;
				//std::string s_inputBamPath = s_relativePath + inputBamFolderArr[i_iterator] + s_inputBamfile;
				std::string s_inputBamPath = s_inputBamfile;
				double d = (samDregion(s_bamPath, s_coordinates) / depthArr[j] * d_minDepth) - (samDregion(s_inputBamPath, s_coordinates) / inputDepthArr[j] * d_minInputDepth); // subtract input 
				if (d > 0) {
					transferArr[j] = (std::to_string(d));
				} else {
					transferArr[j] = "0";
				}
			}
			for (int k = 0; k < i_bamFiles; k++) {
				lineVector.push_back(transferArr[k]);
			}
			normReadsVector.push_back(lineVector);	
			lineVector.clear();

			
			// Progress
			std::cout << "[";
			int i_pos = i_barWidth * f_progress;
			for (int i = 0; i < i_barWidth; i++) {
				if (i <= i_pos) std::cout << "=";
				else std::cout << " ";
			}

			if (d_progiterator == i_peakNumber-1) { // 100% complete
				std::cout << "] " << int(100) << " %\rReplicate " << i_iterator+1 << "/" << i_bamRep << " ";
				std::cout.flush();
			} else {
				std::cout << "] " << int((f_progress+0.01) * 100.0) << "  %\rReplicate " << i_iterator+1 << "/" << i_bamRep << " ";
				std::cout.flush();
			}

			f_progress = d_progiterator/i_peakNumber;
			d_progiterator++;
		}
		std::cout << std::endl;


	} else { // no input 
		while (std::getline(inBed, line, '\n')) {
			std::string s_coordinates = bedToCoordinates(line);
			lineVector.push_back(s_coordinates);
			#pragma omp parallel for 
			for (int j = 0; j < i_bamFiles; j++) { // for each bam file

				std::string s_Bamfile = bamGetter(s_bamDirectory, turnoverTimes[j]);
				//std::string s_bamPath = s_relativePath + bamFolderArr[i_iterator] + s_Bamfile;
				std::string s_bamPath = s_Bamfile;
				transferArr[j] = std::to_string((samDregion(s_bamPath, s_coordinates) / depthArr[j] * d_minDepth));

			}
			for (int k = 0; k < i_bamFiles; k++) {
				lineVector.push_back(transferArr[k]);
			}			
			normReadsVector.push_back(lineVector);
			lineVector.clear();


			// Progress
			std::cout << "[";
			int i_pos = i_barWidth * f_progress;
			for (int i = 0; i < i_barWidth; i++) {
				if (i <= i_pos) std::cout << "=";
				else std::cout << " ";
			}

			if (d_progiterator == i_peakNumber-1) { // 100% complete
				std::cout << "] " << int(100) << " %\rReplicate " << i_iterator+1 << "/" << i_bamRep << " ";
				std::cout.flush();
			} else {
				std::cout << "] " << int((f_progress+0.01) * 100.0) << "  %\rReplicate " << i_iterator+1 << "/" << i_bamRep << " ";
				std::cout.flush();
			}


			f_progress = d_progiterator/i_peakNumber;
			d_progiterator++;
		}
		std::cout << std::endl;

	}






	line = "";
	std::ifstream inGeneList(s_genelist); // user specified genelist file
	int i_validgenes = 0;

	if (b_genelistFlagCall) { // calculate depth at 1% bins of genes
		std::cout << "Calculating 3d gene profiles for rep " << i_iterator+1. << std::endl;
		
		if (b_bamInputFlagCall) { // if input is available
			while (std::getline(inGeneList, line, '\n')) {
				std::cout << "Calculating profile for gene " << line << ".\n";
				// returns gene coordinates as: chr \t start \t end \t strand
				std::string s_geneinfo = geneToCoordinates(line, s_genelistFile);

				if (line == "") { // gene not found
					std::cout << "Gene " << line << " isn't listed as a refseq gene and " <<
						"will not be included in analysis.\n";
				} else { // gene found

					double transferArr[i_bamFiles][150]; //rows, cols

					#pragma omp parallel for 
					for (int j = 0; j < i_bamFiles; j++) { // for each bam file
						std::string s_Bamfile = bamGetter(s_bamDirectory, turnoverTimes[j]);
						std::string s_inputBamfile = bamGetter(s_inputBamDirectory, turnoverTimes[j]);
						//std::string s_bamPath = s_relativePath + bamFolderArr[i_iterator] + s_Bamfile;
						std::string s_bamPath = s_Bamfile;
						//std::string s_inputBamPath = s_relativePath + inputBamFolderArr[i_iterator] + s_inputBamfile;
						std::string s_inputBamPath = s_inputBamfile;
						// calculate depth and write to normGeneVector
						treDcalculatorInput(transferArr, s_bamPath, s_geneinfo, s_inputBamPath, d_minDepth, d_minInputDepth, depthArr, inputDepthArr, j);
					}
					for(int j = 0; j < i_bamFiles; j++) {	 //This loops on the columns   
						for(int i = 0; i < 150; i++) {   	 //This loops on the rows.     
							normGeneVector.push_back(transferArr[j][i]); 			 
						}											 
					}												 
					validGeneVector.push_back(line); 
					i_validgenes++;
				}
				line = "";

			
				//XXX PROGRESS XXX		


			} // while still genes
		} else { // no input declared
			while (std::getline(inGeneList, line, '\n')) {
				std::cout << "Calculating profile for gene " << line << ".\n";
				// returns gene coordinates as: chr \t start \t end \t strand
				std::string s_geneinfo = geneToCoordinates(line, s_genelistFile);

				if (line == "") { // gene not found
					std::cout << "Gene " << line << " isn't listed as a refseq gene and " <<
						"will not be included in analysis.\n";
				} else {

					double transferArr[i_bamFiles][150]; //rows, cols

					#pragma omp parallel for 
					for (int j = 0; j < i_bamFiles; j++) { // for each bam file
						std::string s_Bamfile = bamGetter(s_bamDirectory, turnoverTimes[j]);
						//std::string s_bamPath = s_relativePath + bamFolderArr[i_iterator] + s_Bamfile;
						std::string s_bamPath = s_Bamfile;
						// calculate depth and write to normGeneVector
						treDcalculator(transferArr, s_bamPath, s_geneinfo, d_minDepth, depthArr, j);

					}
					for(int j = 0; j < i_bamFiles; j++) {	 //This loops on the columns  
						for(int i = 0; i < 150; i++) {   	 //This loops on the rows.    
							normGeneVector.push_back(transferArr[j][i]); 			
						}											 
					}												
					validGeneVector.push_back(line); 
					i_validgenes++;
				}
				line = "";

				//XXX PROGRESS XXX


			} // while still genes
		}
	} // if genelist


	high_resolution_clock::time_point t4 = high_resolution_clock::now(); // TIME XXX
	auto samR = duration_cast<seconds>( t4 - t3 ).count(); // TIME XXX
	//std::cout << "samR: " << samR << std::endl; // TIME XXX


	return i_validgenes;
}


