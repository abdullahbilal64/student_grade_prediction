#include "C:\Users\abdul\source\repos\Assignment1\Assignment1\Header.h"

int main() {
	double* Predicted_Array = new double[14]; //MY grades in 14 courses
	Predicted_Array[0] = 3.33;
	Predicted_Array[1] = 3;
	Predicted_Array[2] = 3.67;
	Predicted_Array[3] = 0;
	Predicted_Array[4] = 4;
	Predicted_Array[5] = 1;
	Predicted_Array[6] = 1.33;
	Predicted_Array[7] = 2.33;
	Predicted_Array[8] = 2;
	Predicted_Array[9] = 2.67;
	Predicted_Array[10] = 2.33;
	Predicted_Array[11] = 2;
	Predicted_Array[12] = 3.67;
	Predicted_Array[13] = 1;


	double** data;
	double** distances;
	string path = "Students_Dataset.csv";
	data = Load_Data(path);
	/*for (int i = 0; i < 1779; i++) {
		for (int j = 0; j < 17; j++) {
			cout<<data[i][j]<<" , ";
		}
		cout << endl;
	}*/

	distances = Distance(Predicted_Array, 14, data, 1780, 17);
	for (int i = 0; i < 3; i++) {
		cout << distances[i][0] << "   " << distances[i][1] << endl;
	}
	for (int j = 0; j < 1779; j++) { // deleting memory allocated on heap for those arrays.
		delete[] data[j];
	}
	delete[] data;	//findAllSemesters();
	return 0;
}