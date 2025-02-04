#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NODES 100

// Define a structure for representing a Node in the FANET
typedef struct {
    int node_id;
    int position[2]; // Position: [x, y]
    int routing_table[MAX_NODES]; // To store the routing information
} Node;

// Function to initialize a Node
void init_node(Node *node, int node_id, int x, int y) {
    node->node_id = node_id;
    node->position[0] = x;
    node->position[1] = y;
    for (int i = 0; i < MAX_NODES; i++) {
        node->routing_table[i] = -1; // Initialize the routing table with -1 (no route)
    }
}

// Function to simulate the AODV route discovery process
const char* route_discovery(Node nodes[], int num_nodes, int source_id, int destination_id) {
    printf("Node %d is trying to discover a route to Node %d.\n", source_id, destination_id);

    int visited[MAX_NODES] = {0};  // Array to track visited nodes
    int rreq_queue[MAX_NODES];
    int queue_size = 0;

    // Start with the source node
    rreq_queue[queue_size++] = source_id;

    while (queue_size > 0) {
        int current_node_id = rreq_queue[--queue_size];
        Node *current_node = &nodes[current_node_id];

        // Print the node broadcasting RREQ
        printf("Node %d broadcasting RREQ.\n", current_node_id);

        // Check if we have already visited this node
        if (visited[current_node_id]) {
            continue;
        }
        visited[current_node_id] = 1;

        // Check if the current node is the destination
        if (current_node_id == destination_id) {
            printf("Destination Node %d reached!\n", destination_id);
            return "Route found.";
        }

        // Propagate RREQ to neighboring nodes (simulating by checking all other nodes)
        for (int i = 0; i < num_nodes; i++) {
            if (i != current_node_id && !visited[i]) {
                rreq_queue[queue_size++] = i;
            }
        }
    }

    return "Route discovery failed. No route found.";
}

// Main function to simulate the FANET routing operation
int main() {
    printf("FANET Routing Algorithm Simulation (AODV-like)\n\n");

    // Number of nodes in the FANET
    int num_nodes;
    printf("Enter the number of nodes in the FANET:");
    scanf("%d", &num_nodes);

    // Create the nodes with random positions (x, y)
    Node nodes[num_nodes];
    srand(time(NULL));  // Seed for random number generation

    for (int i = 0; i < num_nodes; i++) {
        int x = rand() % 100;  // Random x-coordinate
        int y = rand() % 100;  // Random y-coordinate
        init_node(&nodes[i], i, x, y);
    }

    // Get the source and destination node IDs from the user
    int source_id, destination_id;
    printf("Enter the source node ID:");
    scanf("%d", &source_id);
    printf("Enter the destination node ID:");
    scanf("%d", &destination_id);

    // Start the route discovery process
    const char* result = route_discovery(nodes, num_nodes, source_id, destination_id);
    printf("%s\n", result);

    return 0;
}
