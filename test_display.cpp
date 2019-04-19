#include "display.h"
#include <cassert>

using namespace std;

void test_basic() {
	vector<result> results;
	result new_result;
	//add time of 1/1/1970, this will be our new lab
	new_result.time = 50;
	new_result.name = "lab0";
	new_result.id = 0;
	new_result.value = "This is our first lab!";
	results.push_back(new_result);
	//just test one result and 1 day
	display_labs(results, 1);
	cout << "test_display() passed!" << endl;
}

void test_time() {
	//test to see how time behaves, order of insertion is descending
	vector<result> results;
	//present time
	result new_result;
	new_result.time = time(NULL);
	results.push_back(new_result);
	//yesterday midnight, calculated by getting rid of excess seconds in a day
	new_result.time = time(NULL) - (time(NULL) % 86400);
	results.push_back(new_result);
	//yesterday = current - 1 day
	new_result.time = time(NULL) - 86400;
	results.push_back(new_result);
	//should result 2 days of data, one at midnight
	display_labs(results, 2);
	cout << "test_time() passed!" << endl;
}

int main() {
	test_basic();
	test_time();
	cout << "All tests passed!" << endl;
}