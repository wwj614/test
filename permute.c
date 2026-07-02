#include "permute.h"

char unique;
void (*Func)(int *P, int n);

// 检查当前排列 P[1..n] 是否应该被输出
// 规则：仅当 P 的字典序小于其逆序排列时输出
void check(int *P, int n) {
	if (unique=='y') {
		// 比较 P[i] 和 P[n-i+1] (即逆序位置的值)
		for (int i = 1; i <= n / 2; i++) {
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
  Func(P, n); 
   
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

void solve(int *P, int n) {
  int *P1=(int *)Nmalloc((n+1)*sizeof(int));      // 使用 1-based 索引，P[1] 到 P[N]
  memcpy(&P1[1], P, n*sizeof(int));
  Backtracking(permute(P1, n, 1));
}
