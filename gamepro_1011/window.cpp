#include "window.h"

namespace 
{
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

[[nodiscard]] HRESULT window::create(HINSTANCE instance, int Width, int height, std::string_view name)noexcept
{
	WNDCLASS wc{};
	wc.lpfnWndProc   = WindowProc;
	wc.hInstance     = instance;
	wc.lpszClassName = name.data();
	wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	RegisterClass(&wc);

	handle_ = CreateWindow(wc.lpszClassName, wc.lpszClassName,
						   WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, Width, height,
						   nullptr, nullptr, instance, nullptr);
	if (!handle_) 
	{
		return E_FAIL;
	}

	ShowWindow(handle_, SW_SHOW);

	UpdateWindow(handle_);

	witdh_ = witdh;
	height_ = height;

	return S_OK;
}
