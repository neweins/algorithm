//https://www.acmicpc.net/problem/2156


#include <stdio.h>
#include <algorithm>

using namespace std;

int N;
int d[10000+10];
long long sum[10000 +10];
long long solve()
{
    sum[1]=d[1];
    sum[2] = d[1] + d[2];
    for(int i=3; i <=N; i++){
        sum[i] = max(sum[i-1], max(d[i]+sum[i-2], d[i]+d[i-1]+sum[i-3]));
    }

    return sum[N];
}

int main()
{
    long long ans;
    scanf("%d", &N);

    for(int i=1; i<=N; ++i){
        scanf("%d", &d[i]);
    }

    ans = solve();
    printf("%lld\n", ans);

}