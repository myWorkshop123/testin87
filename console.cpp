#include <bits/stdc++.h>
#define REP(i, a, b) for (int i = a; i < b; i++)
#define sort(element) sort(elements.begin() , elements.end())
using namespace std;
void performDeletions(vector <int> &elements,int k)
{
    // delete  k
    elements.erase(remove(elements.begin(), elements.end() , k),elements.end() );

    // delete k+1
    elements.erase(remove(elements.begin(), elements.end() , k+1),elements.end() );

    // delete k-1
    elements.erase(remove(elements.begin(), elements.end() , k-1),elements.end() );

}

void changeOccurence(vector < pair <int , int> > &occurence , int firstVal)
{
    int left = firstVal + 1;
    int right = firstVal - 1;

    REP(i , 0 , occurence.size())
    {
        pair <int,int> check = occurence[i];
        cout<<"check.first: "<<check.first<<endl;

        if (check.first == left)
        {
            cout<<"eliminated left\n";
            occurence.erase(occurence.begin()+i);

        }

        else if (check.first == right)
        {
            cout<<"eliminated right\n";
            occurence.erase(occurence.begin()+ i);

            
        }

        else if (check.first == firstVal)
        {
            cout<<"eliminated "<<firstVal<<"\n";
            occurence.erase(occurence.begin() + i);

        }
        
    }

}

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
    cout<<"Occurence array: ";
    REP(i , 0 , occurences.size())
    {
        cout<<occurences[i].second<<" ";

    }
    cout<<"\nElements array: ";
    REP(i , 0 , elements.size())
    {

        cout<<elements[i]<<" ";
    }
    cout<<endl;

    if (maxSum.second > otherSum)
    {
        cout << "this is findMaxSum() up condition\n";



        // occurence pair of k - 1 and k + 1

        // Search for k_left and k_right pairs and then delete those pairs
    
        // perform deletion from occurences

        changeOccurence(occurences , maxSum.first);

     
       
        //todo
        cout<<"occurence after removal down ";
        REP( i , 0 , occurences.size())
        cout<<occurences[i].first<<" ";
        cout<<endl;


        // remove k // this will delete all k , k-1 , k+1 from elements
        performDeletions(elements , maxSum.first);


        answer = maxSum.second;
        return answer;
    }
    else
    {
        cout << "this is findMaxSum() down condition\n";

        // eliminate that maxsum pair from occurence and again call the function
        // Find secondMax
        pair <int , int> secondMax = occurences[0];
        int j=0;
        REP(i , 1 , occurences.size())
        {
            if (i != k && secondMax.second < occurences[i].second)
            {
                secondMax = occurences[i];
                j = i;

            }
        }

        


        pair<int, int> msl, msr;
        int k_left = secondMax.first-1 , k_right = secondMax.first+1;
        cout<<"secondMax: "<<secondMax.first<<" left: "<<k_left<<" right: "<<k_right<<'\n';
        // Search for k_left and k_right pairs and then delete those pairs
        // perform deletion from occurences

        changeOccurence(occurences  , secondMax.first);

         //todo
        cout<<"occurence after removal down ";
        REP( i , 0 , occurences.size())
        cout<<occurences[i].first<<" ";
        cout<<endl;

        // remove k // this will delete all k , k-1 , k+1 from elements
        performDeletions(elements , secondMax.first);


        answer = secondMax.second;
        return answer;




    }







}
int main()
{

    // todo
    // int n;
    // cin >> n;
    int score = 0;
    // vector<int> elements;
    // int elm;
    // REP(i, 0, n)
    // {
    //     cin >> elm;
    //     elements.push_back(elm);
    // }
    vector <int> elements {3 ,3,4,5,4};


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
        cout<<"inside score: "<<score<<"\n";


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
