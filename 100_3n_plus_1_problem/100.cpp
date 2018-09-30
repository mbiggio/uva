#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdio>
using namespace std;
using ll = long long;

/*
 * This solution keeps an unordered map
 * as cache to store the already-computed cycle lengths.
 * This is useful also across test-cases, since the cycle length
 * depends only on the input number itself.
 * Runtime complexity: difficult to tell!
 */

unordered_map<ll,ll> m;

ll cycle_length(ll n) {
  auto it = m.find(n);
  if (it == m.end()) {
    if (n==1) it = m.insert(make_pair(n,1)).first;
    else if (n%2) it = m.insert(make_pair(n,1 + cycle_length(3*n+1))).first;
    else it = m.insert(make_pair(n,1 + cycle_length(n/2))).first;
  }
  return it->second;
}

int main() {
  m.reserve(10000);
  ll a, b;
  while (scanf("%lld %lld", &a, &b) != EOF) {
    ll &m = a<b?a:b;
    ll &M = a<b?b:a;
    ll r = 0;
    for (ll i=m; i<=M; ++i) r = max(r,cycle_length(i));
    printf("%lld %lld %lld\n", a, b, r);
  }
  return 0;
}
