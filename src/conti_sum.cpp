// https://www.acmicpc.net/problem/1912


#include <stdio.h>
#include <algorithm>

using namespace std;

long long maxVal;
int N;
long long d[100000+10];
long long sum[100000 +10];
long long solve()
{
    sum[1] = d[1];
    maxVal = d[1];
    for(int i=2; i<=N; i++){
        // sum[i] = max(sum[i-1]+d[i], d[i]);
        if(sum[i-1] >= 0){
            sum[i] = sum[i-1]+d[i];
        }else{
            sum[i]=d[i];
        }

        maxVal = max(maxVal, sum[i]);
    }

    return maxVal;
}

int main()
{
    long long ans;
    scanf("%d", &N);

    for(int i=1; i<=N; ++i){
        scanf("%lld", &d[i]);
    }

    ans = solve();
    printf("%lld\n", ans);

}