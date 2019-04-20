#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <vector>
#include <iostream>
#include <ctime>

using std::string;
using std::vector;

struct result {
	time_t time;
	string name;
	int id;
	string value;
};

struct Display {
	//three vectors that will be produced
	vector<int> name_row;
	vector<time_t> date_column;
	vector<vector<string>> data;

	void display_labs(vector<result> &results, int days) {
		//Take in an array of datas and a number of days to display
		//Output a hash table with three arrays
		for (unsigned int i = 0; i < results.size(); i++) {
			//only display the results in the given day, calculated by finding cut off
			time_t cut_off = time(NULL) - (time(NULL)%86400) - (days - 1)*86400;
			if (results[i].time > cut_off) {
				name_row.push_back(results[i].name);
				date_column.push_back(results[i].time);
				data.push_back(results[i]);
			}
			else {
				//stop the program to save time, we're given descending order
				break;
			}
		}
	}
}


#endif