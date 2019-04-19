#include "ekg_simulator.h"
#include <unistd.h>

using namespace std;

void simulate(EKG EKG_machine, int value){
	EKG_object measurement;
	//subtract the difference from 1/1/2000 to 1/1/1970 to get time from 1/1/2000
	measurement.time = time(NULL) - 946684800;
	measurement.ST_segment = value;
	cout << "Time: " << measurement.time  << " | " << "ST_segment: " << measurement.ST_segment << endl;
	EKG_machine.ProcessEKG(measurement);
}

int main(){
	cout << "Welcome to EKG simulator!" << endl;
	cout << "To simulate healthy ST segments, type 'normal'" << endl;
	cout << "To simulate unhealthy ST segments, type 'abnormal'" << endl;
	cout << "Type ctrl-c to stop this simulator" << endl;
	string mode;
	cin >> mode;
	EKG EKG_machine;
	while (true) {
		if (mode == "normal"){
			//normal heartrates
			simulate(EKG_machine, rand() % 3 + 79);
		}
		else if (mode == "abnormal") {
			//abnormal ST segment, should print alerts
			simulate(EKG_machine, rand() % 5 + 78);
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