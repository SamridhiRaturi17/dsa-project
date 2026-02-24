/*
 ============================================================
  src/spam_detector.cpp
  DSA Used:
    - string::find()            → pattern search O(n × m)
    - unordered_map<string,int> → word repeat count O(1)
 ============================================================
*/

#include "../include/spam_detector.h"
#include <unordered_map>
#include <algorithm>
#include <cctype>

using namespace std;

// Known spam phrases
vector<string> SPAM_PATTERNS = {
    "buy now", "click here", "free money", "limited offer",
    "act now", "win now", "subscribe now", "promo code",
    "earn money", "work from home"
};

// Convert to lowercase
string toLowerSpam(const string& s) {
    string r = s;
    for (char& c : r) c = tolower(c);
    return r;
}

/*
  detectSpam()
  ────────────
  Stage 1 — Pattern Matching:
    Check if message contains known spam phrases
    string::find() → O(n × m)

  Stage 2 — Flood Detection:
    Word repetition ratio > 40% → FLOOD
    unordered_map word count → O(1)
*/
vector<SpamMessage> detectSpam(const vector<Message>& messages) {

    vector<SpamMessage> spamList;

    for (const auto& msg : messages) {

        string lower   = toLowerSpam(msg.text);
        bool   flagged = false;
        string reason  = "";

        // ── Stage 1: Pattern Matching ─────────────────────
        for (const string& pattern : SPAM_PATTERNS) {
            if (lower.find(pattern) != string::npos) {
                flagged = true;
                reason  = "SPAM PATTERN";
                break;
            }
        }

        // ── Stage 2: Flood Detection ──────────────────────
        if (!flagged) {

            unordered_map<string, int> wordCount;
            string word      = "";
            int    totalWords = 0;

            for (char c : lower) {
                if (isalpha(c)) {
                    word += c;
                } else if (!word.empty()) {
                    wordCount[word]++;
                    totalWords++;
                    word = "";
                }
            }
            if (!word.empty()) {
                wordCount[word]++;
                totalWords++;
            }

            // Find most repeated word
            int maxRepeat = 0;
            for (const auto& p : wordCount) {
                maxRepeat = max(maxRepeat, p.second);
            }

            // If any word is > 40% of message → flood spam
            if (totalWords > 3 &&
                (double)maxRepeat / totalWords > 0.40) {
                flagged = true;
                reason  = "FLOOD";
            }
        }

        if (flagged) {
            spamList.push_back({ msg.time, msg.user, msg.text, reason });
        }
    }

    return spamList;
}
