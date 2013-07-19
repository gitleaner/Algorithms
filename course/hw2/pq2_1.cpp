/**
 Question 1
 GENERAL DIRECTIONS:
 Download the text file here.
 
 The file contains all of the integers between 1 and 10,000 (inclusive, with no repeats) in unsorted order. The integer in the ith row of the file gives you the ith entry of an input array.
 
 Your task is to compute the total number of comparisons used to sort the given input file by QuickSort. As you know, the number of comparisons depends on which elements are chosen as pivots, so we'll ask you to explore three different pivoting rules.
 You should not count comparisons one-by-one. Rather, when there is a recursive call on a subarray of length m, you should simply add m−1 to your running total of comparisons. (This is because the pivot element is compared to each of the other m−1 elements in the subarray in this recursive call.)
 
 WARNING: The Partition subroutine can be implemented in several different ways, and different implementations can give you differing numbers of comparisons. For this problem, you should implement the Partition subroutine exactly as it is described in the video lectures (otherwise you might get the wrong answer).
 
 DIRECTIONS FOR THIS PROBLEM:
 
 For the first part of the programming assignment, you should always use the first element of the array as the pivot element.
 
 HOW TO GIVE US YOUR ANSWER:
 
 Type the numeric answer in the space provided.
 So if your answer is 1198233847, then just type 1198233847 in the space provided without any space / commas / other punctuation marks. You have 5 attempts to get the correct answer.
 (We do not require you to submit your code, so feel free to use the programming language of your choice, just type the numeric answer in the following space.)
 **/

// NumComparison :: 162085

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void QuickSort (vector<int> &numList, int lower, int upper,
                unsigned int &numComp)
{
    if (upper<=lower)
        return;
    
    int pivot = numList[lower];
    int i=lower;
    int tmp = 0;
    
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
    
    for (size_t i=0; i<numList.size(); i++)
        cout << numList[i] << " ";
    cout << endl;

        
    QuickSort (numList, 0, numList.size()-1, numComparisons);
    
    for (size_t i=0; i<numList.size(); i++)
        cout << numList[i] << " ";
    cout << endl;
    
    cout << "NumComparison :: " << numComparisons << endl;
    
}
