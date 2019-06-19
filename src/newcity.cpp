// 지도 정보

// 1. 지도는 정사각형 모양으로 크기 N이며 범위는 4 이상 10 이하임.
// 2. 지도는 1*1 크기 격자 N*N개로 이루어져 있음.
// 3. 각 격자에는 파이프가 설치되어있지 않거나 11가지 모양 중 한 가지 모양의 파이프가 설치되어 있음. 즉, 각 격자 정보는 0 이상 11 이하임.
// 4. 수돗물이 공급되는 격자의 위치 X(가로), Y(세로)가 입력으로 주어지며, 범위는 0 이상 9 이하임.

// 파이프 정보
// 1. 상하좌우 이웃한 파이프의 입출구가 서로 연결되어야 수돗물이 흐름.
// 2. 12진법을 이용해서 정보가 입력됨. 10은 'A'로, 11은 'B'로 표시함.
// 3. 파이프 모양은 아래 표와 같으며 회전은 불가능 함.

// 입력 1의 지도 크기 N은 4이며 수돗물 공급 위치는 (0, 0), 파이프 정보는 다음 표와 같다.

// 그림1. 입력 값

// 그림2. 파이프 모양

// 수돗물이 흐르는 파이프는 아래 그림의 파란색으로 표시한 부분이다. 나머지 검은색 파이프가 제거해야 할 수돗물이 흐르지 않는 파이프로 5개이다.
// 지도 크기 N과 파이프 배치 정보가 주어졌을 때,
// 제거해야 하는 파이프 수를 구하시오.

// [입력형식]
// 첫 번째 줄에 지도 크기 N이 입력.
// 두 번째 줄에는 수돗물이 공급되는 격자의 좌표 X, Y가 입력.
// 세 번째 줄부터 N줄에 걸쳐 N개의 문자가 공백없이 입력.

// [출력 형식]
// 제거해야 하는 파이프 수를 출력

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N;//정사각형 지도 크기
int X, Y;//수돗물 공급되는 시작 좌표, 가로, 세로
int map[20][20];//지도 정보

vector<pair<int,int>> adj[20+5][20+5];

int totalPipe;
int pipeCnt;

// top, bottom, left, right
int direction[12][4] ={{0,0,0,0}, //0
                        {0,0,1,1}, //1
                        {1,1,0,0}, //2
                        {0,1,0,1}, //3
                        {0,1,1,0},//4
                        {1,0,1,0},//5
                        {1,0,0,1},//6
                        {1,1,0,1},//7
                        {0,1,1,1},//8
                        {1,1,1,0},//9
                        {1,0,1,1},//10(A)
                        {1,1,1,1} //11(B)
                    };

void Input_Data(void){
	char str[20];
	cin >> N;
	cin >> X >> Y;
	for (int i = 0; i < N; i++){
		cin >> str;
		for(int j = 0; j < N; j++){
			if(str[j] < 'A') map[i][j] = str[j] - '0';
			else map[i][j] = str[j] - 'A' + 10;
		}
	}
	
	// make adjcent-list
	//calc total pipe
	for(int y=0; y<N; ++y){
		for(int x=0; x<N; ++x){
			// printf("%d ", map[y][x]);
			if(map[y][x] != 0){
				totalPipe++;
				
				//top
				if(y-1 >=0 && y-1 <N && x>=0 && x<N){
					if(direction[map[y][x]][0] == 1 && direction[map[y-1][x]][1] == 1){
						adj[y][x].push_back(make_pair(y-1 ,x));
					}
				}
				
				//bottom
				if(y+1 >=0 && y+1 <N && x>=0 && x<N){
					if(direction[map[y][x]][1] == 1 && direction[map[y+1][x]][0] == 1){
						adj[y][x].push_back(make_pair(y+1 ,x));
					}				
				}
				
				//left
				if(y >=0 && y <N && x-1>=0 && x-1<N){
					if(direction[map[y][x]][2] == 1 && direction[map[y][x-1]][3] == 1){
						adj[y][x].push_back(make_pair(y ,x-1));
					}					
				}		
				
				//right
				if(y >=0 && y <N && x+1>=0 && x+1<N){
					if(direction[map[y][x]][3] == 1 && direction[map[y][x+1]][2] == 1){
						adj[y][x].push_back(make_pair(y ,x+1));
					}					
				}
			}
		}
		// printf("\n");
	}
	
	// for(int y=0; y<N; ++y){
	// 	for(int x=0; x<N; ++x){
	// 		printf("adj[%d][%d] =", y,x);
	// 		for(int i=0; i<adj[y][x].size(); ++i){
	// 			printf("(%d,%d) ", adj[y][x][i].first, adj[y][x][i].second);
	// 		}
	// 		printf("\n");
	// 	}
	// }
	
}

int bfs()
{
	queue<pair<int,int>> que;
	int visit[20+5][20+5]={{0,},};
	
	if(map[Y][X] == 0) return 0;
	que.push(make_pair(Y,X));
	visit[Y][X] = 1;
	
	while(!que.empty()){
		pair<int,int> v = que.front();
		que.pop();
		
		pipeCnt++;
		
		for(size_t i=0; i<adj[v.first][v.second].size(); ++i){
			if(visit[adj[v.first][v.second][i].first][adj[v.first][v.second][i].second] == 0){
				que.push(make_pair(adj[v.first][v.second][i].first  , adj[v.first][v.second][i].second));
				visit[adj[v.first][v.second][i].first][adj[v.first][v.second][i].second] =1;
			}
		}
	}
	
	return pipeCnt;
}

int main(){
	int ans = -1;
	Input_Data();		//	입력 함수

	//	코드를 작성하세요
	ans= totalPipe-bfs();
	
	
	cout << ans << endl;	//	정답 출력
	return 0;
}
