/**
 * Problem: Average of Top 5 Test Scores
 * Given a list of test results (score, student_id, date), find the 
 * average of the top 5 scores for each student.
 * 
 * Strategy: Hash Map + Min-Heap of size K (K=5)
 * - Use a map to store student_id -> min_heap of scores.
 * - For each test result:
 *   - If the student's heap has fewer than 5 scores, add the score.
 *   - If the heap is full and the current score is higher than the minimum 
 *     (top of min-heap), replace the minimum with the current score.
 * - After processing all results, calculate the average for each student.
 * 
 * Time Complexity: O(N log K) where K=5. Since K is small, effectively O(N).
 * Space Complexity: O(Unique Students * K).
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>

using namespace std;

struct TestResult {
    int score;
    int student_id;
    string date;
};

class Solution {
public:
    /**
     * Calculates the average of top 5 scores for each student.
     */
    unordered_map<int, double> getTopFiveAverages(const vector<TestResult>& results) {
        // Map: student_id -> Min-Heap of top 5 scores
        unordered_map<int, priority_queue<int, vector<int>, greater<int>>> studentScores;

        for (const auto& res : results) {
            auto& pq = studentScores[res.student_id];
            if (pq.size() < 5) {
                pq.push(res.score);
            } else if (res.score > pq.top()) {
                pq.pop();
                pq.push(res.score);
            }
        }

        unordered_map<int, double> averages;
        for (auto& [id, pq] : studentScores) {
            double sum = 0;
            int count = pq.size();
            while (!pq.empty()) {
                sum += pq.top();
                pq.pop();
            }
            averages[id] = sum / count;
        }

        return averages;
    }
};

int main() {
    vector<TestResult> results = {
        {50, 1, "2013-05-14"}, {89, 2, "2012-03-25"}, {70, 3, "2010-12-07"},
        {60, 1, "2013-08-09"}, {99, 2, "2011-09-11"}, {100, 4, "2011-07-04"},
        {38, 1, "2014-01-28"}, {46, 1, "2012-11-15"}, {90, 1, "2015-01-01"},
        {80, 1, "2015-02-01"}
    };

    Solution sol;
    auto averages = sol.getTopFiveAverages(results);

    cout << "Top 5 Averages per Student:" << endl;
    for (auto const& [id, avg] : averages) {
        cout << "Student ID " << id << ": " << avg << endl;
    }

    return 0;
}
