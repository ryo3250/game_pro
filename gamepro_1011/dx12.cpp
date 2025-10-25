#include "dx12.h"
#include<d3d12.h>
#include<dxgi1_4.h>
#pragma comment(lib, "dxgi.lib")

IDXGIFactory4* CreateDXGIFactory() 
{
	IDXGIFactory4* factory;
	UINT createFactoryFlags = 0;

# if defined(_DEBUG)
	// �f�o�b�O�r���h�ł̓f�o�b�O�t���O��ݒ�
	createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif

	HRESULT hr = CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&factory));
		if (FAILED(hr)) 
		{
		//�G���[�n���h�����O:�t�@�N�g���[�쐬���s
			OutputDebugString("Faild to create DXGI Factory\n");
			return nullptr;
		}

	return factory;
	
}

IDXGIAdapter* GetHardwareAdaptet(IDXGIFactory4* factory) 
{

}