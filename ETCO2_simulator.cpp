#include "ETCO2.h"
#include <unistd.h>

using namespace std;

int main() {
	cout << "Welcome to ETCO2 monitor simulator!" << endl;
	cout << "To simulate healthy ETCO2 levels, type 'normal'" << endl;
	cout << "To simulate malignant inducint ETCO2 levels, type 'abnormal'" << endl;
	cout << "Press ctrl-c to stop this simulator" << endl;
	string mode;
	cin >> mode;

	ETCO2_monitor monitor;
	vector<int> measurements;
	vector<time_t> times;
	int count = 0;
	while(true){
		if (mode == "normal") {
			//healthy ETCO2 levels
			int measurement = rand()%11 + 35;
			//subtract the difference from 1/1/2000 to 1/1/1970 to get seconds since 1/1/2000
			time_t curr_time = time(NULL) - 946684800;
			measurements.push_back(measurement);
			times.push_back(curr_time);
			cout << "Time: " << curr_time << " | " << "ETCO2 measurement: " << measurement << endl;
			if (count%10 == 0 && count != 0) {
				//10 seconds have elapsed, process data
				monitor.ProcessETCO2(measurements, times);
				int maximum = measurements[monitor.max_index(measurements)];
				cout << "Processing..." << endl;
				cout << "Maximum value in preceding 10 seconds: " << maximum << endl;
			}
		}
		else if (mode == "abnormal") {
			//unhealthy rising ETCO2 levels
			int measurement = rand()%11 + count * 2;
			//subtract the difference from 1/1/2000 to 1/1/1970 to get seconds since 1/1/2000
			time_t curr_time = time(NULL) - 946684800;
			measurements.push_back(measurement);
			times.push_back(curr_time);
			cout << "Time: " << curr_time << " | " << "ETCO2 measurement: " << measurement << endl;
			if (count%10 == 0 && count != 0) {
				//10 seconds have elapsed, process data
				monitor.ProcessETCO2(measurements, times);
				int maximum = measurements[monitor.max_index(measurements)];
				cout << "Processing..." << endl;
				cout << "Maximum value in preceding 10 seconds: " << maximum << endl;
			}
		}
		else {
			cout << "invalid command, exiting ETCO2 monitor simulator..." << endl;
		}
		//values are added every 1 second
		count++;
		usleep(1000000);
	}
}