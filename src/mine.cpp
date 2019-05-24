// https://www.acmicpc.net/problem/2178
// N×M크기의 배열로 표현되는 미로가 있다.
// 1	0	1	1	1	1
// 1	0	1	0	1	0
// 1	0	1	0	1	1
// 1	1	1	0	1	1
// 미로에서 1은 이동할 수 있는 칸을 나타내고, 0은 이동할 수 없는 칸을 나타낸다. 이러한 미로가 주어졌을 때, 
// (1, 1)에서 출발하여 (N, M)의 위치로 이동할 때 지나야 하는 최소의 칸 수를 구하는 프로그램을 작성하시오. 
// 한 칸에서 다른 칸으로 이동할 때, 서로 인접한 칸으로만 이동할 수 있다.
// 위의 예에서는 15칸을 지나야 (N, M)의 위치로 이동할 수 있다. 칸을 셀 때에는 시작 위치와 도착 위치도 포함한다.

// 입력
// 첫째 줄에 두 정수 N, M(2 ≤ N, M ≤ 100)이 주어진다. 다음 N개의 줄에는 M개의 정수로 미로가 주어진다. 
// 각각의 수들은 붙어서 입력으로 주어진다.

// 출력
// 첫째 줄에 지나야 하는 최소의 칸 수를 출력한다. 항상 도착위치로 이동할 수 있는 경우만 입력으로 주어진다.
//--------------------------------------------------------------------------------------------

#include<iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

int Y; //N행 개수
int X; //M열 개수
int mine[100+10][100+10]; // 미로배열

vector<int> adj[10000+10]; 

int dfs(int start)
{
    int min=1000000000000000;
    stack<int> s; 
    int visited[100+10] = {0,};

    s.push(start); // 시작 정점

    while(!s.empty()){
        int v = s.top();
        s.pop();

        if(visited[v] == 0){
            visited[v] = 1; // pop할때 방문체크
            if(mine[Y][X] == v){
                ????
            }
            //printf("%d->", v);
        }
    
        for(size_t i=0; i<adj[v].size(); ++i){
            if(visited[adj[v][i]] == 0){
                s.push(adj[v][i]);
            }
        }
    } 

    return ; 
}

int bfs(int start)
{
    queue<int> que; 
    int visited[1000+10]={0,};

    que.push(start); // 시작 정점
    visited[start] = 1; // push할 때 방문체크

    while(!que.empty()){
        int v = que.front();
        que.pop();
        if(mine[Y][X] == v){
           ????
        }
        // printf("%d->", v);

        for(size_t i=0; i<adj[v].size(); ++i){
            if(visited[adj[v][i]] == 0){ 
                que.push(adj[v][i]);
                visited[adj[v][i]] =1;
            }
        }
    }

    return ;
}

int ascending_order(int a, int b){
    return a < b; // 오름차순
}
int descending_order(int a, int b){
    return a > b; // 내림차순
}
int main()
{
    int count =1;
    scanf("%d %d", &Y, &X);
    for(int y=1; y<=Y ; ++y){
        for(int x=1; x<=X; ++x){
            scanf("%1d", &mine[y][x]);
            if(mine[y][x] !=0){ 
                mine[y][x] = count;
                count++;
            }
        }
    }

    // //debug
    // for(int y=1; y<=Y ; ++y){
    //     for(int x=1; x<=X; ++x){
    //        printf("%d ", mine[y][x]);
    //     }
    //     printf("\n");
    // }

    //make adjacent list
    for(int y=1; y<=Y; ++y){
        for(int x=1; x<=X; ++x){
            if(mine[y][x] == 1){
                if(mine[y-1][x] ==1){
                    adj
                }
                if(mine[y+1][x] ==1){

                }
                if(mine[y][x-1] ==1){

                }
                if(mine[y][x+1]==1){

                }
            }
        }
    }


}

