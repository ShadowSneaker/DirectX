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

struct STempVertex
{
	SVector Position;
	SVector2 UV;
};

class CFont
{
private:

	/// Properties

	// The default path in files where fonts are usually located.
	const std::string DefaultFilePath{ "Content/Assets/Fonts/" };

	// The text that is printed onto the screen.
	std::string Text;


public:
	// Temporary variables. This is just for testing purposes to make sure this is working correctly. The location of this text will be determined by the object the font it attached to.
	// The font should only know how to draw itself, not where to draw itself. - For that matter should the font know how to draw itself as well? or should that be handled by the renderer? I feel as if the text
	// should know how to draw itself, but just give its details to the renderer and allow the renderer to use it's information to draw the font. The font should not draw itself.
	SVector2 Location;

	float Size{ 0.1f };

private:

	// A lot of these variables I don't think are nessissary, but adding them in until I have a better understanding of how the provided class works.
	ID3D11Device* Device{ nullptr };
	ID3D11DeviceContext* DeviceContext{ nullptr };
	
	ID3D11ShaderResourceView* Texture{ nullptr };
	ID3D11SamplerState* Sampler{ nullptr };
	
	STempVertex Vertices[MAX_CHARACTERS * 6];
	
	ID3D11Buffer* VertexBuffer{ nullptr };
	ID3D11VertexShader* VShader{ nullptr };
	ID3D11PixelShader* PShader{ nullptr };
	ID3D11InputLayout* InputLayout{ nullptr };
	
	ID3D11DepthStencilState* DepthEnabledStencilState{ nullptr };
	ID3D11DepthStencilState* DepthDisabledStencilState{ nullptr };




public:
	/// Constructor

	// Constructor, Default.
	//CFont();

	// Constructor, Initiates the font with a default font type.
	//CFont(std::string FileName, bool UseDefaultFilePath = true);

	// This constructor contains information that I don't think is nessissary for a font class. For example having a reference to the device and device context. This should just be handled in the renderer.
	CFont(std::string FileName, ID3D11Device* InDevice, ID3D11DeviceContext* InDeviceContext);

	// Destructor.
	~CFont();


	/// Functions


	inline void SetText(std::string NewText) { Text = NewText; }

	// I don't think this function should exist in here. This should be handled by the renderer.
	void RenderText();

};