#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
using ull = unsigned long long;

/**
 * The algorithm works as follows.
 * If all of the amounts are equal to average or average + 1,
 * then there's no way of further equalize the amounts by exchanging money,
 * so we just return zero.
 * On the other hand, suppose there are a bunch of amonts which 
 * are > average + 1, and some which are < average.
 * Each amount > average + 1 must at least reach average + 1 by removing
 * some money. If, after adding this money to the 
 * amounts < average, every one of them reaches average or average + 1,
 * then this must be the minimal amount of money that we have to exhcnge.
 * On the other hand, if some of them is still below average, then
 * some of the bigger ones must be lowered from average + 1 to average.
 * In this case, the amount that we must exchange is the one strictly 
 * necessary to raise the lower ones to average.
 */

ull min_exchange(vector<ull> &amounts) {
  ull sum = accumulate(amounts.begin(), amounts.end(), 0);
  ull average = sum/amounts.size();
  ull give = 0, take = 0;
  for (auto a : amounts) {
    if (a > average + 1) give += a - average - 1;
    else if (a < average) take += average - a;
  }
  return max(give,take);
}

int main() {
  int students;
  int integer, decimal;
  scanf("%d",&students);
  while (students != 0) {
    vector<ull> amounts(students);
    for (int i=0; i<students; ++i) {
      scanf("%d.%d",&integer, &decimal);
      amounts[i] = integer*100 + decimal;
    }
    printf("$%.2f\n", static_cast<double>(min_exchange(amounts))/100.0);
    scanf("%d",&students);
  }
  return 0;
}
