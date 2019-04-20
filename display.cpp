#include "display.h"

using namespace std;

void print_display(unordered_map<string, vector<result>> display) {
	for (unsigned int i = 0; i < results.size(); i++){
		cout << "date/time: " << ctime(&diresults[i].time) << endl;
	}
}