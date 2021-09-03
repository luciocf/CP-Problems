// CEOI 2014 - Question
// Lúcio Figueiredo

// ------------- ENCODER -------------

#include <bits/stdc++.h>
 
using namespace std;
 
int mask[1010];
 
bool flag = 0;
 
int encode(int n, int x, int y)
{
	if (!flag)
	{
		flag = 1;
 
		int ind = 0;
		for (int i = 0; i < (1<<12); i++)
			if (__builtin_popcount(i) == 6)
				mask[++ind] = i;
	}
 
	for (int i = 0; i <= 11; i++)
		if ((mask[x]&(1<<i)) && (!(mask[y]&(1<<i))))
			return i+1;
}

// ------------- DECODER -------------

#include <bits/stdc++.h>
 
using namespace std;
 
int mask[1010];
 
bool flag = 0;
 
int decode(int n, int q, int h)
{
	if (!flag)
	{
		flag = 1;
 
		int ind = 0;
		for (int i = 0; i < (1<<12); i++)
			if (__builtin_popcount(i) == 6)
				mask[++ind] = i;
	}
 
	if (mask[q]&(1<<(h-1))) return 1;
	return 0;
}
