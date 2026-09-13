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
  The `can_drain_node` function is a direct variation of the classic **Bin Packing 
  Problem** (specifically, the decision version of Bin Packing with unequal, 
  fixed bin capacities), which is a famous **NP-hard** problem.

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
  **First-Fit Decreasing (FFD)** heuristic.
  - Why it works: Large pods are much harder to place than small pods. If a large 
    pod cannot fit into any node, we fail and backtrack immediately. This "fail-fast" 
    behavior prunes massive sections of the recursion tree early, preventing 
    exponential backtracking.

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
    std::vector<Pod> pods; // Active workloads on this node

    int available_gpus() const {
        return total_gpus - used_gpus;
    }
};

class GPUScheduler {
private:
    std::unordered_map<int, Node> nodes; // Sole source of truth!

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

    // Schedule a pod onto a specific node
    bool schedule_pod(int node_id, const Pod& pod) {
        if (nodes.find(node_id) == nodes.end()) return false;
        if (nodes[node_id].available_gpus() < pod.gpus_required) return false;

        nodes[node_id].used_gpus += pod.gpus_required;
        nodes[node_id].pods.push_back(pod); // Store pod directly inside the Node
        return true;
    }

    // Check if all pods on a target node can be reassigned without moving other workloads
    bool can_drain_node(int drain_node_id) {
        if (nodes.find(drain_node_id) == nodes.end()) return false;

        std::vector<Pod> pods_to_place = nodes[drain_node_id].pods; // Retrieve pods directly from Node
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

    // Populate Node 1 (Node to drain)
    const int pod_id_101 = 101;
    const int pod_101_num_gpus = 4;
    scheduler.schedule_pod(node_id_1, {pod_id_101, pod_101_num_gpus});

    const int pod_id_102 = 102;
    const int pod_102_num_gpus = 3;
    scheduler.schedule_pod(node_id_1, {pod_id_102, pod_102_num_gpus});

    // Populate Node 2 and Node 3 with existing workloads
    const int pod_id_201 = 201;
    const int pod_201_num_gpus = 5;
    scheduler.schedule_pod(node_id_2, {pod_id_201, pod_201_num_gpus}); // 3 GPUs remaining on Node 2

    const int pod_id_301 = 301;
    const int pod_301_num_gpus = 4;
    scheduler.schedule_pod(node_id_3, {pod_id_301, pod_301_num_gpus}); // 4 GPUs remaining on Node 3

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
