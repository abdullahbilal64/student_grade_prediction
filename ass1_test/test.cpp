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
	string path = "C:\\Users\\abdul\\source\\repos\\Assignment1\\Assignment1\\Text.txt"; /*give path of the student dataset file in this string*/
	double expectedArray[3][17] = {
			{ 3, 3.33, 4, 4, 1.67, 3.67, 4, 4, 4, 3.67, 3, 4, 3, 4, 3.49, 0, 4 },//grades in 14 courses, cgpa, warning count, and DS grade of first 3 students (excluding those students who have "uk" grade in DS i.e student with serial no 0) 
			{ 3, 4, 4, 4, 4, 3.33, 3.67, 4, 2.33, 4, 3.33, 4, 4, 4, 3.66, 0, 4 }, //MT104, MT119,CS118,CL118,EE182,SL101,SS101,EE227,SS122,MT224,SS111,CS217,EL227,CL217,CGPA,WARNING,CS201
			{ 3.33, 2.33, 2.67, 3, 2.67, 3.33, 3.33, 3.67, 4, 3, 3, 4, 3, 3.67, 3.21, 0, 3.33 }
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
TEST(MyBrothersInDsTest, Distance_Test)
{
	double* Predicted_Array = new double[14]; //MY grades in 14 courses
	Predicted_Array[0] = 3.33;
	Predicted_Array[1] = 3;
	Predicted_Array[2] = 3.67;//
	Predicted_Array[3] = 0;//
	Predicted_Array[4] = 4;
	Predicted_Array[5] = 1;
	Predicted_Array[6] = 1.33;
	Predicted_Array[7] = 2.33;
	Predicted_Array[8] = 2;
	Predicted_Array[9] = 2.67;
	Predicted_Array[10] = 2.33;
	Predicted_Array[11] = 2;//
	Predicted_Array[12] = 3.67;
	Predicted_Array[13] = 1;//

	double expectedArray[3][2] = { { 28.335, 4 }, { 24.655, 4 }, { 24.345, 3.33 } }; //My distance from first 3 students (students with serial no 1,2,3) and DS grades of those 3 students 

	distancee = Distance(Predicted_Array, 14, Data, 1780, 17);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			EXPECT_EQ(distancee[i][j], expectedArray[i][j]);
		}
	}
}
TEST(MyBrothersInDsTest, Sorted_K_Distance_Test)
{
	tempDistanceArray = new double* [3];
	for (int i = 0; i < 3; ++i)
		tempDistanceArray[i] = new double[2];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			tempDistanceArray[i][j] = distancee[i][j];
		}
	}

	sortedKDistance = Sort_k_Dis(2, tempDistanceArray, 3, 2);
	double expectedArray[2][2] = { { 24.345, 3.33 }, { 24.655, 4 } };  //only 2 shortest sorted distances

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			EXPECT_EQ(sortedKDistance[i][j], expectedArray[i][j]);
		}

	}
}
TEST(MyBrothersInDsTest, Grade_Frequence_Test)
{
	string str = "A"; //A+ and B+ are also acceptable. if your output is A+ or B+ on this input then change the value of str accordingly and your test will be passed 
	string grade = Grade_Frequency(sortedKDistance, 2, 2);
	EXPECT_EQ(str, grade);
}
TEST(MyDSGroup, Load_Data_Test)
{
	string path = "C:\\Users\\abdul\\source\\repos\\Assignment1\\Assignment1\\Text.txt"; /*give path of the student dataset file in this string*/
	double expectedArray[3][17] = {
			{ 3, 3.33, 4, 4, 1.67, 3.67, 4, 4, 4, 3.67, 3, 4, 3, 4, 3.49, 0, 4 },//grades in 14 courses, cgpa, warning count, and DS grade of first 3 students (excluding those students who have "uk" grade in DS i.e student with serial no 0) 
			{ 3, 4, 4, 4, 4, 3.33, 3.67, 4, 2.33, 4, 3.33, 4, 4, 4, 3.66, 0, 4 }, //MT104, MT119,CS118,CL118,EE182,SL101,SS101,EE227,SS122,MT224,SS111,CS217,EL227,CL217,CGPA,WARNING,CS201
			{ 3.33, 2.33, 2.67, 3, 2.67, 3.33, 3.33, 3.67, 4, 3, 3, 4, 3, 3.67, 3.21, 0, 3.33 }
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
TEST(MyDSGroup, all_means_Test)
{
	//assumptions
	//F & W = 1 points and UK=0 points
	//If one course is repeated then consider only the highest grade in that course

	allMeans = all_means(Data, 1780, 17);
	double expectedArray[5] = { 155, 164, 137, 83,56 }; // scores/means of each student (only first 5 students excluding student with DS grade equal to "uk" i.e only students with serial no 1,2,3,8,10)
	for (int i = 0; i < 5; i++)
	{
		EXPECT_EQ(allMeans[i], expectedArray[i]);
	}

}
TEST(MyDSGroup, initia_k_Means_Test)
{
	initialClusterMeans = initia_k_Means(2, allMeans, 1780);
	double expectedArray[2] = { 155,164 };  //means of first two clusters
	for (int i = 0; i < 2; i++)
	{
		EXPECT_EQ(initialClusterMeans[i], expectedArray[i]);
	}

}
TEST(MyDSGroup, Dist_Test) //testing for only 1 iteration
{
	allMeansTemp = new double[5];
	for (int i = 0; i < 5; ++i)
		allMeansTemp[i] = allMeans[i];

	initialClusterMeansTemp = new double[2];
	for (int i = 0; i < 2; ++i)
		initialClusterMeansTemp[i] = initialClusterMeans[i];


	newClusterMeans = Dist(allMeansTemp, 5, initialClusterMeansTemp, 2);
	double expectedArray[2] = { 107.75, 164 };
	for (int i = 0; i < 2; i++)
	{
		EXPECT_EQ(newClusterMeans[i], expectedArray[i]);
	}

}
TEST(MyDSGroup, Accuracy_Test)
{
	EXPECT_FALSE(Accuracy(initialClusterMeansTemp, 2, newClusterMeans, 2));
}
TEST(MyDSGroup, Prediction_Test)
{
	string str = Prediction(70, newClusterMeans, 2);
	EXPECT_EQ(str, "F");
}
//
