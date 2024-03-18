#include "resources/mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
    : Vertices(vertices), Indices(indices)
{
}
