#include "ekg_simulator.h"
#include <cassert>

using namespace std;

void test_update(){
	//generic testing to see if insertion works and updates relevant variables, also tests if total works correctly
	EKG EKG_machine;
	//make sure initial semgments is empty
	assert(EKG_machine.ST_segments.empty());
	EKG_object measurement;
	measurement.ST_segment = 80;
	//call processEKG
	EKG_machine.ProcessEKG(measurement);
	//check if all the values line up
	assert(!EKG_machine.ST_segments.empty());
	assert(EKG_machine.total == 80);
	assert(EKG_machine.min == 80);
	assert(EKG_machine.max == 80);
	//add a lot more segments
	for (int i = 0; i < 70; i++){
		EKG_machine.ProcessEKG(measurement);
	}
	//makes sure size doesn't exceed 60 (2 minutes)
	//makes sure total is 4800 = 80*60 
	//check min and max again
	assert(EKG_machine.total == 4800);
	assert(EKG_machine.min == 80);
	assert(EKG_machine.max == 80);
	assert(EKG_machine.ST_segments.size() == 60);
	cout << "test_update() passed!" << endl;
}

void test_ekg_normal() {
	EKG EKG_machine;
	EKG_object measurement;
	//insert data every 2 seconds, so 60 datas in total
	for (int i = 0; i < 60; i++){
		//typical healthy ST segment around 80 with range of 1
		measurement.ST_segment = rand() % 2 + 79;
		EKG_machine.ProcessEKG(measurement);
	}
	//alarm should not have been triggered due to healthy ST segments
	assert(!EKG_machine.alarm_triggered);
	cout << "test_ekg_normal() passed!" << endl;
}

void test_ekg_alarm_triggers() {
	EKG EKG_machine;
	EKG_object measurement;
	//insert data every 2 seconds, so 60 datas in total
	for (int i = 0; i < 60; i++){
		//abnormal heartrate 
		measurement.ST_segment = rand() % 10 + 75;
		EKG_machine.ProcessEKG(measurement);
	}
	//alarm should trigger
	assert(EKG_machine.alarm_triggered);
	cout << "test_ekg_alarm_triggers passed!" << endl;
}

void test_new_min() {
	//test if our minimum value updates correctly when previous min is no longer in the preceding 2 minutes
	EKG EKG_machine;
	EKG_object measurement;
	//insert a really low number
	measurement.ST_segment = 30;
	EKG_machine.ProcessEKG(measurement);
	//do this again for edge case that duplicate minimums exist
	EKG_machine.ProcessEKG(measurement);
	//insert filler numbers higher than the minimum
	for (int i = 0; i < 58; i++){
		measurement.ST_segment = rand() % 10 + 75;
		EKG_machine.ProcessEKG(measurement);
	}
	//insert another low number, but higher than first two low number
	measurement.ST_segment = 35;
	EKG_machine.ProcessEKG(measurement);
	//minimum should still be 30 since the second 30 is still in the 2 minute window
	assert(EKG_machine.min == 30);
	//add 35 again, kicking 30 out of window entirely
	EKG_machine.ProcessEKG(measurement);
	//minimum should not be 30 since 30 is no longer in the 2 minute window
	assert(EKG_machine.min != 30);
	assert(EKG_machine.min == 35);
	cout << "test_new_min() passed!" << endl;
}

void test_new_max() {
	//same as testing new min, but for max
	EKG EKG_machine;
	EKG_object measurement;
	//insert a really high number
	measurement.ST_segment = 130;
	EKG_machine.ProcessEKG(measurement);
	//do this again for edge case that duplicate maximums exist
	EKG_machine.ProcessEKG(measurement);
	//insert filler numbers higher than the maximum
	for (int i = 0; i < 58; i++){
		measurement.ST_segment = rand() % 10 + 75;
		EKG_machine.ProcessEKG(measurement);
	}
	//insert another low number, but lower than first two high number
	measurement.ST_segment = 125;
	EKG_machine.ProcessEKG(measurement);
	//maximum should still be 130 since second one is in it
	assert(EKG_machine.max == 130);
	//130 completely kicked out
	EKG_machine.ProcessEKG(measurement);
	assert(EKG_machine.max != 130);
	assert(EKG_machine.max == 125);
	cout << "test_new_max() passed!" << endl;
}


int main() {
	test_update();
	test_ekg_normal();
	test_ekg_alarm_triggers();
	test_new_min();
	test_new_max();

	cout << "All tests passed!" << endl;
	return 0;
}
