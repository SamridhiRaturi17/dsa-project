/*
 ============================================================
  src/user_activity.cpp
  DSA Used:
    - unordered_map<string,int>  → count messages per user
    - vector<pair<string,int>>   → sortable ranking list
    - sort() with lambda         → O(u log u)
 ============================================================
*/

#include "../include/user_activity.h"
#include <algorithm>

using namespace std;

/*
  userActivity()
  ──────────────
  Algorithm:
    1. Loop all messages
    2. Increment userMap[username]  → O(1) average
    3. Dump map to vector
    4. Sort descending by count     → O(u log u)

  Complexity: O(n + u log u)
    n = total messages
    u = unique users
*/
vector<pair<string, int>> userActivity(const vector<Message>& messages) {

    // HashMap: username → message count
    unordered_map<string, int> userMap;

    for (const auto& msg : messages) {
        userMap[msg.user]++;    // O(1) average
    }

    // Dump to vector for sorting
    vector<pair<string, int>> sorted(userMap.begin(), userMap.end());

    // Sort descending — most active user first
    sort(sorted.begin(), sorted.end(),
        [](const pair<string,int>& a, const pair<string,int>& b) {
            return b.second < a.second;
        });

    return sorted;
}
