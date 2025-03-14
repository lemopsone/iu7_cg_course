#include "renderingfactory.h"

QHash<Renderer::Type, RenderingAlgorithm *> RenderingFactory::cache = QHash<Renderer::Type, RenderingAlgorithm *>();
