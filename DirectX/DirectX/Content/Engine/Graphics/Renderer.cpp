#include "Renderer.h"


CRenderer::CRenderer(HINSTANCE HandleInstance, int CommandShow)
{
	Window = new CWindow{ WindowName };
	if (FAILED(Window->InitialiseWindow(HandleInstance, CommandShow)))
	{
		exit(0);
	}

	Setup = new CDirectXSetup{ Window };

	if (FAILED(Setup->Initialise()))
	{
		exit(0);
	}


}


CRenderer::~CRenderer()
{
	DeleteShaders();
}


void CRenderer::DeleteShaders()
{
	for (auto Index = Shaders.begin(); Index != Shaders.end(); ++Index)
	{
		Index->second.InputLayout->Release();
		Index->second.PixelShader->Release();
		Index->second.VertexShader->Release();
	}
}


void CRenderer::DrawAll()
{
	// TODO:
	// TEMPORARY, MOVE TO INPUT CLASS
	if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

}