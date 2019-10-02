#include "DirectXSetup.h"


CDirectXSetup::CDirectXSetup()
{
	
}


CDirectXSetup::~CDirectXSetup()
{
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
}


void CDirectXSetup::ReadMessage()
{
	if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	else
	{
		// Do something.
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
			MessageBox(HWnd, "Boop", "Beep", NULL);
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

	DeviceContext->OMSetRenderTargets(1, &BackBufferRTView, NULL);

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
	if (VertexShader) VertexShader->Release();
	if (PixelShader) PixelShader->Release();
	if (BackBufferRTView) BackBufferRTView->Release();
	if (SwapChain) SwapChain->Release();
	if (ConstantBuffer) ConstantBuffer->Release();
	if (DeviceContext) DeviceContext->Release();
	if (Device) Device->Release();
}


HRESULT CDirectXSetup::InitialiseGraphics()
{
	HRESULT HR = S_OK;

	SVertex Vertices[] =
	{
		{XMFLOAT3(0.9f,  0.9f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		{XMFLOAT3(0.9f, -0.9f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
		{XMFLOAT3(-0.9f,-0.9f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)}
	};

	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	BufferDesc.ByteWidth = sizeof(SVertex) * 3;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	
	HR = Device->CreateBuffer(&BufferDesc, NULL, &VertexBuffer);
	if (FAILED(HR)) return HR;


	D3D11_BUFFER_DESC CBuffer;
	ZeroMemory(&CBuffer, sizeof(CBuffer));

	CBuffer.Usage = D3D11_USAGE_DEFAULT;
	CBuffer.ByteWidth = 80;
	CBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	HR = Device->CreateBuffer(&CBuffer, NULL, &ConstantBuffer);
	if (FAILED(HR)) return HR;

	SConstantBuffer CBValues;
	CBValues.RedAmount = 0.5f;

	DeviceContext->UpdateSubresource(ConstantBuffer, 0, 0, &CBValues, 0, 0);

	DeviceContext->VSSetConstantBuffers(0, 1, &ConstantBuffer);
	

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
	};

	HR = Device->CreateInputLayout(IEDesc, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &InputLayout);
	if (FAILED(HR)) return HR;

	DeviceContext->IASetInputLayout(InputLayout);


	
	return S_OK;
}


// This should be located in the renderer class. Or this should be the renderer class.
void CDirectXSetup::RenderFrame()
{
	// Clear the back buffer.
	float ClearColour[4] = { 0.1f, 0.2f, 0.6f, 1.0f };

	DeviceContext->ClearRenderTargetView(BackBufferRTView, ClearColour);

	UINT Stride = sizeof(SVertex);
	UINT Offset = 0;
	DeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &Stride, &Offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DeviceContext->Draw(3, 0);


	// Display what has just been rendered.
	SwapChain->Present(0, 0);
}


