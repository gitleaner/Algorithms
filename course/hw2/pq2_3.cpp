/**
 Question 3
 GENERAL DIRECTIONS AND HOW TO GIVE US YOUR ANSWER:
 See the first question.
 
 DIRECTIONS FOR THIS PROBLEM:
 
 Compute the number of comparisons (as in Problem 1), using the "median-of-three" pivot rule. [The primary motivation behind this rule is to do a little bit of extra work to get much better performance on input arrays that are nearly sorted or reverse sorted.] In more detail, you should choose the pivot as follows. 
 
     Consider the first, middle, and final elements of the given array. (If the array has odd length it should be clear what the "middle" element is; for an array with even length 2k, use the kth element as the "middle" element. So for the array 4 5 6 7, the "middle" element is the second one ---- 5 and not 6!) Identify which of these three elements is the median (i.e., the one whose value is in between the other two), and use this as your pivot. As discussed in the first and second parts of this programming assignment, be sure to implement Partition exactly as described in the video lectures (including exchanging the pivot element with the first element just before the main Partition subroutine).
 
 EXAMPLE: For the input array 8 2 4 5 7 1 you would consider the first (8), middle (4), and last (1) elements; since 4 is the median of the set {1,4,8}, you would use 4 as your pivot element.
 
 SUBTLE POINT: A careful analysis would keep track of the comparisons made in identifying the median of the three candidate elements. You should NOT do this. That is, as in the previous two problems, you should simply add m−1 to your running total of comparisons every time you recurse on a subarray with length m.
 **/

// NumComparison :: 164256

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
