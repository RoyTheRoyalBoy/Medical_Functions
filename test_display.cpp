#include "display.h"
#include <cassert>

using namespace std;

void test_basic() {
	vector<result> results;
	result new_result;
	//add time of 1/1/1970, this will be our new lab
	new_result.time = 0;
	new_result.name = "lab0";
	new_result.id = 0;
	new_result.value = "This is our first lab!";
	results.push_back(new_result);
	//just test one result and 1 day
	display_labs(results, 1);

	cout << "test_display() passed!" << endl;
}

int main() {
	test_basic();

	cout << "All tests passed!" << endl;
}