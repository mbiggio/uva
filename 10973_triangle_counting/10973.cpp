#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * Intersect the adjacency lists of 
 * two adjacent nodes v1 and v2 to find all the nodes v3
 * adjacent to both v1 and v2.
 * Normalize for 3! = 6 to discard permutations.
 */

int intersect(const vector<vector<int>> &g, int v1, int v2) {
  const auto &l1 = g[v1];
  const auto &l2 = g[v2];
  int i1 = 0, i2 = 0, count = 0;
  while (i1 < l1.size() && i2 < l2.size()) {
    if (l1[i1] > l2[i2]) ++i2;
    else if (l1[i1] < l2[i2]) ++i1;
    else {
      if (l1[i1++] != v1 && l2[i2++] != v2) ++count;
    }
  }
  return count;
}

int count_triangles(vector<vector<int>> &g) {
  // sort 
  for (int v1=0; v1<g.size(); ++v1) 
    sort(g[v1].begin(), g[v1].end());

  // intersect adjacency lists
  int count = 0;
  for (int v1=0; v1<g.size(); ++v1) {
    for (int v2 : g[v1]) {
      count += intersect(g,v1,v2);
    }
  }
  return count/6;
}


int main() {
  int cases;
  scanf("%d",&cases);
  for (int i=0; i<cases; ++i) {
    int n,m;
    scanf("%d %d",&n, &m);
    vector<vector<int>> g(n);
    for (int j=0; j<m; ++j) {
      int v1, v2;
      scanf("%d %d",&v1,&v2);
      g[v1-1].emplace_back(v2-1);
      g[v2-1].emplace_back(v1-1);
    }
    printf("%d\n",count_triangles(g));
  }
  return 0;
}
