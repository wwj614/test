#include "SRC/CBack.h"
#include <stdio.h>

static char unique;
typedef void (*FuncType)(int *P, int n);
static FuncType Func;

void p(int *P, int n) {
  for (int i = 1; i <= n; i++) {
    printf("%d ", P[i]);
  }
  printf("\n");   
}

void check(int *P, int n) {
	if (unique=='y') {
		int i;
		// 比较 P[i] 和 P[n-i+1] (即逆序位置的值)
		for (i = 1; i <= n / 2; i++) {
			if (P[i] < P[n - i + 1]) {
            // P 小于逆序，符合条件，打印并返回
				break; 
			} else if (P[i] > P[n - i + 1]) {
			// P 大于逆序，不符合条件，直接回溯跳过
				Backtrack();
				return;
			}
        // 如果相等，继续比较下一对
		}
	}
  // 如果循环结束都没有触发 Backtrack，说明 P <= Reverse(P)
  // 由于元素互异，实际上只能是 P < Reverse(P)
  p(P, n); 
   
  // 完后回溯，寻找下一个排列
  Backtrack();
}

// 生成全排列的递归函数
void permute(int *P, int n, int step) {
  // 边界条件：生成了一个完整排列
  if (step > n) {
    check(P, n);
    return;
  }
    
  // 从剩余的 n - step + 1 个元素中选择一个放到位置 step
  int c = Choice(n - step + 1);
  int j = step - 1 + c;
    
  // 做出选择：交换 P[step] 和 P[j]
  int temp = P[step];
  P[step] = P[j];
  P[j] = temp;
    
  // 递归进入下一步
  permute(P, n, step + 1);
    
  //CBack 会自动恢复栈状态，包括 P 数组的内容。因此不需要手动撤销交换。
}

void solve(int *P, int N) {
  // 初始化排列为 1..N
  for (int i = 1; i <= N; i++) {
    P[i] = i;
  }
  
  permute(P, N, 1);
}

int main(int argc, char** argv)
{
	int N=atoi(argv[1]);
  int *P=(int *)Nmalloc((N+1)*sizeof(int));      // 使用 1-based 索引，P[1] 到 P[N]
  unique=argv[2][0];
	Func=p;
  // 使用 Backtracking 宏确保 CBack 正确初始化栈底指针
  Backtracking(solve(P,N));
  Nfree(P);
  return 0;
}