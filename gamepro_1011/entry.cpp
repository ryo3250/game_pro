#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
    switch (uMsg) 
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:

        return 0;
    case WM_KEYDOWN:

        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
int WINAPI WinMain(
    HINSTANCE hInstance,      // �A�v���P�[�V�����̎��ʔԍ�
    HINSTANCE hPrevInstance,  // ��{�g��Ȃ��Ă���
    LPSTR lpCmdLine,          // �R�}���h���C�������i�N�����̃I�v�V�����j
    int nCmdShow              // �E�B���h�E�̕\�����@�i�ő剻�A�ŏ����Ȃǁj
)
// 1. �E�B���h�E�N���X�o�^
{
    WNDCLASS wc{};
    wc.lpfnWndProc = WindowProc; // �E�B���h�E�v���V�[�W�����w��i��q�j
    wc.hInstance = hInstance; // �A�v���P�[�V�����C���X�^���X
    wc.lpszClassName = "GameWindow"; // �E�B���h�E�N���X��
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // �}�E�X�J�[�\��
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // �w�i�F

    RegisterClass(&wc); // Windows�ɓo�^

    // 2. �E�B���h�E�쐬
    HWND hwnd = CreateWindow(
        "GameWindow", // �E�B���h�E�N���X��
        "My GodGame", // �E�B���h�E�^�C�g��
        WS_OVERLAPPEDWINDOW, // �E�B���h�E�X�^�C��
        CW_USEDEFAULT, CW_USEDEFAULT, // �ʒu�i�����j
        800, 600, // �T�C�Y�i���A�����j
        NULL, NULL, // �e�E�B���h�E�A���j���[
        hInstance, // �C���X�^���X
        NULL // �ǉ��f�[�^
    );

    ShowWindow(hwnd, nCmdShow); // �E�B���h�E��\��

    // 3. ���b�Z�[�W���[�v
    bool nextFrame = true;

    //�Q�[�����[�v
    while (nextFrame)
    {
        MSG msg{};
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) 
            {
                nextFrame = false;
            }
            TranslateMessage(&msg); // �L�[�{�[�h���b�Z�[�W���g���₷���`�ɕϊ�
            DispatchMessage(&msg); // �K�؂ȃE�B���h�E�v���V�[�W���ɑ��M
        }
    }
    // �����Ƀ��C���̏���������
    
    return 0;
}