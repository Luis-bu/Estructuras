#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Graph.h"

// -------------------------------------------------------------------------
typedef Graph<Point, float> TGraph;

// -------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  if (argc < 4)
  {
    std::cerr << "Uso: " << argv[0] << " archivo_malla punto_inicio punto_fin" << std::endl;
    return 1;
  }

  long start_id = std::atoi(argv[2]);
  long end_id = std::atoi(argv[3]);

  TGraph g;

  // Lectura del archivo de malla
  std::ifstream in_mesh_stream(argv[1], std::ifstream::binary);
  if (!in_mesh_stream)
  {
    std::cerr << "Error al leer el archivo \"" << argv[1] << "\"" << std::endl;
    return 1;
  }

  in_mesh_stream.seekg(0, in_mesh_stream.end);
  unsigned long in_mesh_file_length = in_mesh_stream.tellg();
  in_mesh_stream.seekg(0, in_mesh_stream.beg);

  char* in_mesh_file_buffer = new char[in_mesh_file_length];
  in_mesh_stream.read(in_mesh_file_buffer, in_mesh_file_length);
  in_mesh_stream.close();

  std::istringstream in_mesh(in_mesh_file_buffer);

  // Leer vértices
  long nPoints;
  in_mesh >> nPoints;
  for (long pId = 0; pId < nPoints; pId++)
  {
    Point pnt;
    in_mesh >> pnt.X >> pnt.Y >> pnt.Z;
    g.AddVertex(pnt);
  }

  // Leer aristas
  long nEdges;
  in_mesh >> nEdges;
  for (long eId = 0; eId < nEdges; eId++)
  {
    long start, end;
    in_mesh >> start >> end;

    float cost = g.GetVertex(start).distanceTo(g.GetVertex(end));
    g.AddEdge(start, end, cost);
    g.AddEdge(end, start, cost);
  }

  delete[] in_mesh_file_buffer;

  if (start_id < 0 || start_id >= g.GetVertexCount() ||
      end_id < 0 || end_id >= g.GetVertexCount())
  {
    std::cerr << "Índices de vértices inválidos." << std::endl;
    return 1;
  }

  // Ejecutar Dijkstra
  std::vector<long> path = g.Dijkstra(start_id, end_id);

  // Mostrar resultados
  std::cout << path.size() << std::endl;
  for (std::size_t i = 0; i < path.size(); i++)
  {
    Point p = g.GetVertex(path[i]);
    std::cout << p.X << " " << p.Y << " " << p.Z << std::endl;
  }

  return 0;
}

// eof -
