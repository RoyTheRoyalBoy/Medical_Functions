#ifndef ETCO2_H
#define ETCO2_H

#include <iostream>
#include <ctime>
#include <deque>
#include <cmath>
#include <vector>

using std::deque;
using std::vector;

class ETCO2_monitor {
	public:
		//metrics to keep track of, running calculation of each summation for optimal speed
		//doubles value for easier conversion when calculating r2 and slope
		deque<int> ETCO2_values;
		deque<double> ETCO2_times;
		double sum_xy = 0;
		double sum_x = 0;
		double sum_y = 0;
		double sum_x2 = 0;
		double sum_y2 = 0;
		bool alarm_triggered = false;

		//declaring and defining functions
		//alarm function that gets called when EKG varies too wildly
		void Alarm(){
			alarm_triggered = true;
			std::cout << "Malignant Hyperthermia alert!" << std::endl;
		}

		void ProcessETCO2(vector<int> &measurements, vector<time_t> &times) {
			//find the maximum ETCO2 measurement in last 10 seconds as well as corresponding time
			int max_ETCO2_index = max_index(measurements);
			int measurement = measurements[max_ETCO2_index];
			double time = (double)times[max_ETCO2_index];
			//push ETCO2 and update each summation as well as occurance
			ETCO2_values.push_back(measurement);
			ETCO2_times.push_back(time);
			sum_xy += time*measurement;
			sum_x += time;
			sum_x2 += pow(time, 2);
			sum_y += measurement;
			sum_y2 += pow(measurement, 2);
			//more than 10 data points, need to pop off earliest data, also have enough data to compute r2 and slope
			if (ETCO2_values.size() > 10) {
				//deduct values and pop front of both times and values
				sum_xy -= ETCO2_values.front()*ETCO2_times.front();
				sum_x -= ETCO2_times.front();
				sum_x2 -= pow(ETCO2_times.front(), 2);
				sum_y -= ETCO2_values.front();
				sum_y2 -= pow(ETCO2_values.front(), 2);
				ETCO2_values.pop_front();
				ETCO2_times.pop_front();
				compute_slope_r2();
			} 
			//if we have 10 datas, still calculate
			else if (ETCO2_values.size() == 10) {
				compute_slope_r2();
			}
		}
		void compute_slope_r2() {
			//computes the slope and r2, also pushes alarm if alarming, n is 10 since we always have 10 data points
			//divide all y by 60 to convert from seconds to minutes, all y2 by 3600
			double slope = pow(((10 * sum_xy/60) - (sum_x * sum_y/60)), 2) / (10 * sum_x2 - pow(sum_x, 2));
			double r2 = slope / ((10 * sum_y2/3600) - pow(sum_y/60, 2));
			std::cout <<  "slope: " << slope << " | " << "r2: " << r2 << std::endl;
			//trigger alarm if slope is greater than 1.5 and r2 is greater than .64
			if (slope > 1.5 && r2 > 0.64) {
				Alarm();
			}
		}
		int max_index(vector<int> &measurements) {
			int max = 0;
			int index = 0;
			//only calculate for the preceding 10 seconds, finding earliest max
			for (unsigned int i = (unsigned int) measurements.size() - 10; i < measurements.size(); i++) {
				if (measurements[i] > max) {
					max = measurements[i];
					index = i;
				}
			}
			return index;
		}
};

#endif