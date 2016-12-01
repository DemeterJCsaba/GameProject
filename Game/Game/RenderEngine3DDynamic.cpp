#include "RenderEngine3DDynamic.h"

RenderEngine3DDynamic::RenderEngine3DDynamic(bool disableDepth, int maxVertexSize):
	RenderEngine3D(disableDepth,maxVertexSize)
{

}

void RenderEngine3DDynamic::submit(RawModel3D* model) {
	m_Models.push_back(model);
}

void RenderEngine3DDynamic::flush() {
	RenderEngine3D::begin();
	for (RawModel3D* model : m_Models) {
		RenderEngine3D::submit(*model);
	}
	RenderEngine3D::end();
	RenderEngine3D::flush();
}
