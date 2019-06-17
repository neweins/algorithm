#include <queue>
#include <vector>
#include <stdio.h>
#include <iostream>

using namespace std;

int N, M;//공장 수, 도로 정보 수
int A[5000], B[5000], D[5000];//공장 A, 공장 B, 거리 D

vector<pair<int,int>> adj[100+10]; //[정점][거리] pair<정점, 거리>
int visit[100+10];

void InputData(){
	int i;
	cin >> N >> M;
	for (i = 0; i < M; i++){
		cin >> A[i] >> B[i] >> D[i];
		
		// 양방향 인접 리스트
		adj[A[i]][D[i]].push_back(make_pair(B[i],D[i]));
		adj[B[i]][D[i]].push_back(make_pair(A[i],D[i]));
	}
}

int bfs(int sp)
{
    queue<pair<int,int>> que;
    for(int i=0; i<adj[sp].size(); ++i){
        que.push(make_pair(adj[sp][i].first, adj[sp][i].second ) );
        visit[sp] = 1; 
    }



 
    return ;
}

int main()
{
    int ans =-1;
	int s[100+10] = {0,};
	InputData();//	입력 함수

    //모든 시작 정점
    for(int i=1; i<=N; ++i)
    	s[i] = bfs(i); // 시작 점으로 부터 가장 먼거리
	
	// s[] 요소 중 가장 작은 값에 해당하는 i가 최적
	
	cout << ans << endl;//	정답 출력
	return 0;
}