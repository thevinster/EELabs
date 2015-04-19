#include "stdafx.h"
#include "student.h"
#include <iostream>
#include <map>

using namespace std;

int main() {
	map<string, Student> studentMap;
	map<string, Student>::iterator it;
	char input;
	string name;
	int idx, updatedScore;
	while (true) {
		cout << "Please enter a command number or 'h' for help: ";
		cin >> input;
		if (input == 'h') {
			cout << "1. Add New Student"<< endl;
			cout << "2. Remove Student" << endl;
			cout << "3. Add a New Score to All Student Objects" << endl;
			cout << "4. Update Score i for Student, s, to the Provided Value" << endl;
			cout << "5. Calculate Average" << endl;
			cout << "6. Print Student Names and Scores" << endl;
			cout << "7. Exit Program" << endl;
		}
		else if (input == '1') {	
			cout << "Please enter the student's first name: ";
			cin >> name;
			Student s(name);
			studentMap.insert(make_pair(name, s));
			cout << name << " added!" << endl;
		}
		else if (input == '2') {
			cout << "Please enter the student's first name: ";
			cin >> name;
			if (studentMap.find(name) != studentMap.end()) {
				studentMap.erase(name);
				cout << name << " erased!" << endl;
				continue;
			}
			cout << name << " is not in the map" << endl;
		}
		else if (input == '3') {
			for (it = studentMap.begin(); it != studentMap.end(); ++it) {
				it->second.add_grade(0);
			}
		}
		else if (input == '4') {
			cout << "Please enter the student's first name: ";
			cin >> name;
			cout << "Please enter an index: ";
			cin >> idx;
			cout << "Please enter updated score: ";
			cin >> updatedScore;
			studentMap[name].update_grade(idx, updatedScore);
			cout << "Updated " << name << "'s score" << endl;
		}
		else if (input == '5') {
			cout << "Please enter an index: ";
			cin >> idx;
			int sum = 0;
			double avg;
			for (it = studentMap.begin(); it != studentMap.end(); ++it) {
				sum += it->second.get_grade(idx);
			}
			avg = (double)sum / studentMap.size();
			cout << "Class Average at index " << idx << " is: " << avg << endl;
		}
		else if (input == '6') {
			for (it = studentMap.begin(); it != studentMap.end(); ++it) {
				cout << it->first << ": ";
				vector<int> temp = it->second.get_grades();
				for (vector<int>::iterator vecIt = temp.begin(); vecIt != temp.end(); ++vecIt) {
					cout << *vecIt << " ";
				}
				cout << endl;
			}
		}
		else if (input == '7') {
			break;
		}
	}
	return 0;
}