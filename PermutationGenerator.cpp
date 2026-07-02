#include <iostream>
#include <vector>
#include <algorithm>

class PermutationGenerator {
private:
  std::vector<int> path;
  std::vector<bool> used;
  std::vector<std::vector<int>> result;

public:
  void backtrack(const std::vector<int>& nums) {
    if (path.size() == nums.size()) {
      result.push_back(path);
      return;
    }

    for (int i = 0; i < nums.size(); ++i) {
      if (used[i]) continue;  // 已使用，跳过

            // 选择
      path.push_back(nums[i]);
      used[i] = true;

    for (int x : path) {
      std::cout << x << " ";
    }
    std::cout << "\n";
            // 递归
      backtrack(nums);
      



            // 撤销选择（回溯）
      path.pop_back();
      used[i] = false;
      }
    }

  std::vector<std::vector<int>> generate(const std::vector<int>& nums) {
    path.clear();
    used.assign(nums.size(), false);
    result.clear();
    backtrack(nums);
    return result;
  }
};

//g++ --std=c++11 -m64 -O3 -o PermutationGenerator PermutationGenerator.cpp
int main() {
  std::vector<int> nums = {59,58,81,75,33};
  PermutationGenerator pg;
  auto perms = pg.generate(nums);

  for (const auto& p : perms) {
    for (int x : p) {
      std::cout << x << " ";
    }
    std::cout << "\n";
  }

  return 0;
}