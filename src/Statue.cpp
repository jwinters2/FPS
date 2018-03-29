#include "GraphicsManager.h"
#include "Statue.h"

Statue::Statue():modelPath("assets/statue.obj")
{
  GraphicsManager& gm = GraphicsManager::getReference(); 
  gm.loadModel(modelPath);
}

Statue::~Statue()
{
}

void Statue::draw() const
{
  const GraphicsManager& gm = GraphicsManager::getReference(); 
  gm.renderModel(modelPath);
}
