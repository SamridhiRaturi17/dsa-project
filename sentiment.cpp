/*
 ============================================================
  src/sentiment.cpp
  DSA Used:
    - unordered_set<string>  → O(1) word membership check
 ============================================================
*/

#include "../include/sentiment.h"
#include <cctype>

using namespace std;

// ── Positive Word Set ─────────────────────────────────────
const unordered_set<string> POSITIVE_WORDS = {
    "amazing","great","awesome","love","happy","excellent","good",
    "best","nice","fantastic","wonderful","super","brilliant","perfect",
    "beautiful","glad","thanks","thank","cool","wow","impressive",
    "incredible","outstanding","helpful","enjoy","loved"
};

// ── Negative Word Set ─────────────────────────────────────
const unordered_set<string> NEGATIVE_WORDS = {
    "bad","hate","awful","terrible","horrible","worst","ugly","sad",
    "angry","disgusting","disappointing","sucks","boring","wrong",
    "fail","failed","useless","stupid","dumb","rubbish","trash",
    "spam","stop","annoying","waste","pathetic"
};

// Convert to lowercase
string toLowerSent(const string& s) {
    string r = s;
    for (char& c : r) c = tolower(c);
    return r;
}

/*
  analyzeSentiment()
  ──────────────────
  Algorithm (per message):
    1. Extract each word
    2. Check POSITIVE_WORDS → O(1)
    3. Check NEGATIVE_WORDS → O(1)
    4. Compare counts → classify message
    5. Accumulate totals

  Complexity: O(n × L)
*/
SentimentResult analyzeSentiment(const vector<Message>& messages) {

    SentimentResult result = {0, 0, 0};

    for (const auto& msg : messages) {

        int pos  = 0;
        int neg  = 0;
        string word  = "";
        string lower = toLowerSent(msg.text);

        for (char c : lower) {
            if (isalpha(c)) {
                word += c;
            } else {
                if (!word.empty()) {
                    if (POSITIVE_WORDS.count(word)) pos++;  // O(1)
                    if (NEGATIVE_WORDS.count(word)) neg++;  // O(1)
                    word = "";
                }
            }
        }

        // Last word
        if (!word.empty()) {
            if (POSITIVE_WORDS.count(word)) pos++;
            if (NEGATIVE_WORDS.count(word)) neg++;
        }

        // Classify this message
        if      (pos > neg) result.pos++;
        else if (neg > pos) result.neg++;
        else                result.neu++;
    }

    return result;
}
