// https://www.acmicpc.net/problem/14502

// 인체에 치명적인 바이러스를 연구하던 연구소에서 바이러스가 유출되었다. 다행히 바이러스는 아직 퍼지지 않았고, 바이러스의 확산을 막기 위해서 연구소에 벽을 세우려고 한다.

// 연구소는 크기가 N×M인 직사각형으로 나타낼 수 있으며, 직사각형은 1×1 크기의 정사각형으로 나누어져 있다. 연구소는 빈 칸, 벽으로 이루어져 있으며, 벽은 칸 하나를 가득 차지한다. 

// 일부 칸은 바이러스가 존재하며, 이 바이러스는 상하좌우로 인접한 빈 칸으로 모두 퍼져나갈 수 있다. 새로 세울 수 있는 벽의 개수는 3개이며, 꼭 3개를 세워야 한다.

// 예를 들어, 아래와 같이 연구소가 생긴 경우를 살펴보자.

// 2 0 0 0 1 1 0
// 0 0 1 0 1 2 0
// 0 1 1 0 1 0 0
// 0 1 0 0 0 0 0
// 0 0 0 0 0 1 1
// 0 1 0 0 0 0 0
// 0 1 0 0 0 0 0
// 이때, 0은 빈 칸, 1은 벽, 2는 바이러스가 있는 곳이다. 아무런 벽을 세우지 않는다면, 바이러스는 모든 빈 칸으로 퍼져나갈 수 있다.

// 2행 1열, 1행 2열, 4행 6열에 벽을 세운다면 지도의 모양은 아래와 같아지게 된다.

// 2 1 0 0 1 1 0
// 1 0 1 0 1 2 0
// 0 1 1 0 1 0 0
// 0 1 0 0 0 1 0
// 0 0 0 0 0 1 1
// 0 1 0 0 0 0 0
// 0 1 0 0 0 0 0
// 바이러스가 퍼진 뒤의 모습은 아래와 같아진다.

// 2 1 0 0 1 1 2
// 1 0 1 0 1 2 2
// 0 1 1 0 1 2 2
// 0 1 0 0 0 1 2
// 0 0 0 0 0 1 1
// 0 1 0 0 0 0 0
// 0 1 0 0 0 0 0
// 벽을 3개 세운 뒤, 바이러스가 퍼질 수 없는 곳을 안전 영역이라고 한다. 위의 지도에서 안전 영역의 크기는 27이다.

// 연구소의 지도가 주어졌을 때 얻을 수 있는 안전 영역 크기의 최댓값을 구하는 프로그램을 작성하시오.

// 입력
// 첫째 줄에 지도의 세로 크기 N과 가로 크기 M이 주어진다. (3 ≤ N, M ≤ 8)

// 둘째 줄부터 N개의 줄에 지도의 모양이 주어진다. 0은 빈 칸, 1은 벽, 2는 바이러스가 있는 위치이다. 2의 개수는 2보다 크거나 같고, 10보다 작거나 같은 자연수이다.

// 빈 칸의 개수는 3개 이상이다.

// 출력
// 첫째 줄에 얻을 수 있는 안전 영역의 최대 크기를 출력한다.


//생각
// 1. 벽 3개가 놓일 수 있는 모든 경우의 map을 구한다. (순차 검색으로 해도 된다. N^6, N=8, 즉 10^10 미만이므로 1초안에 가능)
// 2. 구해진 각 map별로 안전영역 크기를 구한다.(제일 쉽다.)
// 3. 각 안전영역 크기 중 최대 값을 찾는다. (제일 중에 제일 쉽다.)

#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int numOne;
int numTwo;
int map[8+2][8+2];

vector<pair<int,int>> adj[8+2][8+2];

int Y; // N : 세로
int X; // M : 가로
vector<pair<int,int>> start;

int MAX = 0;

int bfs()
{
    int count=0;
    int visit[8+2][8+2]={{0,},};

    queue<pair<int,int>> que;
    for(size_t i=0; i<start.size(); ++i){
        que.push(make_pair(start[i].first, start[i].second));
        visit[start[i].first][start[i].second] = 1;
    }

    while(!que.empty()){
        pair<int,int> v = que.front();
        que.pop();

        count++;

        for(size_t i=0; i<adj[v.first][v.second].size(); ++i){
            if(visit[adj[v.first][v.second][i].first][adj[v.first][v.second][i].second] == 0){
                visit[adj[v.first][v.second][i].first][adj[v.first][v.second][i].second] = 1;
                que.push(make_pair(adj[v.first][v.second][i].first,adj[v.first][v.second][i].second));
            }
        }
    }

    if(MAX < (Y*X) -(count+numOne+3) ){ 
        MAX = (Y*X) -(count+numOne+3);
    }
    return 0;
}

int clear_adj()
{
    for(int y=1; y<=Y; ++y){
        for(int x=1; x<=X; ++x){
            while(!adj[y][x].empty()){
                adj[y][x].clear();
            }
        }
    }

    return 0;
}

int make_adj()
{
// start point를 찾아라
// 2와 0이 배치된 정점을 간선으로 연결한다.

    for(int y=1; y<=Y; ++y){
        for(int x=1; x<=X; ++x){
            if(map[y][x] != 1){
                if(y-1>=1 && y-1<=Y){
                    if(map[y-1][x] !=1){
                        adj[y][x].push_back(make_pair(y-1, x));
                    }
                }

                if(y+1>=1 && y+1<=Y){
                    if(map[y+1][x] !=1){
                        adj[y][x].push_back(make_pair(y+1, x));
                    }
                }

                if(x-1 >=1 && x-1 <=X){
                    if(map[y][x-1] !=1){
                        adj[y][x].push_back(make_pair(y, x-1));
                    }
                }

                if(x+1 >=1 && x+1 <=X){
                    if(map[y][x+1] !=1){
                        adj[y][x].push_back(make_pair(y, x+1));
                    }
                }
            }
        }
    }

    return 0;
}

int main()
{
    scanf("%d %d", &Y, &X);

    for(int y=1; y<=Y; ++y){
        for(int x=1; x<=X; ++x){
            scanf("%1d", &map[y][x]);
            if(map[y][x] == 2){
                start.push_back(make_pair(y,x));
                numTwo++;
            }
            if(map[y][x] == 1) numOne++;
        }
    }

    //순차 탐색(N^6  ㅠㅠ)
    for(int y1=1; y1<=Y; ++y1){
        for(int x1=1; x1<=X; ++x1){
            if(map[y1][x1] == 0){
                map[y1][x1] =1;

                for(int y2=1; y2<=Y; ++y2){
                    for(int x2=1; x2<=X; ++x2){
                        if(map[y2][x2] == 0){
                            map[y2][x2] = 1;

                            for(int y3=1; y3<=Y; ++y3){
                                for(int x3=1; x3<=X; ++x3){
                                    if(map[y3][x3] == 0){
                                        map[y3][x3] =1;
                                        make_adj();
                                        bfs();
                                        clear_adj();
                                        map[y3][x3] =0;
                                    }//if
                                }
                            }
                             map[y2][x2] = 0;
                        }//if
                    }
                }
                map[y1][x1] =0;
            }//if
        }
    }
    
    printf("%d", MAX);  // 가장 큰 값 출력

    return 0;
}