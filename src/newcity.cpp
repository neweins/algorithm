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
