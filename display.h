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

void display_labs(vector<result> &results, int days);

#endif