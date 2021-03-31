#include "C:\Users\abdul\source\repos\Assignment1\Assignment1\Header.h"
// Question 1
//int main() {
//	double** tempDistanceArray;
//	double** sortedKDistance;
//
//	double* Predicted_Array = new double[14]; //MY grades in 14 courses
//	Predicted_Array[0] = 3.33;
//	Predicted_Array[1] = 3;
//	Predicted_Array[2] = 3.67;
//	Predicted_Array[3] = 0;
//	Predicted_Array[4] = 4;
//	Predicted_Array[5] = 1;
//	Predicted_Array[6] = 1.33;
//	Predicted_Array[7] = 2.33;
//	Predicted_Array[8] = 2;
//	Predicted_Array[9] = 2.67;
//	Predicted_Array[10] = 2.33;
//	Predicted_Array[11] = 2;
//	Predicted_Array[12] = 3.67;
//	Predicted_Array[13] = 1;
//
//
//	double** data;
//	double** distances;
//	string path = "Students_Dataset.csv";
//	data = Load_Data(path);
//	for (int i = 0; i < 1779; i++) {
//		for (int j = 0; j < 17; j++) {
//			cout<<data[i][j]<<" , ";
//		}
//		cout << endl;
//	}
//
//	distances = Distance(Predicted_Array, 14, data, 1780, 17);
//	for (int i = 0; i < 3; i++) {
//		cout << distances[i][0] << "   " << distances[i][1] << endl;
//	}
//
//	tempDistanceArray = new double* [3];
//	for (int i = 0; i < 3; ++i)
//		tempDistanceArray[i] = new double[2];
//
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < 2; j++)
//		{
//			tempDistanceArray[i][j] = distances[i][j];
//		}
//	}
//
//	sortedKDistance = Sort_k_Dis(2, tempDistanceArray, 3, 2);
//	for (int i = 0; i < 2; i++) {
//		for (int j = 0; j < 2; j++) {
//			cout << sortedKDistance[i][j] << endl;
//		}
//	}
//
//	cout << Grade_Frequency(sortedKDistance, 2, 2) << endl;
//	for (int j = 0; j < 1779 + 1; j++) { // deleting memory allocated on heap for those arrays.
//		delete[] data[j];
//	}
//	delete[] data;	//findAllSemesters();
//	for (int j = 0; j < 1779 + 1; j++) { // deleting memory allocated on heap for those arrays.
//		delete[] AorAPlus[j];
//	}
//	delete[] AorAPlus;	//findAllSemesters();
//	return 0;
//}

// Question 2

int main() {
	double** Data;
	double* allMeans;
	double* initialClusterMeans;
	double* allMeansTemp;
	double* initialClusterMeansTemp;
	double* newClusterMeans;
	double** distancee;
	double** tempDistanceArray;
	double** sortedKDistance;

	string path = "Text.txt"; /*give path of the student dataset file in this string*/
	Data = Load_Data(path);
	/*for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 17; j++) {
			cout << Data[i][j]<< "   ";
		}
		cout << endl;
	}*/
	allMeans = all_means(Data, 1780, 17);
	initialClusterMeans = initia_k_Means(2, allMeans, 1780);
	allMeansTemp = new double[5];
	for (int i = 0; i < 5; ++i)
		allMeansTemp[i] = allMeans[i];

	initialClusterMeansTemp = new double[2];
	for (int i = 0; i < 2; ++i)
		initialClusterMeansTemp[i] = initialClusterMeans[i];

	for (int i = 0; i < 5; ++i) {
		cout<<allMeansTemp[i]<<"  ";
	}

	newClusterMeans = Dist(allMeansTemp, 5, initialClusterMeansTemp, 2);
	for (int i = 0; i < 2; i++)
	{
		cout << newClusterMeans[i];
	}
	cout << endl;
	return 0;
}
