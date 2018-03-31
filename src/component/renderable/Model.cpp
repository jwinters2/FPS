#include "Model.h"
#include "GraphicsManager.h"

Model::Model(std::string _mn):modelName(_mn)
{
  GraphicsManager& gm = GraphicsManager::getReference();
  if(!gm.isModelLoaded(modelName))
  {
    gm.loadModel(modelName);
  }
}

Model::~Model() {}

void Model::draw() const
{
  GraphicsManager& gm = GraphicsManager::getReference();
  gm.renderModel(modelName);
}
