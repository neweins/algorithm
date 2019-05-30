// https://www.acmicpc.net/problem/7576

// 문제
// 철수의 토마토 농장에서는 토마토를 보관하는 큰 창고를 가지고 있다. 토마토는 아래의 그림과 같이 격자 모양 상자의 칸에 하나씩 넣어서 창고에 보관한다. 



// 창고에 보관되는 토마토들 중에는 잘 익은 것도 있지만, 아직 익지 않은 토마토들도 있을 수 있다. 
// 보관 후 하루가 지나면, 익은 토마토들의 인접한 곳에 있는 익지 않은 토마토들은 익은 토마토의 영향을 받아 익게 된다. 
//하나의 토마토의 인접한 곳은 왼쪽, 오른쪽, 앞, 뒤 네 방향에 있는 토마토를 의미한다. 
//대각선 방향에 있는 토마토들에게는 영향을 주지 못하며, 토마토가 혼자 저절로 익는 경우는 없다고 가정한다. 
//철수는 창고에 보관된 토마토들이 며칠이 지나면 다 익게 되는지, 그 최소 일수를 알고 싶어 한다.

// 토마토를 창고에 보관하는 격자모양의 상자들의 크기와 익은 토마토들과 익지 않은 토마토들의 정보가 주어졌을 때, 
//며칠이 지나면 토마토들이 모두 익는지, 그 최소 일수를 구하는 프로그램을 작성하라. 단, 상자의 일부 칸에는 토마토가 들어있지 않을 수도 있다.

// 입력
// 첫 줄에는 상자의 크기를 나타내는 두 정수 M,N이 주어진다. M은 상자의 가로 칸의 수, N은 상자의 세로 칸의 수를 나타낸다. 
//단, 2 ≤ M,N ≤ 1,000 이다. 둘째 줄부터는 하나의 상자에 저장된 토마토들의 정보가 주어진다. 
//즉, 둘째 줄부터 N개의 줄에는 상자에 담긴 토마토의 정보가 주어진다. 하나의 줄에는 상자 가로줄에 들어있는 토마토의 상태가 M개의 정수로 주어진다. 
//정수 1은 익은 토마토, 정수 0은 익지 않은 토마토, 정수 -1은 토마토가 들어있지 않은 칸을 나타낸다. 

// 출력
// 여러분은 토마토가 모두 익을 때까지의 최소 날짜를 출력해야 한다. 
//만약, 저장될 때부터 모든 토마토가 익어있는 상태이면 0을 출력해야 하고, 토마토가 모두 익지는 못하는 상황이면 -1을 출력해야 한다.


#include <stdint.h>
#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int Y;// 세로
int X;// 가로
int box[1000+10][1000+10]; // 토마토 박스
vector<pair<int,int>> adj[1000+10][1000+10]; // 좌표값을 가지는 인접 리스트
vector<pair<int,int>> start;// 익은 토마토 좌표 배열
int MAX_DAY = 0;
int visit[1000+10][1000+10];

int dfs(){
    // 최소 날짜 구하는 것이므로 
    // dfs는 timeout 발생할 수 있다.
}

// ******중요******
// 1. bfs는 push할때 방문한다.
// 2. bfs는 모든 정점이 탐색되는 시점은 pop할 때이다.
int bfs(vector<pair<int,int>> s)
{
    queue<pair<int,int>> que;

    for(size_t i=0; i<s.size(); ++i){
        que.push(s[i]);
        visit[s[i].first][s[i].second] = 1; // 이미 익은 토마토 좌표값을 모두 que에 넣는다.
    }

    while(!que.empty()){
        pair<int, int> v = que.front();
        que.pop();

        // get result
        if(MAX_DAY < visit[v.first][v.second]){
            MAX_DAY = visit[v.first][v.second];
        }

        for(size_t i=0; i<adj[v.first][v.second].size(); ++i){
            if(visit[adj[v.first][v.second][i].first][adj[v.first][v.second][i].second] == 0){
                que.push(make_pair(adj[v.first][v.second][i].first,adj[v.first][v.second][i].second));
                visit[adj[v.first][v.second][i].first][adj[v.first][v.second][i].second] = visit[v.first][v.second] + 1;
            }
        }
    }
    return MAX_DAY-1;
}

int main()
{
    int ans=0;
    scanf("%d %d",&X, &Y);
    for(int y=1; y<=Y; ++y){
        for(int x=1; x<=X; ++x){
            scanf("%d", &box[y][x]);
            if(box[y][x] == 1){
                start.push_back(make_pair(y,x)); 
            }
        }
    }

    // make adjacent list
    for(int y=1; y<=Y; ++y){
        for(int x=1; x<=X; ++x){
            if(box[y][x] != -1){
                if(y-1>=1 && y-1 <=Y && x>=1 && x<=X){
                    if(box[y-1][x] != -1){
                        adj[y][x].push_back(make_pair(y-1,x)); 
                        adj[y-1][x].push_back(make_pair(y,x));
                    }
                    
                }
                if(y+1 >= 1 && y+1 <=Y && x>=1 && x<= X){
                    if(box[y+1][x] != -1){
                        adj[y][x].push_back(make_pair(y+1, x));
                        adj[y+1][x].push_back(make_pair(y, x));
                    }
                }
                if(y >=1 && y<=Y && x-1 >=1 && x-1 <=X){
                    if(box[y][x-1] != -1){
                        adj[y][x].push_back(make_pair(y, x-1));
                        adj[y][x-1].push_back(make_pair(y,x));
                    }
                }
                if(y>=1 && y<=Y && x+1>=1 && x+1<=X){
                    if(box[y][x+1] != -1){
                        adj[y][x].push_back(make_pair(y, x+1));
                        adj[y][x+1].push_back(make_pair(y,x));
                    }
                }
                
                // 연결된 간선이 없으면 토마토는 익지 않는다.
                if(adj[y][x].size() == 0 && box[y][x] == 0){
                    ans = -1;
                }
            }
        }
    }

    if(ans != -1)
        printf("%d", bfs(start));
    else
        printf("-1");
}