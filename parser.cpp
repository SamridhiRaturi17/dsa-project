/*
 ============================================================
  src/parser.cpp
  Parses raw chat text into structured Message objects
  DSA Used: string::find(), substr(), vector<Message>
 ============================================================
*/

#include "../include/parser.h"
#include <sstream>

using namespace std;

// Remove leading/trailing whitespace
string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

/*
  parseMessages()
  ───────────────
  Input : raw multi-line string
  Output: vector<Message>

  Format expected per line:
    [HH:MM] Username: message text

  Algorithm:
    1. Split raw string by newline
    2. For each line:
       a. Find ']'  → extract time
       b. Find ':'  → extract user and text
       c. Skip invalid lines silently
    3. Push valid Message into vector

  Complexity: O(n × L)
    n = number of lines
    L = average line length
*/
vector<Message> parseMessages(const string& raw) {

    vector<Message> messages;
    istringstream stream(raw);
    string line;

    while (getline(stream, line)) {

        line = trim(line);

        // Skip empty lines or lines not starting with [
        if (line.empty() || line[0] != '[') continue;

        // Find closing bracket ]
        size_t closeB = line.find(']');
        if (closeB == string::npos) continue;

        // Extract time → between [ and ]
        string time = trim(line.substr(1, closeB - 1));

        // Everything after ]
        string rest = trim(line.substr(closeB + 1));

        // Find colon : to split user and text
        size_t colon = rest.find(':');
        if (colon == string::npos) continue;

        string user = trim(rest.substr(0, colon));
        string text = trim(rest.substr(colon + 1));

        // Only add if both user and text exist
        if (!user.empty() && !text.empty())
            messages.push_back({ time, user, text });
    }

    return messages;
}
