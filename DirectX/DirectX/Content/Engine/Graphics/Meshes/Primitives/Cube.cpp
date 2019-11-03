#include "Cube.h"


CCube::CCube(class CRenderer* InRenderer)
	:CStaticMesh::CStaticMesh{ InRenderer }
{
	VertexCount = 36;
	//Vertices = new SModelVertex[VertexCount];
	Vertices = new SVertex[VertexCount];

	// Back face.
	Vertices[0]  = SVertex{ SVector{ -1.0f,  1.0f,  1.0f }, SVector4{ 0.0f, 1.0f, 1.0f, 1.0f }, SVector2{ 0.0f, 0.0f }, SVector{  0.0f,  0.0f,  1.0f } };
	Vertices[1]  = SVertex{ SVector{ -1.0f, -1.0f,  1.0f }, SVector4{ 0.0f, 1.0f, 1.0f, 1.0f }, SVector2{ 0.0f, 1.0f }, SVector{  0.0f,  0.0f,  1.0f } };
	Vertices[2]  = SVertex{ SVector{  1.0f,  1.0f,  1.0f }, SVector4{ 0.0f, 1.0f, 1.0f, 1.0f }, SVector2{ 1.0f, 0.0f }, SVector{  0.0f,  0.0f,  1.0f } };
	Vertices[3]  = SVertex{ SVector{  1.0f,  1.0f,  1.0f }, SVector4{ 0.0f, 1.0f, 1.0f, 1.0f }, SVector2{ 1.0f, 0.0f }, SVector{  0.0f,  0.0f,  1.0f } };
	Vertices[4]  = SVertex{ SVector{ -1.0f, -1.0f,  1.0f }, SVector4{ 0.0f, 1.0f, 1.0f, 1.0f }, SVector2{ 0.0f, 1.0f }, SVector{  0.0f,  0.0f,  1.0f } };
	Vertices[5]  = SVertex{ SVector{  1.0f, -1.0f,  1.0f }, SVector4{ 0.0f, 1.0f, 1.0f, 1.0f }, SVector2{ 1.0f, 1.0f }, SVector{  0.0f,  0.0f,  1.0f } };
			    																									 					 	    
	// Front face.																									 					 	    
	Vertices[6]  = SVertex{ SVector{ -1.0f, -1.0f, -1.0f }, SVector4{ 1.0f, 0.0f, 1.0f, 1.0f }, SVector2{ 0.0f, 1.0f }, SVector{  0.0f,  0.0f, -1.0f } };
	Vertices[7] =  SVertex{ SVector{ -1.0f,  1.0f, -1.0f }, SVector4{ 1.0f, 0.0f, 1.0f, 1.0f }, SVector2{ 0.0f, 0.0f }, SVector{  0.0f,  0.0f, -1.0f } };
	Vertices[8] =  SVertex{ SVector{  1.0f,  1.0f, -1.0f }, SVector4{ 1.0f, 0.0f, 1.0f, 1.0f }, SVector2{ 1.0f, 0.0f }, SVector{  0.0f,  0.0f, -1.0f } };
	Vertices[9] =  SVertex{ SVector{ -1.0f, -1.0f, -1.0f }, SVector4{ 1.0f, 0.0f, 1.0f, 1.0f }, SVector2{ 0.0f, 1.0f }, SVector{  0.0f,  0.0f, -1.0f } };
	Vertices[10] = SVertex{ SVector{  1.0f,  1.0f, -1.0f }, SVector4{ 1.0f, 0.0f, 1.0f, 1.0f }, SVector2{ 1.0f, 0.0f }, SVector{  0.0f,  0.0f, -1.0f } };
	Vertices[11] = SVertex{ SVector{  1.0f, -1.0f, -1.0f }, SVector4{ 1.0f, 0.0f, 1.0f, 1.0f }, SVector2{ 1.0f, 1.0f }, SVector{  0.0f,  0.0f, -1.0f } };
																													 					 	    
	// Left face.																									 					 	    
	Vertices[12] = SVertex{ SVector{ -1.0f, -1.0f, -1.0f }, SVector4{ 1.0f, 1.0f, 0.0f, 1.0f }, SVector2{ 0.0f, 1.0f }, SVector{ -1.0f,  0.0f,  0.0f } };
	Vertices[13] = SVertex{ SVector{ -1.0f, -1.0f,  1.0f }, SVector4{ 1.0f, 1.0f, 0.0f, 1.0f }, SVector2{ 0.0f, 0.0f }, SVector{ -1.0f,  0.0f,  0.0f } };
	Vertices[14] = SVertex{ SVector{ -1.0f,  1.0f, -1.0f }, SVector4{ 1.0f, 1.0f, 0.0f, 1.0f }, SVector2{ 1.0f, 1.0f }, SVector{ -1.0f,  0.0f,  0.0f } };
	Vertices[15] = SVertex{ SVector{ -1.0f, -1.0f,  1.0f }, SVector4{ 1.0f, 1.0f, 0.0f, 1.0f }, SVector2{ 0.0f, 0.0f }, SVector{ -1.0f,  0.0f,  0.0f } };
	Vertices[16] = SVertex{ SVector{ -1.0f,  1.0f,  1.0f }, SVector4{ 1.0f, 1.0f, 0.0f, 1.0f }, SVector2{ 1.0f, 0.0f }, SVector{ -1.0f,  0.0f,  0.0f } };
	Vertices[17] = SVertex{ SVector{ -1.0f,  1.0f, -1.0f }, SVector4{ 1.0f, 1.0f, 0.0f, 1.0f }, SVector2{ 1.0f, 1.0f }, SVector{ -1.0f,  0.0f,  0.0f } };
																													 					 	    
	// Right face.																														 	    
	Vertices[18] = SVertex{ SVector{  1.0f, -1.0f,  1.0f }, SVector4{ 0.0f, 0.0f, 1.0f, 1.0f }, SVector2{ 0.0f, 0.0f }, SVector{  1.0f,  0.0f,  0.0f } };
	Vertices[19] = SVertex{ SVector{  1.0f, -1.0f, -1.0f }, SVector4{ 0.0f, 0.0f, 1.0f, 1.0f }, SVector2{ 0.0f, 1.0f }, SVector{  1.0f,  0.0f,  0.0f } };
	Vertices[20] = SVertex{ SVector{  1.0f,  1.0f, -1.0f }, SVector4{ 0.0f, 0.0f, 1.0f, 1.0f }, SVector2{ 1.0f, 1.0f }, SVector{  1.0f,  0.0f,  0.0f } };
	Vertices[21] = SVertex{ SVector{  1.0f,  1.0f,  1.0f }, SVector4{ 0.0f, 0.0f, 1.0f, 1.0f }, SVector2{ 1.0f, 0.0f }, SVector{  1.0f,  0.0f,  0.0f } };
	Vertices[22] = SVertex{ SVector{  1.0f, -1.0f,  1.0f }, SVector4{ 0.0f, 0.0f, 1.0f, 1.0f }, SVector2{ 0.0f, 0.0f }, SVector{  1.0f,  0.0f,  0.0f } };
	Vertices[23] = SVertex{ SVector{  1.0f,  1.0f, -1.0f }, SVector4{ 0.0f, 0.0f, 1.0f, 1.0f }, SVector2{ 1.0f, 1.0f }, SVector{  1.0f,  0.0f,  0.0f } };
																																  		 	    
	// Bottom face.																												  		 	    
	Vertices[24] = SVertex{ SVector{  1.0f, -1.0f, -1.0f }, SVector4{ 1.0f, 0.0f, 0.0f, 1.0f }, SVector2{ 1.0f, 1.0f }, SVector{  0.0f, -1.0f,  0.0f } };
	Vertices[25] = SVertex{ SVector{  1.0f, -1.0f,  1.0f }, SVector4{ 1.0f, 0.0f, 0.0f, 1.0f }, SVector2{ 1.0f, 0.0f }, SVector{  0.0f, -1.0f,  0.0f } };
	Vertices[26] = SVertex{ SVector{ -1.0f, -1.0f, -1.0f }, SVector4{ 1.0f, 0.0f, 0.0f, 1.0f }, SVector2{ 0.0f, 1.0f }, SVector{  0.0f, -1.0f,  0.0f } };
	Vertices[27] = SVertex{ SVector{  1.0f, -1.0f,  1.0f }, SVector4{ 1.0f, 0.0f, 0.0f, 1.0f }, SVector2{ 1.0f, 0.0f }, SVector{  0.0f, -1.0f,  0.0f } };
	Vertices[28] = SVertex{ SVector{ -1.0f, -1.0f,  1.0f }, SVector4{ 1.0f, 0.0f, 0.0f, 1.0f }, SVector2{ 0.0f, 0.0f }, SVector{  0.0f, -1.0f,  0.0f } };
	Vertices[29] = SVertex{ SVector{ -1.0f, -1.0f, -1.0f }, SVector4{ 1.0f, 0.0f, 0.0f, 1.0f }, SVector2{ 0.0f, 1.0f }, SVector{  0.0f, -1.0f,  0.0f } };

	// Top face.
	Vertices[30] = SVertex{ SVector{  1.0f,  1.0f,  1.0f }, SVector4{ 0.0f, 1.0f, 0.0f, 1.0f }, SVector2{ 1.0f, 0.0f }, SVector{  0.0f,  1.0f,  0.0f } };
	Vertices[31] = SVertex{ SVector{  1.0f,  1.0f, -1.0f }, SVector4{ 0.0f, 1.0f, 0.0f, 1.0f }, SVector2{ 1.0f, 1.0f }, SVector{  0.0f,  1.0f,  0.0f } };
	Vertices[32] = SVertex{ SVector{ -1.0f,  1.0f, -1.0f }, SVector4{ 0.0f, 1.0f, 0.0f, 1.0f }, SVector2{ 0.0f, 1.0f }, SVector{  0.0f,  1.0f,  0.0f } };
	Vertices[33] = SVertex{ SVector{ -1.0f,  1.0f,  1.0f }, SVector4{ 0.0f, 1.0f, 0.0f, 1.0f }, SVector2{ 0.0f, 0.0f }, SVector{  0.0f,  1.0f,  0.0f } };
	Vertices[34] = SVertex{ SVector{  1.0f,  1.0f,  1.0f }, SVector4{ 0.0f, 1.0f, 0.0f, 1.0f }, SVector2{ 1.0f, 0.0f }, SVector{  0.0f,  1.0f,  0.0f } };
	Vertices[35] = SVertex{ SVector{ -1.0f,  1.0f, -1.0f }, SVector4{ 0.0f, 1.0f, 0.0f, 1.0f }, SVector2{ 0.0f, 1.0f }, SVector{  0.0f,  1.0f,  0.0f } };
}


CCube::~CCube()
{
																													 
}