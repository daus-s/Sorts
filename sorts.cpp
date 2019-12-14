#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

void merge(int arr[], int left, int middle, int right) //where these indices of the array so left is left index
{
		//counters
		int i;
		int j;
		int k;

		int nL = middle - left + 1; //number of elements in the left array
		int nR = right - middle; //number of elements in the right array

		int leftArr[nL];
		int rightArr[nR];


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

void mergeSort(int arr[], int left, int right) //l, r indexes to specify subarray
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

void bubbleSort(int arr[], int length)
{
	for (int i = 0; i < length;++i)
	{
		int temp = 0;
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


void selectionSort(int arr[], int n)
{
	int i, j, minI, temp;
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


void insertionSort(int arr[], int length)
{
	for (int j = 1; j < length; ++j)
	{
		int temp = arr[j];
		int k = j;
		while (k>0&&arr[k-1]>=temp)
		{
			arr[k] = arr[k-1];
			--k;
		}
		arr[k] = temp;
	}
}

void printArr(int arr[], int length)
{
		for (int i = 0; i < length; i++)
	    		cout << arr[i] << ", ";
		cout << endl;
}

string stringArr(int arr[], int length)
{
		string ret = "";
		for (int i = 0; i < length; i++)
	  {
		 		ret += arr[i];
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

		int bubbleArr[size];
		int selectionArr[size];
		int insertionArr[size];
		int mergeArr[size];

		int i = 0;
		while( !analyze.eof() && i < size)
		{
		    getline( analyze, data );
		    //process the line
				//then put it into the arrays
				bubbleArr[i] = stoi(data);
				selectionArr[i] = stoi(data);
				insertionArr[i] = stoi(data);
				mergeArr[i] = stoi(data);

				++i;
		}

		analyze.close();

		ofstream clout; //get it like cout but clout, see ten years gone LZ, all things return to how they were
		clout.open ("data.txt");

		//source Stack overflow for time calculations
		clout << "merge sort" << endl;
		milliseconds start = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
		mergeSort(mergeArr, 0, size);
		milliseconds finish = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
		clout << stringArr(mergeArr, size);
		clout << "merge runtime:" << (long)(finish - start) << endl << endl;

		clout << "selection sort" << endl;
		start = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
		selectionSort(selectionArr, size);
		finish = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
		clout << stringArr(mergeArr, size);
		clout << "selection runtime:" << (long)(finish - start) << endl << endl;


		clout << "insertion sort" << endl;
		start = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
		insertionSort(insertionArr, size);
		finish = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
		clout << stringArr(mergeArr, size);
		clout << "insertion runtime:" << (long)(finish - start) << endl << endl;


		clout << "bubble sort" << endl;
		start = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
		bubbleSort(bubbleArr, size);
		finish = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
		clout << stringArr(mergeArr, size);
		clout << "bubble runtime:" << (long)(finish - start) << endl << endl;


		clout.close();


}
