#include "dx12.h"
#include<d3d12.h>
#include<dxgi1_4.h>
#pragma comment(lib, "dxgi.lib")

IDXGIFactory4* CreateDXGIFactory() 
{
	IDXGIFactory4* factory;
	UINT createFactoryFlags = 0;

# if defined(_DEBUG)
	// デバッグビルドではデバッグフラグを設定
	createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif

	HRESULT hr = CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&factory));
		if (FAILED(hr)) 
		{
		//エラーハンドリング:ファクトリー作成失敗
			OutputDebugString("Faild to create DXGI Factory\n");
			return nullptr;
		}

	return factory;
	
}

IDXGIAdapter* GetHardwareAdaptet(IDXGIFactory4* factory) 
{

}