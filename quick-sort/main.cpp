/* Serife Damla Konur
   040160433
   BLG335E Assignment 1
   25.11.2021
*/
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <math.h>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <cstdio>
#include <ctime>
#include <cstdlib>

using namespace std;
typedef struct Tweet                                // The tweet struct holds the tweet data
{
    string id;
    string dateTime;
    long unixTime;
    string artistName;
    string trackTitle;
    string countryCode;
} Tweet;

// swap function exchanges elements of vector while sorting 
void swap_tweet(struct Tweet *left, struct Tweet *right){
    Tweet tmp = *right;
    *right = *left;
    *left = tmp;
}


int caseInsComp(string str1, string str2){              // case-insensitive comparison function takes two strings
    string temp = str1;                                 // and temporarily transform them
    string pivot = str2;                                // to lower case letters from upper case letters
    transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
    transform(pivot.begin(), pivot.end(), pivot.begin(), ::tolower);
    if(temp < pivot)                                    // if the string1 is lower than pivot return 1
        return 1;
    else if (temp == pivot)                             // if the strings are same return 0
        return 0;
    else
        return -1;
}

// partition function 
int partition(vector<struct Tweet> &data, int start, int end){
    // the pivot is selected as first element of vector
    int pivotInd = start;
    // pivot <- data[start].countryCode
    for (int j = start + 1; j <= end; j++){
        // first compare country codes of instant element and pivot
        int res = caseInsComp(data[j].countryCode, data[start].countryCode);
        if (res > 0){                                   // if the element is smaller than pivot
            pivotInd++;                                 // increase the pivot indis
            swap_tweet(&data[pivotInd], &data[j]);      // then swap the elements
        }
        else if (res == 0){                             // if the country codes are same
            // then compare artist names in case-insensitive approach
            res = caseInsComp(data[j].artistName, data[start].artistName);
            if(res > 0){                                // if the element's artist name is smaller than pivot's
                pivotInd++;                             // increase the pivot indis
                swap_tweet(&data[pivotInd], &data[j]);  // then swap the elements
            }
            else if(res == 0){                          // if both country codes and artist names are same
                long pivotVal = data[start].unixTime;   // then compare unix times
                if(data[j].unixTime <= pivotVal){       // if the element's unixtime is equal or smaller than pivot's
                    pivotInd++;                         // increase pivot indis
                    swap_tweet(&data[pivotInd], &data[j]);  // then swap the elements
                }
            }
        }
    }
    // finally, swap the pivot to the right position
    swap_tweet(&data[pivotInd], &data[start]);
    // then return the pivot indis
    return pivotInd;
}
int randPartition(vector<struct Tweet> &data, int start, int end){
    int n = rand();
	// Randomly choosen index value in the range of vector size
	int randPivot = start + n%(end - start + 1);
    // then swap random element end first element of vector
    swap_tweet(&data[start], &data[randPivot]);
    // call the partititon function which selects the first element of vector as pivot
    return partition(data, start, end);
}
//quick sort algorithm with deterministic pivot selection
void detQuickSort(vector<struct Tweet> &data, int start, int end){
	if (start < end){
        // pivot value is selected as first element of vector deterministicly
        int ind = partition(data, start, end);
        // Sort the two subarrays by recursive calls
        detQuickSort(data, start, ind - 1);
        detQuickSort(data, ind + 1, end);
	}
}
//quick sort algorithm with randomized pivot selection
void randQuickSort(vector<struct Tweet> &data, int pivot, int end){
	if (pivot < end){
        // first randomly choose pivot value then 
        // according to this value divide the 
        int ind = randPartition(data, pivot, end);
        // Sort the two subvectors by recursive calls
        randQuickSort(data, pivot, ind - 1);
        randQuickSort(data, ind + 1, end);
	}

}

//if the data is initialized and the vector is not empty, than it can sort
void quickSort(vector<struct Tweet> &data, string pivotSelection, int start, int end){
    string mode1 = "deterministic";
    string mode2 = "randomized";

    if(mode1 == pivotSelection)
        detQuickSort(data, 0, end);
    else if(mode2 == pivotSelection)
        randQuickSort(data, 0, end);
    else
        cout << "The pivot selection mode must be 'randomized' or 'deterministic'.";   
}

int main(int argc, char **argv){
	
	// Take command line arguments
	long numOfTweet = stol(argv[1], nullptr, 10);
    string pivotSelection = argv[2];
    string inFileName = argv[3];
    string oFileName = argv[4];

    ifstream file;
    file.open(inFileName);
    if (!file){
        cerr << "File cannot be opened!";
        exit(1);
    }
    string firstLine;                               // line for taking headers
    getline(file, firstLine);
    
    string line;                                    // line to get input strings
    vector<struct Tweet> data(numOfTweet);          // Vector of struct for storing all data 
    Tweet tweet;                                    // Struct for storing each distinct twitter data 
    // data streaming
    for(int j = 0; j < numOfTweet; j++){
        getline(file, line, '\t');                  // get tweet_id(int)
        tweet.id = line;
        getline(file, line, '\t');                  // get tweet_datetime(string)
        tweet.dateTime = line;
        getline(file, line, '\t');                  // get tweet_unixtime(long)
        tweet.unixTime = stol(line, nullptr, 10);   // conversion string to long int
        getline(file, line, '\t');                  // get artistName(string)
        tweet.artistName = line;
        getline(file, line, '\t');                  // get trackTitle(string)
        tweet.trackTitle = line;
        getline(file, line, '\n');                  // get countryCode(string)
        tweet.countryCode = line;
        data[j] = tweet;                            // add each tweet data to vector
    }
    file.close();
    

	// start clock to calculate execution time
	clock_t time = clock();
    // initial call
	quickSort(data, pivotSelection, 0, data.size()-1);
 
	// elapsed time
	time = clock() - time;
	cout << "Quick sort algorithm takes " << ((float)time)/CLOCKS_PER_SEC<< " seconds" << endl;
    // writing to file
    ofstream myfile;
    myfile.open (oFileName.c_str());
    myfile << "tweet_id\ttweet_datetime\ttweet_unixtime\tartist_name\ttrack_title\tcountry\n";
    for (int i = 0; i < numOfTweet; i++){
        myfile << data[i].id << "\t";
        myfile << data[i].dateTime << "\t";
        myfile << data[i].unixTime<< "\t";
        myfile << data[i].artistName<< "\t";
        myfile << data[i].trackTitle << "\t";
        myfile << data[i].countryCode << "\n";
    }
    myfile.close();
    return 0;
}
