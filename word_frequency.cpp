/*
 ============================================================
  src/word_frequency.cpp
  DSA Used:
    - unordered_map<string,int>  → O(1) avg insert/lookup
    - unordered_set<string>      → O(1) stopword check
    - vector<pair<string,int>>   → sortable container
    - sort() with lambda         → O(n log n)
 ============================================================
*/

#include "../include/word_frequency.h"
#include <algorithm>
#include <cctype>

using namespace std;

// ── Stopwords Set ─────────────────────────────────────────
// Common words with no meaning — skip these during counting
const unordered_set<string> STOPWORDS = {
    "a","an","the","is","it","in","on","at","to","of","and","or",
    "but","for","with","this","that","was","are","be","been","have",
    "has","had","do","did","will","would","could","should","i","you",
    "he","she","we","they","my","your","his","her","our","their","its",
    "me","him","us","them","what","which","who","how","when","where",
    "why","not","no","so","if","as","by","from","up","out","im","ive",
    "just","very","can","get","got","let","hey","okay","yes","yeah"
};

// Convert string to lowercase
string toLowerWF(const string& s) {
    string r = s;
    for (char& c : r) c = tolower(c);
    return r;
}

/*
  wordFrequency()
  ───────────────
  Algorithm:
    1. Loop every message
    2. Scan each character to extract words
    3. Skip stopwords using unordered_set  → O(1)
    4. Increment count in unordered_map    → O(1)
    5. Dump map into vector<pair>
    6. Sort descending by count            → O(k log k)

  Complexity:
    Build map : O(n × L)
    Sort      : O(k log k)
*/
vector<pair<string, int>> wordFrequency(const vector<Message>& messages) {

    // HashMap: word → frequency count
    unordered_map<string, int> freq;

    for (const auto& msg : messages) {

        string word  = "";
        string lower = toLowerWF(msg.text);

        for (char c : lower) {

            if (isalpha(c)) {
                // Build word character by character
                word += c;

            } else {
                // Word boundary hit (space, comma, etc.)
                if (word.size() > 2 &&
                    STOPWORDS.find(word) == STOPWORDS.end()) {
                    freq[word]++;   // O(1) average
                }
                word = "";  // Reset for next word
            }
        }

        // Check last word in message
        if (word.size() > 2 &&
            STOPWORDS.find(word) == STOPWORDS.end()) {
            freq[word]++;
        }
    }

    // Dump map into vector (map cannot be sorted directly)
    vector<pair<string, int>> sorted(freq.begin(), freq.end());

    // Sort descending by count using lambda
    sort(sorted.begin(), sorted.end(),
        [](const pair<string,int>& a, const pair<string,int>& b) {
            return b.second < a.second;
        });

    return sorted;
}
