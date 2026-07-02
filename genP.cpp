#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

int main(int argc, char* argv[]) {
  char *inMareixStr = argv[1];
  char *inRouteStr = argv[2];
  int n = std::atoi(argv[3]); //Route Size

  std::vector<int> nums(n) ;
  std::iota(nums.begin(), nums.end(), 0); // [0,1,2,...,n-1]
 
  std::ifstream matrixFile(inMareixStr);
  if (!matrixFile.is_open()) {
    std::cerr << "can not open matrix file: " << matrixFile << std::endl;
    return 1;
  }
  int N;  //Matrix Rows, Cols
  matrixFile >> N;
  int *M=(int *)malloc(N * N * sizeof(int));

  for (int row = 0; row < N; ++row) {
    for (int col = 0; col < N; ++col) {
      if (!(matrixFile >> M[row * N + col])) {
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
  int *route=(int *)malloc(n * sizeof(int));

  for (int i = 0; i < n; ++i) {
    if (!(routeFile >> route[i])) {
      std::cerr << "read error: data are not enough" << std::endl;
      return 1;
    }
    --route[i];                             //node from 1 in routeFile and from 0 in matrixFile
  }
  routeFile.close();
  
  int minRoute = 1<<30;
  int *minRoutes = (int *)malloc(N * sizeof(int));
  do {
    int s=0;
    int row = route[nums[0]];
    for (int i = 0; i<n; ++i) {
      int col = route[nums[i]];
      s +=M[row * N + col];
//      if (s > minRoute) continue;
      row = col;
    }
    if (s < minRoute) {
      minRoute = s;
      std::cout << minRoute << std::endl;
      for (int i = 0; i<n; ++i) {
        minRoutes[i] = route[nums[i]];
        std::cout << ++minRoutes[i] << " ";
      }
      std::cout << " ( " << n << " ) " <<  std::endl;
    }
  } while (std::next_permutation(nums.begin(), nums.end()));

  return 0;
}
