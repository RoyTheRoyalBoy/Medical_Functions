#include "display.h"
#include <cassert>

using namespace std;

void test_basic() {
	Display displayer;
	vector<result> results;
	result new_result;
	//add time of 1/1/1970, this will be our new lab
	new_result.time = time(NULL);
	new_result.name = "lab0";
	new_result.id = 0;
	new_result.value = "This is our lab!";
	results.push_back(new_result);
	//just test one result and 1 day
	displayer.DisplayLabs(results, 1);
	cout << "test_display() passed!" << endl;
}

void test_time() {
	//test to see how time behaves, order of insertion is descending
	Display displayer;
	vector<result> results;
	//present time
	result new_result;
	new_result.time = time(NULL);
	new_result.name = "blood test";
	new_result.id = 2;
	new_result.value = "AB+";
	results.push_back(new_result);
	//yesterday midnight, calculated by getting rid of excess seconds in a day
	new_result.time = time(NULL) - (time(NULL) % 86400);
	new_result.name = "weight";
	new_result.id = 1;
	new_result.value = "70kg";
	results.push_back(new_result);
	//yesterday = current - 1 day
	new_result.time = time(NULL) - 86400;
	new_result.name = "heart rate";
	new_result.id = 1;
	new_result.value = "100BPM";
	results.push_back(new_result);
	//should result 2 days of data, so 3 datas
	cout << "2 days" << endl;
	displayer.DisplayLabs(results, 2);
	//should only result 1 day of data, so 2 data
	cout << "1 day" << endl;
	displayer.DisplayLabs(results, 1);
	cout << "test_time() passed!" << endl;
}

void test_lab_multiple_days() {
	//test to see if lab data shows on multiple days
	Display displayer;
	vector<result> results;
	result new_result;
	//yesterday midnight, calculated by getting rid of excess seconds in a day
	new_result.time = time(NULL) - (time(NULL) % 86400);
	new_result.name = "weight";
	new_result.id = 1;
	new_result.value = "70kg";
	results.push_back(new_result);
	//current - 2 day, skip a day, result still correct?
	new_result.time = time(NULL) - 86400*2;
	new_result.name = "weight";
	new_result.id = 1;
	new_result.value = "50kg";
	results.push_back(new_result);
	//also, what if we list higher date shown than amount entered?
	displayer.DisplayLabs(results, 4);
	cout << "test_lab_multiple_days() passed!" << endl;
}

void test_multiple_values_in_1_lab() {
	//test to see if lab data shows when same day and lab is appended
	Display displayer;
	vector<result> results;
	result new_result;
	//time is current time
	new_result.time = time(NULL);
	new_result.name = "weight";
	new_result.id = 1;
	new_result.value = "70kg";
	results.push_back(new_result);
	//earlier time, but same day, only difference is the value, will value append?
	new_result.time = time(NULL) - (time(NULL) % 86400);
	new_result.value = "71kg";
	results.push_back(new_result);
	//another lab result, but different name to see how print behaves
	new_result.value = "200IQ";
	new_result.name = "brain power";
	results.push_back(new_result);
	displayer.DisplayLabs(results, 4);
	cout << "test_multiple_values_in_1_lab() passed!" << endl;
}

void test_large() {
	//what if we just had a bunch of values, lots of labs and dates, less than 20 characters per slot
}

int main() {
	test_basic();
	test_time();
	test_lab_multiple_days();
	test_multiple_values_in_1_lab();
	test_large();
	cout << "All tests passed!" << endl;
}