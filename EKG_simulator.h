#ifndef EKG_SIMULATOR_H
#define EKG_SIMULATOR_H

#include <iostream>
#include <ctime>
#include <deque>
#include <unordered_map>
#include <cmath>

struct EKG_object{
	time_t time;
	int ST_segment;
};
class EKG{
	public:
		//necessary metrics to keep track of, hash table keeps track of occurances
		//total will help compute average
		std::unordered_map<int, int> hash; 
		std::deque<int> ST_segments;
		int min;
		int max;
		int total = 0;
		bool alarm_triggered = false;

		//declaring and defining functions
		//alarm function that gets called when EKG varies too wildly
		void Alarm(){
			alarm_triggered = true;
			std::cout << "Ischemia alert!" << std::endl;
		}

		void update_ST_segments(EKG_object &measurement) {
			//check if the new value is new max or min,
			//if so, update max/min for that object
			if (ST_segments.empty()) {
				//nothing in ST segments, so set min/max/total to value of new ST segment
				min = measurement.ST_segment;
				max = measurement.ST_segment;
			}
			else if (measurement.ST_segment < min) {
				min = measurement.ST_segment;
			}
			else if (measurement.ST_segment > max) {
				max = measurement.ST_segment;
			}
			//push new segment data to the back of ST segments, add instance on hash table
			total += measurement.ST_segment;
			ST_segments.push_back(measurement.ST_segment);
			hash[measurement.ST_segment]++;
			//if segments is bigger than 60, need to delete earliest to keep track of last 2 minutes of data
			//also update total and hash table accordingly
			if (ST_segments.size() > 60) {
				total -= ST_segments.front();
				hash[ST_segments.front()]--;
				//if min was popped off, find next min and update hash table
				if (ST_segments.front() == min) {
					for (int i = min; i < max; i++) {
						if (hash[i] > 0){
							min = i;
							hash[i]--;
							break;
						}
					}
				}
				//do the same for max
				else if (ST_segments.front() == max) {
					for (int i = max; i > min; i--) {
						if (hash[i] > 0){
							max = i;
							hash[i]--;
							break;
						}
					}
				}
				ST_segments.pop_front();
			}
		}

		void ProcessEKG(EKG_object &measurement) {
			update_ST_segments(measurement);
			int average = (int)ceil(total/(int)ST_segments.size());
			//compare to see if min/max difference from average is > 2 or max-min > 2, ring alarm if so
			if (abs(average - min) > 2) {
				Alarm();
			}
			else if (abs(average - max) > 2) {
				Alarm();
			}
			else if (abs(max - min) > 2) {
				Alarm();
			}
		}
};


#endif