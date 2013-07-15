/**
 Question 1
 Download the text file here. (Right click and save link as)
 This file contains all of the 100,000 integers between 1 and 100,000 (inclusive) in some order, with no integer repeated.
 
 Your task is to compute the number of inversions in the file given, where the ith row of the file indicates the ith entry of an array.
 Because of the large size of this array, you should implement the fast divide-and-conquer algorithm covered in the video lectures. The numeric answer for the given input file should be typed in the space below.
 So if your answer is 1198233847, then just type 1198233847 in the space provided without any space / commas / any other punctuation marks. You can make up to 5 attempts, and we'll use the best one for grading.
 (We do not require you to submit your code, so feel free to use any programming language you want --- just type the final numeric answer in the following space.)
 
 [TIP: before submitting, first test the correctness of your program on some small test files or your own devising. Then post your best test cases to the discussion forums to help your fellow students!]
 **/

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;

unsigned int mergelist (vector<int> &numlist, int lower, int mid, int upper)
{
    queue<int> firstQ;
    queue<int> secondQ;
    int k=lower;
    unsigned int splitInv = 0;
    
    for (int i=lower; i<=mid; i++)
        firstQ.push(numlist[i]);
    
    for (int j=mid+1; j<=upper; j++)
        secondQ.push(numlist[j]);
    
    while ( !firstQ.empty() && !secondQ.empty() )
    {
        if (firstQ.front() < secondQ.front())
        {
            numlist[k++] = firstQ.front();
            firstQ.pop();
        }
        else
        {
            splitInv += firstQ.size();
            numlist[k++] = secondQ.front();
            secondQ.pop();
        }
    }
    
    while (!firstQ.empty())
    {
        numlist[k++] = firstQ.front();
        firstQ.pop();
    }
    while (!secondQ.empty())
    {
        numlist[k++] = secondQ.front();
        secondQ.pop();
    }
    return splitInv;
}

unsigned int merge_sort (vector<int> &numlist, int lower, int upper)
{
    //cout << lower << " " << upper << endl;
    if (lower >= upper)
        return 0;
    
    int mid = (lower+upper)/2;
    unsigned int numInvA = merge_sort (numlist, lower, mid);
    unsigned int numInvB = merge_sort (numlist, mid+1, upper);
    unsigned int numInvSplit = mergelist (numlist, lower, mid, upper);
    
    return numInvA + numInvB + numInvSplit;
}

int main()
{
    vector<int> numlist;
    
    /* Read the file */
    int num =0, count =0;
    fstream fileread ("IntegerArray.txt");
    
    while (fileread.good() /*&& (count < 5)*/)
    {
        fileread >> num;
        numlist.push_back(num);
        count ++;
    }
    
    unsigned int countInv = merge_sort (numlist, 0, numlist.size()-1);
    
    /*for (size_t i=0;i<numlist.size();i++)
        cout << numlist[i] << " ";
    cout << endl << endl;*/
    
    cout << "NumElements = " << count << "  NumInversions  :: " << countInv << endl;
    
    fileread.close();
    return 1;
}


