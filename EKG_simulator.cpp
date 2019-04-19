#include "ekg_simulator.h"
#include <unistd.h>

using namespace std;

int main(){
	cout << "Welcome to EKG simulator!" << endl;
	cout << "To simulate healthy ST segments, type 'normal'" << endl;
	cout << "To simulate unhealthy ST segments, type 'abnormal'" << endl;
	cout << "Press ctrl-c to stop this simulator" << endl;
	string mode;
	cin >> mode;
	EKG EKG_machine;
	while (true) {
		if (mode == "normal"){
			//normal heartrates
			EKG_object measurement;
			//subtract the difference from 1/1/2000 to 1/1/1970 to get time from 1/1/2000
			measurement.time = time(NULL) - 946684800;
			measurement.ST_segment = rand() % 3 + 78;
			cout << "Time: " << measurement.time  << " | " << "ST_segment: " << measurement.ST_segment << endl;
			EKG_machine.ProcessEKG(measurement);
		}
		else if (mode == "abnormal") {
			//abnormal ST segment, should print alerts
			EKG_object measurement;
			//subtract the difference from 1/1/2000 to 1/1/1970 to get time from 1/1/2000
			measurement.time = time(NULL) - 946684800;
			measurement.ST_segment = rand() % 5 + 77;
			cout << "Time: " << measurement.time  << " | " << "ST_segment: " << measurement.ST_segment << endl;
			EKG_machine.ProcessEKG(measurement);
		}
		else {
			cout << "invalid command, exiting EKG simulator..." << endl;
			break;
		}
		//call this every 2 seconds
		usleep(2000000);
	}
	return 0;
}