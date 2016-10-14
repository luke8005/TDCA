#include <iostream>    // input/output
#include <string>
#include <vector>
#include <math.h>

void normVectorError(int i_peakNumber, int i_bamFiles, int i_bamRep, std::vector<std::vector<std::string> > &normReadsVector, std::vector<std::vector<std::string> > &normAveVector, std::vector<std::vector<std::string> > &normErrorVector)
{
	std::vector<std::string> headerVector;
	// print the header line
	for (int j = 0 ; j < i_bamFiles+1 ; j++) 
		headerVector.push_back(normReadsVector[0][j]);

	normErrorVector.push_back(headerVector);


	std::vector<std::string> lineVector;
	// print the std of each coordinate for each time

	if(i_bamRep > 2) {
		for (int i = 1 ; i < i_peakNumber+1; i++) {

			lineVector.push_back(normReadsVector[i][0]); 	// print the coordinate
			for (int j = 1 ; j < i_bamFiles+1 ; j++) {      // print the average depth for each time and coordinate
			
				double d_sumValue = 0;
				for( int k = 0; k < i_bamRep; k++) 	{	// for each bam replicate
					d_sumValue += (    ( atof(normReadsVector[i+i_peakNumber*k][j].c_str()) - atof(normAveVector[i][j].c_str()) ) *
								 ( atof(normReadsVector[i+i_peakNumber*k][j].c_str()) - atof(normAveVector[i][j].c_str()) )    );
				}

				double d_stdValue = sqrt (d_sumValue/(i_bamRep-1)); 	// This is the only difference b/t the below else statement
				lineVector.push_back((std::to_string(d_stdValue)));
			}
			normErrorVector.push_back(lineVector);
			lineVector.clear();
		}
	} else {
		for (int i = 1 ; i < i_peakNumber+1; i++) {

			lineVector.push_back(normReadsVector[i][0]); 	// print the coordinate
			for (int j = 1 ; j < i_bamFiles+1 ; j++) {      // print the average depth for each time and coordinate
			
				double d_sumValue = 0;
				for( int k = 0; k < i_bamRep; k++) 	{	// for each bam replicate
					d_sumValue += (    ( atof(normReadsVector[i+i_peakNumber*k][j].c_str()) - atof(normAveVector[i][j].c_str()) ) *
								 ( atof(normReadsVector[i+i_peakNumber*k][j].c_str()) - atof(normAveVector[i][j].c_str()) )    );
				}

				double d_stdValue = sqrt (d_sumValue/i_bamRep);
				lineVector.push_back((std::to_string(d_stdValue)));
			}
			normErrorVector.push_back(lineVector);
			lineVector.clear();
		}
	}
}


