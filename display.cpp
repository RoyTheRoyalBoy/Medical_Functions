#include "display.h"

using namespace std;

void display_labs(vector<result> &results, int days){
	for (unsigned int i = 0; i < results.size(); i++) {
		if (days > 0) {
			cout << "date/time: " << ctime(&results[i].time) << endl;
		}
	}
}
