// https://www.acmicpc.net/problem/2667

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int N; // 가로 x 세로 : N x N, 5<=N<=25

int numgrp;
vector<int> ans;

int map[1000+10][1000+10];
vector<pair<int,int>> adj[1000+10][1000+10];
int visit[1000+10][1000+10];
int bfs()
{
    numgrp = 1;
    for(int y=1; y<=N; ++y){
        for(int x=1; x<=N; ++x){

            if(map[y][x] == 1){
                numgrp++; //그래프 수 세기

                /*******************************bfs 기본 골격*************************************************/
                int count=0; //정점갯수 세기
                queue<pair<int,int>> que;
                que.push(make_pair(y,x));
                visit[y][x] = 1;
                map[y][x] = numgrp;

                while(!que.empty()){
                    pair<int,int> v = que.front();
                    que.pop();
                    
                    count++; //모든 정점은 이 지점에서 탐색된다.

                    for(size_t i=0; i<adj[v.first][v.second].size(); ++i){
                        if(visit[adj[v.first][v.second][i].first][adj[v.first][v.second][i].second] == 0){
                            visit[adj[v.first][v.second][i].first][adj[v.first][v.second][i].second] = 1;
                            que.push(make_pair(adj[v.first][v.second][i].first, adj[v.first][v.second][i].second));
                            map[adj[v.first][v.second][i].first][adj[v.first][v.second][i].second] = numgrp;
                        }
                    }
                }
                ans.push_back(count);

                /**********************************************************************************************/
            }
        }
    }

    //결과 출력
    printf("%d\n", numgrp-1);
    sort(ans.begin(), ans.end()); //오름차순 정렬
    for(size_t i=0; i<ans.size(); ++i){
        printf("%d\n", ans[i]);
    }

    return 0;
}
int testcase()
{
    FILE* fp;
    int flag=0;
    fp=fopen("testcase.txt", "wr");
    int size =1000;

    fprintf(fp,"%d\n", size);
    for(int y=1; y<=size+1; ++y){
        for(int i=1; i<=size; ++i){
            if(flag ==1 ){
                fprintf(fp,"1");
                flag =0;
            }else{
                flag=1;
                fprintf(fp,"0");
            }
        }
        fputc(13,fp);
    }
    fclose(fp);
    return 0;
}

int main()
{
    testcase();

    FILE* fp;
    fp = fopen("testcase.txt", "r");
    fscanf(fp, "%d", &N);

    for(int y=1; y<=N; ++y){
        for(int x=1; x<=N; ++x){
            fscanf(fp,"%1d", &map[y][x]);
        }
    }

    clock_t begin, end;
    begin = clock();


    //make adjacent list
    // 순차탐색보다 더 시간복잡도가 낮은 방법이 없을까? 
    // 순차탐색에서는 양방향 그래프 고려를 하지 않아도 된다.(이미 모든 포인트에서 탐색을 실시하므로... 오히려 중복 삽입된다.)
    for(int y=1; y<=N; ++y){
        for(int x=1; x<=N; ++x){
            if(map[y][x] != 0){
                //위
                if(y-1>=1 && y-1<=N && x>=1 && x <= N){
                    if(map[y-1][x] != 0){
                        adj[y][x].push_back(make_pair(y-1, x));
                        // adj[y-1][x].push_back(make_pair(y, x)); // 순차 탐색이므로 할 필요없다.
                    }
                }
                // 아래
                if(y+1 >=1 && y+1 <=N && x>=1 && x<=N){
                    if(map[y+1][x] != 0){
                        adj[y][x].push_back(make_pair(y+1, x));
                    }
                }
                //좌
                if(y>=1 && y<=N && x-1>=1 && x-1<=N){
                    if(map[y][x-1] != 0){
                        adj[y][x].push_back(make_pair(y,x-1));
                    }
                }
                //우
                if(y>=1 && y<=N && x+1 >=1 && x+1 <=N){
                    if(map[y][x+1] != 0){
                        adj[y][x].push_back(make_pair(y,x+1));
                    }
                }
            }
        }
    }

    bfs();



    end = clock();         
    printf("수행시간 : %f",(double)(end-begin)/CLOCKS_PER_SEC); //O(N^2)=1000000일때 0.3sec , 배열 사이즈 최대임


}

