#include "ETCO2.h"
#include <cassert>

using namespace std;

void test_value_updates() {
	//test to see if insertions and values are updating properly
	ETCO2_monitor monitor;
	vector<int> measurements;
	vector<time_t> times;
	//insert 10 constant value, start at 1 for non-zero time
	for (int i = 1; i < 11; i++) {
		//insert values of 40 with incrementing time for 10 seconds
		int measurement = 40;
		time_t time = i;
		measurements.push_back(measurement);
		times.push_back(time);
	}
	monitor.ProcessETCO2(measurements, times);
	//see if values are updated correctly
	assert(monitor.sum_xy == 40);
	//the first 40 at 1 seconds is max value
	assert(monitor.sum_x == 1);
	assert(monitor.sum_x2 == 1);
	//40 is the max value
	assert(monitor.sum_y == 40);
	assert(monitor.sum_y2 == 1600);

	//do it again, this time test to see if max value is added to summations
	for (int i = 11; i < 21; i++) {
		int measurement = i+30;
		time_t time = i;
		measurements.push_back(measurement);
		times.push_back(time);
	}
	monitor.ProcessETCO2(measurements, times);
	//see if values are updated correctly
	//1(40) + 20(50) = 1040
	assert(monitor.sum_xy == 1040);
	//1 + 20 since those are times where value was max
	assert(monitor.sum_x == 21);
	//1 + 20^2 is 401
	assert(monitor.sum_x2 == 401);
	//40 + 50 since 50 should be the max value from the second insertion
	assert(monitor.sum_y == 90);
	//40^2 + 50^2 is 4100
	assert(monitor.sum_y2 == 4100);
	cout << "test_basic() passed!" << endl;
}


void test_ETCO2_normal() {
	//testing normal inputs that won't trigger alarm
	ETCO2_monitor monitor;
	vector<int> measurements;
	vector<time_t> times;
	time_t time = 0;
	//insert 100 normal values and process them 10 times
	for (int j = 0; j < 10; j++){
		for (int i = 0; i < 10; i++) {
			//insert normal values within rance of 35-45 with incrementing time
			int measurement = rand()%11 + 35;
			time++;
			measurements.push_back(measurement);
			times.push_back(time);
		}
		monitor.ProcessETCO2(measurements, times);
	}
	//alarm should not trigger, slope should be less than 1
	assert(!monitor.alarm_triggered);
	cout << "test_ETCO2_normal() passed!" << endl;
}

void test_ETCO2_alarm_trigger() {
	//testing really alarming inputs
	ETCO2_monitor monitor;
	vector<int> measurements;
	vector<time_t> times;
	time_t time = 0;
	//insert 100 abnormal values and process them 10 times
	for (int j = 0; j < 10; j++){
		for (int i = 0; i < 10; i++) {
			//insert rapidly increasing values with incrementing time
			int measurement = j*100;
			time++;
			measurements.push_back(measurement);
			times.push_back(time);
		}
		monitor.ProcessETCO2(measurements, times);
	}
	//alarm should definitely trigger, slope should be greater than 1
	assert(monitor.alarm_triggered);
	cout << "test_ETCO2_alarm_trigger() passed!" << endl;
}

int main() {
	test_value_updates();
	test_ETCO2_normal();
	test_ETCO2_alarm_trigger();
	cout << "All tests passed!" << endl;
}