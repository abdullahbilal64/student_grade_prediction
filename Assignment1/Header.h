#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// COURSE CODES CORRESPONDING TO LOCATION IN ARRAYS:
/*
MT104: 0     MT119: 1     CS118: 2     CL118: 3     EE182: 4     SL101: 5     SS101: 6

EE227: 7     SS122: 8     MT224: 9     SS111: 10    CS217: 11    EL227: 12    CL217: 13

CS201: 16 DATA STRUCTURES 
*/

double** Load_Data(string path) {
	int rollNo = 0;
	ifstream file;  // fstream object to read data in file.
	string lineBuffer = ""; // buffer to read each line.
	string subBuffer = "";  // buffer to read each part of line.
	string semester = "";   // check for semester number for each course;
							// advantage is it will make it easier to keep track of repeated courses.
	int semesterNo = -1;
	int semesterNoForCGPA = -1;  // variable to make sure CGPA is of latest semester
	string courseCode; // to control which position of array to enter which grade point in.
	int* lastAttemptedSemester = new int[21]; // to make sure each entry in array is of latest
													// attempt.
	int itt = 0; // itterator to control position in line while reading file line by line.
	file.open(path, ios::in);
	const int noOfStudents = 1779;
	const int noOfCourses = 14;
	double** gradepoint = new double* [noOfStudents + 1]; // 1 is added because students are starting from 0.
	for (int j = 0; j < noOfStudents + 1; j++) { // creadting dynamic arrays to store grade points of each student.
		gradepoint[j] = new double[noOfCourses + 1 + 1 + 1]; // an extra slot is for CGPA and other for noOfWarnings and another for data structures grade.
	}
	getline(file, lineBuffer); // discarding first line that does not have any student data.
	while (!file.eof() && rollNo <= 1779) { // itterating through each line of file.
		getline(file, lineBuffer); // reading each line of the file.
		itt = 0; // resetting itterator.
		subBuffer = ""; // resetting subBuffer.
		while (lineBuffer[itt] != ',') { // reading first value(roll number/ serial number).
			subBuffer += lineBuffer[itt]; // storing roll number in subBuffer.
			itt++; //  moving itterator.
		}
		if (rollNo != stoi(subBuffer)) { // making sure same roll number is not repeated multiple times.
			rollNo = stoi(subBuffer); // if new roll number read for the first time, update it.
			semesterNoForCGPA = -1;
			for (int i = 0; i < 22; i++) {		// resetting lastAttemptedSemester array every time
				lastAttemptedSemester[i] = -1;  // new roll number is added.
			}
		}
		subBuffer = ""; // resetting subBuffer;
		itt++; // moving itterator to read next value
		while (lineBuffer[itt] != ',') {
			subBuffer += lineBuffer[itt]; // storing semester in subBuffer.
			itt++; // moving itterator.
		}
		itt++;
		semester = subBuffer;
		subBuffer = ""; // resetting subBuffer;
		if (semester == "Spring 2017") {
			semesterNo = 1;
		}
		else if (semester == "Fall 2017") {
			semesterNo = 2;
		}
		else if (semester == "Spring 2018") {
			semesterNo = 3;
		}
		else if (semester == "Fall 2018") {
			semesterNo = 4;
		}
		else if (semester == "Spring 2019") {
			semesterNo = 5;
		}
		else if (semester == "Unknown") {
			semesterNo = 0;
		}
		while (lineBuffer[itt] != ',') {
			subBuffer += lineBuffer[itt]; // storing course codes in subBuffer.
			itt++; // moving itterator.
		}
		itt++; // moving itterator to next position.
		courseCode = subBuffer;
		subBuffer = ""; // resetting subBuffer.
		while (lineBuffer[itt] != ',') { // ignoring course title.
			itt++; // moving itterator.
		}
		itt++; // moving itterator
		while (lineBuffer[itt] != ',') { // ignoring number of credit hours.
			itt++; // moving itterator.
		}
		itt++; // moving itterator.
		while (lineBuffer[itt] != ',') { // ignoring letter grade.
			itt++; // moving itterator.
		}
		itt++; // moving itterator.
		while (lineBuffer[itt] != ',') {
			subBuffer += lineBuffer[itt]; // storing grade points in subBuffer.
			itt++; // moving itterator.
		}
		itt++;
		if (courseCode == "CS201") { // data structures.
			if (lastAttemptedSemester[16] < semesterNo) {
				gradepoint[rollNo][16] = stod(subBuffer);
				lastAttemptedSemester[16] = semesterNo;
			}
		}
		if (courseCode == "MT104") {
			if (lastAttemptedSemester[0] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][0] = stod(subBuffer);
				lastAttemptedSemester[0] = semesterNo;
			}
		}
		else if (courseCode == "MT119") {
			if (lastAttemptedSemester[1] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][1] = stod(subBuffer);
				lastAttemptedSemester[1] = semesterNo;
			}
		}
		else if (courseCode == "CS118") {
			if (lastAttemptedSemester[2] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][2] = stod(subBuffer);
				lastAttemptedSemester[2] = semesterNo;
			}
		}
		else if (courseCode == "CL118") {
			if (lastAttemptedSemester[3] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][3] = stod(subBuffer);
				lastAttemptedSemester[3] = semesterNo;
			}
		}
		else if (courseCode == "EE182") {
			if (lastAttemptedSemester[4] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][4] = stod(subBuffer);
				lastAttemptedSemester[4] = semesterNo;
			}
		}
		else if (courseCode == "SL101") {
			if (lastAttemptedSemester[5] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][5] = stod(subBuffer);
				lastAttemptedSemester[5] = semesterNo;
			}
		}
		else if (courseCode == "SS101") {
			if (lastAttemptedSemester[6] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][6] = stod(subBuffer);
				lastAttemptedSemester[6] = semesterNo;
				if (rollNo == 1779) {
					break;
				}
			}
		}
		else if (courseCode == "EE227") {
			if (lastAttemptedSemester[7] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][7] = stod(subBuffer);
				lastAttemptedSemester[7] = semesterNo;
			}
		}
		else if (courseCode == "SS122") {
			if (lastAttemptedSemester[8] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][8] = stod(subBuffer);
				lastAttemptedSemester[8] = semesterNo;
			}
		}
		else if (courseCode == "MT224") {
			if (lastAttemptedSemester[9] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][9] = stod(subBuffer);
				lastAttemptedSemester[9] = semesterNo;
			}
		}
		else if (courseCode == "SS111") {
			if (lastAttemptedSemester[10] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][10] = stod(subBuffer);
				lastAttemptedSemester[10] = semesterNo;
			}
		}
		else if (courseCode == "CS217") {
			if (lastAttemptedSemester[11] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][11] = stod(subBuffer);
				lastAttemptedSemester[11] = semesterNo;
			}
		}
		else if (courseCode == "EL227") {
			if (lastAttemptedSemester[12] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][12] = stod(subBuffer);
				lastAttemptedSemester[12] = semesterNo;
			}
		}
		else if (courseCode == "CL217") {
			if (lastAttemptedSemester[13] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][13] = stod(subBuffer);
				lastAttemptedSemester[13] = semesterNo;
			}
		}
		subBuffer = "";
		while (lineBuffer[itt] != ',') { // ignoring SGPA
			itt++; // moving itterator.
		}
		itt++;
		while (lineBuffer[itt] != ',') {
			subBuffer += lineBuffer[itt]; // storing CGPA in subBuffer.
			itt++; // moving itterator.
		}
		itt++;
		if (semesterNoForCGPA < semesterNo) { // checking if CGPA of latest semester is already present.
			semesterNoForCGPA = semesterNo;
			gradepoint[rollNo][14] = stod(subBuffer); // if not present, update CGPA.
		}
		subBuffer = "";
		subBuffer += lineBuffer[itt]; // storing warnings in subBuffer.
		if (gradepoint[rollNo][15] < stoi(subBuffer)) { // checking if semester is valid and not unknown.
			gradepoint[rollNo][15] = stoi(subBuffer);
		}
		itt++;
	}
	file.close();
	return gradepoint;
}


double** Distance(double* predictedArray, int predictedArraySize, double** data, int dataRows, int dataCols) {
	double** outArr = new double*[dataRows];
	double subjectDistance = 0;
	double totalDistance = 0;
	for (int i = 0; i < dataRows; i++) {
		outArr[i] = new double[2];
	}
	for (int i = 0; i < dataRows; i++) {
		totalDistance = 0;  
		for (int j = 0; j < 14; j++) {
			subjectDistance = predictedArray[j] - data[i][j]; // calculating distance from each student.
			if (subjectDistance < 0) { // making value positive.
				subjectDistance *= -1;
			}
			if (j == 2 || j == 3 || j == 11 || j == 13) {
				subjectDistance *= 1.5;
			}
			totalDistance += subjectDistance;
		}
		outArr[i][0] = totalDistance;
		outArr[i][1] = data[i][16];
	}
	return outArr;
}

double** Sort_k_Dis(int k, double** distance, int distanceRows, int distanceCols) {
	int i = 0;
	double* tempArr = new double[distanceRows];
	while (i < distanceRows) { // iterating through each row.
		tempArr[i] = distance[i][1]; // storing values in a temporary array.
		i++;
	}
	for (int j = 0; j < distanceRows; j++) {

	}
}







void arrangeData() {
	int rollNo = 0; // variable to store roll number and contolling the array.
	ifstream file;  // fstream object to read data in file.
	string lineBuffer = ""; // buffer to read each line.
	string subBuffer = "";  // buffer to read each part of line.
	string semester = "";   // check for semester number for each course;
							// advantage is it will make it easier to keep track of repeated courses.
	int semesterNo = -1;
	int semesterNoForCGPA = -1;  // variable to make sure CGPA is of latest semester
	string courseCode; // to control which position of array to enter which grade point in.
	int* lastAttemptedSemester = new int[21]; // to make sure each entry in array is of latest
													// attempt.
	int itt = 0; // itterator to control position in line while reading file line by line.
	file.open("Students_Dataset.csv", ios::in);
	const int noOfStudents = 1779;
	const int noOfCourses = 14;
	float** gradepoint = new float* [noOfStudents + 1]; // 1 is added because students are starting from 0.
	for (int j = 0; j < noOfStudents + 1; j++) { // creadting dynamic arrays to store grade points of each student.
		gradepoint[j] = new float[noOfCourses + 1]; // an extra slot is for CGPA
	}
	int* warnings = new int[noOfStudents + 1];
	for (int i = 0; i < noOfStudents + 1; i++) {
		warnings[i] = 0;
	}
	getline(file, lineBuffer); // discarding first line that does not have any student data.
	while (!file.eof() && rollNo <= 1779) { // itterating through each line of file.
		getline(file, lineBuffer); // reading each line of the file.
		itt = 0; // resetting itterator.
		subBuffer = ""; // resetting subBuffer.
		while (lineBuffer[itt] != ',') { // reading first value(roll number/ serial number).
			subBuffer += lineBuffer[itt]; // storing roll number in subBuffer.
			itt++; //  moving itterator.
		}
		if (rollNo != stoi(subBuffer)) { // making sure same roll number is not repeated multiple times.
			rollNo = stoi(subBuffer); // if new roll number read for the first time, update it.
			semesterNoForCGPA = -1;
			//cout << rollNo << endl;
			for (int i = 0; i < 22; i++) {		// resetting lastAttemptedSemester array every time
				lastAttemptedSemester[i] = -1;  // new roll number is added.
			}
		}
		subBuffer = ""; // resetting subBuffer;
		itt++; // moving itterator to read next value
		while (lineBuffer[itt] != ',') {
			subBuffer += lineBuffer[itt]; // storing semester in subBuffer.
			itt++; // moving itterator.
		}
		itt++;
		semester = subBuffer;
		subBuffer = ""; // resetting subBuffer;
		if (semester == "Spring 2017") {
			semesterNo = 1;
		}
		else if (semester == "Fall 2017") {
			semesterNo = 2;
		}
		else if (semester == "Spring 2018") {
			semesterNo = 3;
		}
		else if (semester == "Fall 2018") {
			semesterNo = 4;
		}
		else if (semester == "Spring 2019") {
			semesterNo = 5;
		}
		else if (semester == "Unknown") {
			semesterNo = 0;
		}
		while (lineBuffer[itt] != ',') {
			subBuffer += lineBuffer[itt]; // storing course codes in subBuffer.
			itt++; // moving itterator.
		}
		itt++; // moving itterator to next position.
		courseCode = subBuffer;
		subBuffer = ""; // resetting subBuffer.
		while (lineBuffer[itt] != ',') { // ignoring course title.
			itt++; // moving itterator.
		}
		itt++; // moving itterator
		while (lineBuffer[itt] != ',') { // ignoring number of credit hours.
			itt++; // moving itterator.
		}
		itt++; // moving itterator.
		while (lineBuffer[itt] != ',') { // ignoring letter grade.
			itt++; // moving itterator.
		}
		itt++; // moving itterator.
		while (lineBuffer[itt] != ',') {
			subBuffer += lineBuffer[itt]; // storing grade points in subBuffer.
			itt++; // moving itterator.
		}
		itt++;
		if (courseCode == "MT104") {
			if (lastAttemptedSemester[0] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][0] = stof(subBuffer);
				lastAttemptedSemester[0] = semesterNo;
			}
		}
		else if (courseCode == "MT119") {
			if (lastAttemptedSemester[1] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][1] = stof(subBuffer);
				lastAttemptedSemester[1] = semesterNo;
			}
		}
		else if (courseCode == "CS118") {
			if (lastAttemptedSemester[2] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][2] = stof(subBuffer);
				lastAttemptedSemester[2] = semesterNo;
			}
		}
		else if (courseCode == "CL118") {
			if (lastAttemptedSemester[3] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][3] = stof(subBuffer);
				lastAttemptedSemester[3] = semesterNo;
			}
		}
		else if (courseCode == "EE182") {
			if (lastAttemptedSemester[4] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][4] = stof(subBuffer);
				lastAttemptedSemester[4] = semesterNo;
			}
		}
		else if (courseCode == "SL101") {
			if (lastAttemptedSemester[5] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][5] = stof(subBuffer);
				lastAttemptedSemester[5] = semesterNo;
			}
		}
		else if (courseCode == "SS101") {
			if (lastAttemptedSemester[6] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][6] = stof(subBuffer);
				lastAttemptedSemester[6] = semesterNo;
				if (rollNo == 1779) {
					break;
				}
			}
		}
		else if (courseCode == "EE227") {
			if (lastAttemptedSemester[7] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][7] = stof(subBuffer);
				lastAttemptedSemester[7] = semesterNo;
			}
		}
		else if (courseCode == "SS122") {
			if (lastAttemptedSemester[8] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][8] = stof(subBuffer);
				lastAttemptedSemester[8] = semesterNo;
			}
		}
		else if (courseCode == "MT224") {
			if (lastAttemptedSemester[9] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][9] = stof(subBuffer);
				lastAttemptedSemester[9] = semesterNo;
			}
		}
		else if (courseCode == "SS111") {
			if (lastAttemptedSemester[10] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][10] = stof(subBuffer);
				lastAttemptedSemester[10] = semesterNo;
			}
		}
		else if (courseCode == "CS217") {
			if (lastAttemptedSemester[11] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][11] = stof(subBuffer);
				lastAttemptedSemester[11] = semesterNo;
			}
		}
		else if (courseCode == "EL227") {
			if (lastAttemptedSemester[12] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][12] = stof(subBuffer);
				lastAttemptedSemester[12] = semesterNo;
			}
		}
		else if (courseCode == "CL217") {
			if (lastAttemptedSemester[13] < semesterNo) { // updating everytime a later attempt of same course is found.
				gradepoint[rollNo][13] = stof(subBuffer);
				lastAttemptedSemester[13] = semesterNo;
			}
		}
		subBuffer = "";
		while (lineBuffer[itt] != ',') { // ignoring SGPA
			itt++; // moving itterator.
		}
		itt++;
		while (lineBuffer[itt] != ',') {
			subBuffer += lineBuffer[itt]; // storing CGPA in subBuffer.
			itt++; // moving itterator.
		}
		itt++;
		if (semesterNoForCGPA < semesterNo) { // checking if CGPA of latest semester is already present.
			semesterNoForCGPA = semesterNo;
			gradepoint[rollNo][14] = stof(subBuffer); // if not present, update CGPA.
		}
		subBuffer = "";
		subBuffer += lineBuffer[itt]; // storing warnings in subBuffer.
		if (warnings[rollNo] < stoi(subBuffer)) { // checking if semester is valid and not unknown.
			warnings[rollNo] = stoi(subBuffer);
			//cout << rollNo << "   " << semesterNo << "    " << warnings[rollNo] << endl;
		}
		itt++;
	}
	file.close();
	for (int p = 0; p <= 1779; p++) {
		cout << p << "       ";
		for (int ps = 0; ps <= 14; ps++) {
			cout << gradepoint[p][ps] << " ";
		}
		cout << warnings[p] << endl;
	}
	for (int j = 0; j < noOfStudents; j++) { // deleting memory allocated on heap for those arrays.
		delete[] gradepoint[j];
	}
	delete[] gradepoint;
	delete[] lastAttemptedSemester;
	delete[] warnings;
}

// COURSE CODES CORRESPONDING TO LOCATION IN ARRAYS:
//  [0]: SS122,  [1]: SL101,  [2]: EE182,  [3]: MT119,  [4]: MT104,  [5]: CS118,  [6]: CL118,  [7]: EE117
//  [8]: SS152,  [9]: SL152, [10]: CS217, [11]: CL217, [12]: CS201, [13]: MT224, [14]: EE227, [15]: EL227
// [16]: SS150, [17]: SL150, [18]: CL117, [19]: SS111, [20]: SS113, [21]: SS101, [22]: CGPA
//void cleaningData() {
//	int rollNo = 0; // variable to store roll number and contolling the array.
//	ifstream file;  // fstream object to read data in file.
//	string lineBuffer = ""; // buffer to read each line.
//	string subBuffer = "";  // buffer to read each part of line.
//	string semester = "";   // check for semester number for each course;
//							// advantage is it will make it easier to keep track of repeated courses.
//	int semesterNo = -1;
//	int semesterNoForCGPA = -1;  // variable to make sure CGPA is of latest semester
//	string courseCode; // to control which position of array to enter which grade point in.
//	int* lastAttemptedSemester = new int[21]; // to make sure each entry in array is of latest
//													// attempt.
//	int itt = 0; // itterator to control position in line while reading file line by line.
//	file.open("Students_Dataset.csv", ios::in);
//	const int noOfStudents = 1779;
//	const int noOfCourses = 22;
//	float** gradepoint = new float* [noOfStudents + 1]; // 1 is added because students are starting from 0.
//	for (int j = 0; j < noOfStudents + 1; j++) { // creadting dynamic arrays to store grade points of each student.
//		gradepoint[j] = new float[noOfCourses + 1]; // an extra slot is for CGPA
//	}
//	int* warnings = new int[noOfStudents + 1];
//	for (int i = 0; i < noOfStudents + 1; i++) {
//		warnings[i] = 0;
//	}
//	getline(file, lineBuffer); // discarding first line that does not have any student data.
//	while (!file.eof() && rollNo <= 1779) { // itterating through each line of file.
//		getline(file, lineBuffer); // reading each line of the file.
//		itt = 0; // resetting itterator.
//		subBuffer = ""; // resetting subBuffer.
//		while (lineBuffer[itt] != ',') { // reading first value(roll number/ serial number).
//			subBuffer += lineBuffer[itt]; // storing roll number in subBuffer.
//			itt++; //  moving itterator.
//		}
//		if (rollNo != stoi(subBuffer)) { // making sure same roll number is not repeated multiple times.
//			rollNo = stoi(subBuffer); // if new roll number read for the first time, update it.
//			semesterNoForCGPA = -1;
//			//cout << rollNo << endl;
//			for (int i = 0; i < 22; i++) {		// resetting lastAttemptedSemester array every time
//				lastAttemptedSemester[i] = -1;  // new roll number is added.
//			}
//		}
//		subBuffer = ""; // resetting subBuffer;
//		itt++; // moving itterator to read next value
//		while (lineBuffer[itt] != ',') {
//			subBuffer += lineBuffer[itt]; // storing semester in subBuffer.
//			itt++; // moving itterator.
//		}
//		itt++;
//		semester = subBuffer;
//		subBuffer = ""; // resetting subBuffer;
//		if (semester == "Spring 2017") {
//			semesterNo = 1;
//		}
//		else if (semester == "Fall 2017") {
//			semesterNo = 2;
//		}
//		else if (semester == "Spring 2018") {
//			semesterNo = 3;
//		}
//		else if (semester == "Fall 2018") {
//			semesterNo = 4;
//		}
//		else if (semester == "Spring 2019") {
//			semesterNo = 5;
//		}
//		else if (semester == "Unknown") {
//			semesterNo = 0;
//		}
//		////////////////////////////////////////////////////////////////////cout << semester << endl;
//		while (lineBuffer[itt] != ',') {
//			subBuffer += lineBuffer[itt]; // storing course codes in subBuffer.
//			itt++; // moving itterator.
//		}
//		itt++; // moving itterator to next position.
//		courseCode = subBuffer;
//		subBuffer = ""; // resetting subBuffer.
//		while (lineBuffer[itt] != ',') { // ignoring course title.
//			itt++; // moving itterator.
//		}
//		itt++; // moving itterator
//		while (lineBuffer[itt] != ',') { // ignoring number of credit hours.
//			itt++; // moving itterator.
//		}
//		itt++; // moving itterator.
//		while (lineBuffer[itt] != ',') { // ignoring letter grade.
//			itt++; // moving itterator.
//		}
//		itt++; // moving itterator.
//		while (lineBuffer[itt] != ',') {
//			subBuffer += lineBuffer[itt]; // storing grade points in subBuffer.
//			itt++; // moving itterator.
//		}
//		itt++;
//		if (courseCode == "SS122") {
//			if (lastAttemptedSemester[0] < semesterNo) { // updating everytime a later attempt of same course is found.
//				gradepoint[rollNo][0] = stof(subBuffer);
//				lastAttemptedSemester[0] = semesterNo;
//			}
//		}
//		else if (courseCode == "SL101") {
//			if (lastAttemptedSemester[1] < semesterNo) { // updating everytime a later attempt of same course is found.
//				gradepoint[rollNo][1] = stof(subBuffer);
//				lastAttemptedSemester[1] = semesterNo;
//			}
//		}
//		else if (courseCode == "EE182") {
//			if (lastAttemptedSemester[2] < semesterNo) { // updating everytime a later attempt of same course is found.
//				gradepoint[rollNo][2] = stof(subBuffer);
//				lastAttemptedSemester[2] = semesterNo;
//			}
//		}
//		else if (courseCode == "MT119") {
//			if (lastAttemptedSemester[3] < semesterNo) { // updating everytime a later attempt of same course is found.
//				gradepoint[rollNo][3] = stof(subBuffer);
//				lastAttemptedSemester[3] = semesterNo;
//			}
//		}
//		else if (courseCode == "MT104") {
//			if (lastAttemptedSemester[4] < semesterNo) { // updating everytime a later attempt of same course is found.
//				gradepoint[rollNo][4] = stof(subBuffer);
//				lastAttemptedSemester[4] = semesterNo;
//			}
//		}
//		else if (courseCode == "CS118") {
//			if (lastAttemptedSemester[5] < semesterNo) { // updating everytime a later attempt of same course is found.
//				gradepoint[rollNo][5] = stof(subBuffer);
//				lastAttemptedSemester[5] = semesterNo;
//			}
//		}
//		else if (courseCode == "CL118") {
//			if (lastAttemptedSemester[6] < semesterNo) { // updating everytime a later attempt of same course is found.
//				gradepoint[rollNo][6] = stof(subBuffer);
//				lastAttemptedSemester[6] = semesterNo;
//			}
//		}
//		else if (courseCode == "EE117") {
//			if (lastAttemptedSemester[7] < semesterNo) { // updating everytime a later attempt of same course is found.
//				gradepoint[rollNo][7] = stof(subBuffer);
//				lastAttemptedSemester[7] = semesterNo;
//			}
//		}
//		else if (courseCode == "SS152") {
//			if (lastAttemptedSemester[8] < semesterNo) { // updating everytime a later attempt of same course is found.
//				gradepoint[rollNo][8] = stof(subBuffer);
//				lastAttemptedSemester[8] = semesterNo;
//				if (rollNo == 1779) {
//					break;
//				}
//			}
//		}
//		else if (courseCode == "SL152") {
//			if (lastAttemptedSemester[9] < semesterNo) { // updating everytime a later attempt of same course is found.
//				gradepoint[rollNo][9] = stof(subBuffer);
//				lastAttemptedSemester[9] = semesterNo;
//			}
//		}
//		else if (courseCode == "CS217") {
//			if (lastAttemptedSemester[10] < semesterNo) { // updating everytime a later attempt of same course is found.
//				gradepoint[rollNo][10] = stof(subBuffer);
//				lastAttemptedSemester[10] = semesterNo;
//			}
//		}
//		else if (courseCode == "CL217") {
//			if (lastAttemptedSemester[11] < semesterNo) { // updating everytime a later attempt of same course is found.
//				gradepoint[rollNo][11] = stof(subBuffer);
//				lastAttemptedSemester[11] = semesterNo;
//			}
//		}
//		else if (courseCode == "CS201") {
//			if (lastAttemptedSemester[12] < semesterNo) { // updating everytime a later attempt of same course is found.
//				gradepoint[rollNo][12] = stof(subBuffer);
//				lastAttemptedSemester[12] = semesterNo;
//			}
//		}
//		else if (courseCode == "MT224") {
//			if (lastAttemptedSemester[13] < semesterNo) { // updating everytime a later attempt of same course is found.
//				gradepoint[rollNo][13] = stof(subBuffer);
//				lastAttemptedSemester[13] = semesterNo;
//			}
//		}
//		else if (courseCode == "EE227") {
//			if (lastAttemptedSemester[14] < semesterNo) { // updating everytime a later attempt of same course is found.
//				gradepoint[rollNo][14] = stof(subBuffer);
//				lastAttemptedSemester[14] = semesterNo;
//			}
//		}
//		else if (courseCode == "EL227") {
//			if (lastAttemptedSemester[15] < semesterNo) { // updating everytime a later attempt of same course is found.
//				gradepoint[rollNo][15] = stof(subBuffer);
//				lastAttemptedSemester[15] = semesterNo;
//			}
//		}
//		else if (courseCode == "SS150") {
//			if (lastAttemptedSemester[16] < semesterNo) { // updating everytime a later attempt of same course is found.
//				gradepoint[rollNo][16] = stof(subBuffer);
//				lastAttemptedSemester[16] = semesterNo;
//			}
//		}
//		else if (courseCode == "SL150") {
//			if (lastAttemptedSemester[17] < semesterNo) { // updating everytime a later attempt of same course is found.
//				gradepoint[rollNo][17] = stof(subBuffer);
//				lastAttemptedSemester[17] = semesterNo;
//			}
//		}
//		else if (courseCode == "CL117") {
//			if (lastAttemptedSemester[18] < semesterNo) { // updating everytime a later attempt of same course is found.
//				//cout << lastAttemptedSemester[18] << endl;
//				gradepoint[rollNo][18] = stof(subBuffer);
//				lastAttemptedSemester[18] = semesterNo;
//			}
//		}
//		else if (courseCode == "SS111") {
//			if (lastAttemptedSemester[19] < semesterNo) { // updating everytime a later attempt of same course is found.
//				gradepoint[rollNo][19] = stof(subBuffer);
//				lastAttemptedSemester[19] = semesterNo;
//			}
//		}
//		else if (courseCode == "SS113") {
//			if (lastAttemptedSemester[20] < semesterNo) { // updating everytime a later attempt of same course is found.
//				gradepoint[rollNo][20] = stof(subBuffer);
//				lastAttemptedSemester[20] = semesterNo;
//			}
//		}
//		else if (courseCode == "SS101") {
//			if (lastAttemptedSemester[21] < semesterNo) { // updating everytime a later attempt of same course is found.
//				gradepoint[rollNo][21] = stof(subBuffer);
//				lastAttemptedSemester[21] = semesterNo;
//			}
//		}
//		subBuffer = "";
//		while (lineBuffer[itt] != ',') { // ignoring SGPA
//			itt++; // moving itterator.
//		}
//		itt++;
//		while (lineBuffer[itt] != ',') {
//			subBuffer += lineBuffer[itt]; // storing CGPA in subBuffer.
//			itt++; // moving itterator.
//		}
//		itt++;
//		if (semesterNoForCGPA < semesterNo) { // checking if CGPA of latest semester is already present.
//			semesterNoForCGPA = semesterNo;
//			gradepoint[rollNo][22] = stof(subBuffer); // if not present, update CGPA.
//		}
//		subBuffer = "";
//		subBuffer += lineBuffer[itt]; // storing warnings in subBuffer.
//		if (semesterNo > 0) { // checking if semester is valid and not unknown.
//			warnings[rollNo] = stoi(subBuffer);
//			cout << rollNo << "   " << semesterNo << warnings[rollNo] << endl;
//		}
//		itt++;
//	}
//	file.close();
//	for (int p = 0; p <= 1779; p++) {
//		for (int ps = 0; ps <= 22; ps++) {
//			cout << gradepoint[p][ps] << " ";
//		}
//		cout << warnings[p] << endl;
//	}
//	for (int j = 0; j < noOfStudents; j++) { // deleting memory allocated on heap for those arrays.
//		delete[] gradepoint[j];
//	}
//	delete[] gradepoint;
//	delete[] lastAttemptedSemester;
//	delete[] warnings;
//}

//void findAllCourseCodes() {
//	ifstream file;
//	int i;
//	string lineBuffer, buffer;
//	bool isPresent = false;
//	vector<string> courseCodes;
//	file.open("Students_Dataset.csv", ios::in);
//	getline(file, lineBuffer);
//	getline(file, lineBuffer);
//	i = 0;
//	while (lineBuffer[i] != ',') { // roll number
//		i++;
//	}
//	i++;
//	while (lineBuffer[i] != ',') { // semester
//		i++;
//	}
//	i++;
//	while (lineBuffer[i] != ',') { // course code
//		buffer += lineBuffer[i];
//		i++;
//	}
//	courseCodes.push_back(buffer); // for first course code
//	while (!file.eof()) {
//		getline(file, lineBuffer);
//		buffer = "";
//		i = 0;
//		while (lineBuffer[i] != ',') { // roll number
//			i++;
//		}
//		i++;
//		while (lineBuffer[i] != ',') { // semester
//			i++;
//		}
//		i++;
//		while (lineBuffer[i] != ',') { // course code
//			buffer += lineBuffer[i];
//			i++;
//		}
//		for (int j = 0; j < courseCodes.size(); j++) { // checking if course code already present
//			if (buffer == courseCodes[j]) {
//				isPresent = true;
//				break;
//			}
//		}
//		if (isPresent == false) {
//			courseCodes.push_back(buffer);
//			cout << buffer << endl;
//		}
//		isPresent = false;
//	}
//	file.close();
//}
//
//void findAllSemesters() {
//	ifstream file;
//	int i;
//	string lineBuffer, buffer;
//	bool isPresent = false;
//	vector<string> semesters;
//	file.open("Students_Dataset.csv", ios::in);
//	getline(file, lineBuffer);
//	getline(file, lineBuffer);
//	i = 0;
//	while (lineBuffer[i] != ',') { // roll number
//		i++;
//	}
//	i++;
//	while (lineBuffer[i] != ',') { // semester
//		buffer += lineBuffer[i];
//		i++;
//	}
//	i++;
//	semesters.push_back(buffer); // for first course code
//	while (!file.eof()) {
//		getline(file, lineBuffer);
//		buffer = "";
//		i = 0;
//		while (lineBuffer[i] != ',') { // roll number
//			i++;
//		}
//		i++;
//		while (lineBuffer[i] != ',') { // semester
//			buffer += lineBuffer[i];
//			i++;
//		}
//		for (int j = 0; j < semesters.size(); j++) { // checking if course code already present
//			if (buffer == semesters[j]) {
//				isPresent = true;
//				break;
//			}
//		}
//		if (isPresent == false) {
//			semesters.push_back(buffer);
//			cout << buffer << endl;
//		}
//		isPresent = false;
//	}
//	file.close();
//}