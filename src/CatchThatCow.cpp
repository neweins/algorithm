// https://www.acmicpc.net/problem/1697

// Farmer John has been informed of the location of a fugitive cow and wants to catch her immediately. 
//He starts at a point N (0 <= N <= 100,000) on a number line and the cow is at a point K (0 <= K <= 100,000) on the same number line. 
//Farmer John has two modes of transportation: walking and teleporting.

// Walking: FJ can move from any point X to the points X-1 or X+1 in a single minute
// Teleporting: FJ can move from any point X to the point 2*X in a single minute.
// If the cow, unaware of its pursuit, does not move at all, how long does it take for Farmer John to retrieve it?

// 입력
// * Line 1: Two space-separated integers: N and K

// 출력
// * Line 1: The least amount of time, in minutes, it takes for Farmer John to catch the fugitive cow.

#include<iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

int N; // start point
int K; // location of the cow

vector<int> adj[100000+10];
long long visit[100000+10];
long long MIN = INT32_MAX;

void dfs()
{
    // 최단 시간 문제이므로
    // time out 발생할 수 있음.
}

long long bfs(int s)
{
    queue<int> que; 

    que.push(s);
    if(visit[s] == 0){
        visit[s] =1; // return시 이동 횟수에서 1을 빼야함.
    }

    while(!que.empty()){
        int v = que.front();
        que.pop();

        if(v == K){
            if(MIN > visit[v]){
                MIN = visit[v];
            }
        }

        for(size_t i=0; i<adj[v].size(); ++i){
            if(visit[adj[v][i]] == 0){
                visit[adj[v][i]] =visit[v]+1;
                que.push(adj[v][i]);
            }
        }
    }

    return MIN-1; //처음 시작시 visit가 1부터 시작했으므로 이동횟수에서 1을 빼야 한다.
}

int main()
{
    scanf("%d %d", &N, &K);

    for(int i=0; i<=100000; ++i){
        if(i-1 >=0 && i-1 <=100000){
            // 무향(양방향)이다.
            adj[i].push_back(i-1);
            adj[i-1].push_back(i);
        }
        if(i+1 >=0 && i+1 <=100000){
            // 무향(양방향)이다.
            adj[i].push_back(i+1); 
            adj[i+1].push_back(i);
        }
        if(2*i >=0 && 2*i <=100000){
            // 방향이 있다.
            adj[i].push_back(2*i); 
        }
    }

    printf("%lld",bfs(N));

}

