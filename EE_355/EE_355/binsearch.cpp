#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

#define SWAP(x, y) {int temp = x; x = y; y = temp;}

using namespace std;

void sort(int *, int);
int binsearch(int, int *, int, int);

int main(int argc, char *argv[]){
  if(argc < 3){
    cout << "Provide a filename of the data to be searched and the target value" << endl;
    return 1;
  }
  //ifstream datfile(argv[1], ios::in);
  ifstream datfile("C:\\Users\\Vincent\\Documents\\GitHub\\EELabs\\EE_355\\x64\\Debug\\unsorted_data.in", ios::in);
  if(! datfile.good() ){
    cout << "Unable to open file: " << argv[1] << endl;
    return 1;
  }

  int count = 0;
  // Count how many integers are in the file
  while(datfile.good()){
    int temp;
    datfile >> temp;
    if(datfile.good()){
      count++;
    }
  }
  // When we reach the end of the file, the EOF flag is set
  // To be able to read through the file again we need to clear that flag
  datfile.clear();
  //  We also need to set our internal position in the file back to 0
  datfile.seekg(0,ios::beg);

  // Now allocate an array to store the file data and read in the data
  int *data = new int[count];
  for(int i=0; i < count; i++){
    datfile >> data[i];
  }

  datfile.close();

  cout << "Read " << count << " integers from the data file.\n" << endl;

  // Uncomment the line below if you expect unsorted data
  sort(data, count);
  getchar();

  // Get the target value
  int target = atoi(argv[2]);

  // Call binary search
  int retval = binsearch(target,data,0,count);

  // Interpret and print the results
  if(retval == -1){
    cout << target << " does not appear in the data." << endl;
  }
  else {
    cout << target << " appears at index " << retval << " in the data." << endl;
  }

  // Deallocate the data array
  delete [] data;
  getchar();
  return 0;
}

// sorts the integer values in the 'data' array of size 'len'
void sort(int *data, int len)
{
	// recursive sort
	if (len == 0) {
		return;
	}
	// find largest element, move it to the last index
	int max = data[0];
	int maxIdx = 0;
	for (int i = 1; i < len; i++) {
		if (data[i] > max) {
			max = data[i];
			maxIdx = i;
		}
	}
	SWAP(data[maxIdx], data[len - 1]);
	sort(data, len - 1);

}

// Returns the index in the data array where target is located
//  or -1 if the target value is not in the list
int binsearch(int target, int *data, int start, int end)
{
	int range = end - start;
	if (range == 0 && data[start] != target) {
		return -1;
	}

	int midpoint = (start + end) / 2;

	// accessing arrays can be quite slow
	int val = data[midpoint];
	if (target == val) {
		return midpoint;
	}
	else if (target < val) {
		binsearch(target, data, start, midpoint); // could do midpoint - 1, but this converges faster
	}
	else {
		binsearch(target, data, midpoint + 1, end);
	}
}
