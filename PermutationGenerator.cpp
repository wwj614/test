#include <iostream>
#include <fstream>

class PermutationGenerator {
private:
public:
  int N;  //Matrix Rows, Cols
  int *M;
  int n;
  int *route;
  int minRoute;
  int *minRoutes;

  void p(int *route, int step, int s) {
    for (int i=0; i <= step; ++i) {
        std::cout << route[i] + 1 << " " ;
    }
    std::cout  << " ( " << s << " ) " << std::endl;
  }
  
  void dup(int s) {
    minRoute = s;
    memcpy(minRoutes, route, n*sizeof(int));
  }

  void swap(int first, int second) {
    int temp = route[first];
    route[first] = route[second];
    route[second] = temp;
  }
  
  void backtrack(int step, int s) {
    if (step == n) {
      s += M[route[step-1]*N + route[step]]; 
      if (s < minRoute) dup(s);
      return;
    }
    for (int i = step; i <= n; ++i) {
      swap(step, i);
      int s1 = s;
      if (step > 0) 
        s1 += M[route[step-1]*N + route[step]];
      if (s1 >= minRoute) return;
      backtrack(step+1, s1);
      swap(i, step);
    }
  }

  void generate() {
    minRoute = 1<<20;
    backtrack(0, 0);
    p(route,n,minRoute);
  }

};

//g++ --std=c++11 -m64 -O3 -o PermutationGenerator PermutationGenerator.cpp
int main(int argc, char* argv[]) {
  char *inMareixStr = argv[1];
  char *inRouteStr = argv[2];
 
  PermutationGenerator pg;  

  std::ifstream matrixFile(inMareixStr);
  if (!matrixFile.is_open()) {
    std::cerr << "can not open matrix file: " << matrixFile << std::endl;
    return 1;
  }
  matrixFile >> pg.N;
  pg.M = (int *)malloc(pg.N * pg.N * sizeof(int));
  for (int row = 0; row < pg.N; ++row) {
    for (int col = 0; col < pg.N; ++col) {
      if (!(matrixFile >> pg.M[row * pg.N + col])) {
        std::cerr << "read errow: data are not enough" << std::endl;
        return 1;
      }
    }
  }
  matrixFile.close();

  std::ifstream routeFile(inRouteStr);
  if (!routeFile.is_open()) {
    std::cerr << "can not open route file: " << inRouteStr << std::endl;
    return 1;
  }
//  routeFile >> pg.n;
//  int n = std::atoi(argv[3]); //Route Size
  pg.n = std::atoi(argv[3]); //Route Size
  pg.route = (int *)malloc(pg.n * sizeof(int));
  pg.minRoutes = (int *)malloc(pg.n * sizeof(int));
  pg.n--;
  for (int i = 0; i <= pg.n; ++i) {
    if (!(routeFile >> pg.route[i])) {
      std::cerr << "read error: data are not enough" << std::endl;
      return 1;
    }
    pg.route[i]--;
  }
  routeFile.close();
  
  pg.generate();
  return 0;
}
