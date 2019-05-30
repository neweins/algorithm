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

int MIN = 10000;
int Y; //N행 개수
int X; //M열 개수
int mine[100+10][100+10]; // 미로배열
vector<pair<int, int>> adj[100+10][100+10]; // adj[행][열] = pair(행, 열)

int dfs(int y, int x)
{
    // 시간 복잡도 증가로 time out 발생할 수 있다.
    // 최단 거리 문제는 bfs로 풀자
}

int bfs(int y, int x)
{
    queue<pair<int, int>> que; 
    int visited[100+10][100+10]={0,};

    que.push(make_pair(y,x)); // 시작 정점
    visited[y][x] = 1; // push할 때 방문체크
    
    while(!que.empty()){
        pair<int,int> v = que.front();
        que.pop();
        
        if(v.first == Y && v.second == X){
            if(MIN > visited[v.first][v.second]){
                MIN = visited[v.first][v.second];
            }
        }

        for(size_t i=0; i<adj[v.first][v.second].size(); ++i){
            if(visited[adj[v.first][v.second][i].first][adj[v.first][v.second][i].second] == 0)
                que.push(make_pair(adj[v.first][v.second][i].first, adj[v.first][v.second][i].second));
                visited[adj[v.first][v.second][i].first][adj[v.first][v.second][i].second] = visited[v.first][v.second]+1;
                
        }
    }

    // for(int y=1; y<=Y; ++y){
    //     for(int x=1; x<=X; ++x){
    //         printf("%d ", visited[y][x]);
    //     }
    //     printf("\n");
    // }

    return MIN;
}

int main()
{
    scanf("%d %d", &Y, &X);
    for(int y=1; y<=Y ; ++y){
        for(int x=1; x<=X; ++x){
            scanf("%1d", &mine[y][x]);
        }
    }

    //make adjacent list
    for(int y=1; y<=Y; ++y){
        for(int x=1; x<=X; ++x){
            if(mine[y][x] != 0){
                if(y-1 >=1 && y-1<=Y && x>=1 && x<=X){
                    if(mine[y-1][x] != 0){
                        adj[y][x].push_back(make_pair(y-1,x));
                        adj[y-1][x].push_back(make_pair(y,x));
                    }
                }
                if(y+1 >=1 && y+1<=Y && x>=1 && x<=X){
                    if(mine[y+1][x] !=0){
                        adj[y][x].push_back(make_pair(y+1,x));
                        adj[y+1][x].push_back(make_pair(y,x));     
                    }
                }

                if(y >=1 && y<=Y && x-1>=1 && x-1<=X){
                    if(mine[y][x-1] !=0){
                        adj[y][x].push_back(make_pair(y,x-1));
                        adj[y][x-1].push_back(make_pair(y,x));
                    }

                }

                if(y >=1 && y <=Y && x+1>=1 && x+1<=X){
                    if(mine[y][x+1] != 0){
                        adj[y][x].push_back(make_pair(y,x+1));
                        adj[y][x+1].push_back(make_pair(y,x));
                    }

                }
            }
        }
    }

    printf("%d",bfs(1,1));
}

