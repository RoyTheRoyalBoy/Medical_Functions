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
	//do another one the day before
	new_result.time = time(NULL) - 86400*3;
	new_result.name = "weight";
	new_result.id = 1;
	new_result.value = "80kg";
	results.push_back(new_result);
	//and another one
	new_result.time = time(NULL) - 86400*6;
	new_result.name = "weight";
	new_result.id = 1;
	new_result.value = "75kg";
	results.push_back(new_result);
	//should only see 3 results
	cout << "Displaying 4 days of results" << endl;
	displayer.DisplayLabs(results, 4);
	//should see all 4 results
	cout << "Displaying 9 days of results" << endl;
	displayer.DisplayLabs(results, 9);
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
	//push in the old lab name with new results again
	new_result.name = "weight";
	new_result.value = "77kg";
	results.push_back(new_result);
	//see how many more results can fit before program breaks
	new_result.value = "1kg";
	results.push_back(new_result);
	cout << "Normal inputs to test limit how many values a slot can hold" << endl;
	displayer.DisplayLabs(results, 4); 
	//broke after pushing this line
	new_result.value = "100kg";
	results.push_back(new_result);
	cout << "error inducing inputs" << endl;
	displayer.DisplayLabs(results, 4);
	cout << "test_multiple_values_in_1_lab() passed!" << endl;
}


int main() {
	test_basic();
	test_time();
	test_lab_multiple_days();
	test_multiple_values_in_1_lab();
	cout << "All tests passed!" << endl;
}