#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;



void Merge(float arr[], int left, int mid, int right) //merge two subarrays from given array
{
    //This section creates two arrays with sizes of the first subarray and second subarray
    int n1=mid-left+1;
    int n2=right-mid;
    float X[n1], Y[n2];
    //fills the two arrays with the values from the two subarrays
    for(int i=0;i<n1;i++)
        X[i]=arr[left+i];
    for(int j=0;j<n2;j++)
        Y[j]=arr[mid+1+j];
    //Creates variables to help keep track of position in each array
    int i,j,k;
    i=0;
    j=0;
    k=left;
    //Merges the two arrays by finding the smallest value in the two arrays and inserting into the next position in the given array
    while(i<n1 && j<n2)
    {
        if(X[i]<=Y[j])
        {
            arr[k]=X[i];
            i++;
        }
        else
        {
            arr[k]=Y[j];
            j++;
        }
        k++;
    }
    //When there are no more elements in either X or Y to add, we add the remaining elements, starting with the first subarray, and then the second
    while(i<n1)
    {
        arr[k]=X[i];
        i++;
        k++;
    }
    while(j<n2)
    {
        arr[k]=Y[j];
        j++;
        k++;
    }
}

void MergeSort(float arr[], int left, int right) //performs merge sort on a given array, recursively
{
    if(left<right)
    {
        int mid = left+(right-left)/2; //finds midpoint of array or subarray
        MergeSort(arr,left,mid); //performs merge sort on first half of array or subarray
        MergeSort(arr,mid+1,right); //performs merge sort on second half of array or subarray
        Merge(arr,left,mid,right); //performs merge algorithm to conquer and combine two subarray into one array or subarray
    }
}

int Partition(float arr[], int low, int high)
{
    //Select the pivot element
    float pivot = arr[low];
    int up=low;
    int down=high;
    //performs the algorithm for the partition, explained in report
    while(up<down)
    {
        for(int j=up;j<high;j++)
        {
            if(arr[up]>pivot)
                break;
            up++;
        }
        for(int j=high;j>low;j--)
        {
            if(arr[down]<pivot)
                break;
            down--;
        }
        if(up<down)
        {
            float temp;
            temp = arr[up];
            arr[up]=arr[down];
            arr[down]=temp;
        }
    }
    float temp;
    temp = arr[low];
    arr[low]=arr[down];
    arr[down]=temp;
    return down;
}

void QuickSort(float arr[], int low, int high) //performs quick sort on a given array, recursively
{
    if(low<high)
    {
        int pivot = Partition(arr,low,high); //creates pivot point for next iteration of quick sort
        QuickSort(arr,low,pivot-1); //performs quick sort on subarray of given array
        QuickSort(arr,pivot+1,high); //performs quick sort on subarray of given array
    }
}

float GetMedian(float arr[], int n) //returns median of array given the array and the size of the array, n
{
    if(n%2 == 1) //if array is odd return the middle value
        return arr[(n/2)];
    else //if array is even return average of 2 middle values
        return ((arr[n/2])+(arr[(n/2)-1]))/2;
}

float GetRange(float arr[], int n) //returns range of array given the array and the size of the array, n
{
    return arr[n-1] - arr[0];
}

int main()
{
    int i = 0; //used as a counter
    string temp; //used to store read values from CSV file
    ifstream file;
    file.open("C:/Users/mattl/Downloads/emissions.csv");
    float powerIndustry1[25155],buildings1[25155],transport1[25155],otherIndustry1[25155],otherSectors1[25155],powerIndustry2[25155],buildings2[25155],transport2[25155],otherIndustry2[25155],otherSectors2[25155]; //creates 10 arrays of size 20000 to hold the 20000 different values for each sector
    getline(file,temp); //reads first line, which is just header line in CSV file
    while(i<25155) //will iterate enough times to go through all values
    {
        for(int i=0;i<5;i++) //reads the first 5 values and does nothing with them, as they are not needed for this project
        {
            getline(file,temp, ',');
        }
        //these lines read the values from each sector, remove the quotes around each string, convert them to floats, and store them in their respective arrays for both merge and quick sort
        getline(file,temp, ',');
        temp.erase(remove(temp.begin(),temp.end(),'\"'),temp.end());
        powerIndustry1[i]=stof(temp);
        powerIndustry2[i]=stof(temp);
        getline(file,temp, ',');
        temp.erase(remove(temp.begin(),temp.end(),'\"'),temp.end());
        buildings1[i]=stof(temp);
        buildings2[i]=stof(temp);
        getline(file,temp, ',');
        temp.erase(remove(temp.begin(),temp.end(),'\"'),temp.end());
        transport1[i]=stof(temp);
        transport2[i]=stof(temp);
        getline(file,temp, ',');
        temp.erase(remove(temp.begin(),temp.end(),'\"'),temp.end());
        otherIndustry1[i]=stof(temp);
        otherIndustry2[i]=stof(temp);
        getline(file,temp, ',');
        temp.erase(remove(temp.begin(),temp.end(),'\"'),temp.end());
        otherSectors1[i]=stof(temp);
        otherSectors2[i]=stof(temp);

        getline(file,temp); //retrieves the remainder of the line
        i++; //increments i
    }
    //TESTING MERGE SORT ON ALL 5 SECTORS
    cout << "Testing Merge sort-" << endl;
    MergeSort(powerIndustry1,0,25154);
    MergeSort(buildings1,0,25154);
    MergeSort(transport1,0,25154);
    MergeSort(otherIndustry1,0,25154);
    MergeSort(otherSectors1,0,25154);

    //Testing to see the medians and ranges they yield, and printing them out;
    cout << "Medians and ranges for the 5 sectors are as follows:" << endl;
    cout << "Power Industry: " << GetMedian(powerIndustry1,25155) << ", " << GetRange(powerIndustry1,25155) << endl;
    cout << "Buildings: " << GetMedian(buildings1,25155) << ", " << GetRange(buildings1,25155) << endl;
    cout << "Transport: " << GetMedian(transport1,25155) << ", " << GetRange(transport1,25155) << endl;
    cout << "Other Industry: " << GetMedian(otherIndustry1,25155) << ", " << GetRange(otherIndustry1,25155) << endl;
    cout << "Other Sectors: " << GetMedian(otherSectors1,25155) << ", " << GetRange(otherSectors1,25155) << endl;
    //Add a break for visual purposes
    cout << endl;

    //TESTING QUICK SORT ON ALL 5 SECTORS
    cout << "Testing Quick sort-" << endl;
    QuickSort(powerIndustry2,0,25154);
    QuickSort(buildings2,0,25154);
    QuickSort(transport2,0,25154);
    QuickSort(otherIndustry2,0,25154);
    QuickSort(otherSectors2,0,25154);

    //Testing to see the medians and ranges they yield, and printing them out;
    cout << "Medians and ranges for the 5 sectors are as follows:" << endl;
    cout << "Power Industry: " << GetMedian(powerIndustry2,25155) << ", " << GetRange(powerIndustry2,25155) << endl;
    cout << "Buildings: " << GetMedian(buildings2,25155) << ", " << GetRange(buildings2,25155) << endl;
    cout << "Transport: " << GetMedian(transport2,25155) << ", " << GetRange(transport2,25155) << endl;
    cout << "Other Industry: " << GetMedian(otherIndustry2,25155) << ", " << GetRange(otherIndustry2,25155) << endl;
    cout << "Other Sectors: " << GetMedian(otherSectors2,25155) << ", " << GetRange(otherSectors2,25155) << endl;
    return 0;
}
