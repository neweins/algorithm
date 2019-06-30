// josephus problem same as backjoon queue
#include <stdio.h>

#define MAXQ (1<<16) //65536
#define MOD (MAXQ - 1) //65535

int N;
int S;
int M;

int que[MAXQ];

int wp, rp;
void push(int n){
    que[wp] = n;
    wp = (wp+1) & MOD;
}

int front(){
    return que[rp];
}

void pop(){
    rp = (rp+1) & MOD;
}

int main()
{
    printf("%d ", MAXQ);
    scanf("%d %d %d", &N, &S, &M);

    int j=S;
    for(int i=1; i<=N; ++i){
        push(j); j++;
        if(j > N) j=1;
    }

    // for(int i=0; i<N; ++i){
    //     printf("%d ", que[i]);
    // }

    for(int i=1; i<=N; ++i){
        for(int j=0; j<M-1; ++j){
            push(front()); pop();
        }
        printf("%d ", front()); pop();
    }

}

