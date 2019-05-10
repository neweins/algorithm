// https://www.acmicpc.net/problem/1932

#include <stdio.h>
#include <stdint.h>
#include <algorithm>

using namespace std;

int N;
int d[510][510];
long long sum[510][510];
long long solve()
{
    sum[1][1] = d[1][1];

    for(int y=2; y<=N; ++y){
        //양쪽 끝부분 더함.
        sum[y][1] = sum[y-1][1] + d[y][1];
        sum[y][y] = sum[y-1][y-1] + d[y][y];

        //양쪽 끝부분 이외의 것들 더함.
        if(y >= 3){
            for(int x=2; x<=y-1; ++x){
                sum[y][x] = max(sum[y-1][x-1]+d[y][x], sum[y-1][x]+d[y][x]);
            }
        }
    }

    //debug
    // printf("\n");
    // for(int y=1; y<=N; ++y){
    //     for(int x=1; x<=y; ++x){
    //         printf("%lld ", sum[y][x]);
    //     }
    //     printf("\n");
    // }

    long long maxVal=sum[N][1];
    for(int x=1; x<N; ++x){
        if(maxVal < sum[N][x+1]) maxVal = sum[N][x+1];
    }
    

    return maxVal;
}

int main()
{
    long long ans;
    scanf("%d", &N);
    for(int y =1; y<=N; ++y){
       for(int x=1; x<=y;++x){
           scanf("%d", &d[y][x]);
       }
    }

    ans = solve();
    printf("%lld\n", ans);

}