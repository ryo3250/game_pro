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
    HINSTANCE hInstance,      // アプリケーションの識別番号
    HINSTANCE hPrevInstance,  // 基本使わなくていい
    LPSTR lpCmdLine,          // コマンドライン引数（起動時のオプション）
    int nCmdShow              // ウィンドウの表示方法（最大化、最小化など）
)
// 1. ウィンドウクラス登録
{
    WNDCLASS wc{};
    wc.lpfnWndProc = WindowProc; // ウィンドウプロシージャを指定（後述）
    wc.hInstance = hInstance; // アプリケーションインスタンス
    wc.lpszClassName = "GameWindow"; // ウィンドウクラス名
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // マウスカーソル
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // 背景色

    RegisterClass(&wc); // Windowsに登録

    // 2. ウィンドウ作成
    HWND hwnd = CreateWindow(
        "GameWindow", // ウィンドウクラス名
        "My GodGame", // ウィンドウタイトル
        WS_OVERLAPPEDWINDOW, // ウィンドウスタイル
        CW_USEDEFAULT, CW_USEDEFAULT, // 位置（自動）
        800, 600, // サイズ（幅、高さ）
        NULL, NULL, // 親ウィンドウ、メニュー
        hInstance, // インスタンス
        NULL // 追加データ
    );

    ShowWindow(hwnd, nCmdShow); // ウィンドウを表示

    // 3. メッセージループ
    bool nextFrame = true;

    //ゲームループ
    while (nextFrame)
    {
        MSG msg{};
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) 
            {
                nextFrame = false;
            }
            TranslateMessage(&msg); // キーボードメッセージを使いやすい形に変換
            DispatchMessage(&msg); // 適切なウィンドウプロシージャに送信
        }
    }
    // ここにメインの処理を書く
    
    return 0;
}