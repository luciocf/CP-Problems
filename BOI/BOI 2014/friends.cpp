// BOI 2014 - Friends
// Lúcio Cardoso

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 2e6+10;
 
int n;
 
char num[maxn];

vector<char> a, b;
 
int get_pref(void)
{
	int ind = 0;
	for (int i = 0; i < n/2; i++)
	{
		if (a[i] != b[i]) break;
		ind = i+1;
	}
 
	return ind;
}
 
int get_suf(void)
{
	int ind = (n+1)/2+1;
	for (int i = (n+1)/2-1; i >= 1; i--)
	{
		if (a[i] != b[i-1]) break;
		ind = i+1;
	}
 
	return ind;
}
 
int main(void)
{
	ios::sync_with_stdio(false); cin.tie(0);
 
	cin >> n;
 
	for (int i = 1; i <= n; i++)
		cin >> num[i];
 
	if (n%2==0)
	{
		cout << "NOT POSSIBLE\n";
		return 0;
	}
 
	int add = (n+1)/2;
 
	bool ok = 1;
	for (int i = 1; i < add; i++)
		if (num[i] != num[i+add]) 
			ok = 0;
 	
	if (ok)
	{
		for (int i = 1; i < add; i++)
			cout << num[i];
		cout << "\n";
		return 0;
	}
 	
 	bool deu1 = 0, deu2 = 0;

	for (int i = 1; i <= add; i++)
		a.push_back(num[i]);
	for (int i = add+1; i <= n; i++)
		b.push_back(num[i]);
 
	int pref = get_pref(), suf = get_suf();
 
	for (int i = 1; i < add; i++)
		if (pref >= i-1 && suf <= i+1) 
			deu1 = 1;

	a.clear(), b.clear();
 
	for (int i = add; i <= n; i++)
		a.push_back(num[i]);
	for (int i = 1; i < add; i++)
		b.push_back(num[i]);
 
	pref = get_pref(), suf = get_suf();
 
	for (int i = add+1; i <= n; i++)
		if (pref >= (i-add) && suf <= (i-add)+2)
			deu2 = 1;
 
	if (!deu1 && !deu2) cout << "NOT POSSIBLE\n";
	else if (deu1 && deu2) cout << "NOT UNIQUE\n";
	else
	{
		if (deu1)
			for (int i = add+1; i <= n; i++)
				cout << num[i];
		else
			for (int i = 1; i < add; i++)
				cout << num[i];

		cout << "\n";
	}
}
