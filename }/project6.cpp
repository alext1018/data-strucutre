// Project 6
// CS 2413 Data Structures
// Spring 2023

#include <iostream>
#include <string> // for storing string
#include <fstream> // for reading a file again and again
#include <map> 
#include <unordered_map>
#include <vector>
#include <chrono> // for calculating run time

using namespace std;

// write hash function
int hashKey( string str) {
	// set table size
	int TABLE_SIZE = 1024;

	// randome seed
	int seed = 17;

	unsigned int hash_value = 0;
	for (char c : str) {
		// Multiply the hash value by a random number and add the ASCII code of the character
		hash_value = hash_value * seed + c;
	}

	// 
	hash_value = hash_value % TABLE_SIZE;

	return hash_value;
}


// write display functions for map and unordered map
void display(map<int, vector<string> > m) {
	cout << "Map:" << endl;
	for (map<int, vector<string> >::iterator it = m.begin(); it != m.end(); ++it) {
		// print hash_value
		cout << it->first << ": ";
		// print string
		for (string v : it->second) {
			cout << v << " ";
		}
		cout << endl;
	}
}

void display(unordered_map<int, vector<string> > m) {
	cout << "Unordered Map:" << endl;
	for (unordered_map<int, vector<string> >::iterator it = m.begin(); it != m.end(); ++it) {
		// print hash_value
		cout << it->first << ": ";
		// print string
		for (string v : it->second) {
			cout << v << " ";
		}
		cout << endl;
	}
}


int main()
{
	string fileName; // to read in the name of the fileInput from redirected input

	cin >> fileName;
	cout << "Name of fileInput: " << fileName << endl;


	char option;
	string temp;
	// MAP
	map <int, vector<string> > m1;
	// UNORDERED MAP
	unordered_map<int, vector<string> > m2;

	// Test Remove , fisrt insert 1000000 data into map and unordered map
	//ifstream fI1;
	//fI1.open("I1000000.txt");
	//while(fI1 >> option)
	//{
	//	fI1 >> temp;
	//	// create the structure - map - m1
	//	int key = hashKey(temp);
	//	if (option == 'I') {
	//		m1[key].push_back(temp);
	//		m2[key].push_back(temp);
	//	}
	//}
	//fI1.close();

	// open a fileName in read mode
	ifstream fI; 
	fI.open(fileName);

    // reading and performing operations
    // start timer
	//time_point<high_resolution_clock> start = high_resolution_clock::now();
	while(fI >> option)
	{
		fI >> temp;
		// create the structure - map - m1
		int key = hashKey(temp);
		if (option == 'I') {
			// insert
			m1[key].push_back(temp);
		}
		else {
			// remvoe
			if (m1[key].size() == 1) {
				// If there is only one value, remove it from the map
				m1.erase(key);
			}
			else {
				// There are multiple values, delete the corresponding string
				for (vector<string>::iterator it = m1[key].begin(); it != m1[key].end(); ++it) {
					if (*it == temp) {
						m1[key].erase(it);
						break;
					}
				}
			}
		}
	}
    // stop timer
	//time_point<high_resolution_clock> end = high_resolution_clock::now();
	//duration<double, milli> duration = end - start;
	//cout << "map run time: " << duration.count() << " milliseconds" << endl;

	// close the opened file
	fI.close();

	display(m1);

	// open a file again in read mode
	fI.open(fileName);

    // start timer
	//start = high_resolution_clock::now();
	while(fI >> option)
	{
		fI >> temp;
		// create the structure - unordered map - m2
		int key = hashKey(temp);
		if (option == 'I') {
			// insert
			m2[key].push_back(temp);
		}
		else {
			if (m2[key].size() == 1) {
				// If there is only one value, remove it from the map
				m2.erase(key);
			}
			else {
				// There are multiple values, delete the corresponding string
				for (vector<string>::iterator it = m2[key].begin(); it != m2[key].end(); ++it) {
					if (*it == temp) {
						m2[key].erase(it);
						break;
					}
				}
			}
		}
	}
    // stop timer
	//end = high_resolution_clock::now();

	
	//duration = end - start;
	//cout << "unordered_map run time: " << duration.count() << " milliseconds" << endl;

	display(m2);

	// close the opened file
	fI.close();

	return 0;
}
