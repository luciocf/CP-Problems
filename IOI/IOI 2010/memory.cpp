// IOI 2010 - Memory
// Lúcio Cardoso

#include <bits/stdc++.h>
#include "grader.h"
#include "memory.h"
 
using namespace std;
 
map<char, int> pos1, pos2;
 
void play()
{
	for (int i = 1; i <= 49; i += 2)
	{
		char a = faceup(i);
		char b = faceup(i+1);
 
		if (pos1[a] == 0) pos1[a] = i;
		else pos2[a] = i;
 
		if (pos1[b] == 0) pos1[b] = i+1;
		else pos2[b] = i+1;
	}
 
	for (int i = (int)'A'; i <= (int)'Y'; i++)
	{
		faceup(pos1[(char)i]);
		faceup(pos2[(char)i]);
	}
}
