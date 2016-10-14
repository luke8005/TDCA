
#ifndef LOCUSTURNOVER_H
#define LOCUSTURNOVER_H

class LocusTurnover
{
	public:
		std::string s_locus;			// ex: chr10:400-2222
		std::string s_chr;			// ex: chr10
		std::string s_start;			// ex: 400
		std::string s_end;			// ex: 2222
		int i_numTimePts;				// number of bamFiles (time points)
		double d_overallTurnoverStartEnd;	// 
		double d_overallTurnoverMaxMin;	//
		double d_overallMin;			// the smallest depth value
		int i_overallMinIndex;			// index of the smallest depth value
		double d_overallMax;			// the largest depth value
		int i_overallMaxIndex;			// index of the largest depth value
		double d_maxTurnover;			// 
		bool b_forw_rvrs;				// true if forward
		bool b_realPeak;				// true if turnover inline with majority of peaks
		bool b_sature = false;			// saturation
		std::vector <double> turnoverArr;	// stores the depth values 
		LocusTurnover(std::string,int);	// declares a constructor for this class
		void analysis(void);
};             

#endif

