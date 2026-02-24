/*
 ============================================================
  ChatDSA — main.cpp
  Entry point: reads input, runs DSA pipeline, prints report
 ============================================================
*/

#include <iostream>
#include <fstream>
#include <sstream>

#include "../include/parser.h"
#include "../include/word_frequency.h"
#include "../include/user_activity.h"
#include "../include/sentiment.h"
#include "../include/spam_detector.h"
#include "../include/peak_time.h"
#include "../include/reporter.h"

using namespace std;

int main(int argc, char* argv[]) {

    string raw = "";

    // ── Read from file if given, else manual input ──────────
    if (argc >= 2) {

        ifstream file(argv[1]);

        if (!file.is_open()) {
            cerr << "[ERROR] Cannot open file: " << argv[1] << "\n";
            return 1;
        }

        ostringstream ss;
        ss << file.rdbuf();
        raw = ss.str();

        cout << "[INFO] Reading from: " << argv[1] << "\n";

    } else {

        cout << "╔══════════════════════════════════════════════════════╗\n";
        cout << "║         ChatDSA — AI Chat Conversation Analyzer     ║\n";
        cout << "╚══════════════════════════════════════════════════════╝\n\n";
        cout << "Paste chat log. Format: [HH:MM] User: message\n";
        cout << "Type END on a new line when done:\n\n";

        string line = "";
        while (getline(cin, line)) {
            if (line == "END") break;
            raw += line + "\n";
        }
    }

    // ── Run DSA Pipeline ─────────────────────────────────────
    cout << "\n[INFO] Parsing messages...\n";

    vector<Message> messages = parseMessages(raw);

    if (messages.empty()) {
        cerr << "[ERROR] No valid messages found.\n";
        cerr << "        Format: [HH:MM] Username: message text\n";
        return 1;
    }

    cout << "[INFO] Running analysis on " << messages.size() << " messages...\n\n";

    vector<pair<string,int>> words   = wordFrequency(messages);
    vector<pair<string,int>> users   = userActivity(messages);
    SentimentResult          sent    = analyzeSentiment(messages);
    vector<SpamMessage>      spam    = detectSpam(messages);
    map<string,int>          timeMap = peakTimeAnalysis(messages);

    // ── Print Report ─────────────────────────────────────────
    printReport(messages, words, users, sent, spam, timeMap);

    return 0;
}
