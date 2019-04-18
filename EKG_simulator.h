#ifndef EKG_SIMULATOR_H
#define EKG_SIMULATOR_H

#include <iostream>
#include <ctime>
#include <vector>

class EKG{
	public:
		//necessary metrics to keep track of
		bool alarm_triggered = false;
		std::vector<int> ST_segment; 
		time_t time;
		//alarm function that gets called
		void Alarm(){
			alarm_triggered = true;
		}
};
void ProcessEKG(EKG measurement);

#endif