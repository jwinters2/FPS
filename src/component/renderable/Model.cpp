#include "Model.h"
#include "GraphicsManager.h"

Model::Model(std::string _mn, std::string _tn):modelName(_mn), textureName(_tn)
{
  GraphicsManager& gm = GraphicsManager::getReference();

  if(!gm.isModelLoaded(modelName))
  {
    gm.loadModel(modelName);
  }

  if(!gm.isTextureLoaded(textureName))
  {
    gm.loadTexture(textureName);
  }
}

Model::~Model() {}

void Model::draw() const
{
  GraphicsManager& gm = GraphicsManager::getReference();
  gm.renderModel(modelName, textureName, transform);
}
