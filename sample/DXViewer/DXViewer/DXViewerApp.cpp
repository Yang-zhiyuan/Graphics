#include "stdafx.h"
#include "resource.h"
#include "DXViewerApp.h"

DXViewerApp::DXViewerApp(HINSTANCE instance) {
    instance_ = instance;
}

DXViewerApp::~DXViewerApp() {

}

bool DXViewerApp::Init() {
    window_ = CreateViewerWindow(instance_, width_, height_);
    if (window_) {
        ShowWindow(window_, SW_SHOW);
        UpdateWindow(window_);
    }
    else {
        return false;
    }

    engine_.InitDirect3D(window_, width_, height_);

    return true;
}

void DXViewerApp::Run() {
    MSG msg;
    // ����Ϣѭ��: 
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK DXViewerApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // �����˵�ѡ��: 
        switch (wmId)
        {
        case IDM_ABOUT:
            //DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: �ڴ˴�����ʹ�� hdc ���κλ�ͼ����...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

HWND DXViewerApp::CreateViewerWindow(HINSTANCE instance, const unsigned int width, const unsigned int height) {
    WNDCLASSEXW wcex;
    const LPCWSTR window_class = L"DXViewerClass";
    const LPCWSTR window_title = L"DXViewer";
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = (WNDPROC)DXViewerApp::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = instance;
    wcex.hIcon = LoadIcon(instance, MAKEINTRESOURCE(IDI_DXVIEWER));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DXVIEWER);
    wcex.lpszClassName = window_class;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    ATOM ca = RegisterClassExW(&wcex);
    if (!ca) {
        return NULL;
    }

    return CreateWindowW(window_class, window_title, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, instance, nullptr);
}