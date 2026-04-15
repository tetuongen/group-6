#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int Rand(int l, int r)
{
    return uniform_int_distribution<int>(l, r)(rng);
}

string format(int x)
{
    if (x < 10) return "0" + to_string(x);
    return to_string(x);
}

int sz[]={0,50,100,200,500,1000,2000,3000,5000,10000,20000,50000,100000,200000,300000,500000,1000000,2000000,3000000,4000000,5000000};

int main()
{
    // Compile main.cpp and maintrau.cpp to make main.exe and maintrau.exe before running checker
    for (int test=1;test<=20;test++)
    {

        string id = format(test);

        string input = id + "input" + ".txt";
        string output = id + "output" + ".txt";
        string timefile = id + "time" + ".txt";

        ofstream inp(input);

        int q = sz[test];
        inp<<q<<'\n';
        while (q--)
        {
            int type = Rand(1, 10);
            int val = Rand(1,sz[test]/2 + 5);
            if (type <= 4)
            {
                inp<<"Insert "<<val<<'\n';
            }
            else if (type == 10)
            {
                inp<<"Erase "<<val<<'\n';
            }
            else inp<<"Find "<<val<<'\n';
        }

        inp.close();


        string trau_time = id + "trau_time.txt";
        string cmd_trau = "maintrau.exe < " + input + " > outtrau.txt 2> " + trau_time;
        system(cmd_trau.c_str());

        string real_time = id + "real_time.txt";
        string cmd_real = "main.exe < " + input + " > out.txt 2> " + real_time;
        system(cmd_real.c_str());

        if (system("fc out.txt outtrau.txt > nul") != 0)
        {
            cout<<"Test "<<id<<": WRONG\n";
            return 0;
        }

        system(("copy out.txt " + output + " > nul").c_str());

        ifstream f1(trau_time);
        ifstream f2(real_time);

        string t1, t2;
        getline(f1, t1);
        getline(f2, t2);

        ofstream out(timefile);
        out<<"Naive solution: "<<t1<< '\n';
        out<<"Treap solution: "<<t2<< '\n';
        out.close();

        f1.close();
        f2.close();
        remove(trau_time.c_str());
        remove(real_time.c_str());

        cout<<"Test "<<id<<": OK\n";
    }

    remove("out.txt");
    remove("outtrau.txt");
    cout<<"DONE 20 TESTS";
}
