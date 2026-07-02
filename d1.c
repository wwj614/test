#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "permute.h"

int *M;
int N;
int minTour=1<<30;
int minTours[]={0,59,58,81,75,33,80,86,68,21,24,25,85,92,51,65};

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

void minTourFunc(int *tour, int n){
  int s=sumTour(tour, n);
  if (s<minTour) {
    minTour=s;
    memcpy(minTours, tour, (n+1)*sizeof(int));
    printf("%d \n",minTour);
    for (int i=1; i<=n; ++i) {
	    printf("%d ", minTours[i]);
    }
    printf("\n");
  }
}

void minTourFuncQ1(int *tour, int n){
  int s=0;
  int row=tour[1];
  for (int i=2; i<=n; ++i) {
	  int col=tour[i];
    s +=M[row*N+col];
    row=col;
    if (s>minTour) return;
  }

  if (s<minTour) {
    minTour=s;
    memcpy(minTours, tour, (n+1)*sizeof(int));
    printf("%d \n",minTour);
    for (int i=1; i<=n; ++i) {
	    printf("%d ", minTours[i]);
    }
    printf("\n");
  }
}

//gcc --std=c11 -m64  -o d1 d1.c permute.c SRC/CBack.c
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
  
  Func=minTourFuncQ1; 
  unique='n';
  int tour1[]={59,58,81,75,33,80,86,68,21,24,25,85,92,51,65};
  minTour=sumTour(minTours, n);
  printf("minTour %d \n",minTour);
  solve(tour1, n);
  
  return 0;
}