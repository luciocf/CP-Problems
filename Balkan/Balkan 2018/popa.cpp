// Balkan OI 2018 - Popa
// Lúcio Cardoso

// TODO Solution

#include <bits/stdc++.h>
#include "popa.h"
 
using namespace std;
 
int solve(int n, int *l, int *r)
{
	stack<int> stk;
 
	for (int i = 0; i < n; i++)
	{
		l[i] = r[i] = -1;

		while (stk.size() && query(stk.top(), i, i, i))
		{
			l[i] = stk.top();
			stk.pop();
		}
 
		if (stk.size()) r[stk.top()] = i;
 
		stk.push(i);
	}
 
 	int root;

 	while (stk.size())
 	{
 		root = stk.top();
 		stk.pop();
 	}

 	return root;
}
