#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <dxerr.h>
//#include <xnamath.h>
//#include <vector>

#include "../Math/DataTypes/Vector.h"
#include "../Math/DataTypes/Vertex.h"



// The maximum amount of characters the text can have.
const uint MAX_CHARACTERS = 10000;



// A temporary vertex type for fonts.
struct STempVertex
{
	// The position of the vertex.
	SVector Position;

	// The uv of the vertex.
	SVector2 UV;
};



// Text that can be displayed to the screen.
class CFont
{
private:
	/// Properties

	// The default path in files where fonts are usually located.
	const std::string DefaultFilePath{ "Content/Assets/Fonts/" };

	// The text that is printed onto the screen.
	std::string Text;



public:
	// The location on screen where the text should be displayed.
	SVector2 Location;

	// The scale of the text on the screen.
	float Size{ 0.1f };

private:

	// A lot of these variables I don't think are nessissary, but adding them in until I have a better understanding of how the provided class works.

	// A reference to the directX device.
	ID3D11Device* Device{ nullptr };

	// A reference to the directx device context.
	ID3D11DeviceContext* DeviceContext{ nullptr };
	
	// A reference to the texture of the text.
	ID3D11ShaderResourceView* Texture{ nullptr };

	// A reference to the samepler state.
	ID3D11SamplerState* Sampler{ nullptr };
	
	// A list of vertices to represent each character.
	STempVertex Vertices[MAX_CHARACTERS * 6];
	
	// A reference to the vertex buffer.
	ID3D11Buffer* VertexBuffer{ nullptr };

	// A reference of the vertex shader.
	ID3D11VertexShader* VShader{ nullptr };

	// A reference of the pixel shader.
	ID3D11PixelShader* PShader{ nullptr };

	// A reference of the input layout
	ID3D11InputLayout* InputLayout{ nullptr };
	
	// A reference to the enable depeth stencil state.
	ID3D11DepthStencilState* DepthEnabledStencilState{ nullptr };

	// A reference to the disable depth stencil state.
	ID3D11DepthStencilState* DepthDisabledStencilState{ nullptr };



public:
	/// Constructor

	// This constructor contains information that I don't think is nessissary for a font class. For example having a reference to the device and device context. This should just be handled in the renderer.
	CFont(std::string FileName, ID3D11Device* InDevice, ID3D11DeviceContext* InDeviceContext);

	// Destructor.
	~CFont();



	/// Functions

	// Sets the text to be displayed on the screen.
	inline void SetText(std::string NewText) { Text = NewText; }

	// Draws the text on the screen.
	void RenderText();
};