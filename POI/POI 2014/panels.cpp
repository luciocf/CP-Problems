// POI 2014 - Solar Panels
// Lúcio Cardoso

// Solution:

// Notice that we want to find the greatest number d such that d is the gcd(S, W), where sa <= S <= sb and
// wa <= W <= wb.

// If d is a divisor of some S and W, then ceil(sa/d) <= floor(sb/d) and the same goes for wa and wb.
// Thus, we can try this for all divisors d <= max(sqrt(sb), sqrt(wb)), and for divisors > max(sqrt(sb), sqrt(wb)),
// we can just try floor(sb/d) and floor(wb/d).

// Complexity: O(n sqrt(maxv)) 

#include <bits/stdc++.h>

using namespace std;

int sa, sb, wa, wb;

bool ok(int d)
{
    int ca = (sa/d + (sa%d ? 1 : 0));
    int cb = sb/d;

    if (ca > cb) return 0;

    ca = (wa/d + (wa%d ? 1 : 0));
    cb = wb/d;

    return (ca <= cb);
}

int main(void)
{
    int n;
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++)
    {
        scanf("%d %d %d %d", &sa, &sb, &wa, &wb);

        int ans = 0;

        for (int d = 1; d <= max(sqrt(sb), sqrt(wb))+1; d++)
        {
            if (ok(d)) ans = max(ans, d);

            if (ok(sb/d)) ans = max(ans, sb/d);
            if (ok(wb/d)) ans = max(ans, wb/d);
        }

        printf("%d\n", ans);
    }
}
