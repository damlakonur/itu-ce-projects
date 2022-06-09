/* Serife Damla Konur
   040160433
   BLG335E Assignment 2
   17.12.2021
*/ 
#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <ctime>

using namespace std;
const int numOfVehicle = 1642;                                      // total number of vehicle
vector<struct Vehicle> minHeapArr;                                  // vector of struct represents the priority queue with binary heap
int lastIndex;                                                      // last (biggest) index of the pq
int counter;                                                        // variable for keeping the number of operations
typedef struct Vehicle                                              // The vehicle struct holds the vehicle data
{
    string vehicleId;
    string vehicleLocation;
    string vehicleDistance;
    string vehicleSpeed;
    double timeToReach;
} Vehicle;

typedef struct Request                                              // The request struct holds the request data
{
    string customerLocation;
    string customerDistance;
    int luckyNumber;
} Request;

void swapVehicle(struct Vehicle *left, struct Vehicle *right){      // swap function exchanges elements of heap while maintaining the heap property 
    Vehicle tmp = *right;
    *right = *left;
    *left = tmp;
}

int parent(int index){                                              // for 0 indexed heap returns the parent index of argument index
    return ((index-1) / 2);
}

int left(int index){                                                // for 0 indexed heap returns the left child index of argument index
    return (2*index + 1);
}

int right(int index){                                               // for 0 indexed heap returns the right child index of argument index
    return (2*index + 2);
}
// goal is to put the ith element in the correct position, key is timeToReach value
void minHeapify(int index){       
    int rightChild = right(index);                                  // right child's index
    int leftChild = left(index);                                    // left child's index
    int min = index;                                                //
    // if left child exist and left child's timeToReach(key) value is smaller than current index's timeToReach value
    if(leftChild <= lastIndex and minHeapArr[leftChild].timeToReach < minHeapArr[min].timeToReach)
         min = leftChild;                                           // then the index of the smallest element is left child's index
    else
        min = index;                                                // otherwise the min is still current index
    // if right child exist and right child's timeToReach(key) value is smaller than current index's timeToReach value
    if(rightChild <= lastIndex and minHeapArr[rightChild].timeToReach < minHeapArr[min].timeToReach)
        min = rightChild;                                           // then the index of the smallest element is right child's index
    if(min != index){                                               // if the smallest element in the heap is not in the given index
        swapVehicle(&minHeapArr[index], &minHeapArr[min]);          // swap the smallest element and given element
        minHeapify(min);                                            // heapifies again
    }
}
void buildMinHeap(){                                                // function builds a heap with given a vector of struct
    for(int i = floor(lastIndex/2); i >= 0; i--){
        minHeapify(i);                                              //if some element is violating the min heap property, minHeapify function fix this
    }
}
void insertVehicle(Vehicle newVehicle){                             // Inserts the new vehicles to the heap
    counter++;                                                      // increase operation counter
    lastIndex++;                                                    // increase the last index for insertion
    int index = lastIndex;                  
    minHeapArr[index] = newVehicle;                                 // locates the new vehicle in last index
    // Fix the min heap property for last inserted vehicle
    while(index != 0 and minHeapArr[parent(index)].timeToReach > minHeapArr[index].timeToReach){
        swapVehicle(&minHeapArr[index], &minHeapArr[parent(index)]);     
        index = parent(index);                                      // Moves the element up until index's key value >= parent's key value 
    }
}
struct Vehicle extractRoot(){                                       // pops the vehicle which has smallest timeToReach value
    counter++;                                                      // increase operation counter
    if(lastIndex == 0){                                             // if heap is empty
        cout << "heap is empty!";
        exit(1);
    }
    else if(lastIndex == 1){                                        // if heap has only one element
        lastIndex--;                                        
        return minHeapArr[0];
    }
    Vehicle root = minHeapArr[0];                                   // root is the first element of the heap        
    minHeapArr[0] = minHeapArr[lastIndex];                          // put the last element to the root
    lastIndex = lastIndex -1;                                       // decrease the last index value
    minHeapify(0);                                                  // min heapify for the new first element
    return root;                                                    // return vehicle struct
}
void decreaseKey(int index){                                        // function decrease the timeToReach value in the given index
    counter++;                                                      // increase operation counter
    minHeapArr[index].timeToReach = 0;                              // to make it the first priority vehicle
                                                                    // Fix the min heap property for new key value
    while(index != 0 and minHeapArr[parent(index)].timeToReach > minHeapArr[index].timeToReach){
        swapVehicle(&minHeapArr[index], &minHeapArr[parent(index)]);
        index = parent(index);
    }
}
void writeCallHist(vector<string> callHistory){                     // writes the call history to file
    ofstream myfile;
    myfile.open ("call_history_100K.txt");
    for(int i = 0; i < callHistory.size(); i++){
        myfile << callHistory[i] << "\n";
    }
    myfile.close();
}

int main(int argc, char* argv[]){
    int numOfOps = stoi(argv[1]);                                   // command line argument is the number of operation value
    ifstream file;
    file.open("vehicles.txt");                                      // open input file
    if (!file){
        cerr << "File cannot be opened!";
        exit(1);
    }
    string firstLine;                                               // line for taking headers
    getline(file, firstLine);
    
    string line;                                                    // line to get input strings
    lastIndex = 0;                                                  // initial length of the heap
    Vehicle vehicle;                                                // Struct for storing each distinct vehicle data 
    for(int j = 0; j < numOfVehicle; j++){                          // data streaming
        file >> line;                  
        vehicle.vehicleId = line;
        file >> line;                  
        vehicle.vehicleLocation = line;
        file >> line;                 
        vehicle.vehicleDistance = line;           
        file >> line;                  
        vehicle.vehicleSpeed = line;
        // calculate key value(estimated time)
        vehicle.timeToReach = stod(vehicle.vehicleDistance) / stod(vehicle.vehicleSpeed);
        minHeapArr.push_back(vehicle);                              // add each vehicle data to the heap
        lastIndex +=1;
    }
    lastIndex -= 1;                                                 // (last index = number of vehicle -1) for 0 indexed heap
    file.close();

    buildMinHeap();                                                 // call build heap function to maintain min heap property
    ifstream reqFile;       
    reqFile.open("requests.txt");                                   // open request file 
    if (!reqFile){
        cerr << "File cannot be opened!";
        exit(1);
    }
    getline(reqFile, firstLine);
    counter = 0;                                                    // initialize counter variable
    Request request;                                                // struct for holding each distinct request 
    vector<string> callHistory;                                     // vector for storing call history

    clock_t totalTime = 0;                                          // in order to exclude I/O times create total time variable
    while(counter < numOfOps){                                      // repeat the operations untill the given operation bound
        reqFile >> line;                  
        request.customerLocation = line;
        reqFile >> line;
        request.customerDistance = line;
        reqFile >> line;
        request.luckyNumber = stoi(line);
        clock_t time = clock();                                     // start clock to calculate execution time
        if(request.luckyNumber == 0){                               // if customer has no lucky number
            vehicle = extractRoot();                                // call the first priority vehicle
            callHistory.push_back(vehicle.vehicleId);               // to write file add the vehicle id to call history
            vehicle.vehicleDistance = request.customerDistance;     // update the called vehicle's distance
            vehicle.vehicleLocation = request.customerLocation;     // update the called vehicle's location
                                                                    // calculate the new key value of the called vehicle
            vehicle.timeToReach = stod(vehicle.vehicleDistance) / stod(vehicle.vehicleSpeed);
            insertVehicle(vehicle);                                 // finally insert the vehicle to the heap again 
        }
        else{                                                       // if the customer has lucky number 
            decreaseKey(request.luckyNumber);                       // make it first priority vehicle 
            vehicle = extractRoot();                                // then call it
            callHistory.push_back(vehicle.vehicleId);               // to write file add the vehicle id to call history
            vehicle.vehicleDistance = request.customerDistance;     // update the called vehicle's distance
            vehicle.vehicleLocation = request.customerLocation;     // update the called vehicle's location
                                                                    // calculate the new key value of the called vehicle
            vehicle.timeToReach = stod(vehicle.vehicleDistance) / stod(vehicle.vehicleSpeed);
            insertVehicle(vehicle);                                 // finally insert the vehicle to the heap again 
        }
        time = clock() - time;                                      // elapsed time for first vehicle
        totalTime += time;                                          // sum up total execution time for N operations
    }
    cout << ((float)totalTime)/CLOCKS_PER_SEC<< " seconds" << endl; // print execution time
    reqFile.close();                                                
    writeCallHist(callHistory);                                     // write to file the call history
    return 0;
}