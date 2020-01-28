//https://www.acmicpc.net/problem/2468

#include <iostream>
#include <stack>
#include <algorithm>
#include <queue>
#include <vector>


using namespace std;

int N;
int input[100+10][100+10];
int maxGrp; //answer


int dfs(vector<pair<int,int>> adj[][100+10])
{
    // //debug
    // for(int y = 1; y<=N; ++y){
    //     for(int x =1; x<=N; ++x){
    //         printf("adj[%d][%d] : ", y, x);
    //         for(int i=0; i< adj[y][x].size(); ++i){
    //              cout << "("<< adj[y][x][i].first << "," <<  adj[y][x][i].second << ")" <<" ";
    //         }
    //         cout << endl;
    //     }
    // }
    // cout << endl << endl;

    stack<pair<int,int>> s;
    int visited[100+10][100+10]={0,};
    int cntGrp=0;
    for(int y=1; y<=N; ++y){
        for(int x=1; x<=N; ++x){
            //[ATTENTION] 중복 탐색 방지위해 기 방문 포인트는 skip, 비어 있는 인접리스트는 skip
            if(visited[y][x] == 1 || adj[y][x].empty()) continue; 
            
            s.push(make_pair(y,x));
            while(!s.empty()){
                pair<int,int> v = s.top();
                s.pop();

                if(visited[v.first][v.second] == 0){
                    visited[v.first][v.second] = 1;
                }

                for(int i=0; i<adj[v.first][v.second].size(); ++i){
                    if(visited[adj[v.first][v.second][i].first][adj[v.first][v.second][i].second] == 0){
                        s.push(make_pair(adj[v.first][v.second][i].first, adj[v.first][v.second][i].second));
                    }
                }
            }
            cntGrp++;
        }
    }

    return cntGrp;
}

int main()
{
    vector<int> map[100+10];

    cin >> N;
    for(int y=1; y<=N; ++y){
        map[y].push_back(0);// skip 0th col
        for(int x=1; x<=N; ++x){
            cin >> input[y][x];
            map[y].push_back(input[y][x]);
        }
    }

    //[ATTENTION] 비가 오지 않는 경우에도 탐색해야 한다.(h=0)
    for(int h=0; h<=100; ++h){

        ////debug
        // cout << "height : " << h << endl;

        vector<pair<int,int>> adj[100+10][100+10];
        vector<int> remap[100+10];// initial remap
        for(int p=1; p<=100; ++p){
            copy(map[p].begin(), map[p].end(), back_inserter(remap[p])); // copy map[][] to remap[][]
        }

        for(int y=1; y<=N; ++y){
            for(int x=1; x<=N; ++x){
                if(remap[y][x] <= h){
                    remap[y][x] = 0;
                }
                else{
                    remap[y][x] = 1;
                }
            }
        }

        // // debug
        // for(int y=1; y<=N; ++y){
        //     for(int x=1; x<=N; ++x){
        //         cout << remap[y][x] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        // continue;

        //make adjcent list
        for(int y=1; y<=N; ++y){
            for(int x=1; x<=N; ++x){
                if(remap[y][x] == 1){
                    //위
                    if(y-1 >=1 && remap[y-1][x] == 1){
                        adj[y][x].push_back(make_pair(y-1,x));
                    }

                    //아래
                    if(y+1 <= N && remap[y+1][x] == 1){
                        adj[y][x].push_back(make_pair(y+1,x));
                    }

                    //좌
                    if(x-1 >= 1 && remap[y][x-1] == 1){
                        adj[y][x].push_back(make_pair(y,x-1));
                    }

                    //우
                    if(x+1 <= N && remap[y][x+1] == 1){
                        adj[y][x].push_back(make_pair(y,x+1));
                    }

                    adj[y][x].push_back(make_pair(y,x)); //[ATTENTION] 정점이 한개인 그래프도 count해야 한다.
                }
            }
        }
        maxGrp =  max(maxGrp, dfs(adj));
    }

    cout << maxGrp << endl;

    return 0;
}


