/*
 ============================================================
  src/peak_time.cpp
  DSA Used:
    - map<string,int>  → Red-Black BST
      Keys (hours) stay sorted automatically
      Insert/lookup: O(log n)

  Why map NOT unordered_map?
    We want hours in chronological order (10, 11, 12...)
    map's BST keeps keys sorted automatically — free!
 ============================================================
*/

#include "../include/peak_time.h"

using namespace std;

/*
  peakTimeAnalysis()
  ──────────────────
  Algorithm:
    1. For each message extract hour from "HH:MM"
    2. Increment map[hour]  → O(log h) per insert
    3. Return map (already sorted by BST property)

  Complexity: O(n log h)
    n = messages, h = unique hours
*/
map<string, int> peakTimeAnalysis(const vector<Message>& messages) {

    // BST map — automatically sorted by hour string
    map<string, int> timeMap;

    for (const auto& msg : messages) {

        // Extract hour from "HH:MM"
        size_t colon = msg.time.find(':');

        if (colon != string::npos) {
            string hour = msg.time.substr(0, colon);
            timeMap[hour]++;    // O(log h)
        }
    }

    return timeMap;
}
