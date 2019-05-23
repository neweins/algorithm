// https://www.acmicpc.net/problem/1260

#include<iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

int N; //정점의 개수
int M; //간선의 개수
int V; //시작 정점
vector<int> adj[10000+10]; // 그래프 https://sarah950716.tistory.com/12?category=598483

int recur_visited[1000+10]={0,};
void recursive_dfs(int v)
{
    recur_visited[v] =1;
    printf("%d ", v);
    for(size_t i=0; i<adj[v].size(); ++i){
        if(recur_visited[adj[v][i]] == 0){
            recursive_dfs(adj[v][i]);
        }
    }
}

void dfs()
{
    stack<int> s; 
    int visited[1000+10]={0,};

    s.push(V); // 시작 정점
    while(!s.empty()){
        int v = s.top();
        s.pop();

        if(visited[v] ==0){
            visited[v] =1;
            printf("%d ", v);
        }
    
        for(size_t i=0; i<adj[v].size(); ++i){
            if(visited[adj[v][i]] == 0){
                s.push(adj[v][i]);
            }
        }
    }  
}

void bfs()
{
    queue<int> que; 
    int visited[1000+10]={0,};

    que.push(V); // 시작 정점
    visited[V] = 1;
    while(!que.empty()){
        int v = que.front();
        que.pop();
        printf("%d ", v);

        for(size_t i=0; i<adj[v].size(); ++i){
            if(visited[adj[v][i]] == 0){ 
                visited[adj[v][i]] =1;
                que.push(adj[v][i]);
            }
        }
    }
}

int compare(int a, int b){
    return a < b; // 오름차순
}
int lcompare(int a, int b){
    return a > b; // 내림차순
}
int main()
{
    scanf("%d %d %d", &N, &M, &V);
    for(int i=1; i<=M ; ++i){
        int a, b;
        scanf("%d %d",&a, &b);
        adj[a].push_back(b); //인접리스트로 입력 받음  cf> 인접행렬(이차원 배열)
        adj[b].push_back(a); // 무향그래프이므로 양방향으로 입력되어야 한다.
    }

    //정렬(optional)
    for(int i=1; i<=M; ++i){
        sort(adj[i].begin(), adj[i].end(), lcompare);
    }
    // for debug
    // for(int i=1; i<=N; ++i){
    //     for(int j=0; j<adj[i].size(); ++j){
    //         printf("%d ", adj[i][j]);
    //     }
    //     printf("\n");
    // }
    dfs();
    printf("\n");

    //정렬(optional)
    for(int i=1; i<=M; ++i){
        sort(adj[i].begin(), adj[i].end(), compare);
    }
    bfs();

}

