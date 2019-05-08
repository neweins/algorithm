// https://www.acmicpc.net/problem/1149

#include <stdio.h>
#include <algorithm>

int N;
int h[3][1000 + 10];
int sum[3][1000 + 10];

using namespace std;

int solve()
{
    sum[0][0] = h[0][0];
    sum[1][0] = h[1][0];
    sum[2][0] = h[2][0];
    for(int i = 1; i< N; ++i){
        sum[0][i] += h[0][i] + min(sum[1][i-1], sum[2][i-1]);
        sum[1][i] += h[1][i] + min(sum[0][i-1], sum[2][i-1]);
        sum[2][i] += h[2][i] + min(sum[0][i-1], sum[1][i-1]);

        // printf("%d %d %d \n", sum[0][i], sum[1][i], sum[2][i]);
    }

    return min(min(sum[0][N-1], sum[1][N-1]), sum[2][N-1]);
}

int main()
{
    int ans;
   
    scanf("%d", &N);
    for(int i = 0; i< N; ++i){
        scanf("%d %d %d", &h[0][i], &h[1][i], &h[2][i]); //R G B
    }

    ans =solve();
    
    printf("%d\n", ans);

}