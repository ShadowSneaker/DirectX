#include "DirectXSetup.h"
#include <DirectXMath.h>

#include "Meshes/StaticMesh.h"


CDirectXSetup::CDirectXSetup()
{
	
}


CDirectXSetup::~CDirectXSetup()
{
	delete TempMesh;
	delete TempText;
	delete Camera;
	ShutdownD3D();
}


bool CDirectXSetup::Init(HINSTANCE HandleInstance, int CmdShow)
{
	if (FAILED(InitialiseWindow(HandleInstance, CmdShow)))
	{
		DXTRACE_MSG("Failed to create Window!");
		return false;
	}

	if (FAILED(InitialiseD3D()))
	{
		DXTRACE_MSG("Failed to create Device.");
		return false;
	}

	if (FAILED(InitialiseGraphics()))
	{
		DXTRACE_MSG("Failed to initialise graphics.");
		return false;
	}

	Camera = new CCamera{ SVector4{0.0f, 0.0f, -5.0f, 0.0f}, 0.0f };
	TempText = new CFont{ "Content/Assets/Fonts/font1.bmp", Device, DeviceContext };
	TempText->SetText("Beep Boop");
	TempText->Location = SVector2{ -1.0f, 1.0f };
	TempText->Size = 0.1f;

	TempMesh = new CStaticMesh{ Device, DeviceContext };
	TempMesh->SetMesh((char*)"Content/Assets/Models/Sphere.obj");
	

	return true;
}


void CDirectXSetup::ReadMessage()
{
	if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
}


HRESULT CDirectXSetup::InitialiseWindow(HINSTANCE HandleInstance, int CmdShow)
{
	char Name[100] = "Hello World\0";

	WNDCLASSEX WindowClass{ 0 };
	WindowClass.cbSize = sizeof(WNDCLASSEX);
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = WindowProc;
	WindowClass.hInstance = HandleInstance;
	WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	//WindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Needed for non-D3D apps.
	WindowClass.lpszClassName = Name;

	if (!RegisterClassEx(&WindowClass)) return E_FAIL;

	// Create the window.
	Instance = HandleInstance;
	RECT RC{ 0,0,640,480 };
	AdjustWindowRect(&RC, WS_OVERLAPPEDWINDOW, FALSE);

	WindowHandle = CreateWindow(Name, ProjectName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, RC.right - RC.left, RC.bottom - RC.top, NULL, NULL, HandleInstance, NULL);
	if (!WindowHandle) return E_FAIL;

	ShowWindow(WindowHandle, CmdShow);
	return S_OK;
}


LRESULT CALLBACK CDirectXSetup::WindowProc(HWND HWnd, UINT Message, WPARAM WParam, LPARAM LParam)
{
	PAINTSTRUCT PS;
	HDC Hdc;

	switch (Message)
	{
	case WM_PAINT:
		Hdc = BeginPaint(HWnd, &PS);
		EndPaint(HWnd, &PS);
		break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;


	case WM_KEYDOWN:
		if (WParam == VK_ESCAPE)
			//DestroyWindow(WindowHandle);
			//MessageBox(HWnd, "Boop", "Beep", NULL);
			exit(0);
		return 0;


	case WM_MOUSEMOVE:
		break;


	default:
		return DefWindowProc(HWnd, Message, WParam, LParam);
	}

	return 0;
}


HRESULT CDirectXSetup::InitialiseD3D()
{
	HRESULT HR = S_OK;

	RECT Rect;
	GetClientRect(WindowHandle, &Rect);
	UINT Width = Rect.right - Rect.left;
	UINT Height = Rect.bottom - Rect.top;

	UINT CreateDeviceFlags{ 0 };

#ifdef _DEBUG
	//CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE DriverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE, // Comment out this line if you need to test D3D 11.0 functionality on hardware that doesn't support it.
		D3D_DRIVER_TYPE_WARP, // Comment this out also to use reference device.
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT NumberDriverTypes = ARRAYSIZE(DriverTypes);

	D3D_FEATURE_LEVEL FeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT NumFeatureLevels = ARRAYSIZE(FeatureLevels);

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	ZeroMemory(&SwapChainDesc, sizeof(SwapChainDesc));
	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.BufferDesc.Width = Width;
	SwapChainDesc.BufferDesc.Height = Height;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.OutputWindow = WindowHandle;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.Windowed = true;

	for (UINT DriverTypeIndex = 0; DriverTypeIndex < NumberDriverTypes; ++DriverTypeIndex)
	{
		DriverType = DriverTypes[DriverTypeIndex];
		HR = D3D11CreateDeviceAndSwapChain(NULL, DriverType, NULL, CreateDeviceFlags, FeatureLevels, NumFeatureLevels, D3D11_SDK_VERSION, &SwapChainDesc, &SwapChain, &Device, &FeatureLevel, &DeviceContext);
		if (SUCCEEDED(HR))
			break;
	}

	if (FAILED(HR)) return HR;


	// Get pointer to back buffer texture.
	ID3D11Texture2D* BackBufferTexture;
	HR = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBufferTexture);

	if (FAILED(HR)) return HR;

	// Use the back buffer texture pointer to create the render target view.
	HR = Device->CreateRenderTargetView(BackBufferTexture, NULL, &BackBufferRTView);

	BackBufferTexture->Release();

	if (FAILED(HR)) return HR;

	D3D11_TEXTURE2D_DESC Texture2D;
	ZeroMemory(&Texture2D, sizeof(Texture2D));
	Texture2D.Width = Width;
	Texture2D.Height = Height;
	Texture2D.ArraySize = 1;
	Texture2D.MipLevels = 1;
	Texture2D.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	Texture2D.SampleDesc.Count = SwapChainDesc.SampleDesc.Count;
	Texture2D.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	Texture2D.Usage = D3D11_USAGE_DEFAULT;

	ID3D11Texture2D* BufferTexture;
	HR = Device->CreateTexture2D(&Texture2D, NULL, &BufferTexture);

	if (FAILED(HR)) return HR;

	D3D11_DEPTH_STENCIL_VIEW_DESC DepthViewDesc;
	ZeroMemory(&DepthViewDesc, sizeof(DepthViewDesc));

	DepthViewDesc.Format = Texture2D.Format;
	DepthViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	Device->CreateDepthStencilView(BufferTexture, &DepthViewDesc, &ZBuffer);
	BufferTexture->Release();

	DeviceContext->OMSetRenderTargets(1, &BackBufferRTView, ZBuffer);

	// Set viewport.
	D3D11_VIEWPORT Viewport;
	Viewport.TopLeftX = 0;
	Viewport.TopLeftY = 0;
	Viewport.Width = (FLOAT)Width;
	Viewport.Height = (FLOAT)Height;
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 1.0f;
	DeviceContext->RSSetViewports(1, &Viewport);

	return S_OK;
}


void CDirectXSetup::ShutdownD3D()
{
	if (VertexBuffer) VertexBuffer->Release();
	if (InputLayout) InputLayout->Release();
	if (ConstantBuffer) ConstantBuffer->Release();
	if (VertexShader) VertexShader->Release();
	if (PixelShader) PixelShader->Release();
	if (BackBufferRTView) BackBufferRTView->Release();
	if (ZBuffer) ZBuffer->Release();
	if (Texture0) Texture0->Release();
	if (Sampler0) Sampler0->Release();
	if (SwapChain) SwapChain->Release();
	if (DeviceContext) DeviceContext->Release();
	if (Device) Device->Release();
}


HRESULT CDirectXSetup::InitialiseGraphics()
{
	HRESULT HR = S_OK;

	SVertex Vertices[] =
	{
		//{SVector{ 1.0f,   1.0f,  0.0f}, SVector4{1.0f, 0.0f, 0.0f, 1.0f}},
		//{SVector{ 1.0f,  -1.0f,  0.0f}, SVector4{0.0f, 1.0f, 0.0f, 1.0f}},
		//{SVector{-1.0f,  -1.0f,  0.0f}, SVector4{0.0f, 0.0f, 1.0f, 1.0f}},


		// back face
		{SVector{-1.0f,  1.0f,  1.0f}, SVector4{1.0f, 1.0f, 1.0f, 1.0f}, SVector2{0.0f, 0.0f}, SVector{ 0.0f, 0.0f,  1.0f}},
		{SVector{-1.0f, -1.0f,  1.0f}, SVector4{1.0f, 1.0f, 1.0f, 1.0f}, SVector2{0.0f, 1.0f}, SVector{ 0.0f, 0.0f,  1.0f}},
		{SVector{ 1.0f,  1.0f,  1.0f}, SVector4{1.0f, 1.0f, 1.0f, 1.0f}, SVector2{1.0f, 0.0f}, SVector{ 0.0f, 0.0f,  1.0f}},
		{SVector{ 1.0f,  1.0f,  1.0f}, SVector4{1.0f, 1.0f, 1.0f, 1.0f}, SVector2{1.0f, 0.0f}, SVector{ 0.0f, 0.0f,  1.0f}},
		{SVector{-1.0f, -1.0f,  1.0f}, SVector4{1.0f, 1.0f, 1.0f, 1.0f}, SVector2{0.0f, 1.0f}, SVector{ 0.0f, 0.0f,  1.0f}},
		{SVector{ 1.0f, -1.0f,  1.0f}, SVector4{1.0f, 1.0f, 1.0f, 1.0f}, SVector2{1.0f, 1.0f}, SVector{ 0.0f, 0.0f,  1.0f}},
																		 							    
		// front face													 							    
		{SVector{-1.0f, -1.0f, -1.0f}, SVector4{1.0f, 0.0f, 1.0f, 1.0f}, SVector2{0.0f, 0.0f}, SVector{ 0.0f,  0.0f, -1.0f}},
		{SVector{-1.0f,  1.0f, -1.0f}, SVector4{1.0f, 0.0f, 1.0f, 1.0f}, SVector2{0.0f, 1.0f}, SVector{ 0.0f,  0.0f, -1.0f}},
		{SVector{ 1.0f,  1.0f, -1.0f}, SVector4{1.0f, 0.0f, 1.0f, 1.0f}, SVector2{1.0f, 0.0f}, SVector{ 0.0f,  0.0f, -1.0f}},
		{SVector{-1.0f, -1.0f, -1.0f}, SVector4{1.0f, 0.0f, 1.0f, 1.0f}, SVector2{1.0f, 0.0f}, SVector{ 0.0f,  0.0f, -1.0f}},
		{SVector{ 1.0f,  1.0f, -1.0f}, SVector4{1.0f, 0.0f, 1.0f, 1.0f}, SVector2{0.0f, 1.0f}, SVector{ 0.0f,  0.0f, -1.0f}},
		{SVector{ 1.0f, -1.0f, -1.0f}, SVector4{1.0f, 0.0f, 1.0f, 1.0f}, SVector2{1.0f, 1.0f}, SVector{ 0.0f,  0.0f, -1.0f}},
																									    	   
		// left face																				    	   
		{SVector{-1.0f, -1.0f, -1.0f}, SVector4{0.0f, 0.0f, 1.0f, 1.0f}, SVector2{0.0f, 0.0f}, SVector{-1.0f,  0.0f,  0.0f}},
		{SVector{-1.0f, -1.0f,  1.0f}, SVector4{0.0f, 0.0f, 1.0f, 1.0f}, SVector2{0.0f, 1.0f}, SVector{-1.0f,  0.0f,  0.0f}},
		{SVector{-1.0f,  1.0f, -1.0f}, SVector4{0.0f, 0.0f, 1.0f, 1.0f}, SVector2{1.0f, 0.0f}, SVector{-1.0f,  0.0f,  0.0f}},
		{SVector{-1.0f, -1.0f,  1.0f}, SVector4{0.0f, 0.0f, 1.0f, 1.0f}, SVector2{1.0f, 0.0f}, SVector{-1.0f,  0.0f,  0.0f}},
		{SVector{-1.0f,  1.0f,  1.0f}, SVector4{0.0f, 0.0f, 1.0f, 1.0f}, SVector2{0.0f, 1.0f}, SVector{-1.0f,  0.0f,  0.0f}},
		{SVector{-1.0f,  1.0f, -1.0f}, SVector4{0.0f, 0.0f, 1.0f, 1.0f}, SVector2{1.0f, 1.0f}, SVector{-1.0f,  0.0f,  0.0f}},
																									    	   		  
		// right face																				    	   		  
		{SVector{ 1.0f, -1.0f,  1.0f}, SVector4{0.0f, 1.0f, 1.0f, 1.0f}, SVector2{0.0f, 0.0f}, SVector{ 1.0f,  0.0f,  0.0f}},
		{SVector{ 1.0f, -1.0f, -1.0f}, SVector4{0.0f, 1.0f, 1.0f, 1.0f}, SVector2{0.0f, 1.0f}, SVector{ 1.0f,  0.0f,  0.0f}},
		{SVector{ 1.0f,  1.0f, -1.0f}, SVector4{0.0f, 1.0f, 1.0f, 1.0f}, SVector2{1.0f, 0.0f}, SVector{ 1.0f,  0.0f,  0.0f}},
		{SVector{ 1.0f,  1.0f,  1.0f}, SVector4{0.0f, 1.0f, 1.0f, 1.0f}, SVector2{1.0f, 0.0f}, SVector{ 1.0f,  0.0f,  0.0f}},
		{SVector{ 1.0f, -1.0f,  1.0f}, SVector4{0.0f, 1.0f, 1.0f, 1.0f}, SVector2{0.0f, 1.0f}, SVector{ 1.0f,  0.0f,  0.0f}},
		{SVector{ 1.0f,  1.0f, -1.0f}, SVector4{0.0f, 1.0f, 1.0f, 1.0f}, SVector2{1.0f, 1.0f}, SVector{ 1.0f,  0.0f,  0.0f}},
																									    	   		  
		// bottom face																				    	   		  
		{SVector{ 1.0f, -1.0f, -1.0f}, SVector4{0.0f, 1.0f, 0.0f, 1.0f}, SVector2{0.0f, 0.0f}, SVector{ 0.0f, -1.0f,  0.0f}},
		{SVector{ 1.0f, -1.0f,  1.0f}, SVector4{0.0f, 1.0f, 0.0f, 1.0f}, SVector2{0.0f, 1.0f}, SVector{ 0.0f, -1.0f,  0.0f}},
		{SVector{-1.0f, -1.0f, -1.0f}, SVector4{0.0f, 1.0f, 0.0f, 1.0f}, SVector2{1.0f, 0.0f}, SVector{ 0.0f, -1.0f,  0.0f}},
		{SVector{ 1.0f, -1.0f,  1.0f}, SVector4{0.0f, 1.0f, 0.0f, 1.0f}, SVector2{1.0f, 0.0f}, SVector{ 0.0f, -1.0f,  0.0f}},
		{SVector{-1.0f, -1.0f,  1.0f}, SVector4{0.0f, 1.0f, 0.0f, 1.0f}, SVector2{0.0f, 1.0f}, SVector{ 0.0f, -1.0f,  0.0f}},
		{SVector{-1.0f, -1.0f, -1.0f}, SVector4{0.0f, 1.0f, 0.0f, 1.0f}, SVector2{1.0f, 1.0f}, SVector{ 0.0f, -1.0f,  0.0f}},
																									    	   		  
		// top face																					    	   		  
		{SVector{ 1.0f,  1.0f,  1.0f}, SVector4{1.0f, 1.0f, 0.0f, 1.0f}, SVector2{0.0f, 0.0f}, SVector{ 0.0f,  1.0f,  0.0f}},
		{SVector{ 1.0f,  1.0f, -1.0f}, SVector4{1.0f, 1.0f, 0.0f, 1.0f}, SVector2{0.0f, 1.0f}, SVector{ 0.0f,  1.0f,  0.0f}},
		{SVector{-1.0f,  1.0f, -1.0f}, SVector4{1.0f, 1.0f, 0.0f, 1.0f}, SVector2{1.0f, 0.0f}, SVector{ 0.0f,  1.0f,  0.0f}},
		{SVector{-1.0f,  1.0f,  1.0f}, SVector4{1.0f, 1.0f, 0.0f, 1.0f}, SVector2{1.0f, 0.0f}, SVector{ 0.0f,  1.0f,  0.0f}},
		{SVector{ 1.0f,  1.0f,  1.0f}, SVector4{1.0f, 1.0f, 0.0f, 1.0f}, SVector2{0.0f, 1.0f}, SVector{ 0.0f,  1.0f,  0.0f}},
		{SVector{-1.0f,  1.0f, -1.0f}, SVector4{1.0f, 1.0f, 0.0f, 1.0f}, SVector2{1.0f, 1.0f}, SVector{ 0.0f,  1.0f,  0.0f}},

	};

	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	BufferDesc.ByteWidth = sizeof(SVertex) * 36;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	
	HR = Device->CreateBuffer(&BufferDesc, NULL, &VertexBuffer);
	if (FAILED(HR)) return HR;


	D3D11_BUFFER_DESC CBuffer;
	ZeroMemory(&CBuffer, sizeof(CBuffer));
	
	CBuffer.Usage = D3D11_USAGE_DEFAULT;
	CBuffer.ByteWidth = 112;
	CBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	
	HR = Device->CreateBuffer(&CBuffer, NULL, &ConstantBuffer);
	if (FAILED(HR)) return HR;
	

	D3D11_MAPPED_SUBRESOURCE MS;

	DeviceContext->Map(VertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &MS);
	memcpy(MS.pData, Vertices, sizeof(Vertices));
	DeviceContext->Unmap(VertexBuffer, NULL);

	ID3DBlob* VS;
	ID3DBlob* PS;
	ID3DBlob* Error;

	HR = D3DX11CompileFromFile("shaders.hlsl", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, &Error, 0);
	if (Error != 0)
	{
		OutputDebugStringA((char*)Error->GetBufferPointer());
		Error->Release();
		if (FAILED(HR))
		{
			return HR;
		}
	}

	HR = D3DX11CompileFromFile("shaders.hlsl", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, &Error, 0);
	if (Error != 0)
	{
		OutputDebugStringA((char*)Error->GetBufferPointer());
		Error->Release();
		if (FAILED(HR))
		{
			return HR;
		}
	}

	HR = Device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &VertexShader);
	if (FAILED(HR)) return HR;

	HR = Device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &PixelShader);
	if (FAILED(HR)) return HR;

	DeviceContext->VSSetShader(VertexShader, 0, 0);
	DeviceContext->PSSetShader(PixelShader, 0, 0);

	D3D11_INPUT_ELEMENT_DESC IEDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	HR = Device->CreateInputLayout(IEDesc, ARRAYSIZE(IEDesc), VS->GetBufferPointer(), VS->GetBufferSize(), &InputLayout);
	if (FAILED(HR)) return HR;

	DeviceContext->IASetInputLayout(InputLayout);


	D3DX11CreateShaderResourceViewFromFile(Device, "Content/Assets/Texture.bmp", NULL, NULL, &Texture0, NULL);

	D3D11_SAMPLER_DESC SamplerDesc;
	ZeroMemory(&SamplerDesc, sizeof(SamplerDesc));
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	Device->CreateSamplerState(&SamplerDesc, &Sampler0);
	
	return S_OK;
}


// This should be located in the renderer class. Or this should be the renderer class.
void CDirectXSetup::RenderFrame()
{
	// Clear the back buffer.
	float ClearColour[4] = { 0.1f, 0.2f, 0.6f, 1.0f };

	DeviceContext->ClearRenderTargetView(BackBufferRTView, ClearColour);
	DeviceContext->ClearDepthStencilView(ZBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	DeviceContext->PSSetSamplers(0, 1, &Sampler0);
	DeviceContext->PSSetShaderResources(0, 1, &Texture0);



	UINT Stride = sizeof(SVertex);
	UINT Offset = 0;
	DeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &Stride, &Offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	


	SMatrix4 World;

	SConstantBuffer CBValues;

	DirectionalLight[X] = TMath::Sin(TempRotate * 0.01f);

	SMatrix4 Transpose;
	Transpose = SMatrix4::Transpose(World);
	CBValues.DirectionalLightColour = DirectionalLightColour;
	CBValues.AmbientLightColour = AmbientLightColour;
	CBValues.DirectionalLight = Transpose.VectorTransform(DirectionalLight);
	CBValues.DirectionalLight = DirectionalLight.Normalize();

	SMatrix4 Rotation, Translation, Scale;
	Rotation.SetToIdentity();
	Translation.SetToIdentity();
	Scale.SetToIdentity();

	Scale.SetScale(1.0f, 1.0f, 1.0f);

	TempRotate += 0.01f;
	Rotation.SetRotate(TO_RADIAN(TempRotate), TO_RADIAN(TempRotate * 0.5f), TO_RADIAN(TempRotate));
	Translation.SetLocation(0.0f, 0.0f, 5.0f);

	World = Scale * Rotation * Translation;


	SMatrix4 Projection;
	SMatrix4 View;
	View.SetToIdentity();
	View = Camera->GetViewMatrix();
	//DirectX::XMMATRIX Temp = DirectX::XMMatrixLookAtLH(DirectX::XMVECTOR{ 0.0f, 0.0f, -5.0f, 0.0f }, DirectX::XMVECTOR{ 0.0f, 0.0f, -4.0f, 0.0f }, DirectX::XMVECTOR{ 0.0f, 1.0f, 0.0f, 0.0 }); // - Do NOT delete, this may be important for future debugging as I don't think my function above is correct.

	


	Projection = SMatrix4::PersepctiveFovLH(TO_RADIAN(45.0f), 640.0f / 480.0f, 1.0f, 100.0f);
	CBValues.WorldProjection = World * View * Projection;
	



	DeviceContext->UpdateSubresource(ConstantBuffer, 0, 0, &CBValues, 0, 0);

	DeviceContext->VSSetConstantBuffers(0, 1, &ConstantBuffer);
	DeviceContext->IASetInputLayout(InputLayout);
	DeviceContext->VSSetShader(VertexShader, 0, 0);
	DeviceContext->PSSetShader(PixelShader, 0, 0);

	//DeviceContext->Draw(36, 0);
	TempMesh->Draw(&World, &View);
	TempText->RenderText();

	DirectX::XMVECTOR A;
	A.vector4_f32[0] = 5.0;



	// Display what has just been rendered.
	SwapChain->Present(0, 0);
}


