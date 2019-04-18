#include "EKG_simulator.h"
#include <cassert>

using namespace std; 

void test_ekg_normal() {
	EKG measurement;
	measurement.time = 120; //been at least 2 minutes
	for (int i = 0; i < 60; i++){
		//typical ST segment around 80 with range of 2
		int ST_segment = rand() % 4 + 78;
		measurement.ST_segment.push_back(ST_segment);
		//manually check if ST_segments is reasonable
		cout << ST_segment << " ";
	}
	cout << endl;
	ProcessEKG(measurement);
	//alarm should not have been triggered
	assert(!measurement.alarm_triggered);
	cout << "test_ekg_normal() passed!" << endl;
}

void test_ekg_less_than_2_minutes() {
	assert(false);
	cout << "test_ekg_less_than_2_minutes() passed!" << endl;
}

void test_ekg_alarm_triggers() {
	assert(false);
	cout << "test_ekg_alarm_triggers() passed!" << endl;
}
int main() {
	test_ekg_normal();
	test_ekg_less_than_2_minutes();
	test_ekg_alarm_triggers();

	cout << "test_EKG.cpp passed!" << endl;
	return 0;
}
