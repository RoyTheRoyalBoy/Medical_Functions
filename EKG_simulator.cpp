#include "ekg_simulator.h"

using namespace std;

void ProcessEKG(EKG &measurement) {
	//calculate the average based on information from the top segment
	ST_segment information = measurement.ST_segments.back();
	double average = information.total/int(measurement.ST_segments.size());
	//compare to see if min> 2 or max-min > 2, ring alarm if so
	if (average - information.min > 2) {
		measurement.Alarm();
	}
	else if (average - information.max > 2) {
		measurement.Alarm();
	}
	else if (information.max - information.min > 2) {
		measurement.Alarm();
	}
}
void update_ST_segments(deque<ST_segment> &ST_segments, ST_segment &new_segment) {
	//check if the new value is new max or min,
	//if so, update max/min for that object
	if (ST_segments.empty()) {
		//nothing in ST segments, so set min/max/total to value of new ST segment
		new_segment.min = new_segment.value;
		new_segment.max = new_segment.value;
		new_segment.total = new_segment.value;
	}
	//else, update total accordingly
	else if (new_segment.value < ST_segments.back().min) {
		new_segment.min = new_segment.value;
		new_segment.total = ST_segments.back().total + new_segment.value;
	}
	else if (new_segment.value > ST_segments.back().max) {
		new_segment.max = new_segment.value;
		new_segment.total = ST_segments.back().total + new_segment.value;
	}
	else {
		new_segment.total = ST_segments.back().total + new_segment.value;
	}
	//push new segment data to the back of ST segments
	ST_segments.push_back(new_segment);
	//if segments is bigger than 60, need to delete earliest to keep track of last 2 minutes of data
	//also update total accordingly
	if (ST_segments.size() > 60) {
		ST_segments.back().total -= ST_segments.front().value;
		ST_segments.pop_front();
	}
}
