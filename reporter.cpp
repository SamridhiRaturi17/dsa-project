/*
 ============================================================
  src/reporter.cpp
  Prints formatted analytics report to console
 ============================================================
*/

#include "../include/reporter.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

// Print ASCII bar chart
void printBar(int value, int maxVal, int maxLen = 28) {
    int filled = (maxVal > 0) ? (value * maxLen / maxVal) : 0;
    cout << "[";
    for (int i = 0; i < maxLen; i++) {
        cout << (i < filled ? '#' : '-');
    }
    cout << "] " << value;
}

// Print section header box
void printHeader(const string& title) {
    cout << "\n╔══════════════════════════════════════════════════════╗\n";
    cout << "║  " << left << setw(52) << title << "║\n";
    cout << "╚══════════════════════════════════════════════════════╝\n";
}

void printReport(
    const vector<Message>&              messages,
    const vector<pair<string,int>>&     words,
    const vector<pair<string,int>>&     users,
    const SentimentResult&              sent,
    const vector<SpamMessage>&          spam,
    const map<string,int>&              timeMap
) {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════╗\n";
    cout << "║        ChatDSA — Conversation Analytics Report       ║\n";
    cout << "╚══════════════════════════════════════════════════════╝\n";

    // ── OVERVIEW ─────────────────────────────────────────────
    printHeader("OVERVIEW");
    cout << "  Total Messages   : " << messages.size() << "\n";
    cout << "  Unique Users     : " << users.size()    << "\n";
    cout << "  Spam Detected    : " << spam.size()     << " message(s)\n";
    cout << "  Positive Msgs    : " << sent.pos        << "\n";
    cout << "  Negative Msgs    : " << sent.neg        << "\n";
    cout << "  Neutral Msgs     : " << sent.neu        << "\n";

    if (!users.empty())
        cout << "  Most Active User : " << users[0].first
             << " (" << users[0].second << " messages)\n";

    if (!words.empty())
        cout << "  Top Word         : \"" << words[0].first
             << "\" (used " << words[0].second << "x)\n";

    string mood = (sent.pos > sent.neg) ? "POSITIVE :)" :
                  (sent.neg > sent.pos) ? "NEGATIVE :(" : "NEUTRAL  :|";
    cout << "  Overall Mood     : " << mood << "\n";

    // ── WORD FREQUENCY ────────────────────────────────────────
    printHeader("WORD FREQUENCY  [unordered_map + vector + sort]");
    int topN    = min((int)words.size(), 10);
    int maxFreq = topN > 0 ? words[0].second : 1;

    for (int i = 0; i < topN; i++) {
        cout << "  " << left << setw(16) << words[i].first << " ";
        printBar(words[i].second, maxFreq);
        cout << "\n";
    }
    if (words.empty()) cout << "  (no significant words found)\n";

    // ── USER ACTIVITY ─────────────────────────────────────────
    printHeader("USER ACTIVITY  [unordered_map + sort]");
    int maxMsgs = users.empty() ? 1 : users[0].second;

    for (const pair<string,int>& u : users) {
        cout << "  " << left << setw(14) << u.first << " ";
        printBar(u.second, maxMsgs);
        cout << "\n";
    }

    // ── SENTIMENT ─────────────────────────────────────────────
    printHeader("SENTIMENT ANALYSIS  [unordered_set O(1) lookup]");
    int total = sent.pos + sent.neg + sent.neu;

    if (total > 0) {
        int posW = sent.pos * 20 / total;
        int neuW = sent.neu * 20 / total;
        int negW = 20 - posW - neuW;

        cout << "  [";
        for (int i = 0; i < posW; i++) cout << '+';
        for (int i = 0; i < neuW; i++) cout << '~';
        for (int i = 0; i < negW; i++) cout << '-';
        cout << "]\n";

        cout << "   + Positive (" << sent.pos << ")  "
             << " ~ Neutral (" << sent.neu << ")  "
             << " - Negative (" << sent.neg << ")\n";
    }

    // ── SPAM ──────────────────────────────────────────────────
    printHeader("SPAM DETECTION  [string::find + word ratio]");

    if (spam.empty()) {
        cout << "  [OK] No spam detected.\n";
    } else {
        for (const SpamMessage& s : spam) {
            cout << "  [" << setw(12) << s.reason << "] "
                 << "[" << s.time << "] "
                 << s.user << ": " << s.text << "\n";
        }
    }

    // ── PEAK TIME ─────────────────────────────────────────────
    printHeader("PEAK CHAT TIME  [map BST — sorted keys]");

    if (timeMap.empty()) {
        cout << "  No time data available.\n";
    } else {
        int maxT = 0;
        string peakHour = "";

        for (const auto& t : timeMap) {
            if (t.second > maxT) {
                maxT     = t.second;
                peakHour = t.first;
            }
        }

        for (const auto& t : timeMap) {
            cout << "  " << t.first << ":00 ";
            printBar(t.second, maxT, 20);
            if (t.first == peakHour) cout << "  << PEAK";
            cout << "\n";
        }
    }

    // ── DSA SUMMARY ───────────────────────────────────────────
    printHeader("DSA CONCEPTS SUMMARY");
    cout << "  unordered_map  → word_freq, user_count    O(1) avg\n";
    cout << "  unordered_set  → stopwords, sentiment      O(1) lookup\n";
    cout << "  vector<pair>   → sortable rankings         O(1) push\n";
    cout << "  sort(lambda)   → top-K words, users        O(n log n)\n";
    cout << "  string::find() → spam pattern matching     O(n x m)\n";
    cout << "  map (BST)      → ordered time slots        O(log n)\n";

    cout << "\n══════════════════════════════════════════════════════\n";
    cout << "  Done. " << messages.size() << " messages processed.\n";
    cout << "══════════════════════════════════════════════════════\n\n";
}
