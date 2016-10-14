#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Compresses gene vector into 4 time blocks for each gene
void geneVectorShrinkage(int i_validgenes, int i_bamFiles, std::vector<double> &normGeneVector, std::vector<double> &shrunkGeneVector) 
{

	int i_grouper = (i_bamFiles/2) - 1;

	for (int i = 0; i < i_validgenes; i++) { //for each gene
		for (int j = 0; j < 300; j++) 							// write first and second 
			shrunkGeneVector.push_back(normGeneVector[j+(i*i_bamFiles*150)]);		// turnover block

		double d_sum = 0;
		double d_average = 0;
		if (i_bamFiles%2 == 0) { // even  
			for (int j = 0; j < 150; j++) {
				for (int k = 2; k < i_grouper+2; k++) {				// write second turnover block
					d_sum += normGeneVector[j+(k*150)+(i*i_bamFiles*150)];
				}
				d_average = d_sum/i_grouper;
				shrunkGeneVector.push_back(d_average);
				d_sum = 0;
			}
			for (int j = 0; j < 150; j++) {
				for (int k = i_grouper+1; k < i_bamFiles-1; k++) {		// write third turnover block
					d_sum += normGeneVector[j+(k*150)+(i*i_bamFiles*150)];
				}
				d_average = d_sum/i_grouper;
				shrunkGeneVector.push_back(d_average);
				d_sum = 0;
			}
		} else { // odd
			for (int j = 0; j < 150; j++) {
				for (int k = 2; k < i_grouper+2; k++) {				// write second turnover block
					d_sum += normGeneVector[j+(k*150)+(i*i_bamFiles*150)];
				}
				d_average = d_sum/i_grouper;
				shrunkGeneVector.push_back(d_average);
				d_sum = 0;
			}
			for (int j = 0; j < 150; j++) {
				for (int k = i_grouper+2; k < i_bamFiles-1; k++) {		// write third turnover block
					d_sum += normGeneVector[j+(k*150)+(i*i_bamFiles*150)];
				}
				d_average = d_sum/i_grouper;
				shrunkGeneVector.push_back(d_average);
				d_sum = 0;
			}
		}

		for (int j = 0; j < 150; j++) 							// write fifth turnover block
			shrunkGeneVector.push_back(normGeneVector[j+((i_bamFiles-1)*150)+(i*i_bamFiles*150)]);
	}

}
