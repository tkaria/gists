#!`env python`
queries = int(raw_input().strip())


def bfs(graph, start):
    print graph


def dfs(graph, start):
    pass

for x in range(queries):
    graph = {}
    nodes, edges = map(int, raw_input().strip().split(' '))
    for node in range(nodes + 1):
        graph[node] = []
    print graph[1]
    print "Nodes: %s Edges: %s" % (nodes, edges)
    for y in range(edges):
        u, v = map(int, raw_input().strip().split())
        print "Edge: %s <-> %s" % (u, v)
        graph[u].append(v)
        graph[v].append(u)
    starting_index = int(raw_input().strip())
    print "Starting index: %s" % (starting_index)

    bfs(graph)
