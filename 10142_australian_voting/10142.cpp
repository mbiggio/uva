#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <cstdio>
#include <sstream>
using namespace std;

class VoteCounter {
public:

  /**
   * Runtime complexity: O(candidates)
   */
  VoteCounter(int n) : votes(0) {
    for (int i=1; i<=n; ++i) {
      v[i] = {};
      m[0].insert(i);
    }
  };

  /**
   * Runtime complexity: O(log votes + log candidates)
   */
  unordered_set<int> removeCandidate(int candidate) { 
    if (v.find(candidate) == v.end()) return {}; // candidate already removed
    int cur_votes = v[candidate].size();
    votes -= cur_votes;
    m[cur_votes].erase(candidate);
    if (m[cur_votes].empty()) m.erase(cur_votes);
    auto result = v[candidate];
    v.erase(candidate);
    return result;
  }


  /**
   * Runtime complexity: O(log votes + log candidates)
   */
  void addVote(int candidate, int vote) {
    if (v.find(candidate) == v.end()) return; // candidate not valid
    if (v[candidate].find(vote) != v[candidate].end()) return; // vote already assigned to candidate
    int cur_votes = v[candidate].size();
    v[candidate].insert(vote);
    m[cur_votes].erase(candidate);
    if (m[cur_votes].empty()) m.erase(cur_votes);
    m[cur_votes + 1].insert(candidate);
    ++votes;
  }

  /**
   * Runtime complexity: O(1)
   */
  int getTotVotes() const {
    return votes;
  }

  /**
   * Runtime complexity: O(log votes)
   */
  int getMaxVotes() const {
    return m.crbegin()->first;
  }

  /**
   * Runtime complexity: O(log votes)
   */
  int getMinVotes() const {
    return m.cbegin()->first;
  }

  /**
   * Runtime complexity: O(log votes + candidates)
   */
  set<int> getCandidatesWithMaxVotes() const {
    return m.crbegin()->second;
  }

  /**
   * Runtime complexity: O(log votes + candidates)
   */
  set<int> getCandidatesWithMinVotes() const {
    return m.cbegin()->second;
  }

  /**
   * Runtime complexity: O(1)
   */
  bool isCandidateValid(int candidate) const {
    return v.find(candidate) != v.end();
  }
private:
  unordered_map<int,unordered_set<int>> v; 
  map<int,set<int>> m;
  int votes;
};



/**
 * Runtime complexity: O(candidates * log candidates + votes * log votes)
 */
set<int> australianVoting(vector<vector<int>> &votes) {

  /**
   * Runtime complexity: O(candidates + votes * (log votes + log candidates))
   */
  VoteCounter counter(votes[0].size());
  for (int i=0; i<votes.size(); ++i) {
    counter.addVote(votes[i].back(), i);
    votes[i].pop_back();
  }


  /**
   * Runtime complexity: O(candidates + votes*log votes)
   */
  while (counter.getMaxVotes()*2 <= counter.getTotVotes() && 
         counter.getMaxVotes() > counter.getMinVotes()) {

    auto candToRemove = counter.getCandidatesWithMinVotes();
    for (auto c : candToRemove) {
      auto pendingVotes = counter.removeCandidate(c);
      for (auto v : pendingVotes) {
	while (!votes[v].empty() && !counter.isCandidateValid(votes[v].back())) votes[v].pop_back();
	if (!votes[v].empty()) counter.addVote(votes[v].back(),v);
      }
    }
  }

  return counter.getCandidatesWithMaxVotes();
}



int main() {
  int cases, candidates;
  string tmp;
  cin >> cases;
  while (cases) {
    cin >> candidates;
    vector<string> names(candidates);
    getline(cin,tmp);
    for (int i=0; i<candidates; ++i) {
      getline(cin,names[i]);
    }
    vector<vector<int>> votes;
    while (getline(cin,tmp)) {
      if (tmp.empty()) break;
      istringstream iss(tmp);
      votes.push_back(vector<int>(candidates));
      for (int i=0; i<candidates; ++i) {
	iss >> votes.back()[candidates-1-i];
      }
    }
    auto winners = australianVoting(votes);
    for (auto w : winners) {
      cout << names[w-1] << endl;
    }
    if (cases != 1) cout << endl;
    --cases;
  }
  return 0;
}

