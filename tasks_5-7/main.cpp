#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NODES 1000
#define MAX_EDGES 10000

typedef struct Node Node;
typedef struct Edge Edge;

struct Edge
{
    Node* from;
    Node* to;
    int weight;
    int flow;
    Edge* reverse;
    int isResidual;
};

struct Node
{
    char id[100];
    Edge* outgoing[100];
    int outgoing_count;
    Edge* incoming[100];
    int incoming_count;
};

typedef struct
{
    Node* nodes[MAX_NODES];
    int nodes_count;
    Edge* edges[MAX_EDGES];
    int edges_count;
} Graph;

Graph graph;


Node* find_node(const char* id)
{
    for (int i = 0; i < graph.nodes_count; i++)
    {
        if (strcmp(graph.nodes[i]->id, id) == 0)
            return graph.nodes[i];
    }
    return NULL;
}


void add_node(const char* id)
{
    if (find_node(id) != NULL)
        return;
    
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->id, id);
    node->outgoing_count = 0;
    node->incoming_count = 0;
    
    graph.nodes[graph.nodes_count++] = node;
}


void add_edge(const char* from, const char* to, int weight)
{
    Node* from_node = find_node(from);
    Node* to_node = find_node(to);
    
    if (from_node == NULL && to_node == NULL)
    {
        printf("Unknown nodes %s %s\n", from, to);
        return;
    }
    if (from_node == NULL)
    {
        printf("Unknown node %s\n", from);
        return;
    }
    if (to_node == NULL)
    {
        printf("Unknown node %s\n", to);
        return;
    }
    
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->from = from_node;
    e->to = to_node;
    e->weight = weight;
    e->flow = 0;
    e->reverse = NULL;
    e->isResidual = 0;
    
    from_node->outgoing[from_node->outgoing_count++] = e;
    to_node->incoming[to_node->incoming_count++] = e;
    graph.edges[graph.edges_count++] = e;
}


void remove_edge_helper(Edge* e)
{
    Node* from_node = e->from;
    for (int i = 0; i < from_node->outgoing_count; i++)
    {
        if (from_node->outgoing[i] == e)
        {
            memmove(&from_node->outgoing[i], &from_node->outgoing[i+1], 
                   (from_node->outgoing_count - i - 1) * sizeof(Edge*));
            from_node->outgoing_count--;
            break;
        }
    }

    Node* to_node = e->to;
    for (int i = 0; i < to_node->incoming_count; i++)
    {
        if (to_node->incoming[i] == e)
        {
            memmove(&to_node->incoming[i], &to_node->incoming[i+1], 
                   (to_node->incoming_count - i - 1) * sizeof(Edge*));
            to_node->incoming_count--;
            break;
        }
    }
    
    for (int i = 0; i < graph.edges_count; i++)
    {
        if (graph.edges[i] == e)
        {
            memmove(&graph.edges[i], &graph.edges[i+1], 
                   (graph.edges_count - i - 1) * sizeof(Edge*));
            graph.edges_count--;
            break;
        }
    }
    
    free(e);
}


void remove_node(const char* id)
{
    Node* node = find_node(id);
    if (node == NULL)
    {
        printf("Unknown node %s\n", id);
        return;
    }
    
    for (int i = node->incoming_count - 1; i >= 0; i--)
    {
        Edge* e = node->incoming[i];
        if (e->reverse && e->reverse->isResidual)
        {
            Edge* rev = e->reverse;
            remove_edge_helper(rev);
        }
        remove_edge_helper(e);
    }
    
    for (int i = node->outgoing_count - 1; i >= 0; i--)
    {
        Edge* e = node->outgoing[i];
        if (e->reverse && e->reverse->isResidual)
        {
            Edge* rev = e->reverse;
            remove_edge_helper(rev);
        }
        remove_edge_helper(e);
    }
    
    for (int i = 0; i < graph.nodes_count; i++)
    {
        if (graph.nodes[i] == node)
        {
            memmove(&graph.nodes[i], &graph.nodes[i+1], 
                   (graph.nodes_count - i - 1) * sizeof(Node*));
            graph.nodes_count--;
            break;
        }
    }
    
    free(node);
}


void remove_edge(const char* from, const char* to)
{
    Node* from_node = find_node(from);
    Node* to_node = find_node(to);
    
    if (from_node == NULL || to_node == NULL)
    {
        printf("Unknown nodes %s %s\n", from, to);
        return;
    }
    
    for (int i = 0; i < from_node->outgoing_count; i++)
    {
        Edge* e = from_node->outgoing[i];
        if (e->to == to_node)
        {
            if (e->reverse && e->reverse->isResidual)
            {
                Edge* rev = e->reverse;
                remove_edge_helper(rev);
            }
            remove_edge_helper(e);
            break;
        }
    }
}


int dfs(Node* node, int visited[], int recStack[], char order[][100], int* order_count, 
        char* loopFrom, char* loopTo)
{
    int node_index = -1;
    for (int i = 0; i < graph.nodes_count; i++)
    {
        if (graph.nodes[i] == node)
        {
            node_index = i;
            break;
        }
    }
    
    visited[node_index] = 1;
    recStack[node_index] = 1;
    
    for (int i = 0; i < node->outgoing_count; i++)
    {
        Node* neighbor = node->outgoing[i]->to;
        int neighbor_index = -1;
        for (int j = 0; j < graph.nodes_count; j++)
        {
            if (graph.nodes[j] == neighbor)
            {
                neighbor_index = j;
                break;
            }
        }
        
        if (!visited[neighbor_index])
        {
            if (!dfs(neighbor, visited, recStack, order, order_count, loopFrom, loopTo))
                return 0;
            
        }
        else if (recStack[neighbor_index])
        {
            strcpy(loopFrom, node->id);
            strcpy(loopTo, neighbor->id);
            return 0;
        }
    }
    
    recStack[node_index] = 0;
    strcpy(order[*order_count], node->id);
    (*order_count)++;
    return 1;
}


void rpo_numbering(const char* startId)
{
    Node* start = find_node(startId);
    if (start == NULL)
    {
        printf("Unknown node %s\n", startId);
        return;
    }
    
    int visited[MAX_NODES] = {0};
    int recStack[MAX_NODES] = {0};
    char order[MAX_NODES][100];
    int order_count = 0;
    char loopFrom[100], loopTo[100];
    
    if (!dfs(start, visited, recStack, order, &order_count, loopFrom, loopTo))
    {
        printf("Found loop %s->%s\n", loopFrom, loopTo);
        return;
    }
    
    for (int i = order_count - 1; i >= 0; i--)
    {
        printf("%s ", order[i]);
    }
    printf("\n");
}


void dijkstra(const char* startId)
{
    Node* start = find_node(startId);
    if (start == NULL)
    {
        printf("Unknown node %s\n", startId);
        return;
    }

    int dist[MAX_NODES];
    int processed[MAX_NODES] = {0};
    for (int i = 0; i < graph.nodes_count; i++)
    {
        dist[i] = INT_MAX;
    }

    int start_index = -1;
    for (int i = 0; i < graph.nodes_count; i++)
    {
        if (graph.nodes[i] == start)
        {
            start_index = i;
            break;
        }
    }
    dist[start_index] = 0;

    for (int i = 0; i < graph.nodes_count; i++)
    {
        int min_dist = INT_MAX;
        int u = -1;
        for (int j = 0; j < graph.nodes_count; j++)
        {
            if (!processed[j] && dist[j] < min_dist)
            {
                min_dist = dist[j];
                u = j;
            }
        }

        if (u == -1)
            break;

        processed[u] = 1;    

        Node* current = graph.nodes[u];
        for (int j = 0; j < current->outgoing_count; j++)
        {
            Edge* edge = current->outgoing[j];
            Node* neighbor = edge->to;

            int neighbor_index = -1;
            for (int k = 0; k < graph.nodes_count; k++)
            {
                if (graph.nodes[k] == neighbor)
                {
                    neighbor_index = k;
                    break;
                }
            }

            if (neighbor_index == -1)
                continue;

            int new_dist = dist[u] + edge->weight;
            if (new_dist < dist[neighbor_index])
            {
                dist[neighbor_index] = new_dist;
            }
        }
    }

    for (int i = 0; i < graph.nodes_count; i++)
    {
        if (graph.nodes[i] == start)
            continue;

        printf("%s ", graph.nodes[i]->id);
        if (dist[i] == INT_MAX)
        {
            printf("unreachable\n");
        }
        else
        {
            printf("%d\n", dist[i]);
        }
    }
}


int bfs(Edge* parent[], Node* source, Node* sink)
{
    int visited[MAX_NODES] = {0};
    Node* queue[MAX_NODES];
    int front = 0, rear = 0;
    
    int source_index = -1;
    for (int i = 0; i < graph.nodes_count; i++)
    {
        if (graph.nodes[i] == source)
        {
            source_index = i;
            break;
        }
    }
    visited[source_index] = 1;
    queue[rear++] = source;
    
    while (front < rear)
    {
        Node* current = queue[front++];
        
        for (int i = 0; i < current->outgoing_count; i++)
        {
            Edge* e = current->outgoing[i];
            int capacity = e->weight - e->flow;
            
            int to_index = -1;
            for (int j = 0; j < graph.nodes_count; j++)
            {
                if (graph.nodes[j] == e->to)
                {
                    to_index = j;
                    break;
                }
            }
            
            if (capacity > 0 && !visited[to_index])
            {
                visited[to_index] = 1;
                parent[to_index] = e;
                queue[rear++] = e->to;
                if (e->to == sink) return 1;
            }
        }
    }
    return 0;
}


void max_flow(const char* sourceId, const char* sinkId)
{
    Node* source = find_node(sourceId);
    Node* sink = find_node(sinkId);
    
    if (source == NULL || sink == NULL)
    {
        printf("Unknown nodes %s %s\n", sourceId, sinkId);
        return;
    }
    
    for (int i = 0; i < graph.edges_count; i++)
    {
        Edge* e = graph.edges[i];
        e->flow = 0;
        
        if (!e->reverse) {
            Edge* rev = (Edge*)malloc(sizeof(Edge));
            rev->from = e->to;
            rev->to = e->from;
            rev->weight = 0;
            rev->flow = 0;
            rev->reverse = e;
            rev->isResidual = 1;
            e->reverse = rev;
            
            e->to->outgoing[e->to->outgoing_count++] = rev;
            e->from->incoming[e->from->incoming_count++] = rev;
            graph.edges[graph.edges_count++] = rev;
        }
    }
    
    Edge* parent[MAX_NODES] = {NULL};
    int maxFlow = 0;
    
    while (bfs(parent, source, sink))
    {
        int pathFlow = INT_MAX;
        
        for (Node* v = sink; v != source;)
        {
            int v_index = -1;
            for (int i = 0; i < graph.nodes_count; i++)
            {
                if (graph.nodes[i] == v)
                {
                    v_index = i;
                    break;
                }
            }
            Edge* e = parent[v_index];
            pathFlow = (pathFlow < e->weight - e->flow) ? pathFlow : (e->weight - e->flow);
            v = e->from;
        }
        
        for (Node* v = sink; v != source;)
        {
            int v_index = -1;
            for (int i = 0; i < graph.nodes_count; i++)
            {
                if (graph.nodes[i] == v)
                {
                    v_index = i;
                    break;
                }
            }
            Edge* e = parent[v_index];
            e->flow += pathFlow;
            e->reverse->flow -= pathFlow;
            v = e->from;
        }
        
        maxFlow += pathFlow;
        memset(parent, 0, sizeof(parent));
    }
    
    printf("%d\n", maxFlow);
}


void cleanup()
{
    for (int i = 0; i < graph.nodes_count; i++)
    {
        free(graph.nodes[i]);
    }
    
    for (int i = 0; i < graph.edges_count; i++)
    {
        free(graph.edges[i]);
    }
}


int main()
{
    graph.nodes_count = 0;
    graph.edges_count = 0;
    
    char cmd[100];
    while (scanf("%s", cmd) == 1)
    {
        if (strcmp(cmd, "NODE") == 0)
        {
            char id[100];
            scanf("%s", id);
            add_node(id);
        }
        else if (strcmp(cmd, "EDGE") == 0)
        {
            char from[100], to[100];
            int w;
            scanf("%s %s %d", from, to, &w);
            add_edge(from, to, w);
        }
        else if (strcmp(cmd, "REMOVE") == 0)
        {
            char type[100];
            scanf("%s", type);
            if (strcmp(type, "NODE") == 0)
            {
                char id[100];
                scanf("%s", id);
                remove_node(id);
            }
            else if (strcmp(type, "EDGE") == 0)
            {
                char from[100], to[100];
                scanf("%s %s", from, to);
                remove_edge(from, to);
            }
        }
        else if (strcmp(cmd, "RPO_NUMBERING") == 0)
        {
            char start[100];
            scanf("%s", start);
            rpo_numbering(start);
        }
        else if (strcmp(cmd, "DIJKSTRA") == 0)
        {
            char start[100];
            scanf("%s", start);
            dijkstra(start);
        }
        else if (strcmp(cmd, "MAX") == 0)
        {
            char subcmd[100];
            scanf("%s", subcmd);
            if (strcmp(subcmd, "FLOW") == 0)
            {
                char from[100], to[100];
                scanf("%s %s", from, to);
                max_flow(from, to);
            }
        }
    }
    
    cleanup();
    return 0;
}