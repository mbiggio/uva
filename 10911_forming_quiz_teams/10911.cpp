#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <limits>
using namespace std;

/*
 * Dynamic programming solution.
 * The rationale is that, given an optimal pairing of a subset S of students, 
 * represented as a bit vector (bit = 1 meaning that the student has been paired with some other student), 
 * suppose paired student i has been associated to paired student j.
 * Then, removing this pair from the subset S, we must have an optimal pairing of
 * subset S - {i} - {j}.
 * Runtime complexity: O(N*2^(2*N))
 */


template <typename T>
double get_distance(const tuple<T,T> &p1, const tuple<T,T> &p2) {
  return sqrt((get<0>(p1)-get<0>(p2))*(get<0>(p1)-get<0>(p2)) + (get<1>(p1)-get<1>(p2))*(get<1>(p1)-get<1>(p2)));
}

double find_min_cost_helper(const vector<tuple<double,double>> &coordinates,
                            vector<double> &costs,
			    const int target) {
  const int size = coordinates.size();
  if (costs[target] < 0) {
    if (!target) costs[target] = 0.0;
    else {
      costs[target] = numeric_limits<double>::max();
      int last_bit_set = target & ~(target-1);
      int cur_bit = last_bit_set << 1;
      while (cur_bit < (1<<size)) {
	if (target & cur_bit) {
	  double new_cost = 
	    get_distance(coordinates[log2(cur_bit)], coordinates[log2(last_bit_set)]) + 
	    find_min_cost_helper(coordinates, costs, target & ~cur_bit & ~last_bit_set);

	  costs[target] = min(costs[target],new_cost);
	}
	cur_bit = cur_bit << 1;
      }
    }
  }
  return costs[target];
}

double find_min_cost(const vector<tuple<double,double>> &coordinates) {
  const int size = coordinates.size();
  vector<double> costs(1<<size, -1.0);
  int target = (1<<size)-1;
  return find_min_cost_helper(coordinates, costs, target);
}


int main(int argc, char *argv[]) {
  int n;
  int num_case = 1;
  while (cin >> n) {
    if (!n) return 0;
    vector<tuple<double,double>> coordinates;
    for (int i=0; i<2*n; ++i) {
      string name;
      double x,y;
      cin >> name;
      cin >> x >> y;
      coordinates.emplace_back(x,y);
    }
    double result = round(100.0*find_min_cost(coordinates))/100.0;
    printf("Case %d: %.2f\n", num_case, result);
    ++num_case;
  }

  return 0;
}
