#pragma once

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

#include <winrt/base.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <dxgi1_6.h>
#include <dstorage.h>

#ifndef NDEBUG
#include <pix3.h>
#endif

#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <DirectXColors.h>
#include <DirectXHelpers.h>

#include <Keyboard.h>
#include <Mouse.h>
#include <Gamepad.h>

#include <string>
#include <memory>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <filesystem>
#include <cstdint>