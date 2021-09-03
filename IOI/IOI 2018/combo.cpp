// IOI 2018 - Combo
// Lúcio Figueiredo

#include <bits/stdc++.h>
#include "combo.h"

using namespace std;

string guess_sequence(int N)
{
    string ans;
    string c;

    if (press("AB") >= 1)
    {
        if (press("A") == 1) ans += 'A';
        else ans += 'B';
    }
    else
    {
        if (press("X") == 1) ans += 'X';
        else ans += 'Y'; 
    }

    if (N == 1) return ans;

    if (ans[0] == 'A') c = "BXY";
    else if (ans[0] == 'B') c = "AXY";
    else if (ans[0] == 'X') c = "ABY";
    else c = "ABX";

    for (int i = 1; i < N-1; i++)
    {
        string aux = ans + c[0] + ans + c[1] + c[0] + ans + c[1] + c[1] + ans + c[1] + c[2];

        int k = press(aux);

        if (k == i) ans += c[2];
        else if (k == i+1) ans += c[0];
        else ans += c[1]; 
    }


    if (press(ans+c[0]) == N) ans += c[0];
    else
    {
        if (press(ans+c[1]) == N) ans += c[1];
        else ans += c[2];
    }

    return ans;
}
