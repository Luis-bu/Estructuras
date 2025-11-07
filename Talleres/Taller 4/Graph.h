#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <limits>
#include <queue>
#include <algorithm>
#include <cmath>

// -------------------------------------------------------------------------
// Estructura para representar un punto en 3D
struct Point
{
  float X, Y, Z;
  float distanceTo(const Point& b) const;
};

// -------------------------------------------------------------------------
// Definición de la plantilla de grafo genérico
template <typename TVertex, typename TCost>
class Graph
{
private:
  std::vector<TVertex> vertices;
  std::vector<std::vector<std::pair<long, TCost>>> adj;

public:
  Graph();
  void AddVertex(const TVertex& v);
  void AddEdge(long from, long to, TCost cost);
  TVertex GetVertex(long id) const;
  long GetVertexCount() const;
  std::vector<long> Dijkstra(long start, long end);
};

#endif
