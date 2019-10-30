#include "StaticMesh.h"
#include "../Renderer.h"




CStaticMesh::CStaticMesh(class CRenderer* InRenderer)
	:Renderer{ InRenderer }
{

}


CStaticMesh::~CStaticMesh()
{
	Shader.Clear();
}


void CStaticMesh::SetShader(std::string FilePath, bool UseDefaultPath)
{
	Shader = Renderer->SetShader(this, FilePath, UseDefaultPath);
}


SShader CStaticMesh::GetShader() const
{
	return Shader;
}