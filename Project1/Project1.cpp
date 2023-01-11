// Project1.cpp : Definuje vstupní bod pro aplikaci.

#include "pch.h"
#include "Project1.h"
#include "Utils.h"
#include <string>
#include <iostream>
#include <fstream>
#include "GameLogic.h"

#define MAX_LOADSTRING 100

using namespace Utils;

// Globální proměnné:
HWND inputBox;
std::vector<unsigned int> seed;
std::vector<int> r;
HWND Life;
HWND Score;
HINSTANCE hInst;                                // aktuální instance
WCHAR szTitle[MAX_LOADSTRING];                  // Text záhlaví
WCHAR szWindowClass[MAX_LOADSTRING];            // název třídy hlavního okna

// Předat dál deklarace funkcí zahrnuté v tomto modulu kódu:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    

    // Inicializovat globální řetězce
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Provést inicializaci aplikace:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT1));

    MSG msg;

    // MAIN PROGRAM LOOP
    // Hlavní smyčka zpráv:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        //MessageBoxA(NULL, "Sus", "Amogus", MB_OK);
    }

    return (int) msg.wParam;
}



//
//  FUNKCE: MyRegisterClass()
//
//  ÚČEL: Zaregistruje třídu okna.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNKCE: InitInstance(HINSTANCE, int)
//
//   ÚČEL: Uloží popisovač instance a vytvoří hlavní okno.
//
//   KOMENTÁŘE:
//
//        V této funkci uložíme popisovač instance do globální proměnné
//        a vytvoříme a zobrazíme hlavní okno programu.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    // Konzole
    //AllocConsole();
    //FILE* file;
    //freopen_s(&file, "CONOUT$", "w", stdout);

    hInst = hInstance; // Uloží popisovač instance do naší globální proměnné.

    // Window scaling mega věc
    RECT s;
    s.left = 0;
    s.top = 0;
    s.right = 640;
    s.bottom = 640;

    AdjustWindowRectEx(&s, WS_OVERLAPPEDWINDOW, 0, 0);
    int width = s.right - s.left;
    int height = s.bottom - s.top;

    HWND hWnd = CreateWindowEx(NULL,szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
      CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

// Přidá interaktivní prvky 

void AddControl(const HWND* hWnd) {
    HWND Start = CreateWindow(L"BUTTON", L"Try", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 280, 220, 100, 50, *hWnd, (HMENU)1, (HINSTANCE)GetWindowLongPtr(*hWnd, GWLP_HINSTANCE), NULL);
    inputBox = CreateWindow(L"Edit", L"", WS_BORDER | WS_CHILD | WS_VISIBLE, 280, 100, 200, 50, *hWnd, (HMENU)3, NULL, NULL);
    CreateWindow(L"static", L"Enter your prediction:", WS_BORDER | WS_CHILD | WS_VISIBLE, 180, 100, 100, 50, *hWnd, (HMENU)NULL, NULL, NULL);
    CreateWindow(L"static", L"Score:", WS_BORDER | WS_CHILD | WS_VISIBLE, 180, 160, 60, 20, *hWnd, (HMENU)NULL, NULL, NULL);
    CreateWindow(L"static", L"Life:", WS_BORDER | WS_CHILD | WS_VISIBLE, 180, 180, 60, 20, *hWnd, (HMENU)NULL, NULL, NULL);
    Score = CreateWindow(L"static", L"0", WS_BORDER | WS_CHILD | WS_VISIBLE, 230, 160, 20, 20, *hWnd, (HMENU)NULL, NULL, NULL);
    Life = CreateWindow(L"static", L"5", WS_BORDER | WS_CHILD | WS_VISIBLE, 230, 180, 20, 20, *hWnd, (HMENU)NULL, NULL, NULL);
    HWND Restart = CreateWindow(L"BUTTON", L"Restart", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 280, 280, 100, 50, *hWnd, (HMENU)2, (HINSTANCE)GetWindowLongPtr(*hWnd, GWLP_HINSTANCE), NULL);
    //HWND Shop = CreateWindow(L"BUTTON", L"Shop", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 280, 340, 100, 50, *hWnd, (HMENU)4, (HINSTANCE)GetWindowLongPtr(*hWnd, GWLP_HINSTANCE), NULL);
}

void RandomNumber(int range, int* rndNum, unsigned int* seed) {
    unsigned int sd = (unsigned)std::time(NULL);
    std::srand(sd);
    *rndNum = 1 + (std::rand() % range);
    *seed = sd;
}

//
//  FUNKCE: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ÚČEL: Zpracuje zprávy pro hlavní okno.
//
//  WM_COMMAND  - zpracování aplikační nabídky
//  WM_PAINT    - Vykreslení hlavního okna
//  WM_DESTROY  - vystavení zprávy o ukončení a návrat
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        AddControl(&hWnd);
        break;
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analyzovat vybrané možnosti nabídky:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case IDM_DARKMODE: {
                ::MessageBox(NULL, L"IN THE CONSTRUCTION!", L"GAME", MB_OK);
                //Game game(1600, 900);
                //game.Run();
                break;
            }
            case 1: {
                char inp[10];
                char life[2];
                char score[2];  // Broken
                GetWindowTextA(Life, life, 2);
                GetWindowTextA(Score, score, 2);
                if (std::stoi(score) == 8) {
                    ::MessageBoxW(NULL, L"YOU WON! 🥳 Press restart to play again!", L"Game", MB_OK | MB_ICONINFORMATION);
                    break;
                }
                if (life == std::to_string(0)) {
                    int moz = ::MessageBoxW(NULL, L"You lost! Do you want to save random numbers?", L"Game", MB_YESNO | MB_ICONINFORMATION);
                    switch (moz) {
                    case IDYES: {
                        ::MessageBoxW(NULL, L"Saving to current directory!", L"Game", MB_OK | MB_ICONINFORMATION);
                        std::ofstream pRnd("past_rnd.txt", std::ios_base::app);
                        std::ofstream sed("seeds.txt", std::ios_base::app);
                        for (int i = 0; i < r.size(); i++) {
                            pRnd << r[i] << std::endl;
                        }
                        for (int i = 0; i < seed.size(); i++) {
                            sed << seed[i] << std::endl;
                        }
                        sed.close();
                        pRnd.close();
                        break;
                    }
                    case IDNO:
                    default:
                        break;
                    }
                    break;
                }

                int rnd;
                unsigned int sd;
                RandomNumber(10, &rnd, &sd);
                int su = GetWindowTextA(inputBox, inp, 10);
                r.push_back(rnd);
                seed.push_back(sd);
                if (inp == std::to_string(rnd)) {
                    SetWindowText(Score, std::to_wstring(std::stoi(score) + 1).c_str());
                    SetWindowText(inputBox, L"");
                    break;
                }
                if (inp == std::to_string(69420)) {
                    SetWindowText(Score, std::to_wstring(std::stoi(score) + 1).c_str());
                    SetWindowText(inputBox, L"");
                    break;
                }
                SetWindowText(Life, std::to_wstring(std::stoi(life) - 1).c_str());
                ::MessageBox(NULL, std::to_wstring(rnd).c_str(), L"Correct num", MB_OK);
                SetWindowText(inputBox, L"");
                break;
                //::MessageBoxA(NULL, std::to_string(rnd).c_str(), "Game", MB_OK | MB_ICONINFORMATION);
            }
            case 2:
                ::MessageBox(NULL, L"Restarted game!", L"Game", MB_OK | MB_ICONINFORMATION);
                SetWindowTextA(Score, "0");
                SetWindowTextA(Life, "5");
                r.clear();
                seed.clear();
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
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        //FreeConsole();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Obslužná rutina zprávy pro pole O produktu
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
