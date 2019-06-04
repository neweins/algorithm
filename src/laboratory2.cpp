// https://www.acmicpc.net/problem/14502
#include <stdio.h>
#include <queue>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int numOne;
int map[8+2][8+2];

list<pair<int,int>> adj[8+2][8+2];

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

        for(list<pair<int,int>>::iterator it = adj[v.first][v.second].begin(); it !=adj[v.first][v.second].end(); ++it ){
            if(visit[(*it).first][(*it).second] == 0){
                visit[(*it).first][(*it).second] = 1;
                que.push(make_pair((*it).first,(*it).second));
            }
        }
    }

    if(MAX < (Y*X) -(count+numOne+3) ){ 
        MAX = (Y*X) -(count+numOne+3);
    }
    return 0;
}

int del_adj(int y, int x)
{
    if(!adj[y][x].empty()) adj[y][x].clear(); // 간선 제거(벽을 세움)

    //인접 좌표에서 벽 좌표 제거
    if(y-1 >=1 && y-1 <=Y){
        for(list<pair<int,int>>::iterator it=adj[y-1][x].begin(); it !=adj[y-1][x].end(); ++it){
            if( (*it).first == y && (*it).second ==x ){
                it = adj[y-1][x].erase(it);
            }
        }
    }

    if(y+1 >=1 && y+1 <=Y){
        for(list<pair<int,int>>::iterator it=adj[y+1][x].begin(); it != adj[y+1][x].end(); ++it){
            if((*it).first == y && (*it).second == x){
                it = adj[y+1][x].erase(it);
            }
        }
    }

    if(x-1 >=1 && x-1 <=X){
        for(list<pair<int,int>>::iterator it = adj[y][x-1].begin(); it != adj[y][x-1].end(); ++it){
            if((*it).first == y && (*it).second == x){
                it = adj[y][x-1].erase(it);
            }
        }
    }

    if(x+1 >=1 && x+1 <=X){
        for(list<pair<int,int>>::iterator it = adj[y][x+1].begin(); it != adj[y][x+1].end(); ++it){
            if((*it).first == y && (*it).second == x){
                it = adj[y][x+1].erase(it);
            }
        }
    }

    return 0;
}
int add_adj(int y, int x)
{
    
    if(map[y][x] != 1){
        if(y-1>=1 && y-1<=Y){
            if(map[y-1][x] !=1){
                adj[y][x].push_back(make_pair(y-1, x));
                 adj[y-1][x].push_back(make_pair(y, x));
            }
        }

        if(y+1>=1 && y+1<=Y){
            if(map[y+1][x] !=1){
                adj[y][x].push_back(make_pair(y+1, x));
                adj[y+1][x].push_back(make_pair(y, x));
            }
        }

        if(x-1 >=1 && x-1 <=X){
            if(map[y][x-1] !=1){
                adj[y][x].push_back(make_pair(y, x-1));
                adj[y][x-1].push_back(make_pair(y, x));
            }
        }

        if(x+1 >=1 && x+1 <=X){
            if(map[y][x+1] !=1){
                adj[y][x].push_back(make_pair(y, x+1));
                adj[y][x+1].push_back(make_pair(y, x));
            }
        }
    }

    return 0;
}

int make_adj()
{
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

            // start point를 찾아라
            if(map[y][x] == 2){
                start.push_back(make_pair(y,x));
            }

            // 벽의 갯수
            if(map[y][x] == 1) numOne++;
        }
    }

    make_adj();

    //순차 탐색(N^6  ㅠㅠ)
    for(int y1=1; y1<=Y; ++y1){
        for(int x1=1; x1<=X; ++x1){
            if(map[y1][x1] == 0){
                map[y1][x1] =1;
                del_adj(y1,x1);// 벽 추가

                for(int y2=1; y2<=Y; ++y2){
                    for(int x2=1; x2<=X; ++x2){
                        if(map[y2][x2] == 0){
                            map[y2][x2] = 1;
                            del_adj(y2, x2);// 벽 추가

                            for(int y3=1; y3<=Y; ++y3){
                                for(int x3=1; x3<=X; ++x3){
                                    if(map[y3][x3] == 0){
                                        map[y3][x3] =1;
                                        del_adj(y3, x3);// 벽 추가
                                        bfs();

                                        map[y3][x3] =0;
                                        add_adj(y3, x3);//벽 제거
                                        
                                    }//if
                                }
                            }

                            map[y2][x2] = 0;
                            add_adj(y2, x2);//벽 제거
                            
                        }//if
                    }
                }

                map[y1][x1] =0;
                add_adj(y1, x1);//벽 제거
                 
            }//if
        }
    }
    
    printf("%d", MAX);  // 가장 큰 값 출력

    return 0;
}