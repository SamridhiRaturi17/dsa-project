ChatDSA — AI Chat Conversation Analyzer
   A DSA Project | C++ | Data Structures & Algorithms
=======================================================

PROJECT OVERVIEW
----------------
ChatDSA is a chat conversation analyzer built using
core Data Structures & Algorithms concepts in C++.

It takes raw chat messages as input and produces:
  - Word Frequency Analysis
  - User Activity Rankings
  - Sentiment Analysis (Positive/Negative/Neutral)
  - Spam Detection
  - Peak Chat Time Analysis

-------------------------------------------------------

INPUT FORMAT
------------
  [HH:MM] Username: message text

Examples:
  [10:01] Alice: Hello everyone!
  [10:02] Bob: This project is amazing
  [10:03] Charlie: buy now buy now buy now

-------------------------------------------------------

DSA CONCEPTS USED
-----------------

Feature          | Data Structure      | Time Complexity
-----------------|---------------------|----------------
Word Frequency   | unordered_map       | O(n) build
Top Words        | vector + sort()     | O(k log k)
User Activity    | unordered_map       | O(n)
Stopword Filter  | unordered_set       | O(1) lookup
Sentiment Check  | unordered_set       | O(1) lookup
Spam Detection   | string::find()      | O(n x m)
Peak Time        | map (BST)           | O(log n) insert

-------------------------------------------------------
