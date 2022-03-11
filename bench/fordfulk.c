// C implementation of Ford Fulkerson algorithm

// Number of vertices in given graph
#define V 32
#define INF 1e6

#define MIN(a, b) ((a) < (b) ? (a) : (b))

static int queue[V], head, tail;
static void clear()
{
    head = 0;
    tail = 0;
}
static void push(int a)
{
    queue[tail] = a;
    tail = (tail + 1) % V;
}
static int pop()
{
    int a = queue[head];
    head = (head + 1) % V;
    return a;
}
static int empty()
{
    return head == tail;
}

static int visited[V];

static int bfs(int rGraph[V][V], int s, int t, int parent[])
{
    // Create a visited array and mark all vertices as not
    // visited
    for (int i = 0; i < V; i++)
        visited[i] = -i;

    // Create a queue, enqueue source vertex and mark source
    // vertex as visited
    clear();
    push(s);
    visited[s] = 1;
    parent[s] = -1;

    // Standard BFS Loop
    while (!empty()) {
        int u = pop();

        for (int v = 0; v < V; v++) {
            if (visited[v] <= 0 && rGraph[u][v] > 0) {
                // If we find a connection to the sink node,
                // then there is no point in BFS anymore We
                // just have to set its parent and can return
                // 1
                if (v == t) {
                    parent[v] = u;
                    return 1;
                }
                push(v);
                parent[v] = u;
                visited[v] = 1;
            }
        }
    }

    // We didn't reach sink in BFS starting from source, so
    // return 0
    return 0;
}

// Residual graph where rGraph[i][j] indicates residual capacity of edge
// from i to j (if there is an edge. If rGraph[i][j] is 0, then there is not)
static int rGraph[V][V];
static int parent[V]; // This array is filled by BFS and to store path

// Returns the maximum flow from s to t in the given graph
static int FordFulkerson(int graph[V][V], int s, int t)
{
    int u, v;

    // Create a residual graph and fill the residual graph
    // with given capacities in the original graph as
    // residual capacities in residual graph

    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int max_flow = 0; // There is no flow initially

    // Augment the flow while there is path from source to
    // sink
    while (bfs(rGraph, s, t, parent)) {
        // Find minimum residual capacity of the edges along
        // the path filled by BFS. Or we can say find the
        // maximum flow through the path found.
        int path_flow = INF;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = MIN(path_flow, rGraph[u][v]);
        }

        // update residual capacities of the edges and
        // reverse edges along the path
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        // Add path flow to overall flow
        max_flow += path_flow;
    }

    // Return the overall flow
    return max_flow;
}

static int graph[V][V] = {
    {32, 0, 731, 923, 854, 0, 575, 0, 0, 0, 689, 440, 0, 0, 740, 992, 147, 530, 510, 631, 0, 160, 461, 0, 877, 229, 631, 280, 181, 0, 282, 599},
    {0, 698, 269, 845, 341, 648, 0, 228, 503, 0, 0, 633, 0, 973, 0, 874, 417, 141, 36, 0, 586, 122, 0, 0, 647, 769, 245, 0, 937, 677, 596, 19},
    {0, 0, 209, 399, 862, 792, 457, 427, 451, 0, 0, 0, 975, 0, 600, 0, 933, 665, 228, 0, 744, 882, 206, 976, 61, 651, 122, 684, 360, 293, 110, 0},
    {447, 53, 768, 609, 530, 0, 0, 0, 579, 540, 455, 0, 0, 919, 69, 0, 820, 0, 922, 924, 0, 488, 0, 0, 0, 0, 0, 356, 0, 490, 685, 914},
    {631, 929, 539, 0, 525, 412, 0, 0, 578, 26, 0, 17, 0, 683, 231, 698, 0, 542, 0, 498, 0, 442, 0, 694, 168, 0, 629, 417, 0, 672, 732, 795},
    {426, 0, 0, 747, 672, 142, 8, 0, 709, 0, 969, 99, 218, 673, 751, 966, 211, 877, 712, 397, 0, 609, 446, 50, 944, 799, 0, 778, 482, 226, 607, 228},
    {157, 0, 0, 0, 0, 96, 731, 182, 164, 845, 961, 743, 0, 516, 449, 926, 965, 114, 837, 949, 964, 171, 0, 0, 116, 0, 188, 0, 876, 0, 853, 932},
    {910, 0, 724, 986, 0, 190, 0, 314, 100, 0, 984, 17, 567, 406, 325, 758, 144, 360, 781, 169, 0, 335, 0, 243, 891, 386, 0, 72, 563, 0, 0, 24},
    {0, 506, 989, 0, 609, 975, 531, 520, 94, 0, 0, 665, 678, 737, 553, 975, 272, 143, 82, 895, 167, 413, 488, 100, 84, 839, 751, 0, 0, 590, 450, 0},
    {793, 519, 36, 10, 495, 0, 0, 0, 272, 72, 352, 0, 0, 0, 69, 425, 0, 410, 0, 0, 0, 0, 10, 953, 0, 0, 614, 804, 0, 0, 0, 258},
    {691, 18, 656, 690, 324, 59, 49, 341, 0, 572, 0, 146, 0, 729, 939, 989, 0, 887, 903, 351, 284, 0, 855, 417, 175, 859, 329, 682, 0, 0, 401, 959},
    {347, 452, 704, 66, 438, 529, 319, 0, 976, 85, 757, 0, 110, 0, 753, 0, 192, 318, 0, 0, 636, 842, 168, 112, 161, 573, 195, 598, 5, 443, 360, 101},
    {653, 0, 0, 0, 378, 980, 0, 172, 59, 0, 0, 0, 1, 934, 952, 506, 321, 336, 692, 0, 599, 714, 31, 689, 41, 993, 284, 0, 676, 0, 852, 570},
    {959, 52, 238, 539, 0, 166, 0, 227, 551, 0, 218, 310, 318, 537, 0, 97, 0, 0, 0, 762, 0, 794, 174, 409, 0, 575, 656, 776, 214, 952, 163, 32},
    {700, 0, 0, 0, 954, 658, 650, 910, 0, 0, 618, 868, 13, 916, 0, 606, 0, 0, 262, 0, 166, 537, 737, 192, 370, 53, 0, 199, 0, 900, 323, 977},
    {0, 0, 908, 0, 990, 652, 0, 303, 166, 888, 338, 16, 95, 0, 0, 712, 252, 960, 541, 0, 694, 578, 115, 881, 0, 532, 350, 804, 0, 0, 0, 0},
    {34, 0, 204, 0, 147, 0, 0, 81, 0, 547, 240, 0, 883, 0, 117, 811, 391, 0, 295, 0, 275, 0, 159, 498, 0, 0, 54, 866, 65, 689, 939, 0},
    {0, 0, 267, 0, 482, 0, 957, 0, 35, 439, 597, 0, 987, 632, 694, 28, 987, 0, 695, 819, 0, 216, 0, 0, 910, 582, 418, 149, 0, 218, 0, 709},
    {626, 912, 0, 507, 0, 938, 0, 138, 632, 155, 323, 0, 0, 893, 593, 0, 290, 174, 0, 0, 0, 639, 798, 0, 210, 688, 0, 273, 0, 134, 45, 199},
    {70, 0, 106, 122, 724, 603, 844, 60, 427, 0, 614, 56, 0, 0, 105, 590, 505, 0, 0, 923, 94, 0, 314, 497, 306, 735, 0, 0, 446, 333, 175, 428},
    {267, 0, 91, 0, 69, 967, 110, 0, 701, 132, 272, 0, 631, 365, 909, 21, 10, 0, 0, 357, 145, 749, 204, 809, 32, 228, 158, 0, 427, 0, 294, 26},
    {614, 300, 0, 0, 147, 22, 0, 181, 388, 527, 782, 0, 0, 148, 181, 738, 638, 323, 339, 0, 682, 606, 242, 0, 0, 69, 600, 0, 0, 409, 0, 0},
    {0, 0, 0, 435, 560, 132, 806, 522, 954, 0, 0, 198, 162, 781, 0, 0, 609, 0, 637, 528, 753, 55, 0, 347, 159, 243, 0, 404, 26, 0, 89, 0},
    {281, 988, 599, 0, 788, 975, 0, 884, 350, 70, 974, 130, 573, 556, 706, 0, 717, 213, 973, 920, 529, 696, 0, 0, 371, 951, 628, 790, 545, 450, 0, 393},
    {461, 428, 855, 0, 342, 0, 844, 879, 351, 795, 0, 503, 506, 582, 26, 0, 0, 0, 48, 355, 553, 0, 0, 854, 0, 0, 222, 158, 820, 309, 799, 942},
    {923, 754, 872, 925, 36, 0, 797, 0, 141, 0, 578, 924, 0, 597, 262, 199, 0, 0, 656, 981, 0, 86, 423, 412, 448, 131, 332, 0, 206, 799, 167, 0},
    {0, 0, 0, 266, 0, 32, 0, 0, 347, 676, 0, 881, 0, 576, 0, 164, 380, 0, 795, 0, 653, 0, 971, 0, 378, 321, 944, 656, 590, 754, 692, 0},
    {276, 931, 0, 713, 0, 157, 121, 26, 672, 180, 0, 0, 724, 154, 25, 486, 0, 462, 697, 0, 265, 527, 780, 950, 352, 297, 0, 938, 717, 637, 580, 0},
    {330, 991, 0, 0, 0, 129, 365, 0, 296, 258, 84, 640, 938, 115, 541, 0, 66, 691, 898, 933, 468, 195, 0, 958, 126, 584, 887, 0, 0, 0, 472, 684},
    {577, 0, 0, 0, 0, 672, 0, 384, 920, 0, 0, 454, 95, 314, 0, 269, 352, 283, 851, 0, 797, 680, 0, 0, 898, 0, 0, 236, 0, 327, 787, 982},
    {606, 136, 640, 378, 527, 85, 423, 773, 166, 0, 859, 0, 41, 127, 597, 0, 159, 0, 748, 531, 420, 0, 64, 726, 0, 921, 586, 0, 134, 554, 297, 0},
    {71, 978, 794, 402, 22, 0, 650, 0, 718, 805, 146, 636, 38, 0, 141, 107, 506, 844, 897, 875, 669, 47, 0, 967, 744, 302, 640, 877, 950, 0, 522, 862},
};

int do_fordfulk()
{
    return FordFulkerson(graph, 0, V - 1);
}

#ifdef WITH_MAIN
#include <stdio.h>
int main()
{
    printf("code = %d\n", do_fordfulk());
}
#endif
