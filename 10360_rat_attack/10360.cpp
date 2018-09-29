#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

/*
 * Simple brute-force solution.
 * Compute first a matrix of the sum of rectangles 
 * having as upper-left corner (0,0) and as lower-right corner (i,j).
 * This allows to compute the desired square sums in constant time each.
 * Runtime complexity: O(n^2)
 */

vector<vector<int>> build_sum_matrix(const vector<vector<int>> &m) {
  vector<vector<int>> s(m.size(), vector<int>(m[0].size()));
  s[0][0] = m[0][0];
  for (int i=1; i<s.size(); ++i) s[i][0] = m[i][0] + s[i-1][0];
  for (int j=1; j<s[0].size(); ++j) s[0][j] = m[0][j] + s[0][j-1];
  for (int i=1; i<s.size(); ++i) {
    for (int j=1; j<s[0].size(); ++j) {
      s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + m[i][j];
    }
  }
  return s;
}

tuple<int,int,int> rat_attack(const vector<vector<int>> &m, const int d) {
  auto s = build_sum_matrix(m);
  int cur_max = 0;
  int cur_x = -1;
  int cur_y = -1;
  for (int i=d; i<m.size(); ++i) {
    for (int j=d; j<m[0].size(); ++j) {
      int cur_sum = s[i][j];
      if (i-2*d-1 >= 0) cur_sum -= s[i-2*d-1][j];
      if (j-2*d-1 >= 0) cur_sum -= s[i][j-2*d-1];
      if (i-2*d-1 >= 0 && j-2*d-1 >= 0) cur_sum += s[i-2*d-1][j-2*d-1];
      if (cur_sum > cur_max) {
	cur_max = cur_sum;
	cur_x = i-d;
	cur_y = j-d;
      }
    }
  }
  return {cur_x,cur_y,cur_max};
}


int main(int argc, char *argv[]) {
  int scenarios;
  cin >> scenarios;
  for (int i=0; i<scenarios; ++i) {
    vector<vector<int>> m(1025, vector<int>(1025,0));
    int positions;
    int diameter;
    cin >> diameter >> positions;
    for (int j=0; j<positions; ++j) {
      int x, y, q;
      cin >> x >> y >> q;
      m[x][y] = q;
    }
    auto t = rat_attack(m,diameter);
    printf("%d %d %d\n", get<0>(t), get<1>(t), get<2>(t));
  }
  return 0;
}
