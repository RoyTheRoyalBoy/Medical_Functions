#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <unordered_map>
#include <iomanip>

using std::string;
using std::to_string;
using std::vector;
using std::cout;
using std::endl;
using std::left;
using std::setw;
using std::setfill;

struct result {
	time_t time = 0;
	string name = "NULL";
	int id = 0;
	string value = "NULL";
};

class Display {
	public:
		//three data structure that will be produced
		vector<string> name_row;
		vector<time_t> date_col;
		std::unordered_map<time_t, vector<result>> data;
		std::unordered_map<string, int> date_occurance;

		void DisplayLabs(vector<result> &results, int days) {
			//Take in an array of datas and a number of days to display
			//clear vectors out before every call, then append values to it
			name_row.clear();
			date_col.clear();
			data.clear();
			date_occurance.clear();
			for (unsigned int i = 0; i < results.size(); i++) {
				//only display the results within the given day, calculated by finding cut off
				time_t cut_off = time(NULL) - (time(NULL)%86400) - (days - 1)*86400;
				if (results[i].time >= cut_off) {
					if (date_occurance[results[i].name] == 0) {
						name_row.push_back(results[i].name);
						date_occurance[results[i].name]++;
					}
					//just push back the time of the day, only if it hasn't already been seen
					time_t date = results[i].time - (results[i].time % 86400);
					if (data[date].empty()) {
						date_col.push_back(date);
					}
					//push into hash table vector the time and the day
					data[date].push_back(results[i]);
				}
				else {
					//stop the program to save time, we're given descending order so data after cutoff is unneeded
					break;
				}
			}
			print_display();
		}

		void print_display() {
			int col_width = 20;
			cout << left << setw(col_width) << setfill(' ') << "date";
			//print the dates column first
			for (unsigned int i = 0; i < date_col.size(); i++){
				//display local time month, day, year
				tm *ltm = localtime(&date_col[i]);
				string date = "|" + to_string(1 + ltm->tm_mon) + "/" + to_string(ltm->tm_mday) + "/" + to_string(1900 + ltm->tm_year);
				cout << left << setw(col_width) << setfill(' ') << date;
			}
			cout << endl;
			//iterate through rows and begin the row string
			for (unsigned int i = 0; i < name_row.size(); i++){
				cout << left << setw(col_width) << setfill(' ') << name_row[i];
				string row = "";
				//iterate through columns and append | to separate columns
				for (unsigned int j = 0; j < date_col.size(); j++) {
					row += "|";
					//search through data map to add to row, keep appending values with the same lab names for that column
					for (unsigned int k = 0; k < data[date_col[j]].size(); k++) {
						if (data[date_col[j]][k].name == name_row[i]) {
							row += data[date_col[j]][k].value + " ";
						}
					}
					//fill in the remaining spaces by calculating (column)*(col_width)-(spaces already occupied)
					int remaining_space = col_width * (j+1) - (int)row.length();
				 	row.append(remaining_space, ' ');
				}
				//print out the row
				cout << row << endl;
			}
		}
};


#endif