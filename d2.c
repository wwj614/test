#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "SRC/CBack.h"

int *M;
int N;
int S;

int minTour=0;
int minTours[]={0,59,58,81,75,33,80,86,68,21,24,25,85,92,51,65};

// 生成全排列的递归函数
void permute(int *P, int n, int step) {
    // 边界条件：生成了一个完整排列
    if (step > n) {
      if (S < minTour) {
        minTour=S;
        memcpy(minTours, P, (n+1)*sizeof(int));
        printf("%d \n",minTour);
        for (int i=1; i<=n; ++i) {
	        printf("%d ", minTours[i]);
        }
        printf("\n");
      } 
      S=0;
      Backtrack();
      return;
    }
    
    // 从剩余的 n - step + 1 个元素中选择一个放到位置 step
    int c = Choice(n - step + 1);
    int j = step - 1 + c;

    S +=M[P[step-1]*N+P[j]];
    // 边界条件：生成了一个非完整排列，距离已超，交换下一个
    if (S>minTour) { 
      S=0;
      Backtrack();
      return;   
    }
    
    // 做出选择：交换 P[step] 和 P[j]
    int temp = P[step];
    P[step] = P[j];
    P[j] = temp;

      // 递归进入下一步
    permute(P, n, step + 1);
    
    /* 
     * CBack 会自动恢复栈状态，包括 P 数组的内容。
     * 因此不需要手动撤销交换。
     */
}

void solve(int *P, int n) {
    int *P1=(int *)Nmalloc((n+1)*sizeof(int));      // 使用 1-based 索引，P[1] 到 P[N]
    for (int i=0; i<n; ++i) {
	    P1[i+1]=P[i];
    }    
  S=0;
  P1[0]=0;
//  Notify(S);
  Backtracking(permute(P1, n, 1));
}

int sumTour(int *tour, int n){
  int s=0;
  int row=tour[1];
  for (int i=2; i<=n; ++i) {
	  int col=tour[i];
    s +=M[row*N+col];
    row=col;
  }
  return s;
}

//gcc --std=c11 -m64 -o d2 d2.c SRC/CBack.c
int main(int argc, char** argv) {
  char *infileStr=argv[1];
  FILE *fin=fopen(infileStr,"rb");  
  int n=atoi(argv[2]);
  fscanf(fin, "%d \n", &N);
  printf("%d \n",N);
  ++N;
  
  M=(int *)malloc(N*N*sizeof(int));
  for (int row=1; row<N; ++row) {
	  for (int col=1; col<N; ++col) {
	    fscanf(fin, "%d", &M[row*N+col]);
    }
  }
  for(int i=0; i<N; ++i) {
    M[i*N+0]=0;
    M[0*N+i]=0;
  }
  
  int tour1[]={59,58,81,75,33,80,86,68,21,24,25,85,92,51,65};
  minTour=sumTour(minTours, n);
  printf("minTour %d \n",minTour);
  S=0;
  solve(tour1, n);
  
  return 0;
}