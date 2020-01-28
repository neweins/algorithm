// https://www.acmicpc.net/problem/4991

#include <iostream>
#include <vector>
#include <stack> // dfs 완전 탐색
#include <queue> // bfs 최단 경로
#include <algorithm>

using namespace std;

char map[30][30];

/*
. : 깨끗한 칸
* : 더러운 칸
x : 가구
o : 시작 위치

*/

vector<pair<int,int>> Node;
vector<pair<int,int>> dirtNode; // limit : 10
pair<int,int> startNode; 
vector<pair<int,int>> adj[30][30];

vector<pair<int,int>> adjdfs[11+3];  // <node value, weight(=distance)>

// 최단 거리
int bfs(pair<int,int> start, pair<int,int> end)
{
    int dis=-1;
    int visited[30][30] = {0, };
    queue<pair<int,int>> q;

    q.push(make_pair(start.first,start.second));
    visited[start.first][start.second] = 1;
    while(!q.empty()){
        pair<int,int> v = q.front();
        q.pop();

        dis++;

        if(v == end) return dis;

        for(int i=0; i<adj[v.first][v.second].size(); ++i){
            if(visited[adj[v.first][v.second][i].first][adj[v.first][v.second][i].second] == 0){
                q.push(make_pair(adj[v.first][v.second][i].first, adj[v.first][v.second][i].second));
                visited[adj[v.first][v.second][i].first][adj[v.first][v.second][i].second] = 1;
            }
        }
    }

    return -1;

}

int dfs()
{
    int visited[30]={0,};
    stack<pair<int,int>> s;
    int finalDis=0;

    s.push(1);
    while(!s.empty()){
        int v = s.top();
        s.pop();

        if(visited[v] == 0){
            visited[v] = 1;
        }

        for(int i=0; i< adjdfs[v].size(); ++i){
            if(visited[adjdfs[v][i].first] == 0){
                s.push(adjdfs[v][i].first, adjdfs[v][i].second);
                // finalDis +=adjdfs[v][i].second;
            }
        }
    }

    return finalDis;
}

int main()
{
    int h, w;
    scanf("%d %d", &w, &h);
    for(int y=1; y<=h; ++y){
        for(int x=1; x<=w; ++x){
            scanf("%c ",&map[y][x]);
            if(map[y][x] == 'o'){
                startNode.first = y;
                startNode.second = x;
            }
            if(map[y][x] == '*'){
                dirtNode.push_back(make_pair(y,x));
            }
        }
    }

    //make adjcent list
    for(int y=1; y<=h; ++y){
        for(int x=1; x<=w; ++x){
            if(map[y][x] != 'x'){
                //위
                if(y-1 >=1 && map[y-1][x] != 'x'){
                    adj[y][x].push_back(make_pair(y-1,x));
                }
                //아래
                if(y+1 <=h && map[y+1][x] != 'x'){
                    adj[y][x].push_back(make_pair(y+1,x));
                }
                //좌
                if(x-1 >=1 && map[y][x-1] != 'x'){
                    adj[y][x].push_back(make_pair(y, x-1));
                }
                //우
                if(x+1 <=w && map[y][x+1] != 'x'){
                    adj[y][x].push_back(make_pair(y,x+1));
                }

                adj[y][x].push_back(make_pair(y,x)); // 노드가 한개인 그래프 포함.
            }
        }
    }

    // Node 배열에 모든 node를 copy
    Node.push_back(make_pair(startNode.first,startNode.second));
    for(int i=0; i < dirtNode.size(); i++){
       Node.push_back(make_pair(dirtNode[i].first, dirtNode[i].second));
    }
    
    for(int i=0; i<Node.size()-1; ++i){
        for(int j=i+1; j<Node.size(); ++j){
            int dis=bfs(Node[i], Node[j]);
            adjdfs[i].push_back(make_pair(j, dis)); // make_pair(node val, distance)
            adjdfs[j].push_back(make_pair(i, dis)); // add both direction graph
        }
    }

    cout << dfs() << endl;

    return 0;
}
