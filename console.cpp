#include <bits/stdc++.h>
#define REP(i, a, b) for (int i = a; i < b; i++)
#define sort(element) sort(elements.begin() , elements.end())
using namespace std;
int findMaxSum(vector<pair<int, int> > &occurences, vector<int> &elements)
{
    pair<int, int> maxSum;
    int answer = 0;
    maxSum = make_pair(0, occurences[0].second);

    // findMaxSum and k
    int k = 0;
    
    REP(i, 0, occurences.size())
    {
        if (maxSum.second <= occurences[i].second)
        {
            maxSum = occurences[i];
            k = i;
        }
    };
    
    // find the sum of others
    int otherSum = 0;
    REP(i, 0, occurences.size())
    {
        if ( occurences[i].second != maxSum.second)
        {
            otherSum += occurences[i].second;
        
        }
    }
    // othersum is coming out to be zero 
    cout << "OtherSum: " << otherSum << " maxSum: " << maxSum.second << '\n';

    if (maxSum.second > otherSum)
    {

        // occurence pair of k - 1 and k + 1
        pair<int, int> msl, msr;
        // k - 1
        msl = make_pair(occurences[k - 1].first, occurences[k - 1].second);
        // k+1
        msr = make_pair(occurences[k + 1].first, occurences[k + 1].second);

        // Now remove maxSum.first element , first+1 , first - 1 elements too

        // remove k
        elements.erase(remove(elements.begin(), elements.end(), maxSum.first), elements.end());
        occurences.erase(remove(occurences.begin(), occurences.end(), maxSum), occurences.end());

        // remove k-1
        elements.erase(remove(elements.begin(), elements.end(), maxSum.first - 1), elements.end());
        occurences.erase(remove(occurences.begin(), occurences.end(), msl), occurences.end());

        // remove k+1
        elements.erase(remove(elements.begin(), elements.end(), maxSum.first + 1), elements.end());
        occurences.erase(remove(occurences.begin(), occurences.end(), msr), occurences.end());
        answer = maxSum.second;
        cout << "this is findMaxSum() up condition\n";
        return answer;
    }
    else 
    {
        // eliminate that maxsum pair from occurence and again call the function
        occurences.erase(remove(occurences.begin(), occurences.end(), maxSum), occurences.end());
        answer += findMaxSum(occurences, elements);
        cout << "this is findMaxSum() down condition\n";

        return answer;

    
    }





    
    
}
int main()
{

    int n;
    cin >> n;
    int score = 0;
    vector<int> elements;
    int elm;
    REP(i, 0, n)
    {
        cin >> elm;
        elements.push_back(elm);
    }


    // sort the elements first 
    sort(elements);



    vector<pair<int, int> > occurences;

    REP(i, 0, elements.size())
    {
        pair<int, int> count_of_element;
        count_of_element = make_pair(elements[i], elements[i] * count(elements.begin(), elements.end(), elements[i]));

        //  if that pair is already present then no need to insert again
        if (count(occurences.begin() , occurences.end() , count_of_element) == 0)
        {
            occurences.push_back(count_of_element);
        }
        
    }

    int newMax = occurences[0].second;

    while (elements.size() != 0)
    {

        score += findMaxSum(occurences, elements);
    }
    cout << score;

    /*
    
    1. Find the k with max sum 
    2. If that maxsum > the other sums 
        then
        2. score += sum 
        3. eliminate k , k + 1 , k - 1 
    3. else 
    4. Consider other options  
    4. Repeat step 1

    */
}