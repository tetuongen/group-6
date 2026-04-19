#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;

vector<int> contains;

void insert(int key)
{
    for (int i:contains)
    {
        if (i == key) return;
    }
    contains.push_back(key);
}

void erase(int key)
{
    for (int i=0;i<contains.size();i++)
    {
        if (contains[i] == key)
        {
            contains.erase(contains.begin() + i);
            return;
        }
    }
}

bool find(int key)
{
    for (int i:contains)
    {
        if (i == key) return 1;
    }
    return 0;
}

int main()
{
    // NAIVE SOLUTION
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    auto start = chrono::high_resolution_clock::now();

    // Enter the number of queries
    int q;
    cin>>q;

    while(q--)
    {
        // Enter the type of operations:
        // "Find"/ "Insert"/ "Erase" + a value
        string s;
        int val;
        cin>>s>>val;

        if (s == "Find")
        {
            if (find(val)) cout<<"Exist"; else cout<<"Non-exist";
            cout<<'\n';
        }
        else if (s == "Insert") insert(val);
        else if (s == "Erase") erase(val);

    }

    auto end = chrono::high_resolution_clock::now();

    auto duration = duration_cast<chrono::microseconds>(end-start).count();
    double ms = duration/1000.0;
    cerr<<fixed<<setprecision(5)<<ms<<" ms\n";

}
