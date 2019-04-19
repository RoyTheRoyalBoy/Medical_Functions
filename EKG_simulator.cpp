#include "ekg_simulator.h"
#include <unistd.h>

using namespace std;

int main(){
	cout << "Welcome to EKG simulator!" << endl;
	cout << "To simulate healthy heartbeat, type 'normal'" << endl;
	cout << "To simulate unhealth heartbeat, type 'abnormal'" << endl;
	cout << "Type ctrl-c to stop this simulator" << endl;
	string mode;
	cin >> mode;
	EKG EKG_machine;
	while (true) {
		//pretend 2000 = 1970
		if (mode == "normal"){
			EKG_object measurement;
			measurement.time = time(NULL);
			measurement.ST_segment = rand() % 3 + 79;
			cout << "Time: " << measurement.time << " | " << "ST_segment: " << measurement.ST_segment << endl;
			EKG_machine.ProcessEKG(measurement);
		}
		else if (mode == "abnormal") {
			//abnormal ST segment, should print alerts
			EKG_object measurement;
			measurement.time = time(NULL);
			measurement.ST_segment = rand() % 6 + 78;
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