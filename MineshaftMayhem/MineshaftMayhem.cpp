// MineshaftMayhem.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "framework.h"
#include "MineshaftMayhem.h"

#include "Game.h"
#include "GameTimer.hpp"

#include <format>

extern "C"
{
    __declspec(dllexport) extern const UINT D3D12SDKVersion = D3D12_SDK_VERSION;
}

extern "C"
{
    __declspec(dllexport) extern const auto* D3D12SDKPath = u8".\\D3D12\\";
}

int APIENTRY wWinMain(_In_ HINSTANCE     hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR        lpCmdLine,
                      _In_ int           nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);

    std::unique_ptr<Game> game;
    try
    {
        game = std::make_unique<Game>(hInstance, lpCmdLine, nCmdShow);
    }
    catch (const std::exception& e)
    {
        const std::string errorMessage = std::format("Error: {}\n", e.what());
        OutputDebugStringA(errorMessage.c_str());
        return EXIT_FAILURE;
    }

    GameTimer timer;
    timer.ResetElapsedTime();
    timer.SetFixedTimeStep(false);

    MSG msg = {};
    while (game->IsRunning())
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        const float deltaTime = timer.GetElapsedSeconds();

        Game*       g = game.get();
        timer.Tick([&] { g->Update(deltaTime); });

        game->Render(deltaTime);
    }

    game.reset();

    return (int)msg.wParam;
}
