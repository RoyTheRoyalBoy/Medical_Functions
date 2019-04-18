#include "ekg_simulator.h"
#include <cassert>

using namespace std; 

void test_update(){
	EKG measurement;
	//make sure initial semgments is empty
	assert(measurement.ST_segments.empty());
	int new_segment_value = 80;
	ST_segment new_segment;
	new_segment.value = new_segment_value;
	//add one segment to ST_segments vector
	update_ST_segments(measurement.ST_segments, new_segment);
	//check if all the values line up
	assert(!measurement.ST_segments.empty());
	assert(measurement.ST_segments.back().total == 80);
	assert(measurement.ST_segments.back().min == 80);
	assert(measurement.ST_segments.back().max == 80);
	//add a few more segments
	for (int i = 0; i < 70; i++){
		//typical normal ST segment around 80 with range of 1
		new_segment.value = rand() % 2 + 79;
		update_ST_segments(measurement.ST_segments, new_segment);
	}
	assert(measurement.ST_segments.back().total > 80);
	assert(measurement.ST_segments.back().total < 4860);
	assert(measurement.ST_segments.size() == 60);
	cout << "test_update() passed!" << endl;
}

void test_ekg_normal() {
	EKG measurement;
	measurement.time = 120; //been at least 2 minutes
	//insert data every 2 seconds, so 60 datas in total
	for (int i = 0; i < 60; i++){
		//typical normal ST segment around 80 with range of 1
		int new_segment_value = rand() % 3 + 79;
		ST_segment new_segment;
		new_segment.value = new_segment_value;
		update_ST_segments(measurement.ST_segments, new_segment);
	}
	cout << endl;;
	//testing our progress function
	ProcessEKG(measurement);
	//alarm should not have been triggere
	assert(!measurement.alarm_triggered);
	cout << "test_ekg_normal() passed!" << endl;
}

void test_ekg_alarm_triggers() {
	EKG measurement;
	measurement.time = 120; //been at least 2 minutes
	for (int i = 0; i < 60; i++){
		//adding in abnormal values
		int new_segment_value = rand() % 6 + 79;
		ST_segment new_segment;
		new_segment.value = new_segment_value;
		update_ST_segments(measurement.ST_segments, new_segment);
		//manually check if ST_segments 
		cout << new_segment_value << " ";
	}
	cout << endl;
	//testing our progress funciton
	ProcessEKG(measurement);
	//alarm should have been triggered
	assert(measurement.alarm_triggered);
	cout << "test_ekg_alarm_triggers() passed!" << endl;
}

void test_ekg_not_2_minutes() {
	EKG measurement;
	int new_segment_value = 80;
	ST_segment new_segment;
	new_segment.value = new_segment_value;
	//add one segment to ST_segments vector
	update_ST_segments(measurement.ST_segments, new_segment);
	ProcessEKG(measurement);
	//make sure no false flag is raised
	assert(!measurement.alarm_triggered);
	//add more than 2 minute's worth of segments
	for (int i = 0; i < 70; i++){
		//typical normal ST segment around 80 with range of 1
		new_segment.value = rand() % 2 + 79;
		update_ST_segments(measurement.ST_segments, new_segment);
	}
	ProcessEKG(measurement);
	//make sure no false flag is raised again
	assert(!measurement.alarm_triggered);
	cout << "test_ekg_2_minutes() passed!" << endl;
}

int main() {
	test_update();
	test_ekg_normal();
	test_ekg_alarm_triggers();
	test_ekg_not_2_minutes();

	cout << "All tests passed!" << endl;
	return 0;
}
