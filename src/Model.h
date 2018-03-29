#include <vector>
#include <glm/glm.hpp>

struct Model
{
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec2> uvs;
  std::vector<glm::vec3> normals;
};
