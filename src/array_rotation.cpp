#include <stdio.h>
#include <cmath>
#include <time.h>
#include <iostream>

using namespace std;



int T;
int n;
int d;

int arr[500+10][500+10];


int makeCnt()
{
    while(d > 360 | d < -360){
            d = d% 360; 
    }
    switch(d){
        case 45:
        case -315:
            return 1;
        case 90:
        case -270:
            return 2;
        case 135:
        case -225:
            return 3;
        case 180:
        case -180:
            return 4;
        case 225:
        case -135:
            return -3;
        case 270:
        case -90:
            return -2;
        case 315:
        case -45:
            return -1;
        default:
            return 0;
    }
}

void rotation(int i, int cnt)
{
    int cy=(n+1)/2;
    int cx=(n+1)/2;

    if(cnt >=0){
        // cw
        for(int c=0; c<cnt; ++c){
            int temp = arr[cy-i][cx-i];
            arr[cy-i][cx-i] = arr[cy][cx-i];
            arr[cy][cx-i] = arr[cy+i][cx-i];
            arr[cy+i][cx-i] = arr[cy+i][cx];
            arr[cy+i][cx] = arr[cy+i][cx+i];
            arr[cy+i][cx+i] = arr[cy][cx+i];
            arr[cy][cx+i] = arr[cy-i][cx+i];
            arr[cy-i][cx+i] = arr[cy-i][cx];
            arr[cy-i][cx] = temp;
        }
    }
    else{
        //ccw
        cnt = -1*cnt;
        for(int c=0; c<cnt; ++c){
            int temp = arr[cy-i][cx-i];
            arr[cy-i][cx-i] = arr[cy-i][cx];
            arr[cy-i][cx] = arr[cy-i][cx+i];
            arr[cy-i][cx+i] = arr[cy][cx+i];
            arr[cy][cx+i] = arr[cy+i][cx+i];
            arr[cy+i][cx+i] = arr[cy+i][cx];
            arr[cy+i][cx] = arr[cy+i][cx-i];
            arr[cy+i][cx-i] = arr[cy][cx-i];
            arr[cy][cx-i] = temp;
        }
    }
}

void solve(int cnt)
{
    int lim = (n-1)/2;
    for(int i=1; i<=lim; ++i){
        rotation(i, cnt);
    }
}

void display(){
    for(int y=1; y<=n; ++y){
        for(int x=1; x<=n; ++x){
            cout << arr[y][x];
            cout << " ";
        }
        cout << "\n";
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int cnt;

    cin >> T;
    for(int i=0; i<T; ++i){
        cin >> n;
        cin >> d;

        for(int y=1; y<=n; ++y){
            for(int x=1; x<=n; ++x){
                cin >> arr[y][x];
            }
        }

    cnt =makeCnt();
    solve(cnt);

    display();
    }
}