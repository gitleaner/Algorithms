/**
 Question 2
 GENERAL DIRECTIONS AND HOW TO GIVE US YOUR ANSWER:
 See the first question.
 
 DIRECTIONS FOR THIS PROBLEM:
 
 Compute the number of comparisons (as in Problem 1), always using the final element of the given array as the pivot element. Again, be sure to implement the Partition subroutine exactly as it is described in the video lectures. Recall from the lectures that, just before the main Partition subroutine, you should exchange the pivot element (i.e., the last element) with the first element.
 **/

// NumComparison :: 164123

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void QuickSort (vector<int> &numList, int lower, int upper,
                unsigned int &numComp)
{
    if (upper<=lower)
        return;
    
    int tmp=0;
    /* Always use the last element as pivot */
    tmp = numList[lower];
    numList[lower] = numList[upper];
    numList[upper] = tmp;
    
    int pivot = numList[lower];
    int i=lower;
    
    numComp = numComp + (upper-lower);
    
    for (int j=lower+1; j<=upper; j++)
    {
        if (numList[j] < pivot)
        {
            tmp = numList[i+1];
            numList[i+1] = numList[j];
            numList[j] = tmp;
            i++;
        }
    }
    numList[lower] = numList[i];
    numList[i] = pivot;
    
    QuickSort (numList, lower,  i-1, numComp);
    QuickSort (numList, i+1, upper, numComp);
}


int main()
{
    vector<int> numList;
    fstream fread ("QuickSort.txt");
    //fstream fread ("qs.txt");
    
    int num; int count = 0;
    unsigned int numComparisons =0;
    
    while (!fread.eof())
    {
        fread >> num;
        numList.push_back(num);
    }
    
    fread.close();
        
    QuickSort (numList, 0, numList.size()-1, numComparisons);
    
    for (size_t i=0; i<numList.size(); i++)
        cout << numList[i] << " ";
    cout << endl;
    
    cout << "NumComparison :: " << numComparisons << endl;
    
}
