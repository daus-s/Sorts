#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;



void merge(double arr[], int left, int middle, int right) //where these indices of the array so left is left index
{
		//counters
		int i;
		int j;
		int k;

		int nL = middle - left + 1; //number of elements in the left array
		int nR = right - middle; //number of elements in the right array

		double leftArr[nL];
		double rightArr[nR];


		for (i = 0; i < nL; ++i)
        leftArr[i] = arr[left + i];
    for (j = 0; j < nR; ++j)
        rightArr[j] = arr[middle + j + 1]; //beacuse otherwise double of one data peice

		i = 0; //index of left array
		j = 0; //index of right array
		k = left; //index where the soreted array will go in array

		while (i < nL && j < nR)
		{
				if (leftArr[i] < rightArr[j])
				{
						arr[k] = leftArr[i];
						++i;
				}
				else
				{
						arr[k] = rightArr[j];
						j++;
				}
				++k; //always increment so outside of conditionals
		}

		//if any remainging for left arr fills now
		while (i < nL)
		{
				arr[k] = leftArr[i];
				++i;
				++k;
		}

		//if any remainging for right arr fills now
		while (j < nR)
		{
				arr[k] = rightArr[j];
				++j;
				++k;
		}
}

void mergeSort(double arr[], int left, int right) //l, r indexes to specify subarray
{
		if (left < right)
		{
				//mergesort on both left and right side by int m
				int middle = (left + right)/2;

				//ensures there is no data overlap
				mergeSort(arr, left, middle); //l to m
				mergeSort(arr, middle+1, right); //m+1 to r

				merge(arr, left, middle, right);

		}
}

void bubbleSort(double arr[], int length)
{
	for (int i = 0; i < length;++i)
	{
		double temp = 0;
		for (int j = 0; j < length - 1;++j)
		{
			if (arr[j]>arr[j+1])
			{
				temp = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = temp;
			}
		}
	}
}


void selectionSort(double arr[], int n)
{
	int i, j, minI;
	double temp;
	for (i = 0; i < n; ++i)
	{
		minI = i;
		for (j = i+1; j<n; ++j)
		{
			if (arr[j] < arr[minI])
			{
				minI = j;
			}
			if (minI != 1)
			{
				temp = arr[i];
				arr[i] = arr[minI];
				arr[minI] = temp;
			}
		}
	}
}


void insertionSort(double arr[], int length)
{
	for (int j = 1; j < length; ++j)
	{
		double temp = arr[j];
		int k = j;
		while (k>0&&arr[k-1]>=temp)
		{
			arr[k] = arr[k-1];
			--k;
		}
		arr[k] = temp;
	}
}

void printArr(double arr[], int length)
{
		for (int i = 0; i < length; i++)
	    		cout << arr[i] << ", ";
		cout << endl;
}

string stringArr(double arr[], int length)
{
		string ret = "";
		for (int i = 0; i < length; i++)
	  {
		 		ret += to_string(arr[i]);
				ret += ",";
		}
		ret += "\n";
		return ret;
}

// int main(int argc, char** argv)
// {
// 	int arr1[] = {1,3,6,2,3,23,7};
// 	printArr(arr1, sizeof(arr1)/sizeof(arr1[0]));
// 	bubbleSort(arr1, sizeof(arr1)/sizeof(arr1[0]));
// 	printArr(arr1, sizeof(arr1)/sizeof(arr1[0]));
//
// 	int arr2[] = {2,4,8,6,4,16,0};
// 	printArr(arr2, sizeof(arr2)/sizeof(arr2[0]));
// 	selectionSort(arr2, sizeof(arr2)/sizeof(arr2[0]));
// 	printArr(arr2, sizeof(arr2)/sizeof(arr2[0]));
//
// 	int arr3[] = {10,9,8,7,6,5,4,3,2,1,5,3,3,5,576,2,23,4,65,77};
// 	printArr(arr3, sizeof(arr3)/sizeof(arr3[0]));
// 	insertionSort(arr3, sizeof(arr3)/sizeof(arr3[0]));
// 	printArr(arr3, sizeof(arr3)/sizeof(arr3[0]));
//
// 	int arr4[] = {4,6,4,2,6,8,33,5,6,9,32,2,4134,4463,46,56,45768,6,67354,6};
// 	printArr(arr4, sizeof(arr4)/sizeof(arr4[0]));
// 	mergeSort(arr4, 0, sizeof(arr4)/sizeof(arr4[0]));
// 	printArr(arr4, sizeof(arr4)/sizeof(arr4[0]));
// }

int main()
{
		ifstream analyze;
		analyze.open("data.txt", ifstream::in);
		string data;

		getline( analyze, data );
		int size = stoi(data);

		double bubbleArr[size];
		double selectionArr[size];
		double insertionArr[size];
		double mergeArr[size];

		int i = 0;
		while( !analyze.eof() && i < size)
		{
		    getline( analyze, data );
		    //process the line
				//then put it into the arrays
				bubbleArr[i] = stod(data);
				selectionArr[i] = stod(data);
				insertionArr[i] = stod(data);
				mergeArr[i] = stod(data);

				++i;
		}

		analyze.close();

		ofstream clout; //get it like cout but clout, see ten years gone LZ, all things return to how they were
		clout.open ("sorted.txt");

		//source Stack overflow for time calculations

		clout << "merge sort" << endl;
		auto start = std::chrono::high_resolution_clock::now();
		mergeSort(mergeArr, 0, size);
		auto end = std::chrono::high_resolution_clock::now();
		auto difference = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		clout << stringArr(mergeArr, size);
		clout << "merge runtime:" << difference << endl << endl;

		clout << "selection sort" << endl;
		start = std::chrono::high_resolution_clock::now();
		selectionSort(selectionArr, size);
		end = std::chrono::high_resolution_clock::now();
		clout << stringArr(mergeArr, size);
		difference = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		clout << "selection runtime:" << difference << endl << endl;


		clout << "insertion sort" << endl;
		start = std::chrono::high_resolution_clock::now();
		insertionSort(insertionArr, size);
		end = std::chrono::high_resolution_clock::now();
		clout << stringArr(mergeArr, size);
		difference = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		clout << "insertion runtime:" << difference << endl << endl;


		clout << "bubble sort" << endl;
		start = std::chrono::high_resolution_clock::now();
		bubbleSort(bubbleArr, size);
		end = std::chrono::high_resolution_clock::now();
		clout << stringArr(mergeArr, size);
		difference = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		clout << "bubble runtime:" << difference << endl << endl;


		clout.close();

		return 0;
}
