/**
 * @file rate_limiter.c++
 * @brief Thread-safe Sliding Window Log Rate Limiter implementation in C++.
 *
 * This component implements a Sliding Window Log rate limiter, which tracks
 * the exact timestamps of individual requests per client and evicts outdated
 * timestamps outside the sliding time window. It prevents bursts of traffic
 * and guarantees a strict rate limit.
 *
 * ============================================================================
 * System Design Question / Problem Statement:
 * ============================================================================
 * Question: How do you design a thread-safe rate limiter in C++?
 *
 * Requirements & Constraints:
 *   - Input Parameters:
 *       - clientId (string): Unique identifier representing the user or client (e.g., "ClientA").
 *       - currentTimestampMs (long long): The current epoch time in milliseconds (e.g., 1234).
 *   - Output:
 *       - Return true (ALLOW) or false (DENY) based on whether the request falls within the allowed threshold.
 *   - Configuration:
 *       - RateLimiter is initialized with:
 *           - maxRequests: Maximum requests allowed (e.g., 30 requests).
 *           - windowSizeMs: The sliding time window size in milliseconds (e.g., 500 ms).
 *   - Example:
 *       - Allow 30 requests in a 500 ms sliding window for "ClientA".
 *
 * ============================================================================
 * Complexity Analysis:
 * ============================================================================
 * Time Complexity (allowRequest):
 *   - Worst-Case: O(N)
 *     Where N is the number of timestamps currently stored in the client's window.
 *     In the worst-case scenario, all previously recorded requests are outdated and
 *     must be popped from the front of the deque.
 *   - Amortized / Average-Case: O(1)
 *     Since each request timestamp is pushed to the deque once and popped at most
 *     once, the amortized cost per request is constant.
 *
 * Space Complexity:
 *   - Worst-Case: O(M * N)
 *     Where M is the number of distinct clientIds and N is the maximum requests
 *     allowed per sliding window (maxRequests) stored in memory.
 * ============================================================================
 */

#include <iostream>
#include <unordered_map>
#include <deque>
#include <mutex>
#include <string>

using namespace std;

class RateLimiter {
private:
    int maxRequests;
    long long windowSizeMs;
    
    // Maps clientId -> deque of timestamps (in milliseconds)
    std::unordered_map<std::string, std::deque<long long>> clientRequests;
    std::mutex mtx; // Ensures thread safety across multiple requests

public:
    /**
     * @brief Construct a new Rate Limiter object.
     * 
     * @param maxReqs Maximum number of requests allowed in the window.
     * @param windowMs The duration of the sliding window in milliseconds.
     */
    RateLimiter(int maxReqs, long long windowMs)
        : maxRequests(maxReqs), windowSizeMs(windowMs) {}

    /**
     * @brief Evaluates whether a client's request is allowed under the rate limit.
     * 
     * ============================================================================
     * Complexity Analysis:
     * ============================================================================
     * Time Complexity:
     *   - Amortized: O(1)
     *   - Worst-Case: O(N) where N is the current size of the timestamps list.
     * Space Complexity:
     *   - O(1) auxiliary space (modifies existing deque in-place).
     * ============================================================================
     * 
     * @param clientId Unique identifier for the client making the request.
     * @param currentTimestampMs The current timestamp of the request in milliseconds.
     * @return true if the request is within the limit and allowed, false otherwise.
     */
    bool allowRequest(const std::string& clientId, long long currentTimestampMs) {
        std::lock_guard<std::mutex> lock(mtx);

        auto& timestamps = clientRequests[clientId];

        // 1. Evict timestamps outside the current sliding window
        long long windowStart = currentTimestampMs - windowSizeMs;
        while (!timestamps.empty() && timestamps.front() <= windowStart) {
            timestamps.pop_front();
        }

        // 2. Check if client has exceeded capacity
        if (timestamps.size() < static_cast<size_t>(maxRequests)) {
            timestamps.push_back(currentTimestampMs);
            return true; // ALLOW
        }

        return false; // DENY
    }
};

int main() {
    // Limit: Allow 30 requests within a 500 ms window
    RateLimiter limiter(30, 500);

    std::string clientA = "ClientA";

    // Simulate 32 requests at timestamp 1234 ms
    for (int i = 1; i <= 32; ++i) {
        bool allowed = limiter.allowRequest(clientA, 1234);
        std::cout << "Request " << i << " at 1234ms: " 
                  << (allowed ? "ALLOW" : "DENY") << "\n";
    }

    // Simulate a request after the 500ms window has passed (1234 + 501 = 1735)
    bool allowedAfterWindow = limiter.allowRequest(clientA, 1735);
    std::cout << "Request at 1735ms: " 
              << (allowedAfterWindow ? "ALLOW" : "DENY") << "\n";

    return 0;
}
