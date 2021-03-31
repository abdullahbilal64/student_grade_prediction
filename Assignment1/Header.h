#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool** AorAPlus;

// COURSE CODES CORRESPONDING TO LOCATION IN ARRAYS:
/*
MT104: 0     MT119: 1     CS118: 2     CL118: 3     EE182: 4     SL101: 5     SS101: 6

EE227: 7     SS122: 8     MT224: 9     SS111: 10    CS217: 11    EL227: 12    CL217: 13

CS201: 16 DATA STRUCTURES 
*/

double** Load_Data(string path) {
	double secondSemester = -1;
	int rollNo = 0;
	bool APlus;
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
	if (!file.is_open()) {
		cout << "Error: File not open." << endl;
		exit(0);
	}
	const int noOfStudents = 1779;
	const int noOfCourses = 14;
	int UnkownDSStudents = 0;
	double** gradepoint = new double* [noOfStudents + 1]; // 1 is added because students are starting from 0.
	for (int j = 0; j < noOfStudents + 1; j++) { // creadting dynamic arrays to store grade points of each student.
		gradepoint[j] = new double[noOfCourses + 1 + 1 + 1 + 1]; // an extra slot is for CGPA and other for noOfWarnings and another for data structures grade.
	} // and another for differentiating between A and A+.
	AorAPlus = new bool* [noOfStudents + 1];
	for (int j = 0; j < noOfStudents + 1; j++) {
		AorAPlus[j] = new bool[noOfCourses + 1]; // creating arrays for each students grade. extra for DS grade.
		for (int k = 0; k < noOfCourses + 1; k++) {
			AorAPlus[j][k] = false; // initializing arrays with default values.
		}
	}
	getline(file, lineBuffer); // discarding first line that does not have any student data.
	while (!file.eof() && rollNo <= 1779) { // itterating through each line of file.
		getline(file, lineBuffer); // reading each line of the file.
		itt = 0; // resetting itterator.
		subBuffer = ""; // resetting subBuffer.
		APlus = false; // resetting variable.
		while (lineBuffer[itt] != ',') { // reading first value(roll number/ serial number).
			subBuffer += lineBuffer[itt]; // storing roll number in subBuffer.
			itt++; //  moving itterator.
		}
		if (rollNo != stoi(subBuffer)) { // making sure same roll number is not repeated multiple times.
			if (secondSemester != -1) {
				gradepoint[rollNo][14] = secondSemester;
			}
			rollNo = stoi(subBuffer); // if new roll number read for the first time, update it.
			semesterNoForCGPA = -1;
			secondSemester = -1;
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
			subBuffer += lineBuffer[itt];
			itt++; // moving itterator.
		}
		if (subBuffer == "A+") {
			APlus = true;
		}
		subBuffer = "";
		itt++; // moving itterator.
		while (lineBuffer[itt] != ',') {
			subBuffer += lineBuffer[itt]; // storing grade points in subBuffer.
			itt++; // moving itterator.
		}
		itt++;
		if (courseCode == "CS201") { // data structures.
			if (semesterNo == 0) {
				UnkownDSStudents++;
			}
			if (lastAttemptedSemester[16] < semesterNo) {
				if (APlus == true) {
					AorAPlus[rollNo][14] = true; // as for this array 14 index is for CS201.
				}
				gradepoint[rollNo][16] = stod(subBuffer);
				lastAttemptedSemester[16] = semesterNo;
			}
		}
		if (courseCode == "MT104") {
			if (lastAttemptedSemester[0] < semesterNo) { // updating everytime a later attempt of same course is found.
				if (APlus == true) {
					AorAPlus[rollNo][0] = true; // as for this array 14 index is for CS201.
				}
				gradepoint[rollNo][0] = stod(subBuffer);
				lastAttemptedSemester[0] = semesterNo;
			}
		}
		else if (courseCode == "MT119") {
			if (lastAttemptedSemester[1] < semesterNo) { // updating everytime a later attempt of same course is found.
				if (APlus == true) {
					AorAPlus[rollNo][1] = true; // as for this array 14 index is for CS201.
				}
				gradepoint[rollNo][1] = stod(subBuffer);
				lastAttemptedSemester[1] = semesterNo;
			}
		}
		else if (courseCode == "CS118") {
			if (lastAttemptedSemester[2] < semesterNo) { // updating everytime a later attempt of same course is found.
				if (APlus == true) {
					AorAPlus[rollNo][2] = true; // as for this array 14 index is for CS201.
				}
				gradepoint[rollNo][2] = stod(subBuffer);
				lastAttemptedSemester[2] = semesterNo;
			}
		}
		else if (courseCode == "CL118") {
			if (lastAttemptedSemester[3] < semesterNo) { // updating everytime a later attempt of same course is found.
				if (APlus == true) {
					AorAPlus[rollNo][3] = true; // as for this array 14 index is for CS201.
				}
				gradepoint[rollNo][3] = stod(subBuffer);
				lastAttemptedSemester[3] = semesterNo;
			}
		}
		else if (courseCode == "EE182") {
			if (lastAttemptedSemester[4] < semesterNo) { // updating everytime a later attempt of same course is found.
				if (APlus == true) {
					AorAPlus[rollNo][4] = true; // as for this array 14 index is for CS201.
				}
				gradepoint[rollNo][4] = stod(subBuffer);
				lastAttemptedSemester[4] = semesterNo;
			}
		}
		else if (courseCode == "SL101") {
			if (lastAttemptedSemester[5] < semesterNo) { // updating everytime a later attempt of same course is found.
				if (APlus == true) {
					AorAPlus[rollNo][5] = true; // as for this array 14 index is for CS201.
				}
				gradepoint[rollNo][5] = stod(subBuffer);
				lastAttemptedSemester[5] = semesterNo;
			}
		}
		else if (courseCode == "SS101") {
			if (lastAttemptedSemester[6] < semesterNo) { // updating everytime a later attempt of same course is found.
				if (APlus == true) {
					AorAPlus[rollNo][6] = true; // as for this array 14 index is for CS201.
				}
				gradepoint[rollNo][6] = stod(subBuffer);
				lastAttemptedSemester[6] = semesterNo;
				if (rollNo == 1779) {
					break;
				}
			}
		}
		else if (courseCode == "EE227") {
			if (lastAttemptedSemester[7] < semesterNo) { // updating everytime a later attempt of same course is found.
				if (APlus == true) {
					AorAPlus[rollNo][7] = true; // as for this array 14 index is for CS201.
				}
				gradepoint[rollNo][7] = stod(subBuffer);
				lastAttemptedSemester[7] = semesterNo;
			}
		}
		else if (courseCode == "SS122") {
			if (lastAttemptedSemester[8] < semesterNo) { // updating everytime a later attempt of same course is found.
				if (APlus == true) {
					AorAPlus[rollNo][8] = true; // as for this array 14 index is for CS201.
				}
				gradepoint[rollNo][8] = stod(subBuffer);
				lastAttemptedSemester[8] = semesterNo;
			}
		}
		else if (courseCode == "MT224") {
			if (lastAttemptedSemester[9] < semesterNo) { // updating everytime a later attempt of same course is found.
				if (APlus == true) {
					AorAPlus[rollNo][9] = true; // as for this array 14 index is for CS201.
				}
				gradepoint[rollNo][9] = stod(subBuffer);
				lastAttemptedSemester[9] = semesterNo;
			}
		}
		else if (courseCode == "SS111") {
			if (lastAttemptedSemester[10] < semesterNo) { // updating everytime a later attempt of same course is found.
				if (APlus == true) {
					AorAPlus[rollNo][10] = true; // as for this array 14 index is for CS201.
				}
				gradepoint[rollNo][10] = stod(subBuffer);
				lastAttemptedSemester[10] = semesterNo;
			}
		}
		else if (courseCode == "CS217") {
			if (lastAttemptedSemester[11] < semesterNo) { // updating everytime a later attempt of same course is found.
				if (APlus == true) {
					AorAPlus[rollNo][11] = true; // as for this array 14 index is for CS201.
				}
				gradepoint[rollNo][11] = stod(subBuffer);
				lastAttemptedSemester[11] = semesterNo;
			}
		}
		else if (courseCode == "EL227") {
			if (lastAttemptedSemester[12] < semesterNo) { // updating everytime a later attempt of same course is found.
				if (APlus == true) {
					AorAPlus[rollNo][12] = true; // as for this array 14 index is for CS201.
				}
				gradepoint[rollNo][12] = stod(subBuffer);
				lastAttemptedSemester[12] = semesterNo;
			}
		}
		else if (courseCode == "CL217") {
			if (lastAttemptedSemester[13] < semesterNo) { // updating everytime a later attempt of same course is found.
				if (APlus == true) {
					AorAPlus[rollNo][13] = true; // as for this array 14 index is for CS201.
				}
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
			secondSemester = gradepoint[rollNo][14];
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
	int passedDSStudentCount = 0;
	int all = 0;
	double** finalArray = new double*[noOfStudents + 1];
	for (int i = 0; i < noOfStudents + 1; i++) {
		finalArray[i] = new double[noOfCourses + 1 + 1 + 1 + 1];
	}
	while (all < noOfStudents + 1) {
		if (gradepoint[all][16] != -1) {
			for (int i = 0; i < noOfCourses + 1 + 1 + 1 + 1; i++) {
				finalArray[passedDSStudentCount][i] = gradepoint[all][i];
			}
			passedDSStudentCount++;
		}
		all++;
	}
	return finalArray;
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
	double temp, temp2;
	double** tempArr = new double*[distanceRows];
	for (int j = 0; j < distanceRows; j++) { // initiating arrays.
		tempArr[j] = new double[2];
	}
	double** outArr = new double*[k];
	for (int j = 0; j < k; j++) {
		outArr[j] = new double[2];
	}
	int i = 0;
	while (i < distanceRows) { // iterating through each row.
		tempArr[i][0] = distance[i][0]; // storing values in a temporary array.
		tempArr[i][1] = distance[i][1];
		i++;
	}
	for (int j = 0; j < distanceRows - 1; j++) { // bubble sort to sort temporary array
		for (int l = 0; l < distanceRows - j - 1; l++) {
			if (tempArr[l][0] > tempArr[l + 1][0]) {

				temp = tempArr[l][0];
				tempArr[l][0] = tempArr[l + 1][0];
				tempArr[l + 1][0] = temp;

				temp2 = tempArr[l][1];
				tempArr[l][1] = tempArr[l + 1][1];
				tempArr[l + 1][1] = temp2;
			}
		}
	}
	for (int j = 0; j < k; j++) { // transfering two least distances to new array that will be output.
		outArr[j][0] = tempArr[j][0];
		outArr[j][1] = tempArr[j][1];
	}
	for (int j = 0; j < distanceRows; j++) {
		delete tempArr[j];
	}
	delete[] tempArr;
	return outArr;
}

string Grade_Frequency(double** sortedKList, int sortedKListRows, int sortedKListCols) {
	double* arrOfGrades = new double[12];
	double grade;
	int largest = 0;
	for (int i = 0; i < sortedKListRows; i++) {
		grade = sortedKList[i][1];
		if (grade == 4) // A grade
			arrOfGrades[0]++;
		else if (grade == 3.67) // A- grade
			arrOfGrades[1]++;
		else if (grade == 3.33) // B+ Grade
			arrOfGrades[2]++;
		else if (grade == 3.00) // B Grade
			arrOfGrades[3]++; 
		else if (grade == 2.67) // B- Grade
			arrOfGrades[4]++;
		else if (grade == 2.33) // C+ Grade
			arrOfGrades[5]++;
		else if (grade == 2.00) // C Grade
			arrOfGrades[6]++;
		else if (grade == 1.67) // C- Grade
			arrOfGrades[7]++;
		else if (grade == 1.33) // D+ Grade
			arrOfGrades[8]++;
		else if (grade == 1.00) // D Grade
			arrOfGrades[9]++;
		else if (grade == 0.00) // F Grade
			arrOfGrades[10]++;
	}
	for (int i = 0; i < sortedKListRows; i++) {
		if (arrOfGrades[largest] < arrOfGrades[i]) {
			largest = i;
		}
	}
	if (largest == 0)
		return "A";
	else if (largest == 1)
		return "A-";
	else if (largest == 2)
		return "B+";
	else if (largest == 3)
		return "B";
	else if (largest == 4)
		return "B-";
	else if (largest == 5)
		return "C+";
	else if (largest == 6)
		return "C";
	else if (largest == 7)
		return "C-";
	else if (largest == 8)
		return "D+";
	else if (largest == 9)
		return "D";
	else
		return "F";
}



// COURSE CODES CORRESPONDING TO LOCATION IN ARRAYS:
/*
MT104: 0     MT119: 1     CS118: 2     CL118: 3     EE182: 4     SL101: 5     SS101: 6

EE227: 7     SS122: 8     MT224: 9     SS111: 10    CS217: 11    EL227: 12    CL217: 13

CS201: 16 DATA STRUCTURES
*/
double* all_means(double** Data, int dataRows, int dataCols) {  // calculate and return mean of all datapoints
	double* mean = new double[dataRows];
	for (int itt = 0; itt < 1780; itt++) {
		mean[itt] = 0;
		for (int i = 0; i < 14; i++) {
			if (Data[itt][i] == 4) // A or A+ grade
				mean[itt] += 13;
			else if (Data[itt][i] == 3.67) // A- grade
				mean[itt] += 11;
			else if (Data[itt][i] == 3.33) // B+ Grade
				mean[itt] += 10;
			else if (Data[itt][i] == 3.00) // B Grade
				mean[itt] += 9;
			else if (Data[itt][i] == 2.67) // B- Grade
				mean[itt] += 8;
			else if (Data[itt][i] == 2.33) // C+ Grade
				mean[itt] += 7;
			else if (Data[itt][i] == 2.00) // C Grade
				mean[itt] += 6;
			else if (Data[itt][i] == 1.67) // C- Grade
				mean[itt] += 5;
			else if (Data[itt][i] == 1.33) // D+ Grade
				mean[itt] += 4;
			else if (Data[itt][i] == 1.00) // D Grade
				mean[itt] += 3;
			else if (Data[itt][i] == 0.67) // D- Grade
				mean[itt] += 2;
			else if (Data[itt][i] == 0.00) // F Grade
				mean[itt] += 1;
			else if (Data[itt][i] == -1) // UK Grade
				mean[itt] += 0;
		}
	}
	return mean;
}

double* initia_k_Means(int k, double* allMeans, int allMeansSize) {
	double* initKMeans = new double[k];
	for (int i = 0; i < k; i++) {
		initKMeans[i] = allMeans[i];
	}
	return initKMeans;
}

//double* Dist(double* allMeans, int allMeansSize, double* clusterMeans, int clusterMeansSize) {
//	double smallestDistance;
//	int tally;
//	int size = allMeansSize - clusterMeansSize; // size in example is 1780 - 13 = 1767.
//	double** tempDist = new double*[size]; // to store distance from all clusters.
//	for (int i = 0; i < size; i++) {
//		tempDist[i] = new double[clusterMeansSize]; // cluster mean size in example is 13.
//	}
//	double* newDist = new double[size]; // to store smallest distances from cluster.
//	int* indexes = new int[size]; // to keep track which value belongs to which cluster.
//	double* finalMeans = new double[clusterMeansSize];
//	for (int i = 0; i < size; i++) { // new distances from each cluster stored.
//		for (int j = 0; j < clusterMeansSize; j++) {
//			tempDist[i][j] = clusterMeans[j] - allMeans[i + clusterMeansSize]; // distance of each mean from each cluster.
//		}
//	}
//	for (int i = 0; i < size; i++) {
//		smallestDistance = 100000; // imposibly large value assigned.
//		indexes[i] = -1;
//		for (int j = 0; j < clusterMeansSize; j++) {
//			//cout << tempDist[i][j] << "  " << allMeans[i] << endl;
//			if (tempDist[i][j] < 0) { // if distance is negative multiply by -1.
//				tempDist[i][j] *= -1;
//			}
//			if (smallestDistance > tempDist[i][j]) {
//				smallestDistance = tempDist[i][j]; // updating distance if smaller found.
//				indexes[i] = j; // updating with which cluster is smallest distance.
//			}
//		}
//		newDist[i] = smallestDistance; // array containing all smallest distances from each cluster.
//	}
//	for (int i = 0; i < clusterMeansSize; i++) { // for each cluster
//		tally = 0;
//		finalMeans[i] = 0;
//		for (int j = 0; j < size; j++) { // for each smallest distances calculated
//			if (indexes[j] == i) { // checking what distance corresponds to what cluster.
//				finalMeans[i] += newDist[j]; // summing all smallest distances.
//				cout << finalMeans[i] << endl;
//				tally++; // keeping count of number of distances.
//			}
//		}
//		finalMeans[i] /= tally;
//	}
//	for (int i = 0; i < size; i++) {
//		delete[] tempDist[i];
//	}
//	delete[] tempDist;
//	delete[] newDist;
//	delete[] indexes;
//	return finalMeans;
//}


double* Dist(double* allMeans, int allMeansSize, double* clusterMeans, int clusterMeansSize) {
	cout << endl;
	double* newClusterMeans = new double[clusterMeansSize];
	int size = allMeansSize - clusterMeansSize;
	int* countForClusterNo = new int[clusterMeansSize];
	int count;
	double* smallDistances = new double[size];
	double** sumsArr = new double*[size];
	for (int i = 0; i < size; i++) {
		sumsArr[i] = new double[clusterMeansSize];
	}
	double smallest;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < clusterMeansSize; j++) {
			sumsArr[i][j] = allMeans[i + clusterMeansSize] - clusterMeans[j]; // finding distance between cluster mean and student mean.
			if (sumsArr[i][j] < 0) { // if negative, multiply by -1 to make it positive.
				sumsArr[i][j] *= -1;
			}
		}
	}
	for (int j = 0; j < clusterMeansSize; j++) {
		newClusterMeans[j] = clusterMeans[j];
		countForClusterNo[j] = 1;
	}
	cout << countForClusterNo[0] << "  " << newClusterMeans[0] << endl;
	cout << countForClusterNo[1] << "  " << newClusterMeans[1] << endl;
	int j = 0;
	int index = 0;
	for (int i = 0; i < size; i++) {
		smallest = 10000;
		j = 0;
		index = -1;
		while( j < clusterMeansSize) {
			if (smallest > sumsArr[i][j]) {
				smallest = sumsArr[i][j]; // updating distance if lesser distance found.
				index++;
			}
			j++;
		}
		if (index == -1) {
			index = 0;
		}
		newClusterMeans[index] += allMeans[i + clusterMeansSize];
		countForClusterNo[index]++; // updating no. of smallest distance means of particular cluster
		cout << index << "  " << newClusterMeans[index - 1] << "   " << countForClusterNo[index - 1] << endl;
	}
	for (int j = 0; j < clusterMeansSize; j++) {
		newClusterMeans[j] /= countForClusterNo[j];
	}




	//for (int i = 0; i < size; i++) {
	//	smallest = 0;
	//	for (int j = 0; j < clusterMeansSize; j++) {
	//		cout << sumsArr[i][j] << endl;
	//		if (sumsArr[i][smallest] > sumsArr[i][j]) {
	//			smallest = j; // updating distance if lesser distance found.
	//			countForClusterNo[i] = j; // storing/updating cluster number with which it has smallest distance.
	//		}
	//	}
	//	smallDistances[i] = allMeans[smallest + clusterMeansSize];
	//	cout << endl;
	//	cout << smallest << endl;
	//	cout << endl;
	//}
	//cout << endl << endl;
	//for (int i = 0; i < clusterMeansSize; i++) {
	//	newClusterMeans[i] = 0;
	//	count = 1;
	//	for (int j = 0; j < size; j++) {
	//		if (countForClusterNo[j] == i) { // checking that cluster no. is same for all values of each mean.
	//			newClusterMeans[i] += smallDistances[j];
	//			count++;
	//		}
	//	}
	//	/*if (count == 0) {
	//		count++;
	//	}*/
	//	newClusterMeans[i] += clusterMeans[i];
	//	newClusterMeans[i] /= count;
	//	//newClusterMeans[i] += clusterMeans[i];
	//	//cout << newClusterMeans[i] << endl;
	//}
	for (int i = 0; i < size; i++) {
		delete[] sumsArr[i];
	}
	delete[] sumsArr;
	return newClusterMeans;
}

bool  Accuracy(double* oldClusterMeans, int oldClusterMeansSize, double* newClusterMeans, int newClusterMeansSize) {
	int itt;
	double result;
	if (oldClusterMeansSize <= newClusterMeansSize) {
		itt = oldClusterMeansSize;
	}
	else {
		itt = newClusterMeansSize;
	}
	for (int i = 0; i < itt; i++) {
		result = oldClusterMeans[i] - newClusterMeans[i];
		if (result < 0) {
			result *= -1;
		}
		if (result > 0.001) {
			return false;
		}
	}
	return true;;
}

string Prediction(double newData, double* meansOfClustors, int meansOfClustorsSize) {
	int smallest = 13;
	double* distances = new double[meansOfClustorsSize];
	for (int i = 0; i < meansOfClustorsSize; i++) {
		distances[i] = meansOfClustors[i] - newData; // finding distances with each cluster mean.
		if (distances[i] < 0) {
			distances[i] *= -1;
		}
	}
	for (int i = 0; i < meansOfClustorsSize; i++) {
		if (distances[smallest] > distances[i]) {
			smallest = i; // finding cluster number for smallest cluster.
		}
	}
	if (smallest == 0) {
		return "A+";
	}
	else if (smallest == 1) {
		return "A";
	}
	else if (smallest == 2) {
		return "A-";
	}
	else if (smallest == 3) {
		return "B+";
	}
	else if (smallest == 4) {
		return "B";
	}
	else if (smallest == 5) {
		return "B-";
	}
	else if (smallest == 6) {
		return "C+";
	}
	else if (smallest == 7) {
		return "C";
	}
	else if (smallest == 8) {
		return "C-";
	}
	else if (smallest == 9) {
		return "D+";
	}
	else if (smallest == 10) {
		return "D";
	}
	else if (smallest == 11) {
		return "F";
	}
	else if (smallest == 12) {
		return "F";
	}
	else if (smallest == 13) {
		return "F";
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