#include "Cube.h"


CCube::CCube(class CRenderer* InRenderer)
	:CStaticMesh::CStaticMesh{ InRenderer }
{
	VertexCount = 3;
	//Vertices = new SModelVertex[VertexCount];
	Vertices = new SVertexBase[VertexCount];

	Vertices[0] = SVertexBase{ SVector{  0.9f,  0.9f,  0.0f }, SVector4{ 1.0f, 0.0f, 0.0f, 1.0f } };
	Vertices[1] = SVertexBase{ SVector{  0.9f, -0.9f,  0.0f }, SVector4{ 0.0f, 1.0f, 0.0f, 1.0f } };
	Vertices[2] = SVertexBase{ SVector{ -0.9f, -0.9f,  0.0f }, SVector4{ 0.0f, 0.0f, 1.0f, 1.0f } };
}


CCube::~CCube()
{

}