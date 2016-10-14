/**
 **  This file handles all flags and records necessary values for downstream calculations
 **/
#include <fstream>     		// write to file
#include <iostream>    		// input/output
#include <sstream>
#include <string>
#include <dirent.h>    		// directory access
#include <vector>
#include "LocusTurnover.h"
#include <algorithm>


// Forward declarations
int welcome();
int fileCount(std::string s_dir);
int bamFileCount(std::string s_dir, int i_fileNumber);
int timeLogger(int *arr, std::string s_dir, int i_fileNumber);
double samDregion(std::string s_Bamfile, std::string s_PeakCoordinates);
std::string bedToCoordinates(std::string bedLine);
std::string bamGetter(std::string s_dir, int i_turnoverTime);
double samDtotal(std::string s_Bamfile);
std::string getExecPath();
int peakCounter(std::string s_bed);
int writeReadsToVectorParallel(std::string bamFolderArr[], std::string inputBamFolderArr[], bool b_bamInputFlagCall, int i_bamRep, int i_iterator, std::string s_name, int i_bamFiles, int turnoverTimes[], std::string s_bed, std::vector<std::vector<std::string> > &normReadsVector, bool b_genelistFlagCall, std::string s_genelist, std::vector<double> &normGeneVector, std::string s_genelistFile, std::vector<std::string> &validGeneVector, int i_peakNumber);
void normVectorAverage(int i_peakNumber, int i_bamFiles, int i_bamRep, std::vector<std::vector<std::string> > &normReadsVector, std::vector<std::vector<std::string> > &normAveVector);
void normVectorError(int i_peakNumber, int i_bamFiles, int i_bamRep, std::vector<std::vector<std::string> > &normReadsVector, std::vector<std::vector<std::string> > &normAveVector, std::vector<std::vector<std::string> > &normErrorVector);
bool genomeGetter(std::string s_dir, std::string s_genome, int i_fileNumber);
int extFileCount(std::string s_dir, int i_fileNumber, std::string s_extension);
std::string bedGetter(std::string s_dir, int i_iterator);
void bedToolsIntersect(std::string s_genomePath, std::string s_bed, std::vector<std::string> &featureVector, int i_loop);
void drcScriptGenerator(int i_loopNumber, int i_bamFiles, int i_truncDiff, int turnoverTimes[], std::vector<double> &turnoverArr, bool b_real, bool b_turnoverDirection, double d_overallMax);
void inflectionWriter(std::vector<std::string> &drcInflectionVector, std::vector<std::string> &drcResidualsVector,  std::vector<std::string> &drcUpperAsymVector, std::vector<std::string> &linResVector);
void rBar(std::string s_rPltsName, int i_bamFiles, int turnoverTimes[], int maxIndexArray[], int minIndexArray[], int i_peakNumber);
void rEnd(std::string s_rPltsName,std::string s_rPltsPDF, bool b_genomeFlagCall, int i_bamRep);
void rBegin(std::string s_rPltsName, std::string s_rPltsPDF, std::string s_args);
void rDensity(std::string s_rPltsName, int i_peakNumber, std::vector<std::string> drcInflectionVector, int i_bamFiles, int turnoverTimes[], std::string s_name);
void drcNormScriptGenerator(int i_loopNumber, int i_bamFiles, int i_truncDiff, int turnoverTimes[], std::vector<double> &turnoverArr, bool b_real, int i_minIndex, bool b_turnoverDirection, double d_overallMax);
void drcNormScriptGeneratorString(int i_loopNumber, int i_bamFiles, int i_truncDiff, int turnoverTimes[], std::vector<std::vector<std::string> > &normReadsVector, bool b_real, int i_minIndex, int i_bamRep, int i_peakNumber);
void rBoxplot(std::string s_rPltsName, int i_peakNumber, int i_genomeFileCount, int i_bamFiles, std::vector<std::vector<std::string> > &dataArray);
void rIdeohg19(std::string s_rPltsName, int i_bamFiles, int i_peakNumber, std::vector<std::vector<std::string> > &dataArray);
void rIdeohg38(std::string s_rPltsName, int i_bamFiles, int i_peakNumber, std::vector<std::vector<std::string> > &dataArray);
void rIdeomm10(std::string s_rPltsName, int i_bamFiles, int i_peakNumber, std::vector<std::vector<std::string> > &dataArray);
void rIdeomm9(std::string s_rPltsName, int i_bamFiles, int i_peakNumber, std::vector<std::vector<std::string> > &dataArray);
void rIdeodm3(std::string s_rPltsName, int i_bamFiles, int i_peakNumber, std::vector<std::vector<std::string> > &dataArray);
void rIdeodm6(std::string s_rPltsName, int i_bamFiles, int i_peakNumber, std::vector<std::vector<std::string> > &dataArray);
void rIdeoce11(std::string s_rPltsName, int i_bamFiles, int i_peakNumber, std::vector<std::vector<std::string> > &dataArray);
void normGeneVectorAverage(int i_bamFiles, int i_bamRep, int i_validgenes, std::vector<double> &normGeneVector, std::vector<double> &normGeneAveVector);
void r3Dadjusted(std::string s_genelistFile, std::string s_rGenePltsName, int i_bamFiles, int turnoverTimes[], int i_validgenes, std::vector<double> &normGeneVector, std::vector<std::string> &validGeneVector);
void geneVectorShrinkage(int i_validgenes, int i_bamFiles, std::vector<double> &normGeneVector, std::vector<double> &shrunkGeneVector);
void rBoxRes(std::string s_rPltsName, int i_peakNumber, int i_bamFiles, std::vector<std::string> &truncLinResVector, std::vector<std::string> &linResVector, std::vector<std::vector<std::string> > &dataArray);
void rPie(std::string s_rPltsName, int i_peakNumber, int i_tuncSat, int i_tuncNotSat, int i_notTuncSat, int i_notTuncNotSat, int i_eliminated);
void rStdev(std::string s_rPltsName, int i_bamFiles, int i_peakNumber, std::vector<std::vector<std::string> > &dataArray, std::vector<std::string> &drcUpperAsymVector, int turnoverTimes[]);
void rScat(std::string s_rPltsName, int i_bamFiles, int i_peakNumber, std::vector<std::vector<std::string> > &dataArray, std::vector<std::string> &drcUpperAsymVector);
void inflectionWriterReverse(std::vector<std::string> &drcInflectionVector, std::vector<std::string> &drcResidualsVector, std::vector<std::string> &linResVector);
std::string exec(const char* cmd);


bool exists(std::string filename)
{

	std::string s_command = "if [ -e ./" + filename + " ]; then echo \"t\"; fi;";
	std::string s_out = exec(s_command.c_str());
	s_out.erase(std::remove(s_out.begin(), s_out.end(), '\n'), s_out.end());
	if (s_out=="t") {
		return true;
	} else {return false;}
}

int main(int argc, char* argv[])
{
	/** -b flag variables **/
	std::string s_bamFlag = "-bam";	//name flag
	bool b_bamFlagCall(false);		//true if bam flag called
	std::string s_bamFolder; 		//folder name containing bam files of different 
							//turnover experiments 
	int i_totalBamFiles; 			//total files in the bamFolder
	int i_bamRep = 0;				//Number of replicates determined from number 
							//of bamFolders
	int i_bamFiles;				//number of bam files

	/** -i flag variables **/
	std::string s_bamInputFlag = "-i";	//name flag
	bool b_bamInputFlagCall(false);	//true if bamInput flag called
	std::string s_inputBamFolder; 	//folder name containing input bam files
							//for different turnover experiments.  
	int i_totalInputBamFiles;		//total files in the inputBamFolders
	int i_bamInputRep = 0; 			//Number of replicates determined from number 
							//of inputBamFolders. bamFolders == inputBamFolders.
	int i_bamInputFiles; 			//number of input bam files

	/** -g flag variables **/
	std::string s_genomeFlag = "-g";	//name flag
	bool b_genomeFlagCall(false);		//true if genome flag called
	std::string s_genome; 			//what genome was called

	/** -3d flag variables **/
	std::string s_genelistFlag = "-3d";	//name flag
	bool b_genelistFlagCall(false);	//true if gene list flag called
	std::string s_genelist; 		//file name of gene list

	/** -bed flag variables **/
	std::string s_bedFlag = "-bed";	//name flag
	bool b_bedFlagCall(false);		//true if bed flag called (if false, end program)
	std::string s_bed; 			//name of bed file

	/** -n, --name flag variables **/
	std::string s_nameFlag = "-n";	//name flag
	std::string s_name; 			//output name. If std::string = NULL, call output 
							//files some default name

	/** -v, --version flag variables **/
	bool b_versionFlagCall(false);	//if true, only print version and do not run 
							//program regardless of other flags

	/** -h, --help flag variables **/
	bool b_helpFlagCall(false);		//if true, only print help page and do not run 
							//program regardless of other flags

	/** -s, --sat flag saturation threshold **/
	double d_satthresh = 0.9;		// default is 0.9
	std::string s_satFlag = "-s";

	std::string s_execPath = getExecPath();
	std::cout << "Program path: " << s_execPath << std::endl;


	// display welcome message when there is no argument given
	if (argc < 2) {
		welcome();
		std::exit(0);
	}

	// count bam folder and input bam folder reps
	for (int i = 1; i < argc; i++){
		std::string arg = argv[i];
		if (arg == "-bam"){
			b_bamFlagCall = true;
			i_bamRep++;
		}
		if (arg == "-i"){
			b_bamInputFlagCall = true;
			i_bamInputRep++;
		}
	}

	// make an array of all bam folder names
	std::string bamFolderArr[i_bamRep];
	int i_bamFolderPos = 0; //index place holder for bamFolderArr

	std::string inputBamFolderArr[i_bamInputRep];
	int i_inputBamFolderPos = 0; //index place holder for inputBamFolderArr 

	// Go through arguments again and check if input is specified after appropriate flags
	for (int i = 1; i < argc; i++){
		// print out each argument
		std::string arg = argv[i];

		if ((arg == "--help") || (arg == "-h") || (arg == "-help")){
			b_helpFlagCall = true;
		} else if ((arg == "--version") || (arg == "-v") || (arg == "-version")){
			b_versionFlagCall = true;	
		} else if (arg.find(s_bamFlag) != std::string::npos){
			i++;
			try {	
				std::string s = argv[i];
			}
			catch(...){
				std::cerr << "-bam flag must preceed a folder name" << std::endl;
				std::exit(0);
			}
			bamFolderArr[i_bamFolderPos] = argv[i];
			i_bamFolderPos++;
		} else if (arg.find(s_bamInputFlag) != std::string::npos){
			i++;
			try {	
				std::string s = argv[i];
			}
			catch(...){
				std::cerr << "-i flag must preceed a folder name" << std::endl;
				std::exit(0);
			}
			inputBamFolderArr[i_inputBamFolderPos] = argv[i];
			i_inputBamFolderPos++;
		} else if (arg.find(s_bedFlag) != std::string::npos){
			i++;
			b_bedFlagCall = true;
			try {	
				std::string s = argv[i];
				bool b_ex = exists(s);
				if (b_ex == 0) {
					std::cout << s << " is not a file in directory." << std::endl;
					std::exit(0);
				}
			}
			catch(...){
				std::cerr << "-bed flag must preceed a file name" << std::endl;
				std::exit(0);
			}
			s_bed = argv[i];
		} else if (arg.find(s_genomeFlag) != std::string::npos){
			i++;
			b_genomeFlagCall = true;
			try {	
				std::string s = argv[i];
			}
			catch(...){
				std::cerr << "-g flag must preceed a genome name" << std::endl;
				std::exit(0);
			}
			s_genome = argv[i];

			// check if genome input is valid
			if(genomeGetter(s_execPath + "lib/GenomeFeatures/", s_genome, fileCount(s_execPath + "lib/GenomeFeatures/"))) {
				std::cout << "Valid genome feature folder detected." << std::endl;
			} else {
				std::cerr << s_genome << " is not a valid genome." << std::endl;
				std::exit(0);
			}
		} else if (arg.find(s_nameFlag) != std::string::npos){
			i++;
			try {	
				std::string s = argv[i];
			}
			catch(...){
				std::cerr << "-n flag must preceed an output file name" << std::endl;
				std::exit(0);
			}
			s_name = argv[i];
		} else if (arg.find(s_genelistFlag) != std::string::npos){
			i++;
			b_genelistFlagCall = true;
			try {	
				std::string s = argv[i];
				bool b_ex = exists(s);
				if (b_ex == 0) {
					std::cout << s << " is not a file in directory." << std::endl;
					std::exit(0);
				}
			}
			catch(...){
				std::cerr << "-3d flag must preceed an file name" << std::endl;
				std::exit(0);
			}
			s_genelist = argv[i];
		} else if (arg.find(s_satFlag) != std::string::npos){
			i++;
			try {	
				std::string s = argv[i];
				d_satthresh = std::stod(argv[i]);
				if (d_satthresh > 1 || d_satthresh < 0.5) {
					std::cerr << "-s flag must be between 0.95 and 0.5." << std::endl;
					std::exit(0);
				}
			}
			catch(...){
				std::cerr << "-s flag must be between 0.95 and 0.5." << std::endl;
				std::exit(0);
			}
		} else {
			std::cout << "Invalid flag called. Program terminated." <<  std::endl;
			std::exit(0);
		}

	} //for loop

	// check if user specified information is logical
	if (b_helpFlagCall) {
		welcome();
		std::exit(0);
	}
	if (b_versionFlagCall) {
		std::cout << "tdca 1.0.0" <<  std::endl;
		std::exit(0);
	}
	if (!b_bedFlagCall) {
		std::cout << "Bed file required. Program terminated." <<  std::endl;
		std::exit(0);
	}
	if (!b_bamFlagCall) {
		std::cout << "Bam folder required. Program terminated." <<  std::endl;
		std::exit(0);
	}
	if (i_bamInputRep > 0 && i_bamRep != i_bamInputRep) {
		std::cout << "Bam replicates do not equal bam input replicates. Program terminated." <<
			std::endl;
		std::exit(0);
	}
	if (b_genelistFlagCall == true && b_genomeFlagCall == false) {
		std::cout << "Gene list flag (-3d) must be combined with genome flag (-g). Program terminated." <<
			std::endl;
		std::exit(0);
	}

	// bam folder checks to ensure number of bam files are equivalent
	for (int i = 0; i < i_bamRep; i++){

		std::string s_relativePath ("./");
		std::string s_bamDirectory1 = s_relativePath + bamFolderArr[i];

		//number of bam files in directory
		int i_bamFiles1 = bamFileCount(s_bamDirectory1, fileCount(s_bamDirectory1));

		if (i_bamFiles1 < 4) {
			std::cout << "Turnover values cannot be calculated with less" <<
				"then four time points." << std::endl;
			std::exit(0);
		}

		// check if bam folder replicates have same number of bam files
		if (i < i_bamRep-1) {
			std::string s_bamDirectory2 = s_relativePath + bamFolderArr[i+1];
			int i_bamFiles2 = bamFileCount(s_bamDirectory2, fileCount(s_bamDirectory2));

			if (i_bamFiles1 != i_bamFiles2) {
				std::cout << "Number of bam files not equivalent in each bam" <<
					" folder replicate." << std::endl;
				std::exit(0);
			}
		}

		// check if bam folder has same number of bam files in input if available
		if (i_bamInputRep > 0) {
			std::string s_inputBamDirectory = s_relativePath + inputBamFolderArr[i];
			int i_inputBamFiles = bamFileCount(s_inputBamDirectory, fileCount(s_inputBamDirectory));

			if (i_bamFiles1 != i_inputBamFiles) {
				std::cout << "Number of bam files not equivalent in each bam" <<
					" folder and bam input folder." << std::endl;
				std::exit(0);
			}
		}
	}

	// check if time extensions are equal in each bam folder
	std::string s_relativePath ("./");
	std::string s_bamDirectory = s_relativePath + bamFolderArr[0];
	i_bamFiles = bamFileCount(s_bamDirectory, fileCount(s_bamDirectory));

	int turnoverTimes[i_bamFiles]; // array containing ChIP-seq turnover times

	timeLogger(turnoverTimes, s_bamDirectory, fileCount(s_bamDirectory));

	// sort the turnoverTimes array in asending order
	int temp = 0;
	for(int i = 0; i< i_bamFiles; i++) {
		for(int j = 0; j < i_bamFiles; j++) {
			if(turnoverTimes[i] < turnoverTimes[j]) {
				temp = turnoverTimes[i];
				turnoverTimes[i] = turnoverTimes[j];
				turnoverTimes[j] = temp;
			}
		}
	}

	for (int i = 0; i < i_bamRep; i++){

		// check if time extensions are equal in each bam folder
		std::string s_relativePath ("./");
		std::string s_bamDirectory = s_relativePath + bamFolderArr[i];
		i_bamFiles = bamFileCount(s_bamDirectory, fileCount(s_bamDirectory));

		int otherTurnoverTimes[i_bamFiles]; // array containing ChIP-seq turnover 
						    // times for all other bam foders
		timeLogger(otherTurnoverTimes, s_bamDirectory, fileCount(s_bamDirectory));

		// sort the otherTurnoverTimes array in asending order
		int temp = 0;
		for(int i = 0; i< i_bamFiles; i++) {
			for(int j = 0; j < i_bamFiles; j++) {
				if(otherTurnoverTimes[i] < otherTurnoverTimes[j]) {
					temp = otherTurnoverTimes[i];
					otherTurnoverTimes[i] = otherTurnoverTimes[j];
					otherTurnoverTimes[j] = temp;
				}
			}
		}

		for (int i = 0; i < i_bamFiles; i++) {
			if (turnoverTimes[i] != otherTurnoverTimes[i]) {
				std::cout << "Bam turnover times not equivalent in each bam" <<
						" folder replicate." << std::endl;
				std::exit(0);
			}
		}

		// check if bam folder has same turnover extensions as input if available
		if (i_bamInputRep > 0) {
			std::string s_bamDirectory = s_relativePath + inputBamFolderArr[i];
			i_bamFiles = bamFileCount(s_bamDirectory, fileCount(s_bamDirectory));

			int otherTurnoverTimes[i_bamFiles]; // array containing ChIP-seq turnover 
							    // times for all other bam foders
			timeLogger(otherTurnoverTimes, s_bamDirectory, fileCount(s_bamDirectory));

			// sort the otherTurnoverTimes array in asending order
			int temp = 0;
			for(int i = 0; i< i_bamFiles; i++) {
				for(int j = 0; j < i_bamFiles; j++) {
					if(otherTurnoverTimes[i] < otherTurnoverTimes[j]) {
						temp = otherTurnoverTimes[i];
						otherTurnoverTimes[i] = otherTurnoverTimes[j];
						otherTurnoverTimes[j] = temp;
					}
				}
			}

			for (int i = 0; i < i_bamFiles; i++) {
				if (turnoverTimes[i] != otherTurnoverTimes[i]) {
					std::cout << "Bam turnover times not equivalent in bam experiment" <<
							" folder and bam input folder." << std::endl;
					std::exit(0);
				}
			}
		}
	} 

	std::string s_args = "Bam rep = "; // write to R script at begining
	// output all user specified information
	std::cout << "TDCA will run based on the following parameters:" << std::endl;

	if (b_bamFlagCall) {
		std::cout << "Bam replicates = " << i_bamRep << std::endl; 
		for (int i = 0; i < i_bamRep; i++){
			std::cout << "Bam rep " << i+1 << " = " << bamFolderArr[i] << std::endl;
			s_args += bamFolderArr[i] + ", ";
		}
	}

	if (b_bamInputFlagCall) {
		std::cout << "Input bam replicates = " << i_bamInputRep << std::endl; 
		s_args += "Bam input rep = ";
		for (int i = 0; i < i_bamInputRep; i++){
			std::cout << "Input bam rep " << i+1 << " = " << inputBamFolderArr[i] << std::endl;
			s_args += inputBamFolderArr[i] + ", ";
		}
	}

	if (b_bedFlagCall) {
		std::cout << "Bed file name = " << s_bed << std::endl;
		s_args += "Bed file name = " + s_bed + ", ";
	}

	if (b_genomeFlagCall) {
		std::cout << "Genome name = " << s_genome << std::endl;
		s_args += "Genome name = " + s_genome + ", ";
	}

	if (!s_name.empty()) {
		std::cout << "Output files will be named " << s_name << std::endl;
		s_args += "Output files will be named " + s_name + ", ";
	} else {
		s_name = "turnover.exp";
		std::cout << "Output files will be named " << s_name << " by default" << std::endl;
	}

	std::cout << "The following turnover times were detected: " << std::endl;
	s_args += "The following turnover times were detected (in minutes): ";
	for (int i = 0; i < i_bamFiles; i++) { // for each bam file
		std::cout << "time " << i+1 << " = " << turnoverTimes[i] << " minutes." << std::endl;
		s_args += std::to_string(turnoverTimes[i]) + " ";
	}






	// print number of peaks in bed file
	int i_peakNumber = peakCounter(s_bed);
	std::cout << "The bed file " << s_bed << " contains " << i_peakNumber << " peaks." << std::endl;


	// make an array of files in genome folder for gene feature overlap
	std::string s_genomeDir = s_execPath + "lib/GenomeFeatures/" + s_genome + "/";
	int i_genomeFileCount = extFileCount(s_genomeDir, fileCount(s_genomeDir), ".bed");
	std::string genomeFilesArr[i_genomeFileCount];
	std::cout << i_genomeFileCount << " gene feature files will be used:" <<std::endl;	
	for (int i = 0; i < i_genomeFileCount; i++) {
		genomeFilesArr[i] = bedGetter(s_genomeDir, i);
		std::cout << genomeFilesArr[i] << std::endl;
	}


 	// ======================== XXX CALCULATION COMPONENT OF PROGRAM XXX =======================//

	//================================== XXX VARIABLE RECAP XXX ================================//

	// Number of bam file turnover times = i_bamFiles
	// Turnover times stored in ordered array turnoverTimes[]. Use this as REGEX to samD bam files
	// Number of replicates = i_bamRep
	// Array storing folder name of replicates = bamFolderArr[]
	// Array storing folder name of replicates = inputBamFolderArr[]
	//==========================================================================================//

	// vector holding ALL loci information - print contents to output file.
	// rows = i_peakNumber + 1; columns	= 2*i_bamFiles + i_genomeFileCount + 11
	int i_dataArrCols = (2*i_bamFiles + i_genomeFileCount + 12);
	std::vector< std::vector<std::string> > dataArray ((i_peakNumber + 1), std::vector<std::string>(i_dataArrCols, "-" ) );

	// make the header for dataArray 	
	dataArray[0][0] = "chrom";							// chromosome
	dataArray[0][1] = "start";							// start
	dataArray[0][2] = "end";							// end
	for (int i = 3; i < (i_bamFiles + 3); i++) 
		dataArray[0][i] = ("time = " + std::to_string(turnoverTimes[i-3]));

	for (int i = (3 + i_bamFiles); i < (2*i_bamFiles + 3); i++) 
		dataArray[0][i] = ("time = " + std::to_string(turnoverTimes[i-(3 + i_bamFiles)]) + " stdev");

	dataArray[0][2*i_bamFiles + 3] = "truncDiff"; 				// truncDiff
	dataArray[0][2*i_bamFiles + 4] = "saturation"; 				// saturation
	dataArray[0][2*i_bamFiles + 5] = "inflection point";			// inflection point
	dataArray[0][2*i_bamFiles + 6] = "residuals"; 				// goodness of fit
	dataArray[0][2*i_bamFiles + 7] = "adjusted inflection point";	// inflection point
	dataArray[0][2*i_bamFiles + 8] = "adjusted residuals"; 		// goodness of fit
	dataArray[0][2*i_bamFiles + 9] = "turnover direction"; 		// turnover direction
	dataArray[0][2*i_bamFiles + 10] = "real peak"; 				// real peak
	dataArray[0][2*i_bamFiles + 11] = "upper asymptote"; 			// upper asymptote
	
	for ( int i = (i_dataArrCols - i_genomeFileCount); i < (i_dataArrCols); i++) {
		dataArray[0][i] = genomeFilesArr[i-(i_dataArrCols - i_genomeFileCount)]; // feature hits
	}



	// Bedtools intesect on genome features commands - make additional bed files of genome features
	if (b_genomeFlagCall) {
		std::cout << "Intersecting peaks with genome features." << std::endl;
		#pragma omp parallel for 
		for (int i = 0; i < i_genomeFileCount; i++) {
			std::vector<std::string> featureVector(i_peakNumber, "0");
			//std::cout << "s_genomeDir + genomeFilesArr[i] = " << s_genomeDir + genomeFilesArr[i] << std::endl;
			bedToolsIntersect(s_genomeDir + genomeFilesArr[i], s_bed, featureVector, i);

			for (int j = 0; j < i_peakNumber; j++)
				dataArray[(j+1)][(i_dataArrCols - i_genomeFileCount + i)] = featureVector[j]; 
		}
	}

	// write normalized reads to vector
	std::vector<std::vector<std::string> > normReadsVector;

	// write normalized gene reads to vector
	std::vector<double> normGeneVector;

	// write the header to normReadsVector
	std::vector<std::string> headerVector;
	headerVector.push_back("Region");

	for (int j = 0; j < i_bamFiles; j++) // for each bam file
		headerVector.push_back(std::to_string(turnoverTimes[j]));
	normReadsVector.push_back(headerVector);

	// establish directory of proper genome refseq gene list
	std::string s_genelistFile = s_execPath + "lib/GeneLists/" + s_genome + "/" + s_genome + ".genes";
	// vector containing VALID user input refseq gene names
	std::vector<std::string> validGeneVector;
	// number of user input VALID refseq gene names
	int i_validgenes;


	for (int i = 0; i < i_bamRep; i++) // for each folder
		i_validgenes = writeReadsToVectorParallel(bamFolderArr, inputBamFolderArr, b_bamInputFlagCall, i_bamRep, i, s_name, i_bamFiles, turnoverTimes, s_bed, normReadsVector, b_genelistFlagCall, s_genelist, normGeneVector, s_genelistFile, validGeneVector, i_peakNumber);

	// Compress normalized reads in normvector if there is mltiple replicates
	std::vector<std::vector<std::string> > normAveVector;

	// Create a vector to hold variability of compressed normalized reads when multiple replicates are available
	std::vector<std::vector<std::string> > normErrorVector;

	// compress replicates into one vector and give an additional vector for replicate variance
	if (i_bamRep > 1) {
		//std::cout << "Compressing normReadsVector to normAveVector." << std::endl;
		normVectorAverage(i_peakNumber, i_bamFiles, i_bamRep, normReadsVector, normAveVector);
		normVectorError(i_peakNumber, i_bamFiles, i_bamRep, normReadsVector, normAveVector, normErrorVector);
	}	

	// Compress normalized reads in normGeneVector if there is mltiple replicates
	std::vector<double> normGeneAveVector;
	if (b_genelistFlagCall == true && i_bamRep > 1) {
		//std::cout << "Compressing normGeneVector to normGeneAveVector." << std::endl;
		normGeneVectorAverage(i_bamFiles, i_bamRep, i_validgenes, normGeneVector, normGeneAveVector);

	}

	// write normReadsVector OR normAveVector && normErrorVector to dataArray
	if (i_bamRep > 1) { // multiple replicates
		for (int i = 1; i < i_peakNumber+1; i++) {
			for (int j = 0; j < i_bamFiles; j++) {
				dataArray[i][j + 3] = normAveVector[i][j+1]; 
				dataArray[i][j + i_bamFiles + 3] = normErrorVector[i][j+1];
			}
		}
	} else { // one replicate
		for (int i = 1; i < i_peakNumber+1; i++) {
			for (int j = 0; j < i_bamFiles; j++) {
				dataArray[i][j + 3] = normReadsVector[i][j+1];
			}
		}
	}

	bool b_turnoverDirection; // forward = true, reverse = false
	double d_forwardCounter = 0;

	// Establish forward or reverse turnover
	for (int i = 1; i < i_peakNumber + 1; i++) {
		std::string objName;
		if (i_bamRep > 1) {
			objName = normAveVector[i][0];
		} else {
			objName = normReadsVector[i][0]; 
		}
		LocusTurnover ($objName) (objName, i_bamFiles);
		if (i_bamRep > 1) {
			for (int j = 0; j < i_bamFiles; j++) {
				double d_depth = stod(normAveVector[i][j+1]);
				($objName).turnoverArr[j] = d_depth;
			}
		} else { 
			for (int j = 0; j < i_bamFiles; j++) {
				double d_depth = stod(normReadsVector[i][j+1]);
				($objName).turnoverArr[j] = d_depth;
			}
		}
		($objName).analysis();
		if (($objName).b_forw_rvrs == true) {
			d_forwardCounter++;
			dataArray[i][i_bamFiles*2 + 9] = "forward";
		} else {
			dataArray[i][i_bamFiles*2 + 9] = "reverse";
		}
	}

	std::cout << "Number of peaks recorded as forward turnover = " << d_forwardCounter << "/" << i_peakNumber <<
		" = " << d_forwardCounter / i_peakNumber * 100 << "%" << std::endl;

	if (d_forwardCounter > (double(i_peakNumber) / 2)) {
		b_turnoverDirection = true;
	} else {	
		b_turnoverDirection = false;
	}
	
	int i_realPeaks; // number of real peaks (follow turnover direction of majority)
	if (b_turnoverDirection) {
		std::cout << "Forward turnover detected" << std::endl;
		i_realPeaks = d_forwardCounter; 
	} else {
 		std::cout << "Reverse turnover detected" << std::endl;
		i_realPeaks = (i_peakNumber - d_forwardCounter);
	}


	// R script file
	std::string s_rPltsName = s_name + ".tdca.R";
	std::string s_rPltsPDF = s_name + ".tdca.pdf";
	rBegin(s_rPltsName, s_rPltsPDF, s_args); 

	// initialize arrays for histogram of timepoints of min and max 
	int maxIndexArray [i_bamFiles];
	int minIndexArray [i_bamFiles];
	for (int i = 0; i < i_bamFiles; i++) {
		maxIndexArray[i] = 0;
		minIndexArray[i] = 0;		
	}

	int i_loopOneCounter = 0;
	std::remove("drcInflections.txt");
	std::remove("drcInflection.R");
	std::remove("linearResiduals.txt"); // linear regression
	std::remove("linearResiduals.R"); // linear regression



	// for progress
	float f_progress = 0.0;
	int i_barWidth = 20;
	double d_progiterator = 0;

	std::cout << "Calculating non-adjusted inflection points." << std::endl;
 
	// OBJECT LOOP 1 
	// =============
	for (int i = 1; i < i_peakNumber + 1; i++) {
		std::string objName;
		if (i_bamRep > 1) {
			objName = normAveVector[i][0];
		} else {
			objName = normReadsVector[i][0]; 
		}
		LocusTurnover ($objName) (objName, i_bamFiles);
		if (i_bamRep > 1) {
			for (int j = 0; j < i_bamFiles; j++) {
				double d_depth = stod(normAveVector[i][j+1]);
				($objName).turnoverArr[j] = d_depth;
			}
		} else { 
			for (int j = 0; j < i_bamFiles; j++) {
				double d_depth = stod(normReadsVector[i][j+1]);
				($objName).turnoverArr[j] = d_depth;
			}
		}
		($objName).analysis();
		dataArray[i][0] = ($objName).s_chr;
		dataArray[i][1] = ($objName).s_start;
		dataArray[i][2] = ($objName).s_end;

		bool b_real = true;
	
		// This makes inflection point of non-truncated data
		drcScriptGenerator(i_loopOneCounter, i_bamFiles, 0, turnoverTimes, ($objName).turnoverArr, b_real, b_turnoverDirection, (($objName).d_overallMax));

		// fill in array for histogram of timepoints of min and max 
		int i_maxIndex = ($objName).i_overallMaxIndex;
		for (int m = 0; m < i_bamFiles; m++) {
			if (m == i_maxIndex) {
				int i_temp = maxIndexArray[m]; 
				maxIndexArray[m] = (i_temp + 1);
			}
		} 
		int i_minIndex = ($objName).i_overallMinIndex;
		for (int n = 0; n < i_bamFiles; n++) {
			if (n == i_minIndex) {
				int i_temp = minIndexArray[n];
				minIndexArray[n] = (i_temp + 1);
			}
		}

		// Progress
		std::cout << "[";
		int i_pos = i_barWidth * f_progress;
		for (int i = 0; i < i_barWidth; i++) {
			if (i <= i_pos) std::cout << "=";
			else std::cout << " ";
		}
		if (i == i_peakNumber) { // 100% complete
			std::cout << "] " << int(100) << " %\r";
			std::cout.flush();
		} else {
			std::cout << "] " << int((f_progress+0.01) * 100.0) << " %\r";
			std::cout.flush();
		}

		f_progress = d_progiterator/i_peakNumber;
		d_progiterator++;
		i_loopOneCounter++;
	}
	std::cout << std::endl;
	std::cout << "Analysing results." << std::endl;

	std::vector<std::string> drcInflectionVector(i_peakNumber);
	std::vector<std::string> drcResidualsVector(i_peakNumber);
	std::vector<std::string> drcUpperAsymVector(i_peakNumber);
	std::vector<std::string> linResVector(i_peakNumber);

	if (b_turnoverDirection) { // Forward turnover
		inflectionWriter(drcInflectionVector, drcResidualsVector, drcUpperAsymVector, linResVector);
	} else { // Reverse turnover
		for (int i = 1; i < i_peakNumber + 1; i++) {
			std::string objName;
			if (i_bamRep > 1) {
				objName = normAveVector[i][0];
			} else {
				objName = normReadsVector[i][0]; 
			}
			LocusTurnover ($objName) (objName, i_bamFiles);
			if (i_bamRep > 1) {
				for (int j = 0; j < i_bamFiles; j++) {
					double d_depth = stod(normAveVector[i][j+1]);
					($objName).turnoverArr[j] = d_depth;
				}
			} else { 
				for (int j = 0; j < i_bamFiles; j++) {
					double d_depth = stod(normReadsVector[i][j+1]);
					($objName).turnoverArr[j] = d_depth;
				}
			}
			($objName).analysis();
			drcUpperAsymVector[i-1] = std::to_string(($objName).d_overallMax);
		}
		inflectionWriterReverse(drcInflectionVector, drcResidualsVector, linResVector);
	}

	// write inflection points to data array for forward
	for (int i = 0; i < i_peakNumber; i++) {
		dataArray[i+1][i_bamFiles*2 + 5] = drcInflectionVector[i];
		dataArray[i+1][i_bamFiles*2 + 6] = drcResidualsVector[i];
		//std::cout << "drcInflectionVector[i] = " << drcInflectionVector[i] << std::endl;
		//std::cout << "linResVector[" << i << "] = " << linResVector[i] << std::endl;
	}

	// bar chart of absolute min max
	rBar(s_rPltsName, i_bamFiles, turnoverTimes, maxIndexArray, minIndexArray, i_peakNumber);

	// density plot of untruncated turnover points
	// rDensity(s_rPltsName, i_peakNumber, drcInflectionVector, i_bamFiles, turnoverTimes, std::string("non_truncated")); 

	// quality graph pie chart metrics
	int i_truncated = 0;
	int i_notTruncated = 0;
	int i_eliminated = 0;

	int i_loopTwoCounter = 0;
	// get rid of any confilicting files for drcNormScriptGenerator
	std::remove("drcInflections.txt");
	std::remove("drcInflection.R");
	std::remove("linearResiduals.txt"); // linear regression
	std::remove("linearResiduals.R"); // linear regression

	// for progress
	f_progress = 0.0;
	d_progiterator = 0;

	std::cout << "Calculating adjusted inflection points." << std::endl;

	// OBJECT LOOP 2
	// =============
	for (int i = 1; i < i_peakNumber + 1; i++) {
		std::string objName;
		if (i_bamRep > 1) {
			objName = normAveVector[i][0];
		} else {
			objName = normReadsVector[i][0];
		}
		LocusTurnover ($objName) (objName, i_bamFiles);
		// write data to objects
		if (i_bamRep > 1) {
			for (int j = 0; j < i_bamFiles; j++) {
				double d_depth = stod(normAveVector[i][j+1]); 
				($objName).turnoverArr[j] = d_depth;
			}
		} else {
			for (int j = 0; j < i_bamFiles; j++) {
				double d_depth = stod(normReadsVector[i][j+1]);
				($objName).turnoverArr[j] = d_depth;
			}
		}
		($objName).analysis();
		($objName).b_realPeak = true;

		// get a truncDiff indicated how much data to trim
		int i_truncDiff;
		// overall forward and loci forward(1 - 0.9)
		if (b_turnoverDirection == true && ($objName).b_forw_rvrs == true) { 
			// equal to zero if i_overallMaxIndex is last point.
			i_truncDiff = (i_bamFiles-1) - ($objName).i_overallMaxIndex;  
			if (i_truncDiff > 0) {

				// check saturation
				int i_upOne = ($objName).i_overallMaxIndex + 1;
				int i_downOne = ($objName).i_overallMaxIndex - 1;

				if ( ($objName).turnoverArr[i_upOne] > ((($objName).d_overallMax) * d_satthresh) ) {
					($objName).b_sature = true; 
				} else if ( (i_downOne > -1) && ($objName).turnoverArr[i_downOne] > ((($objName).d_overallMax) * d_satthresh) ) {
					($objName).b_sature = true; 
				} else {
				}

				for (int k = ($objName).i_overallMaxIndex + 1; k < i_bamFiles; k++) {
					if ( ($objName).turnoverArr[k] > ((($objName).d_overallMax) * d_satthresh) ) {
						i_truncDiff--; 
					} else { 
						break; // break for loop
					}					
				}
			}
		// overall reverse and loci reverse
		} else if (b_turnoverDirection == false && ($objName).b_forw_rvrs == false) { 
			// equal to zero if i_overallMinIndex is last point.
			i_truncDiff = (i_bamFiles-1) - ($objName).i_overallMinIndex;  
			if (i_truncDiff > 0) {

				// check saturation
				int i_upOne = ($objName).i_overallMinIndex + 1;
				int i_downOne = ($objName).i_overallMinIndex - 1;

				if ( ($objName).turnoverArr[i_upOne] < ((($objName).d_overallMin) * (1 + (1 - d_satthresh))) ) {
					($objName).b_sature = true; 
				} else if ( (i_downOne > -1) && ($objName).turnoverArr[i_downOne] < ((($objName).d_overallMin) * (1 + (1 - d_satthresh))) ) {
					($objName).b_sature = true; 
				} else {
				}

				for (int k = ($objName).i_overallMinIndex + 1; k < i_bamFiles; k++) {
					// 90% user specified? XXX
					if ( ($objName).turnoverArr[k] < ((($objName).d_overallMin) * (1 + (1 - d_satthresh))) ) {
						i_truncDiff--; 	
					} else { 
						break; // break for loop
					}					
				}
			} 
		// overall and loci are opposite
		} else { 
			i_eliminated++;
			($objName).b_realPeak = false;
		}
		if (i_truncDiff > 0) {
			i_truncated++;
		} else {
			i_notTruncated++;
		}
		dataArray[i][i_bamFiles*2 + 10] = std::to_string(($objName).b_realPeak);
		dataArray[i][i_bamFiles*2 + 3] = std::to_string(i_truncDiff);
		dataArray[i][2*i_bamFiles + 4] = std::to_string(($objName).b_sature);

		int i_minIndex = ($objName).i_overallMinIndex;

// XXX==================================================================================================XXX
// SWITCHING IF FROM 500 TO 1 WILL CAUSE INFLECTION POINTS WITH REPLICATES TO BE CALCULATED WITH INDIVIDUAL
// REPLICATES RATHER THEN BY AVERAGE. TEST IF THIS IS BEST LATER.
// XXX==================================================================================================XXX

		if (i_bamRep > 500) { // for replicates only
			drcNormScriptGeneratorString(i_loopTwoCounter, i_bamFiles, i_truncDiff, turnoverTimes, normReadsVector, ($objName).b_realPeak, i_minIndex, i_bamRep, i_peakNumber);

		} else {
			drcNormScriptGenerator(i_loopTwoCounter, i_bamFiles, i_truncDiff, turnoverTimes, ($objName).turnoverArr, ($objName).b_realPeak, i_minIndex, b_turnoverDirection, (($objName).d_overallMax));
		}
		

		// Progress
		std::cout << "[";
		int i_pos = i_barWidth * f_progress;
		for (int i = 0; i < i_barWidth; i++) {
			if (i <= i_pos) std::cout << "=";
			else std::cout << " ";
		}
		if (i == i_peakNumber) { // 100% complete
			std::cout << "] " << int(100) << " %\r";
			std::cout.flush();
		} else {
			std::cout << "] " << int((f_progress+0.01) * 100.0) << " %\r";
			std::cout.flush();
		}

		f_progress = d_progiterator/i_peakNumber;
		d_progiterator++;
		i_loopTwoCounter++;
	}
	std::cout << std::endl;
	std::cout << "Analysing results." << std::endl;


	std::vector<std::string> drcTruncInflectionVector(i_peakNumber);
	std::vector<std::string> drcTruncResidualsVector(i_peakNumber);
	std::vector<std::string> drcTruncUpperAsymVector(i_peakNumber);
	std::vector<std::string> truncLinResVector(i_peakNumber);


	if (b_turnoverDirection) { // Forward turnover
		inflectionWriter(drcTruncInflectionVector, drcTruncResidualsVector, drcTruncUpperAsymVector, truncLinResVector); // write values to these vectors
	} else { // Reverse turnover
		for (int i = 1; i < i_peakNumber + 1; i++) {
			std::string objName;
			if (i_bamRep > 1) {
				objName = normAveVector[i][0];
			} else {
				objName = normReadsVector[i][0]; 
			}
			LocusTurnover ($objName) (objName, i_bamFiles);
			if (i_bamRep > 1) {
				for (int j = 0; j < i_bamFiles; j++) {
					double d_depth = stod(normAveVector[i][j+1]);
					($objName).turnoverArr[j] = d_depth;
				}
			} else { 
				for (int j = 0; j < i_bamFiles; j++) {
					double d_depth = stod(normReadsVector[i][j+1]);
					($objName).turnoverArr[j] = d_depth;
				}
			}
			($objName).analysis();
			int i_minIndex = ($objName).i_overallMinIndex;
			drcTruncUpperAsymVector[i-1] = std::to_string(($objName).d_overallMax - ($objName).turnoverArr[i_minIndex]);
		}
		inflectionWriterReverse(drcTruncInflectionVector, drcTruncResidualsVector, truncLinResVector);
	}


	// print upper assymptote to data array
	for (int i = 0; i < i_peakNumber; i++) 
		dataArray[i+1][i_bamFiles*2 + 11] = drcTruncUpperAsymVector[i];

	// re-write drcTruncUpperAsymVector by normalized length in preperation for graphing
	for (int i = 0; i < i_peakNumber; i++) {
		double d_start = std::stod(dataArray[i+1][1]);
		double d_end = std::stod(dataArray[i+1][2]);
		double d_length = d_end - d_start;
		double d_normAss = std::stod(drcTruncUpperAsymVector[i]) / d_length;
		drcTruncUpperAsymVector[i] = std::to_string(d_normAss);
	}

	std::cout << "Writing R script." << std::endl;


	// print inflection vector to data array
	for (int i = 0; i < i_peakNumber; i++) {
		dataArray[i+1][i_bamFiles*2 + 7] = drcTruncInflectionVector[i];
		dataArray[i+1][i_bamFiles*2 + 8] = drcTruncResidualsVector[i];
	}
	//for (int i = 0; i < i_peakNumber; i++) 
		//std::cout << "truncLinResVector[" << i << "] = " << truncLinResVector[i] << std::endl;

	// boxplot of residuals
	rBoxRes(s_rPltsName, i_peakNumber, i_bamFiles, truncLinResVector, linResVector, dataArray);

	// density plot of truncated turnover points
	rDensity(s_rPltsName, i_peakNumber, drcTruncInflectionVector, i_bamFiles, turnoverTimes, std::string("truncated")); 
	// boxplot of gene features and ideogram heat map
	if ( b_genomeFlagCall == true ) {
		rBoxplot(s_rPltsName,i_peakNumber,i_genomeFileCount,i_bamFiles,dataArray);
		if ( s_genome == "hg19")
			rIdeohg19(s_rPltsName,i_bamFiles,i_peakNumber,dataArray);
		if ( s_genome == "hg38")
			rIdeohg38(s_rPltsName,i_bamFiles,i_peakNumber,dataArray);
		if ( s_genome == "mm9")
			rIdeomm9(s_rPltsName,i_bamFiles,i_peakNumber,dataArray);
		if ( s_genome == "mm10")
			rIdeomm10(s_rPltsName,i_bamFiles,i_peakNumber,dataArray);
		if ( s_genome == "dm6")
			rIdeodm6(s_rPltsName,i_bamFiles,i_peakNumber,dataArray);
		if ( s_genome == "dm3")
			rIdeodm3(s_rPltsName,i_bamFiles,i_peakNumber,dataArray);
		if ( s_genome == "ce11")
			rIdeoce11(s_rPltsName,i_bamFiles,i_peakNumber,dataArray);
	}

	// stdev graphs
	if (i_bamRep > 1) {
		rStdev(s_rPltsName, i_bamFiles, i_peakNumber, dataArray, drcTruncUpperAsymVector, turnoverTimes);
	} else {
		rScat(s_rPltsName, i_bamFiles, i_peakNumber, dataArray, drcTruncUpperAsymVector);
	}


	// 3D GRAPHS
	if (b_genelistFlagCall) {
		// R script file
		std::string s_rGenePltsName = s_name + ".tdca3Dgenes.R";
		std::vector<double> shrunkGeneVector;

		// 3d scatter plots
		if (i_bamRep > 1 && i_bamFiles < 6) {
			r3Dadjusted(s_genelistFile, s_rGenePltsName, i_bamFiles, turnoverTimes, i_validgenes, normGeneAveVector, validGeneVector);

			//std::cout << "(i_bamRep > 1 && i_bamFiles < 6)" << std::endl;	//XXX
			//for (int i = 0; i < normGeneVector.size(); i++) {			//XXX
			//	std::cout << "normGeneVector[" << i << "] = " << normGeneVector[i] << std::endl;//XXX
			//}											//XXX
			//for (int i = 0; i < normGeneAveVector.size(); i++) {			//XXX
			//	std::cout << "normGeneAveVector[" << i << "] = " << normGeneAveVector[i] << std::endl;//XXX
			//}											//XXX

		} else if (i_bamRep == 1 && i_bamFiles < 6) {
			r3Dadjusted(s_genelistFile, s_rGenePltsName, i_bamFiles, turnoverTimes, i_validgenes, normGeneVector, validGeneVector);

			//std::cout << "(i_bamRep == 1 && i_bamFiles < 6)" << std::endl;	//XXX
			//for (int i = 0; i < normGeneVector.size(); i++) {			//XXX
			//	std::cout << "normGeneVector[" << i << "] = " << normGeneVector[i] << std::endl;//XXX
			//}											//XXX

		} else if (i_bamRep > 1 && i_bamFiles > 5) {
			geneVectorShrinkage(i_validgenes, i_bamFiles, normGeneAveVector, shrunkGeneVector);
			r3Dadjusted(s_genelistFile, s_rGenePltsName, i_bamFiles, turnoverTimes, i_validgenes, shrunkGeneVector, validGeneVector);

			//std::cout << "(i_bamRep > 1 && i_bamFiles > 5)" << std::endl;	//XXX
			//for (int i = 0; i < shrunkGeneVector.size(); i++) {			//XXX
			//	std::cout << "shrunkGeneVector[" << i << "] = " << shrunkGeneVector[i] << std::endl;//XXX
			//}											//XXX

		} else if (i_bamRep == 1 && i_bamFiles > 5) {
			geneVectorShrinkage(i_validgenes, i_bamFiles, normGeneVector, shrunkGeneVector);
			r3Dadjusted(s_genelistFile, s_rGenePltsName, i_bamFiles, turnoverTimes, i_validgenes, shrunkGeneVector, validGeneVector);

			//std::cout << "(i_bamRep == 1 && i_bamFiles > 5)" << std::endl;	//XXX
			//for (int i = 0; i < shrunkGeneVector.size(); i++) {			//XXX
			//	std::cout << "shrunkGeneVector[" << i << "] = " << shrunkGeneVector[i] << std::endl;//XXX
			//}											//XXX

		} else {
			std::cout << "Error with 3d gene graphing." << std::endl;	
		}

		// run r script
		std::string s_rGeneScript = "Rscript " + s_rGenePltsName; // temp file
		try {
			std::system(s_rGeneScript.c_str());
		}
		catch(...){
			std::cerr << "Cannot access R" << std::endl;
			std::exit(0);
		}
		// change name of Rplot.pdf
		std::string s_changeName = "mv Rplots.pdf " + s_name + ".tdca3Dgenes.pdf";
		try {
			std::system(s_changeName.c_str());
		}
		catch(...){
			std::cerr << "Cannot change name of Rplot" << std::endl;
			std::exit(0);
		}
	}


/**
	// print out quality graph pie chart metrics
	std::cout << "Eliminated peaks = " << i_eliminated << std::endl;
	std::cout << "Truncated peaks = " << i_truncated << std::endl;
	std::cout << "Non-truncated peaks = " << i_notTruncated << std::endl;
**/
	// dataArray[i][2*i_bamFiles + 3] = "truncDiff"; 				// truncDiff
	// dataArray[i][2*i_bamFiles + 4] = "saturation"; 				// saturation
	// dataArray[0][2*i_bamFiles + 10] = "real peak"; 	

	int i_tuncSat = 0;		// tuncated + saturated
	int i_tuncNotSat = 0;		// tuncated + non-saturated
	int i_notTuncSat = 0;		// non-truncated + saturated 
	int i_notTuncNotSat = 0;	// non-truncated + non-saturated

	for (int i = 1; i < i_peakNumber+1; i++) {
		if (stoi(dataArray[i][2*i_bamFiles + 3]) > 0 && stoi(dataArray[i][2*i_bamFiles + 4]) > 0) 
			i_tuncSat++;	
		if (stoi(dataArray[i][2*i_bamFiles + 3]) > 0 && stoi(dataArray[i][2*i_bamFiles + 4]) < 1) 
			i_tuncNotSat++;
		if (stoi(dataArray[i][2*i_bamFiles + 3]) < 1 && stoi(dataArray[i][2*i_bamFiles + 4]) > 0) 
			i_notTuncSat++;
		if (stoi(dataArray[i][2*i_bamFiles + 3]) < 1 && stoi(dataArray[i][2*i_bamFiles + 4]) < 1) 
			i_notTuncNotSat++;
	}

	//std::cout << "i_tuncSat = " << i_tuncSat << std::endl;
	//std::cout << "i_tuncNotSat = " << i_tuncNotSat << std::endl;
	//std::cout << "i_notTuncSat = " << i_notTuncSat << std::endl;
	//std::cout << "i_notTuncNotSat = " << i_notTuncNotSat << std::endl;
	//std::cout << "i_eliminated = " << i_eliminated << std::endl;

	// pie plot
	rPie(s_rPltsName, i_peakNumber, i_tuncSat, i_tuncNotSat, i_notTuncSat, i_notTuncNotSat, i_eliminated);


	// print data array to output file
	// rows = i_peakNumber + 1; columns	= 2*i_bamFiles + i_genomeFileCount + 11
	std::ofstream outputFile;
	outputFile.open(s_name + ".tdca.txt"); 

	for (int i = 0; i < i_peakNumber; i++) {
		for (int j = 0; j < (i_dataArrCols-1); j++) 
			outputFile << dataArray[i][j] << '\t';

		outputFile << dataArray[i][(i_dataArrCols-1)] << '\n';		
	}
	for (int i = 0; i < (i_dataArrCols-1); i++) 
		outputFile << dataArray[i_peakNumber][i] << '\t';
	outputFile << dataArray[i_peakNumber][(i_dataArrCols-1)];

	outputFile.close();

	rEnd(s_rPltsName, s_rPltsPDF, b_genomeFlagCall, i_bamRep);


	// print normalized reads vector XXX
	//for(int i = 0; i < normReadsVector.size(); i++) {
	//	for (int j = 0 ; j < normReadsVector[i].size(); j++) {
	//		std::cout << "normReadsVector[" << i << "][" << j << "] = " <<  normReadsVector[i][j] << std::endl;
	//	}
	//}

} //main



