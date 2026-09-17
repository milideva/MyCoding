#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/*
  ==============================================================================
  Software Engineer Interview Question: 
  Multi-Tenant GPU Cluster Scheduler with Node Eviction (Drain)
  ==============================================================================

  System Context:
  In large-scale high-performance cloud infrastructure and orchestration systems 
  for distributed AI training and inference, managing GPU resources, allocating 
  workloads to nodes, and safely evicting nodes for cluster maintenance (draining) 
  without disrupting other tenants' workloads is a fundamental infrastructure 
  requirement.

  Problem Description:
  You are designing a custom scheduling agent for a multi-tenant GPU cluster. 
  The cluster contains multiple compute nodes, each equipped with a maximum physical 
  GPU capacity. Tenants deploy workloads inside "Pods", each requesting a specific 
  number of GPUs.

  Implement a `GPUScheduler` class supporting:
  1. `add_node(int node_id, int total_gpus)`:
     Registers a new compute node in the cluster.
  2. `schedule_pod(int node_id, const Pod& pod)`:
     Schedules a pod on a specific node if it has enough available GPUs.
  3. `get_eligible_nodes(int gpus_required)`:
     Finds all nodes that can currently accommodate a new pod of size `gpus_required`.
  4. `can_drain_node(int drain_node_id)`:
     Determines if all pods currently running on the target node can be safely 
     reassigned to the remaining nodes in the cluster.
     - Constraint: You cannot move existing workloads on other nodes. You can only 
       utilize their current idle capacities.

  ==============================================================================
  Mathematical Connection to the Bin Packing Problem
  ==============================================================================
  The `can_drain_node` function is a direct variation of the classic Bin Packing 
  Problem (specifically, the decision version of Bin Packing with unequal, 
  fixed bin capacities), which is a famous NP-hard problem.

  Mapping:
  - Bins -----------------> Candidate remaining nodes (each with a fixed remaining 
                            capacity = total_gpus - used_gpus).
  - Items to Pack --------> Pods being evicted from the drain node (each with a 
                            weight equal to its gpus_required).
  - Bin Capacities -------> Available GPUs on each target node.

  Algorithmic Optimization (First-Fit Decreasing Heuristic):
  Since this problem is NP-complete, there is no polynomial-time solution. We 
  must use Backtracking to explore the state space of O(N^P) placements, where N is 
  the number of candidate nodes and P is the number of evicted pods.
  
  To optimize this, we sort the evicted pods in DESCENDING order of GPU requirements 
  before running our backtracking search. In bin-packing theory, this is the 
  First-Fit Decreasing (FFD) heuristic.
  - Why it works: Large pods are much harder to place than small pods. If a large 
    pod cannot fit into any node, we fail and backtrack immediately. This "fail-fast" 
    behavior prunes massive sections of the recursion tree early, preventing 
    exponential backtracking.

  ==============================================================================
  Why Do We Need Backtracking? Why Pure Recursion (No Backtracking) Fails:
  ==============================================================================
  Recursion is merely the mechanism of traversing down a decision tree, but 
  Backtracking is the act of restoring state when a path hits a dead end. Without 
  restoring state, a wrong choice made early on permanently locks resources.

  Concrete Failure Scenario with Pure Recursion:
  - We have two evicted pods to place:
    1. Pod A (requests 3 GPUs)
    2. Pod B (requests 4 GPUs)
  - We have two available remaining nodes in the cluster:
    * Node 1 (has 4 GPUs available)
    * Node 2 (has 3 GPUs available)

  - Step 1: Place Pod A (3 GPUs).
    * A naive recursive search checks Node 1 first. Since Node 1 has 4 GPUs, Pod A fits!
    * We deduct 3 GPUs from Node 1. Node 1 now has 1 GPU remaining.
  - Step 2: Place Pod B (4 GPUs).
    * The recursion moves to Pod B. It checks Node 1 (1 GPU left) -> doesn't fit.
    * It checks Node 2 (3 GPUs left) -> doesn't fit.
    * This recursive branch fails and returns `false`.

  - Step 3 (Where Pure Recursion vs. Backtracking diverges):
    * If we used pure recursion (without state restoration), the algorithm would return `false`. 
      Node 1 remains locked with only 1 GPU available. The algorithm exits and incorrectly 
      claims draining is impossible, even though we could have placed Pod A on Node 2 and Pod B on Node 1.
    * With Backtracking (the "un-choose" step), when Pod B returns `false`, Level 0 catches the 
      failure, undoes Pod A's allocation on Node 1 (adds 3 GPUs back), and proceeds to try the next 
      eligible node for Pod A (Node 2). This allows Pod A to be placed on Node 2 and Pod B on Node 1, 
      correctly returning `true`!

  How we avoid choosing the same choice again after unchoosing?
  ------------------------------------------------------------
  We prevent repeating a failed choice through two structural properties of the algorithm:
  1. Loop State Progress (Horizontal traversal):
     Within a single recursive stack frame (representing a single pod placement decision), 
     we use a `for` loop to iterate through the list of remaining candidate nodes:
         for (auto& node : candidate_nodes) { ... }
     When we choose candidate_nodes[0], recurse, and subsequently backtrack (un-choose), 
     the `for` loop naturally increments to the next index, trying candidate_nodes[1]. 
     The loop index itself acts as our memory to prevent repeating the same choice.
  2. Index State Progress (Vertical traversal):
     When recursing, we advance the `pod_index` argument (`pod_index + 1`). This ensures 
     we are moving forward to the next pod in the eviction list, preventing the algorithm 
     from attempting to re-place the same pod within the current path.

  ==============================================================================
  Complexity Analysis:
  ==============================================================================
  1. `get_eligible_nodes`:
     - Time Complexity: O(N) where N is the number of nodes in the cluster. We 
       iterate through all nodes once.
     - Space Complexity: O(N) worst-case to return eligible node IDs.

  2. `can_drain_node` (Backtracking + First-Fit Decreasing):
     - Time Complexity: O(N^P) worst-case, where N is candidate nodes and P is 
       evicted pods. In practice, the FFD heuristic prunes the search space 
       such that average execution is highly efficient.
     - Space Complexity: O(P + N) due to the recursive stack depth bounded by P 
       and local node state copies stored in candidate list.

  3. `add_node` & `schedule_pod`:
     - Time Complexity: O(1) average-case.
     - Space Complexity: O(1) auxiliary space.
  ==============================================================================
*/

struct Pod {
    int id;
    int gpus_required;
};

struct Node {
    int id;
    int total_gpus;
    int used_gpus;
    std::vector<int> pod_ids; // Active workloads (by ID) on this node

    int available_gpus() const {
        return total_gpus - used_gpus;
    }
};

class GPUScheduler {
private:
    std::unordered_map<int, Node> nodes; // Sole source of truth for Nodes!
    std::unordered_map<int, Pod> pods;   // Sole source of truth for Pod registrations!

    // Helper function for backtracking placement during drain
    bool can_place_pods(size_t pod_index, 
                        const std::vector<Pod>& pods_to_place, 
                        std::vector<Node>& candidate_nodes) {
        if (pod_index == pods_to_place.size()) {
            return true; // All pods successfully reassigned
        }

        const auto& pod = pods_to_place[pod_index];

        for (auto& node : candidate_nodes) {
            if (node.available_gpus() >= pod.gpus_required) {
                // Place pod temporarily (Choose)
                node.used_gpus += pod.gpus_required;

                // Recurse to place the remaining pods (Explore)
                if (can_place_pods(pod_index + 1, pods_to_place, candidate_nodes)) {
                    return true;
                }

                // Backtrack if placement failed (Un-choose)
                node.used_gpus -= pod.gpus_required;
            }
        }

        return false;
    }

public:
    void add_node(int node_id, int total_gpus) {
        nodes[node_id] = {node_id, total_gpus, 0, {}};
    }

    bool add_pod(int pod_id, int gpus_required) {
        if (pods.find(pod_id) != pods.end()) return false; // Already registered
        pods[pod_id] = {pod_id, gpus_required};
        return true;
    }

    // Return list of Node IDs that can accommodate a new pod
    std::vector<int> get_eligible_nodes(int gpus_required) const {
        std::vector<int> eligible_nodes;
        for (const auto& [id, node] : nodes) {
            if (node.available_gpus() >= gpus_required) {
                eligible_nodes.push_back(id);
            }
        }
        return eligible_nodes;
    }

    // Schedule a registered pod onto a specific node
    bool schedule_pod(int node_id, int pod_id) {
        if (nodes.find(node_id) == nodes.end()) return false;
        if (pods.find(pod_id) == pods.end()) return false; // Pod must be registered first

        const auto& pod = pods[pod_id];
        if (nodes[node_id].available_gpus() < pod.gpus_required) return false;

        nodes[node_id].used_gpus += pod.gpus_required;
        nodes[node_id].pod_ids.push_back(pod_id); // Store only the Pod ID inside the Node
        return true;
    }

    // Check if all pods on a target node can be reassigned without moving other workloads
    bool can_drain_node(int drain_node_id) {
        if (nodes.find(drain_node_id) == nodes.end()) return false;

        // Reconstruct Pod objects to place from scheduled pod_ids on the drain node
        std::vector<Pod> pods_to_place;
        for (int pod_id : nodes[drain_node_id].pod_ids) {
            pods_to_place.push_back(pods[pod_id]);
        }

        if (pods_to_place.empty()) return true; // Nothing to move

        // Sort pods descending by required GPUs to prune the search space faster
        std::sort(pods_to_place.begin(), pods_to_place.end(), [](const Pod& a, const Pod& b) {
            return a.gpus_required > b.gpus_required;
        });

        // Collect remaining candidate nodes
        std::vector<Node> candidate_nodes;
        for (const auto& [id, node] : nodes) {
            if (id != drain_node_id) {
                candidate_nodes.push_back(node);
            }
        }

        return can_place_pods(0, pods_to_place, candidate_nodes);
    }
};

int main() {
    GPUScheduler scheduler;

    // Cluster setup: 3 nodes with 8 GPUs each
    const int node_id_1 = 1;
    const int node_id_2 = 2;
    const int node_id_3 = 3;
    const int node_num_gpus = 8;

    scheduler.add_node(node_id_1, node_num_gpus);
    scheduler.add_node(node_id_2, node_num_gpus);
    scheduler.add_node(node_id_3, node_num_gpus);

    // Register Pod definitions
    const int pod_id_101 = 101;
    const int pod_101_num_gpus = 4;
    scheduler.add_pod(pod_id_101, pod_101_num_gpus);

    const int pod_id_102 = 102;
    const int pod_102_num_gpus = 3;
    scheduler.add_pod(pod_id_102, pod_102_num_gpus);

    const int pod_id_201 = 201;
    const int pod_201_num_gpus = 5;
    scheduler.add_pod(pod_id_201, pod_201_num_gpus);

    const int pod_id_301 = 301;
    const int pod_301_num_gpus = 4;
    scheduler.add_pod(pod_id_301, pod_301_num_gpus);

    // Schedule Pods on respective Nodes
    scheduler.schedule_pod(node_id_1, pod_id_101);
    scheduler.schedule_pod(node_id_1, pod_id_102);
    scheduler.schedule_pod(node_id_2, pod_id_201); // 3 GPUs remaining on Node 2
    scheduler.schedule_pod(node_id_3, pod_id_301); // 4 GPUs remaining on Node 3

    // Check eligible nodes for a new 4-GPU request
    const int request_num_gpus = 4;
    std::vector<int> eligible = scheduler.get_eligible_nodes(request_num_gpus);
    std::cout << "Eligible nodes for " << request_num_gpus << "-GPU pod: ";
    for (int id : eligible) std::cout << id << " ";
    std::cout << "\n";

    // Check if Node 1 can be drained
    bool can_drain = scheduler.can_drain_node(node_id_1);
    std::cout << "Can drain Node " << node_id_1 << "? " << (can_drain ? "Yes" : "No") 
              << " (Expected: Yes - Pod 101 goes to Node 3, Pod 102 goes to Node 2)\n";

    return 0;
}
