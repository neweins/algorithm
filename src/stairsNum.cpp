// https://www.acmicpc.net/problem/10844


#include <stdio.h>
#include <algorithm>

using namespace std;

int N;
long long d[100+10][10];
long long sum;
long long solve()
{
    for(int i=1; i<=9; ++i){
         d[1][i]=1;
    }
   
    for(int i=2; i<=N; ++i){
        for(int l=0; l<=9; ++l){
            if(l==0){
                d[i][l]=d[i-1][l+1]%1000000000;
            }else if(l>=1 && l<=8){
                d[i][l]=(d[i-1][l-1] + d[i-1][l+1])%1000000000;
            }else{
                d[i][l]=d[i-1][l-1]%1000000000;
            }
        }
    }

    // for(int i=1; i<=N; ++i){
    //     for(int j=0; j<=9; ++j){
    //         printf("%lld ", d[i][j]);
    //     }
    //     printf("\n");
    // }

    for(int i=0; i<=9; ++i){
        sum =(sum+d[N][i])%1000000000;
    }

    return sum%1000000000;
    
}

int main()
{
    long long ans;
    scanf("%d", &N);

    ans = solve();
    printf("%lld\n", ans);

}