#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/*
  Problem: Depth-First Search (DFS) Traversal

  Problem Description:
  Implement Depth-First Search (DFS) traversal for a given graph. 
  The traversal should be able to explore all nodes reachable from a 
  starting vertex. Both recursive and iterative implementations are 
  provided.

  Algorithm 1: Recursive DFS
  - Standard backtracking-style traversal. Marks a node as visited and 
    recursively visits unvisited neighbors.

  Algorithm 2: Iterative DFS
  - Uses a manual stack to simulate recursion. 
  - Note: The order of neighbor processing is reversed compared to 
    recursion unless neighbors are pushed in reverse order.

  Complexity Analysis:
  - Time Complexity: O(V + E)
    Reason: In a graph with V vertices and E edges, DFS visits every vertex 
    once and explores every edge exactly twice (for undirected graphs).
  - Space Complexity: O(V)
    Reason: In the worst case (a line graph), the recursion stack or manual 
    stack can hold all V vertices.

  Alternative Approaches:
  - Breadth-First Search (BFS): Uses a queue. Finds the shortest path in 
    unweighted graphs.
    - Time: O(V + E), Space: O(V).
  - Comparison: DFS is better for exhaustive searches, finding cycles, 
    and topological sorting. BFS is better for shortest path problems.

  Brute Force comparison:
  - A brute force search for reachability between two nodes without 
    tracking 'visited' state would lead to infinite loops in graphs 
    with cycles. The O(V+E) DFS is the optimized standard.
*/

typedef struct node_tag node_t;
struct node_tag {
    int vertex;
    bool visited;
    unsigned int num_edges;
    struct node_tag *edges[0]; // edges are assumed bi-directional.
};

typedef struct graph_tag graph_t;
struct graph_tag {
    int num_vertices; // how many in this graph populated
    int max_edges; // per vertex
    int max_vertices; // max in this graph
    node_t *vertices[0]; // size max_vertices
};

node_t *get_vertex (graph_t *graph, int index) {
    if (!graph) return NULL;
    int i, max = graph->max_vertices;
    for (i = 0; i< max; i++) {
        node_t *node = graph->vertices[i];
        if (node && node->vertex == index) {
            printf("get_vertex():%d \n", index);
            return node;
        }
    }
    return NULL;
}

bool find_edge (graph_t *graph, int src_index, int dst_index) {

    if (!graph) return false;

    node_t *src = get_vertex(graph, src_index);
    if (!src) {
        return false;
    }

    node_t *dst = get_vertex(graph, dst_index);
    if (!dst) {
        return false;
    }

    if (!src || !dst) return false;

    for (int i = 0; i < graph->max_edges; i++) {
        node_t *to = src->edges[i];
        if (to && (to == dst)) {
            return true;
        }
    }
    return false;
}

graph_t *create_graph (int max_vertices, int max_edges) {
    if (!max_vertices || !max_edges) return NULL;
    graph_t *graph = calloc(1, sizeof(*graph) + max_vertices * sizeof(graph->vertices[0]));
    if (!graph) return NULL;
    graph->max_vertices = max_vertices;
    graph->max_edges = max_edges;
    printf("Created Graph max_vertices:%d max_edges/vertex:%d \n", max_vertices, max_edges); 
    return graph;
}

node_t *create_vertex (graph_t *graph, int index) {
    if (graph->num_vertices == graph->max_vertices) 
        return NULL;

    node_t *node = calloc(1, sizeof(*node) + sizeof(node->edges[0]) * graph->max_edges );
    if (!node) return NULL;

    node->vertex = index;
    printf("Created Vertex : %d \n", index);
    graph->vertices[graph->num_vertices] = node;
    graph->num_vertices++;

    return node;
}

bool add_edge (graph_t *graph, int src_index, int dst_index) {

    if (!graph) return false;

    node_t *src = get_vertex(graph, src_index);
    if (!src) {
        src = create_vertex(graph, src_index);
    }
    node_t *dst = get_vertex(graph, dst_index);
    if (!dst) {
        dst = create_vertex(graph, dst_index);
    }

    if (!src || !dst) return false;

    if (src->num_edges >= graph->max_edges) return false;
    if (dst->num_edges >= graph->max_edges) return false;

    /* Duplicate edge is not checked for*/
    
    src->edges[src->num_edges] = dst;
    src->num_edges++;

    dst->edges[dst->num_edges] = src;
    dst->num_edges++;

    printf("Created Edge %d <---> %d\n", src_index, dst_index);

    return true;
}

/*

procedure DFS(G, v) is
    label v as discovered
    for all directed edges from v to w that are in G.adjacentEdges(v) do
        if vertex w is not labeled as discovered then
            recursively call DFS(G, w)
*/
bool dfs (graph_t *graph, int src_index, int dst_index) {
    if (!graph) return false;
    
    node_t *src, *dst;

    src = get_vertex(graph, src_index);
    dst = get_vertex(graph, dst_index);
    
    if (!src || !dst) {
        printf("src:%d %s dst:%d %s\n", src_index, src ? "found" : "not found", dst_index, dst ? "found" : "not found");
        return false;
    }
    if (src == dst) {
        printf("src:%d = dst:%d \n", src_index, dst_index);
        return true;
    }

    printf("DFS src:%d dst:%d \n", src_index, dst_index);
    src->visited = true;

    int i;

    for (i = 0; i < graph->max_edges; i++) {
        node_t *to = src->edges[i];
        if (to && (to == dst)) {
            printf("DFS reached dst:%d \n", dst_index);
            return true;
        }
        if (to->visited == false) {
            // Recursive call to DFS with the new vertex w off edge of v
            return dfs(graph, to->vertex, dst_index);
        }
    }

    return false;
}
//  ///////////////////////// stack code //////////////////////////
typedef struct stack_node_tag stack_node_t;

struct stack_node_tag {
    void *data;
    struct stack_node_tag *next;
};

typedef struct stack_tag stack_;
struct stack_tag {
    stack_node_t *top;
};

stack_ *create_stack (void) {
    return calloc(1, sizeof(stack_));
}

/* allocates stack_node_t */
void push (stack_ *stack, void *data) {
    stack_node_t *stack_node = calloc(1, sizeof *stack_node);
    stack_node->data = data;
    stack_node->next = stack->top;

    printf("push: top:%d\n", ((node_t *)data)->vertex); 
    stack->top = stack_node;
}

void *pop (stack_ *stack) {
    stack_node_t *top = stack->top;
    void *data = NULL;

    if (top) {
        stack->top = top->next;
        data = top->data;
        free(top);
        printf("pop:%d\n", ((node_t *)data)->vertex);
    }
    return data;
}

void delete_stack (stack_ *stack) {
    while (stack->top) {
        stack_node_t *curr = stack->top;
        if (curr) {
            stack->top = curr->next;
            free(curr);
            continue;
        }
        break;
    }
    free(stack);
}

///////////////////////////////////////////////////////////////////
/*
A non-recursive implementation of DFS with worst-case space complexity O(|E|)

procedure DFS-iterative(G, v) is
    let S be a stack
    S.push(v)
    while S is not empty do
        v = S.pop()
        if v is not labeled as discovered then
            label v as discovered
            for all edges from v to w in G.adjacentEdges(v) do 
                S.push(w)
*/
bool dfs_iterative (graph_t *graph, int src_index, int dst_index) {
    if (!graph) return false;

    node_t *src = get_vertex(graph, src_index);
    node_t *dst = get_vertex(graph, dst_index);

    if (!src || !dst) {
        printf("src:%d %s dst:%d %s\n", src_index, src ? "found" : "not found", dst_index, dst ? "found" : "not found");
        return false;
    }
    if (src == dst) {
        printf("src:%d = dst:%d \n", src_index, dst_index);
        return true;
    }

    printf("DFS Iterative src:%d dst:%d \n", src_index, dst_index);

    stack_ *s = create_stack();
    push(s, src);

    while (s->top) {
        node *v = pop(s);
        if (v->visited == false) { 
            v->visited = true;
            for (int i = 0; i < graph->max_edges; i++) {
                node_t *to = v->edges[i];
                if (to && (to == dst)) {
                    printf("DFS iterative reaached dst:%d \n", dst_index);
                    delete_stack(s);
                    return true;
                }
                if (to && (to->visited == false)) {
                    push(s, to);
                }    
            }
        }
    }
        
    delete_stack(s);
    return false;    
}

void test1 (void) {
    int max_vertices = 10;
    int max_edges = 5;

    graph_t *graph = create_graph(max_vertices, max_edges);
    add_edge(graph, 0, 10);
    add_edge(graph, 0, 20);
    add_edge(graph, 10, 20);

    add_edge(graph, 10, 30);
    add_edge(graph, 20, 40);
    add_edge(graph, 40, 50);

    //dfs(graph, 0, 50);
    // visited should be moved to graph so that it can be cleared in one shot
    dfs_iterative(graph, 10, 50);

}

int main () {
    test1();
}
