#include "Cube.h"


CCube::CCube(class CRenderer* InRenderer)
	:CStaticMesh::CStaticMesh{ InRenderer }
{
	VertexCount = 36;
	//Vertices = new SModelVertex[VertexCount];
	Vertices = new SVertexBase[VertexCount];

	// Back face.
	Vertices[0]  = SVertexBase{ SVector{ -1.0f,  1.0f,  1.0f }, SVector4{ 0.0f, 1.0f, 1.0f, 1.0f } };
	Vertices[1]  = SVertexBase{ SVector{ -1.0f, -1.0f,  1.0f }, SVector4{ 0.0f, 1.0f, 1.0f, 1.0f } };
	Vertices[2]  = SVertexBase{ SVector{  1.0f,  1.0f,  1.0f }, SVector4{ 0.0f, 1.0f, 1.0f, 1.0f } };
	Vertices[3]  = SVertexBase{ SVector{  1.0f,  1.0f,  1.0f }, SVector4{ 0.0f, 1.0f, 1.0f, 1.0f } };
	Vertices[4]  = SVertexBase{ SVector{ -1.0f, -1.0f,  1.0f }, SVector4{ 0.0f, 1.0f, 1.0f, 1.0f } };
	Vertices[5]  = SVertexBase{ SVector{  1.0f, -1.0f,  1.0f }, SVector4{ 0.0f, 1.0f, 1.0f, 1.0f } };
			    
	// Front face.
	Vertices[6]  = SVertexBase{ SVector{ -1.0f, -1.0f, -1.0f }, SVector4{ 1.0f, 0.0f, 1.0f, 1.0f } };
	Vertices[7]  = SVertexBase{ SVector{ -1.0f,  1.0f, -1.0f }, SVector4{ 1.0f, 0.0f, 1.0f, 1.0f } };
	Vertices[8]  = SVertexBase{ SVector{  1.0f,  1.0f, -1.0f }, SVector4{ 1.0f, 0.0f, 1.0f, 1.0f } };
	Vertices[9]  = SVertexBase{ SVector{ -1.0f, -1.0f, -1.0f }, SVector4{ 1.0f, 0.0f, 1.0f, 1.0f } };
	Vertices[10] = SVertexBase{ SVector{  1.0f,  1.0f, -1.0f }, SVector4{ 1.0f, 0.0f, 1.0f, 1.0f } };
	Vertices[11] = SVertexBase{ SVector{  1.0f, -1.0f, -1.0f }, SVector4{ 1.0f, 0.0f, 1.0f, 1.0f } };
														
	// Left face.										
	Vertices[12] = SVertexBase{ SVector{ -1.0f, -1.0f, -1.0f }, SVector4{ 1.0f, 1.0f, 0.0f, 1.0f } };
	Vertices[13] = SVertexBase{ SVector{ -1.0f, -1.0f,  1.0f }, SVector4{ 1.0f, 1.0f, 0.0f, 1.0f } };
	Vertices[14] = SVertexBase{ SVector{ -1.0f,  1.0f, -1.0f }, SVector4{ 1.0f, 1.0f, 0.0f, 1.0f } };
	Vertices[15] = SVertexBase{ SVector{ -1.0f, -1.0f,  1.0f }, SVector4{ 1.0f, 1.0f, 0.0f, 1.0f } };
	Vertices[16] = SVertexBase{ SVector{ -1.0f,  1.0f,  1.0f }, SVector4{ 1.0f, 1.0f, 0.0f, 1.0f } };
	Vertices[17] = SVertexBase{ SVector{ -1.0f,  1.0f, -1.0f }, SVector4{ 1.0f, 1.0f, 0.0f, 1.0f } };
														
	// Right face.										
	Vertices[18] = SVertexBase{ SVector{  1.0f, -1.0f,  1.0f }, SVector4{ 0.0f, 0.0f, 1.0f, 1.0f } };
	Vertices[19] = SVertexBase{ SVector{  1.0f, -1.0f, -1.0f }, SVector4{ 0.0f, 0.0f, 1.0f, 1.0f } };
	Vertices[20] = SVertexBase{ SVector{  1.0f,  1.0f, -1.0f }, SVector4{ 0.0f, 0.0f, 1.0f, 1.0f } };
	Vertices[21] = SVertexBase{ SVector{  1.0f,  1.0f,  1.0f }, SVector4{ 0.0f, 0.0f, 1.0f, 1.0f } };
	Vertices[22] = SVertexBase{ SVector{  1.0f, -1.0f,  1.0f }, SVector4{ 0.0f, 0.0f, 1.0f, 1.0f } };
	Vertices[23] = SVertexBase{ SVector{  1.0f,  1.0f, -1.0f }, SVector4{ 0.0f, 0.0f, 1.0f, 1.0f } };
														
	// Bottom face.										
	Vertices[24] = SVertexBase{ SVector{  1.0f, -1.0f, -1.0f }, SVector4{ 1.0f, 0.0f, 0.0f, 1.0f } };
	Vertices[25] = SVertexBase{ SVector{  1.0f, -1.0f,  1.0f }, SVector4{ 1.0f, 0.0f, 0.0f, 1.0f } };
	Vertices[26] = SVertexBase{ SVector{ -1.0f, -1.0f, -1.0f }, SVector4{ 1.0f, 0.0f, 0.0f, 1.0f } };
	Vertices[27] = SVertexBase{ SVector{  1.0f, -1.0f,  1.0f }, SVector4{ 1.0f, 0.0f, 0.0f, 1.0f } };
	Vertices[28] = SVertexBase{ SVector{ -1.0f, -1.0f,  1.0f }, SVector4{ 1.0f, 0.0f, 0.0f, 1.0f } };
	Vertices[29] = SVertexBase{ SVector{ -1.0f, -1.0f, -1.0f }, SVector4{ 1.0f, 0.0f, 0.0f, 1.0f } };
														
	// Top face.										
	Vertices[30] = SVertexBase{ SVector{  1.0f,  1.0f,  1.0f }, SVector4{ 0.0f, 1.0f, 0.0f, 1.0f } };
	Vertices[31] = SVertexBase{ SVector{  1.0f,  1.0f, -1.0f }, SVector4{ 0.0f, 1.0f, 0.0f, 1.0f } };
	Vertices[32] = SVertexBase{ SVector{ -1.0f,  1.0f, -1.0f }, SVector4{ 0.0f, 1.0f, 0.0f, 1.0f } };
	Vertices[33] = SVertexBase{ SVector{ -1.0f,  1.0f,  1.0f }, SVector4{ 0.0f, 1.0f, 0.0f, 1.0f } };
	Vertices[34] = SVertexBase{ SVector{  1.0f,  1.0f,  1.0f }, SVector4{ 0.0f, 1.0f, 0.0f, 1.0f } };
	Vertices[35] = SVertexBase{ SVector{ -1.0f,  1.0f, -1.0f }, SVector4{ 0.0f, 1.0f, 0.0f, 1.0f } };
}


CCube::~CCube()
{

}