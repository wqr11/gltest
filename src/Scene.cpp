#include "Scene.h"

Scene::Scene(std::unique_ptr<Object> obj) : root(std::move(obj)) {}

void Scene::upload() { root->upload(); }
void Scene::draw() { root->draw(); }
