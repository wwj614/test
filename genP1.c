#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>


int *M;
int N;

int *route;
int minTour=1<<30;
int minTours[]={0,59,58,81,75,33,80,86,68,21,24,25,85,92,51,65};

int sumTour(int *nums, int n){
  if (n < 2) return 1 << 30;
  int s=0;  
  int row=route[nums[0]];
  for (int i = 1; i < n; ++i) {
	  int col = route[nums[i]];
    s += M[row*N+col];
    row = col;
  }
  return s;
}

static int itemCompare(const void *p1, const void *p2) {
  int *a=(int *)p1;
  int *b=(int *)p2;

  return *b - *a;
}

void p_route(int n) {
  for (int i = 0; i<n; ++i) {
    printf("%d ", route[minTours[i]]+1);
  }
  printf("(n=%d) (s=%d) \n",n, minTour);    
}

int check(int *nums, int n) {
  int s=0;  
  int row=route[nums[0]];
  for (int i = 1; i < n; ++i) {
	  int col = route[nums[i]];
    s += M[row*N+col];
    if (s > minTour) return 0;      
    row = col;
  }
  if (s < minTour) {
    minTour = s;
    memcpy(minTours, nums, n * sizeof(int));
    return 1;
  }
  return 0;
}  
void p(int *nums, int n) {
  for (int i = 0; i<n; ++i) {
    printf("%d ", route[nums[i]]+1);
  }
  printf("(n=%d) (s=%d) \n",n, minTour);    
}

void iter_swap(int *first, int *second) {
  int temp = *first;
  *first = *second;
  *second = temp;
}

void reverse(int *first, int *last) {
  if (first >= last )
    return;
  while (first < last) {
	  iter_swap(first, last);
	  ++first;
	  --last;
	}
}

//gcc --std=c11 -m64 -O3 -o genP1 genP1.c 
int main(int argc, char* argv[]) {
  char *inMareixStr = argv[1];
  char *inRouteStr = argv[2];
  int n = atoi(argv[3]); //Route Size

  FILE *fM = fopen(inMareixStr, "r");  
  fscanf(fM, "%d \n", &N);
  
  M = (int *)malloc(N*N*sizeof(int));
  for (int row = 0; row < N; ++row) {
	  for (int col = 0; col < N; ++col) {
	    fscanf(fM, "%d", &M[row*N+col]);
    }
  }
  fclose(fM);
  
  FILE *fRoute = fopen(inRouteStr,"r");  
  route = (int *)malloc(n * sizeof(int));
  int *nums = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; ++i) {
    fscanf(fRoute, "%d", &route[i]);
    --route[i];
    nums[i] = i;
  }
  fclose(fRoute);
  
  check(nums, n); 
  p(nums, n);

  int *first = nums;
  int *last = nums + n - 1;
  for(;;)	{
    //从右往左找最大索引 i，使得 a[i] < a[i+1]
    int *R2L_i = last - 1;
    
    int v_i = *R2L_i;    
    int v_ip1 = *last;
    while ((R2L_i >= first) && (v_i > v_ip1)){
      v_ip1 = v_i;
      --R2L_i; 
      v_i = *R2L_i;
    }
    if (R2L_i < first) break;
    
    //从右往左找最大索引 j，使得 a[j] > a[i]
    int *R2L_j = last;
    while (*R2L_j < *R2L_i) {
      --R2L_j; 
    }
   
    //交换 a[i] 与 a[j]
	  iter_swap(R2L_i, R2L_j);
    //反转 a[i+1] 到末尾的所有元素
    reverse(R2L_i+1, last); 
    check(nums, n); 
  } 
  p_route(n);
  return 0;
}
