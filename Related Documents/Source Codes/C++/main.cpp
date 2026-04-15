#include<iostream>
#include "treap.h"

int main()
{
    HeapTree* myTree =  new HeapTree;
    
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
            bool c = myTree->find(myTree->root, val);
            if (c) cout<<"Exist"; else cout<<"Non-exist";
            cout<<'\n';
        } 
        else if (s == "Insert") myTree->insert(val); 
        else if (s == "Erase") myTree->erase(val);

    }

    delete myTree;
}
