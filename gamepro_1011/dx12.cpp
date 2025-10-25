#include "dx12.h"

#pragma comment(lib, "dxgi.lib")

IDXGIFactory4* dx12::CreateDXGIFactory() 
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

IDXGIAdapter1* dx12::GetHardwareAdapter(IDXGIFactory4* factory)
{
    IDXGIAdapter1* adapter;

    // �n�[�h�E�F�A�A�_�v�^�[�����ԂɌ���
    for (UINT adapterIndex = 0; ; ++adapterIndex)
    {
        adapter = nullptr;
        if (DXGI_ERROR_NOT_FOUND == factory->EnumAdapters1(adapterIndex, &adapter))
        {
            break; // �A�_�v�^�[��������Ȃ��ꍇ�͏I��
        }

        // �A�_�v�^�[�����擾
        DXGI_ADAPTER_DESC1 desc;
        adapter->GetDesc1(&desc);

        // �\�t�g�E�F�A�A�_�v�^�[���X�L�b�v
        if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
        {
            adapter->Release();
            continue;
        }

        // DirectX12�Ή��e�X�g
        if (SUCCEEDED(D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)))
        {
            return adapter; // �K�؂ȃA�_�v�^�[�𔭌�
        }

        adapter->Release();
    }

    return nullptr;
}
ID3D12Device* dx12::CreateD3D12Device(IDXGIAdapter1* adapter)
{
    ID3D12Device* device;

    // �f�o�C�X�쐬�����s
    HRESULT hr = D3D12CreateDevice(
        adapter,                    // �g�p����A�_�v�^�[
        D3D_FEATURE_LEVEL_11_0,     // �ŏ��@�\���x��
        IID_PPV_ARGS(&device)       // �쐬�����f�o�C�X
    );

    if (FAILED(hr))
    {
        // �t�H�[���o�b�N�F�\�t�g�E�F�A�A�_�v�^�[�����s
        hr = D3D12CreateDevice(
            nullptr,                // �K��A�_�v�^�[
            D3D_FEATURE_LEVEL_11_0,
            IID_PPV_ARGS(&device)
        );

        if (FAILED(hr))
        {
            OutputDebugString("Failed to create D3D12 Device\n");
            return nullptr;
        }

        OutputDebugString("Using software adapter (WARP)\n");
    }

    return device;
}
ID3D12CommandQueue* dx12::CreateCommandQueue(ID3D12Device* device)
{
    // �R�}���h�L���[�̐ݒ�
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;    // ���ڎ��s�^
    queueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;  // �ʏ�D��x
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;    // ���ʃt���O�Ȃ�
    queueDesc.NodeMask = 0;                             // �P��GPU�g�p

    ID3D12CommandQueue* commandQueue;
    HRESULT hr = device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue));

    if (FAILED(hr))
    {
        OutputDebugString("Failed to create Command Queue\n");
        return nullptr;
    }

    // �f�o�b�O�p�̖��O�ݒ�i�C�ӂ��������j
    commandQueue->SetName(L"Main Command Queue");

    return commandQueue;
}
IDXGISwapChain3* dx12::CreateSwapChain(IDXGIFactory4* factory, ID3D12CommandQueue* commandQueue, HWND hwnd)
{
    // �X���b�v�`�F�[���̏ڍאݒ�
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.BufferCount = 2;                      // �_�u���o�b�t�@�����O
    swapChainDesc.Width = 1280;                         // ��ʕ�
    swapChainDesc.Height = 720;                         // ��ʍ�
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // �s�N�Z���t�H�[�}�b�g
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;  // �����_�[�^�[�Q�b�g�p
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;     // �����ؑ�
    swapChainDesc.SampleDesc.Count = 1;                 // �}���`�T���v�����O�Ȃ�

    IDXGISwapChain1* swapChain1;
    HRESULT hr = factory->CreateSwapChainForHwnd(
        commandQueue,       // �R�}���h�L���[
        hwnd,              // �^�[�Q�b�g�E�B���h�E
        &swapChainDesc,    // �ݒ�
        nullptr,           // �t���X�N���[���ݒ�
        nullptr,           // �o�͐���
        &swapChain1        // �쐬�����X���b�v�`�F�[��
    );

    if (FAILED(hr))
    {
        OutputDebugString("Failed to create Swap Chain\n");
        return nullptr;
    }

    // ��荂�@�\�ȃC���^�[�t�F�[�X�ɃL���X�g
    IDXGISwapChain3* swapChain;
    hr = swapChain1->QueryInterface(IID_PPV_ARGS(&swapChain));
    swapChain1->Release();

    if (FAILED(hr))
    {
        OutputDebugString("Failed to cast to SwapChain3\n");
        return nullptr;
    }

    return swapChain;
}
void dx12::EnableDebugLayer()
{
#if defined(_DEBUG)
    // �f�o�b�O�C���^�[�t�F�[�X���擾
    ID3D12Debug* debugController;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
    {
        // �f�o�b�O���C���[��L����
        debugController->EnableDebugLayer();

        // ���ڍׂȌ��؂�L�����i�C�Ӂj
        ID3D12Debug1* debugController1;
        if (SUCCEEDED(debugController->QueryInterface(IID_PPV_ARGS(&debugController1))))
        {
            debugController1->SetEnableGPUBasedValidation(TRUE);
        }
    }
#endif
}