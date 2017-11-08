#include <iostream>
#include <vector>

using namespace std;
//copies vect a into vect b starting at index iBegin and stopping at index iEnd-1
void CopyArray(vector<int *>& a, int iBegin, int iEnd, vector<int *>& b)
{
    b.clear();
    for(int k = iBegin; k < iEnd; k++) {
        b.push_back(a.at(k));
    }
    
}

// Left source half is a[ iBegin:iMiddle-1].
// Right source half is a[iMiddle:iEnd-1   ].
// Result is            b[ iBegin:iEnd-1   ].
void TopDownMerge(vector<int*>& a, int iBegin, int iMiddle, int iEnd, vector<int*>& b)
{
    int i = iBegin;
    int j = iMiddle;
    
    // While there are elements in the left or right runs...
    for (int k = iBegin; k < iEnd; k++) {
        // If left run head exists and is <= existing right run head.
        if (i < iMiddle && (j >= iEnd || (*a.at(i)) <= (*a.at(j)))) {
            b.at(k) = a.at(i);
            i++;
        } else {
            b.at(k) = a.at(j);
            j++;
        }
    }
}

// Sort the given run of vet a using vect b as a source.
// iBegin is inclusive; iEnd is exclusive (a.at(iEnd) is not in the set).
void TopDownSplitMerge(vector<int*>& b, int iBegin, int iEnd, vector<int*>& a)
{
    if(iEnd - iBegin < 2) {// if run size == 1
        return;//   consider it sorted
    }
    
    // split the run longer than 1 item into halves
    int iMiddle = (iEnd + iBegin) / 2;              // iMiddle = mid point
    // recursively sort both runs from vector a into b
    TopDownSplitMerge(a, iBegin,  iMiddle, b);  // sort the left  run
    TopDownSplitMerge(a, iMiddle,    iEnd, b);  // sort the right run
    // merge the resulting runs from vector b into a
    TopDownMerge(b, iBegin, iMiddle, iEnd, a);
}

// vector a has the items to sort; vect b is a work array.
void TopDownMergeSort(vector<int*>& a, vector<int*>& b, int n)
{
    CopyArray(a, 0, n, b);           // duplicate vect a into b
    TopDownSplitMerge(b, 0, n, a);   // sort data from b into a
}

int main(int argc, char *argv[]) {
    vector<int*> intVect;
    vector<int*> workVect;
    int a = 5;
    int b = 2;
    int c = 11;
    int d = 6;
    int e = 32;
    
    intVect.push_back(&a);
    intVect.push_back(&b);
    intVect.push_back(&c);
    intVect.push_back(&d);
    intVect.push_back(&e);
    
    cout << "intVect's size is: "<< intVect.size() << endl;
    cout << "initial vector" << endl;
    for(int* num : intVect) {
        cout << *num << endl;
    }
    cout << endl;
    cout << "sorting..." << endl;
    cout << endl;
    TopDownMergeSort(intVect, workVect, intVect.size());
    
    
    for(int* num : intVect) {
        cout << *num << endl;
    }
    
}
