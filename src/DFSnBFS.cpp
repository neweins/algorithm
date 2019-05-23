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
vector<int> adj[1000+10]; // 그래프 https://sarah950716.tistory.com/12?category=598483

// int dfs_visited[1000+10]={0,};
void dfs(int v)
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

    
    // dfs_visited[v] =1;
    // printf("%d ", v);
    // for(size_t i=0; i<adj[v].size(); ++i){
    //     if(dfs_visited[adj[v][i]] == 0){
    //         dfs(adj[v][i]);
    //     }
    // }

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
 
        for(size_t i=0; i<adj[v].size(); ++i){
            if(visited[adj[v][i]] == 0){ 
                visited[adj[v][i]] =1;
                que.push(adj[v][i]);
            }
        }

        printf("%d ", v);

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
    dfs(V);
    printf("\n");

    //정렬(optional)
    for(int i=1; i<=M; ++i){
        sort(adj[i].begin(), adj[i].end(), compare);
    }
    bfs();

}


// #include<iostream>
// #include<queue>
// using namespace std;
 
// #define MAX_VALUE 1001            //'N이 1~1000 이므로 1000번째 인덱스에 접근 -> 크기 1001까지 선언
// int N, M, V;                    //노드 개수, 간선 개수, 시작할 노드 번호
// int mat[MAX_VALUE][MAX_VALUE];    //인접행렬 배열 선언
// int visit[MAX_VALUE];            //visit 배열 default 는 0으로. . . 
 
// void dfs(int v) {
    
//     cout << v << ' ' ;
//     visit[v] = 1;            //방문한 노드를 visit 0에서 1로 변경
//     for(int i=1; i<=N; i++) {
//         if(visit[i] == 1 || mat[v][i] == 0)     
//             continue;
//         dfs(i);                //dfs에서 재귀를 사용
//     }
// }
 
// void bfs(int v) {
//     queue<int> q;            //bfs에서는 q를사용
//     q.push(v);
//     visit[v] = 0;            //방문한 노드를 visit 1에서 0으로 변경
//     while(!q.empty()) {
//         v = q.front();
//         cout << q.front() << ' ';
//         q.pop();
//         for(int i=1; i<=N; i++) {
//             if(visit[i] == 0 || mat[v][i] == 0)
//                 continue;
//             q.push(i);
//             visit[i] = 0;
//         }
//     }
// }
 
// int main() {
//     int x, y;
//     cin >> N >> M >> V;            //N은 노드개수, M은 간선의개수, V는 처음 위치의 기준이 되는 노드
//     for(int i=0; i<M; i++) {    //간선의 개수만큼 서로 이어줄 x와 y노드를 입력받습니다.
//         cin >> x >> y;            
//         mat[x][y] = mat[y][x] = 1;    //인접행렬 표시
//     }
//     dfs(V);            
//     cout << '\n';
//     bfs(V);
//     return 0;
// }
