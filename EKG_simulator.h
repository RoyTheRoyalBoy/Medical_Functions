#ifndef EKG_SIMULATOR_H
#define EKG_SIMULATOR_H

#include <iostream>
#include <ctime>
#include <deque>

struct ST_segment{
	//ST_segments where all default values are 80
	//each segment will have a running min/max to keep track of
	//total and size will help keep track of average
	int value;
	int total = 0;
	int min;
	int max;
};

class EKG{
	public:
		//necessary metrics to keep track of
		bool alarm_triggered = false;
		std::deque<ST_segment> ST_segments;
		time_t time;

		//alarm function that gets called when EKG varies too wildly
		void Alarm(){
			alarm_triggered = true;
		}
};


void ProcessEKG(EKG &measurement);
void update_ST_segments(std::deque<ST_segment> &ST_segments, ST_segment &new_segment);

#endif