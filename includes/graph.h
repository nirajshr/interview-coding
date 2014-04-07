#include <iostream>
#include <vector>
#include <queue>

namespace ADM {

struct EdgeNode {
  EdgeNode () : y(0), weight(0), next(0) {}
  EdgeNode (int y, int w, EdgeNode* n) : y(y), weight(w), next (n) {}

  int y;
  int weight;
  EdgeNode* next;
};

struct Graph {
  enum { MAXV = 1000 };

  Graph () : nvertices(0), nedges(0), directed(false) {
    for (int i=1; i<=MAXV; i++) degree[i] = 0;
    for (int i=1; i<=MAXV; i++) edges[i] = NULL;
  }

  void insert_edge(int x, int y, bool directed) {
    EdgeNode* p = new EdgeNode(y, 0, edges[x]);

    edges[x] = p;
    degree[x]++;

    if (directed == false) {
      insert_edge(y, x, true);
    }
    else {
      nedges++;
    }
  }

  EdgeNode* edges[MAXV + 1];
  int degree[MAXV + 1];
  int nvertices;
  int nedges;
  bool directed;
};

std::ostream& operator<< (std::ostream& oss, Graph const& g) {
  for (int i=1; i<=g.nvertices; ++i) {
    std::cout << ":" << i;
    EdgeNode* p = g.edges[i];
    while (p != NULL) {
      std::cout << " " << p->y;
      p = p->next;
    }
    std::cout << std::endl;
  }

  return oss;
}

struct GraphSearch {
  GraphSearch (Graph const& graph) : g(graph) {
    init();
  }

  void init() {
    for (int i=1; i<=g.nvertices; i++) {
      processed[i] = discovered[i] = false;
      parent[i] = -1;
    } 
  }

  virtual void process_vertex_early(int v) {
    std::cout << "Visiting vertex: " << v << std::endl;
  }

  virtual void process_edge(int x, int y) {
    std::cout << "Processed Edge: " << x << " -> " << y << std::endl;
  }

  virtual void process_vertex_late(int v) {
  }

  void bfs (int start) {
    std::queue<int> q;

    q.push(start);
    discovered[start] = true;

    while(!q.empty()) {
      int v = q.front();
      q.pop();

      process_vertex_early(v);
      processed[v] = true;

      EdgeNode* p = g.edges[v];
      while (p) {
        int y = p->y;
        if (processed[y] == false || g.directed) {
          process_edge(v, y);
        }
        if (discovered[y] == false) {
          q.push(y);
          discovered[y] = true;
          parent[y] = v;
        }
        p = p->next;
      };
      process_vertex_late(v);
    }
  }

  void printConnectedComponents() {
    int c = 0;

    for (int i=1; i<g.nvertices; ++i) {
      if (discovered[i] == false) {
        c++;
        std::cout << "Found Component #" << c << std::endl; 
        bfs(i);
      }
    }
  }

  void printPathToRoot(int start, int vertex) {
    if (start == vertex || vertex == -1) {
      std::cout << vertex << std::endl;
    }

    if (start != vertex) {
      std::cout << vertex << "->";
      printPathToRoot(start, parent[vertex]);
    }
  }


  bool processed[Graph::MAXV+1];
  bool discovered[Graph::MAXV+1];
  int parent[Graph::MAXV+1];
  Graph const& g;
};

void read_graph(Graph& g) {
  int i;
  int m;
  int x, y;

  scanf("%d %d", &(g.nvertices), &m);
  std::cout << g.nvertices << ", " << m << std::endl;
  for (i=1; i<=m; i++) {
    scanf("%d %d", &x, &y);
    g.insert_edge(x, y, g.directed);
  } 
}

};
