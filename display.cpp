#include "display.h"

using namespace std;

int main() {
	cout << "Welcome to Lab displayer!" << endl;
	cout << "For optimal display, please maximize terminal to full screen" << endl;
	cout << "Press ctrl-c to exit out anytime" << endl;
	cout << "To use this, please follow the prompts carefully" << endl;
	Display displayer;
	vector<result> results;
	bool done = false;
	while (true) {
		if (done == false) {
			//collect information
			result new_result;
			cout << "Please enter the name of the lab" << endl;
			cout << "Lab name: ";
			getline(cin, new_result.name);
			cout << endl;
			cout << "Please enter the ID of the lab (numbers only)" << endl;
			cout << "Lab ID: ";
			string id;
			getline(cin, id);
			new_result.id = stoi(id);
			cout << endl;
			cout << "Please enter the time of the lab (in Epoch and descending order)" << endl;
			cout << "Current Epoch time is " << time(NULL) << endl;
			cout << "Lab time: ";
			string time;
			getline(cin, time);
			new_result.time = stol(time);
			cout << endl;
			cout << "Please enter the value of the lab (cannot exceed 20 characters long accumatively per lab)" << endl;
			cout << "Lab value: ";
			getline(cin, new_result.value);
			results.push_back(new_result);
			cout << endl;
			cout << "Result appended, type 'done' if you are done adding in results, else type anything else to continue" << endl;
			string done_or_more;
			getline(cin, done_or_more);
			if (done_or_more == "done") {
				done = true;
			}
			cout << endl;
		}
		else {
			cout << "Please enter how many days of labs you wish to see" << endl;
			cout << "Days of history to display: ";
			int days;
			cin >> days;
			cout << endl;
			cout << "Displaying labs from past " << days << " days" << endl;
			displayer.DisplayLabs(results, days);
			cout << "Exiting program, have a nice day!" << endl;
			cout << endl;
			break;
		}

	}
	return 0;
}