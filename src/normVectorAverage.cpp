#include <iostream>    // input/output
#include <string>
#include <vector>

void normVectorAverage(int i_peakNumber, int i_bamFiles, int i_bamRep, std::vector<std::vector<std::string> > &normReadsVector, std::vector<std::vector<std::string> > &normAveVector)
{
	
	std::vector<std::string> headerVector;
	// print the header line
	for (int j = 0 ; j < i_bamFiles+1 ; j++) 
		headerVector.push_back(normReadsVector[0][j]);

	normAveVector.push_back(headerVector);


	std::vector<std::string> lineVector;
	// print the average of each coordinate for each time
	for (int i = 1 ; i < i_peakNumber+1; i++) {

		lineVector.push_back(normReadsVector[i][0]); 	// print the coordinate
		for (int j = 1 ; j < i_bamFiles+1 ; j++) {      // print the average depth for each time and coordinate
			
			double d_sumValue = 0;
			for( int k = 0; k < i_bamRep; k++) 		// for each bam replicate
				d_sumValue += atof(normReadsVector[i+i_peakNumber*k][j].c_str());

			double d_aveValue = d_sumValue/i_bamRep;
			lineVector.push_back((std::to_string(d_aveValue)));
		}
		normAveVector.push_back(lineVector);
		lineVector.clear();
	}

}


