#include "SRC/CBack.h"
#include <stdio.h>

extern char unique;
extern void (*Func)(int *P, int n);

void check(int *P, int n);
void permute(int *P, int n, int step);
void solve(int *P, int N);
