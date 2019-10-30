#include "DirectXSetup.h"


CDirectXSetup::CDirectXSetup(CWindow* InWindow)
	:Window{ InWindow }
{

}


CDirectXSetup::~CDirectXSetup()
{
	if (SwapChain) SwapChain->Release();
	if (DeviceContext) DeviceContext->Release();
	if (Device) Device->Release();
}


HRESULT CDirectXSetup::Initialise()
{
	HRESULT HR = S_OK;

	RECT Rect;
	GetClientRect(Window->GetWindowHandle(), &Rect);
	UINT Width = Rect.right - Rect.left;
	UINT Height = Rect.bottom - Rect.top;

	UINT CreateDeviceFlags = 0;

#ifdef _DEBUG
	//CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE DriverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};

	UINT NumDriverTypes = ARRAYSIZE(DriverTypes);

	D3D_FEATURE_LEVEL FeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	uint NumFeatureLevels = ARRAYSIZE(FeatureLevels);

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	ZeroMemory(&SwapChainDesc, sizeof(SwapChainDesc));
	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.BufferDesc.Width = Width;
	SwapChainDesc.BufferDesc.Height = Height;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.OutputWindow = Window->GetWindowHandle();
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.Windowed = true;

	for (uint i = 0; i < NumDriverTypes; ++i)
	{
		DriverType = DriverTypes[i];
		HR = D3D11CreateDeviceAndSwapChain(NULL, DriverType, NULL, CreateDeviceFlags, FeatureLevels, NumFeatureLevels, D3D11_SDK_VERSION, &SwapChainDesc, &SwapChain, &Device, &FeatureLevel, &DeviceContext);
		
		if (SUCCEEDED(HR)) break;
	}

	if (FAILED(HR)) return HR;


	ID3D11Texture2D* BackBufferTexture;
	HR = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBufferTexture);

	if (FAILED(HR)) return HR;

	HR = Device->CreateRenderTargetView(BackBufferTexture, NULL, &BackBuffer);

	BackBufferTexture->Release();

	DeviceContext->OMSetRenderTargets(1, &BackBuffer, NULL);

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


void CDirectXSetup::ClearView()
{
	DeviceContext->ClearRenderTargetView(BackBuffer, ClearColour);
}