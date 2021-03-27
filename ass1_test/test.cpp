#include "pch.h"
#include "C:\Users\abdul\source\repos\Assignment1\Assignment1\Header.h"

double** Data;
double* allMeans;
double* initialClusterMeans;
double* allMeansTemp;
double* initialClusterMeansTemp;
double* newClusterMeans;
double** distancee;
double** tempDistanceArray;
double** sortedKDistance;

TEST(MyBrothersInDsTest, Load_Data_Test)
{
	string path = "Students_Dataset.csv"; /*give path of the student dataset file in this string*/
	double expectedArray[3][17] = {
			{0,1.33,0,0,1,3,3.67,-1,3,-1,-1,-1,-1,-1,1.5,2,-1}, //grades in 14 courses, cgpa, warning count, and DS grade of first 3 students
			{3,3.33,4,4,1.67,3.67,4,4,4,3.67,3,4,3,4,3.57,0,4}, //MT104, MT119,CS118,CL118,EE182,SL101,SS101,EE227,SS122,MT224,SS111,CS217,EL227,CL217,CGPA,WARNING,CS201
			{3,4,4,4,4,3.33,3.67,4,2.33,4,3.33,4,4,4,3.57,0,4}
	};
	Data = Load_Data(path);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			EXPECT_EQ(Data[i][j], expectedArray[i][j]);
		}
	}
}
