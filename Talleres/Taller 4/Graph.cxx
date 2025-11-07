#include "Graph.h"
#include <iostream>

// -------------------------------------------------------------------------
// Implementación de Point
float Point::distanceTo(const Point& b) const
{
  float x = X - b.X;
  float y = Y - b.Y;
  float z = Z - b.Z;
  return std::sqrt((x * x) + (y * y) + (z * z));
}

// -------------------------------------------------------------------------
// Implementaciones de Graph

template <typename TVertex, typename TCost>
Graph<TVertex, TCost>::Graph() {}

// -------------------------------------------------------------------------
template <typename TVertex, typename TCost>
void Graph<TVertex, TCost>::AddVertex(const TVertex& v)
{
  vertices.push_back(v);
  adj.push_back(std::vector<std::pair<long, TCost>>());
}

// -------------------------------------------------------------------------
template <typename TVertex, typename TCost>
void Graph<TVertex, TCost>::AddEdge(long from, long to, TCost cost)
{
  if (from < 0 || from >= (long)vertices.size() || to < 0 || to >= (long)vertices.size())
    return;
  adj[from].push_back(std::make_pair(to, cost));
}

// -------------------------------------------------------------------------
template <typename TVertex, typename TCost>
TVertex Graph<TVertex, TCost>::GetVertex(long id) const
{
  return vertices[id];
}

// -------------------------------------------------------------------------
template <typename TVertex, typename TCost>
long Graph<TVertex, TCost>::GetVertexCount() const
{
  return (long)vertices.size();
}

// -------------------------------------------------------------------------
template <typename TVertex, typename TCost>
std::vector<long> Graph<TVertex, TCost>::Dijkstra(long start, long end)
{
  long n = (long)vertices.size();
  std::vector<TCost> dist(n, std::numeric_limits<TCost>::infinity());
  std::vector<long> prev(n, -1);
  std::vector<bool> visited(n, false);

  typedef std::pair<TCost, long> Node;
  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;

  dist[start] = 0;
  pq.push(std::make_pair(0, start));

  while (!pq.empty())
  {
    long u = pq.top().second;
    pq.pop();

    if (visited[u]) continue;
    visited[u] = true;
    if (u == end) break;

    for (std::size_t i = 0; i < adj[u].size(); i++)
    {
      long v = adj[u][i].first;
      TCost weight = adj[u][i].second;
      if (!visited[v] && dist[u] + weight < dist[v])
      {
        dist[v] = dist[u] + weight;
        prev[v] = u;
        pq.push(std::make_pair(dist[v], v));
      }
    }
  }

  std::vector<long> path;
  for (long at = end; at != -1; at = prev[at])
    path.push_back(at);
  std::reverse(path.begin(), path.end());
  return path;
}


template class Graph<Point, float>;
