#pragma once

#include <DirectXColors.h>

#include "StaticGeometry.h"

class GeometryBuilder
{
public:
    explicit GeometryBuilder(ID3D12Device* device) : m_device(device)
    {
    }

    template <typename VertexType>
    inline std::unique_ptr<StaticGeometry<VertexType>> ConstructCube(float size = 1.0f)
    {
    }

    template <typename VertexType>
    inline std::unique_ptr<StaticGeometry<VertexType>> ConstructQuad(float size = 1.0f)
    {
    }

    template <typename VertexType>
    inline std::unique_ptr<StaticGeometry<VertexType>> ConstructQuadCulled(float size = 1.0f)
    {
    }

    template <typename VertexType>
    inline std::unique_ptr<StaticGeometry<VertexType>> ConstructQuad(DirectX::SimpleMath::Vector2 origin,
                                                                     float                        size = 1.0f);

private:
    ID3D12Device* m_device;
};

template <>
inline std::unique_ptr<StaticGeometry<VertexPositionColor>> GeometryBuilder::ConstructCube(float size)
{
    using namespace DirectX::SimpleMath;

    // Define the geometry for a cube.
    const VertexPositionColor cubeVertices[] = {
        // Back Face
        {{size, size, -size}, Vector4{DirectX::Colors::Black}},
        {{-size, size, -size}, Vector4{DirectX::Colors::White}},
        {{size, -size, -size}, Vector4{DirectX::Colors::LimeGreen}},
        {{-size, -size, -size}, Vector4{DirectX::Colors::Purple}},

        // Front Face
        {{-size, size, size}, Vector4{DirectX::Colors::Black}},
        {{size, size, size}, Vector4{DirectX::Colors::White}},
        {{-size, -size, size}, Vector4{DirectX::Colors::LimeGreen}},
        {{size, -size, size}, Vector4{DirectX::Colors::Purple}},

        //// Top Face
        {{-size, size, -size}, Vector4{DirectX::Colors::Black}},
        {{size, size, -size}, Vector4{DirectX::Colors::White}},
        {{-size, size, size}, Vector4{DirectX::Colors::LimeGreen}},
        {{size, size, size}, Vector4{DirectX::Colors::Purple}},

        // Bottom Face
        {{size, -size, -size}, Vector4{DirectX::Colors::Black}},
        {{-size, -size, -size}, Vector4{DirectX::Colors::White}},
        {{size, -size, size}, Vector4{DirectX::Colors::LimeGreen}},
        {{-size, -size, size}, Vector4{DirectX::Colors::Purple}},

        //// Left Face
        {{-size, size, -size}, Vector4{DirectX::Colors::Black}},
        {{-size, size, size}, Vector4{DirectX::Colors::White}},
        {{-size, -size, -size}, Vector4{DirectX::Colors::LimeGreen}},
        {{-size, -size, size}, Vector4{DirectX::Colors::Purple}},

        // Right Face
        {{size, size, size}, Vector4{DirectX::Colors::Black}},
        {{size, size, -size}, Vector4{DirectX::Colors::White}},
        {{size, -size, size}, Vector4{DirectX::Colors::LimeGreen}},
        {{size, -size, -size}, Vector4{DirectX::Colors::Purple}},
    };

    // Define indices for a cube so that each triangle is front-facing
    constexpr uint16_t cubeIndices[] = {
        0,  1,  2,  2,  1,  3,  // Front Face
        4,  5,  6,  6,  5,  7,  // Back Face
        8,  9,  10, 10, 9,  11, // Top Face
        12, 13, 14, 14, 13, 15, // Bottom Face
        16, 17, 18, 18, 17, 19, // Left Face
        20, 21, 22, 22, 21, 23  // Right Face
    };

    return std::make_unique<StaticGeometry<VertexPositionColor>>(m_device, cubeVertices, ARRAYSIZE(cubeVertices),
                                                                 cubeIndices, ARRAYSIZE(cubeIndices));
}

template <>
inline std::unique_ptr<StaticGeometry<VertexPositionTexture>> GeometryBuilder::ConstructCube(float size)
{
    using namespace DirectX::SimpleMath;

    // Define the geometry for a cube.
    const VertexPositionTexture cubeVertices[] = {
        // Back Face
        {{size, size, -size}, {0.0f, 0.0f}},
        {{-size, size, -size}, {1.0f, 0.0f}},
        {{size, -size, -size}, {0.0f, 1.0f}},
        {{-size, -size, -size}, {1.0f, 1.0f}},

        // Front Face
        {{-size, size, size}, {0.0f, 0.0f}},
        {{size, size, size}, {1.0f, 0.0f}},
        {{-size, -size, size}, {0.0f, 1.0f}},
        {{size, -size, size}, {1.0f, 1.0f}},

        //// Top Face
        {{-size, size, -size}, {0.0f, 0.0f}},
        {{size, size, -size}, {1.0f, 0.0f}},
        {{-size, size, size}, {0.0f, 1.0f}},
        {{size, size, size}, {1.0f, 1.0f}},

        // Bottom Face
        {{size, -size, -size}, {0.0f, 0.0f}},
        {{-size, -size, -size}, {1.0f, 0.0f}},
        {{size, -size, size}, {0.0f, 1.0f}},
        {{-size, -size, size}, {1.0f, 1.0f}},

        //// Left Face
        {{-size, size, -size}, {0.0f, 0.0f}},
        {{-size, size, size}, {1.0f, 0.0f}},
        {{-size, -size, -size}, {0.0f, 1.0f}},
        {{-size, -size, size}, {1.0f, 1.0f}},

        // Right Face
        {{size, size, size}, {0.0f, 0.0f}},
        {{size, size, -size}, {1.0f, 0.0f}},
        {{size, -size, size}, {0.0f, 1.0f}},
        {{size, -size, -size}, {1.0f, 1.0f}},
    };

    // Define indices for a cube so that each triangle is front-facing
    constexpr uint16_t cubeIndices[] = {
        0,  1,  2,  2,  1,  3,  // Front Face
        4,  5,  6,  6,  5,  7,  // Back Face
        8,  9,  10, 10, 9,  11, // Top Face
        12, 13, 14, 14, 13, 15, // Bottom Face
        16, 17, 18, 18, 17, 19, // Left Face
        20, 21, 22, 22, 21, 23  // Right Face
    };

    return std::make_unique<StaticGeometry<VertexPositionTexture>>(m_device, cubeVertices, ARRAYSIZE(cubeVertices),
                                                                   cubeIndices, ARRAYSIZE(cubeIndices));
}

template <>
inline std::unique_ptr<StaticGeometry<Vertex>> GeometryBuilder::ConstructCube(float size)
{
    using namespace DirectX::SimpleMath;

    // Define the geometry for a cube.
    const Vertex cubeVertices[] = {
        // Back Face
        {{size, size, -size}, Vector4{DirectX::Colors::Black}, {0.0f, 0.0f}},
        {{-size, size, -size}, Vector4{DirectX::Colors::White}, {1.0f, 0.0f}},
        {{size, -size, -size}, Vector4{DirectX::Colors::LimeGreen}, {0.0f, 1.0f}},
        {{-size, -size, -size}, Vector4{DirectX::Colors::Purple}, {1.0f, 1.0f}},

        // Front Face
        {{-size, size, size}, Vector4{DirectX::Colors::Black}, {0.0f, 0.0f}},
        {{size, size, size}, Vector4{DirectX::Colors::White}, {1.0f, 0.0f}},
        {{-size, -size, size}, Vector4{DirectX::Colors::LimeGreen}, {0.0f, 1.0f}},
        {{size, -size, size}, Vector4{DirectX::Colors::Purple}, {1.0f, 1.0f}},

        //// Top Face
        {{-size, size, -size}, Vector4{DirectX::Colors::Black}, {0.0f, 0.0f}},
        {{size, size, -size}, Vector4{DirectX::Colors::White}, {1.0f, 0.0f}},
        {{-size, size, size}, Vector4{DirectX::Colors::LimeGreen}, {0.0f, 1.0f}},
        {{size, size, size}, Vector4{DirectX::Colors::Purple}, {1.0f, 1.0f}},

        // Bottom Face
        {{size, -size, -size}, Vector4{DirectX::Colors::Black}, {0.0f, 0.0f}},
        {{-size, -size, -size}, Vector4{DirectX::Colors::White}, {1.0f, 0.0f}},
        {{size, -size, size}, Vector4{DirectX::Colors::LimeGreen}, {0.0f, 1.0f}},
        {{-size, -size, size}, Vector4{DirectX::Colors::Purple}, {1.0f, 1.0f}},

        //// Left Face
        {{-size, size, -size}, Vector4{DirectX::Colors::Black}, {0.0f, 0.0f}},
        {{-size, size, size}, Vector4{DirectX::Colors::White}, {1.0f, 0.0f}},
        {{-size, -size, -size}, Vector4{DirectX::Colors::LimeGreen}, {0.0f, 1.0f}},
        {{-size, -size, size}, Vector4{DirectX::Colors::Purple}, {1.0f, 1.0f}},

        // Right Face
        {{size, size, size}, Vector4{DirectX::Colors::Black}, {0.0f, 0.0f}},
        {{size, size, -size}, Vector4{DirectX::Colors::White}, {1.0f, 0.0f}},
        {{size, -size, size}, Vector4{DirectX::Colors::LimeGreen}, {0.0f, 1.0f}},
        {{size, -size, -size}, Vector4{DirectX::Colors::Purple}, {1.0f, 1.0f}},
    };

    // Define indices for a cube so that each triangle is front-facing
    constexpr uint16_t cubeIndices[] = {
        0,  1,  2,  2,  1,  3,  // Front Face
        4,  5,  6,  6,  5,  7,  // Back Face
        8,  9,  10, 10, 9,  11, // Top Face
        12, 13, 14, 14, 13, 15, // Bottom Face
        16, 17, 18, 18, 17, 19, // Left Face
        20, 21, 22, 22, 21, 23  // Right Face
    };

    return std::make_unique<StaticGeometry<Vertex>>(m_device, cubeVertices, ARRAYSIZE(cubeVertices), cubeIndices,
                                                    ARRAYSIZE(cubeIndices));
}

template <>
inline std::unique_ptr<StaticGeometry<VertexPositionTexture>> GeometryBuilder::ConstructQuad(float size)
{
    using namespace DirectX::SimpleMath;

    const VertexPositionTexture quadVerts[] = {
        // Front face
        {{-size, size, 0.0f}, {0.0f, 0.0f}},
        {{size, size, 0.0f}, {1.0f, 0.0f}},
        {{-size, -size, 0.0f}, {0.0f, 1.0f}},
        {{size, -size, 0.0f}, {1.0f, 1.0f}},

        // Back face
        {{size, size, 0.0f}, {0.0f, 0.0f}},
        {{-size, size, 0.0f}, {1.0f, 0.0f}},
        {{size, -size, 0.0f}, {0.0f, 1.0f}},
        {{-size, -size, 0.0f}, {1.0f, 1.0f}},
    };

    constexpr uint16_t quadIndices[] = {0, 1, 2, 2, 1, 3, 4, 5, 6, 6, 5, 7};

    return std::make_unique<StaticGeometry<VertexPositionTexture>>(m_device, quadVerts, ARRAYSIZE(quadVerts),
                                                                   quadIndices, ARRAYSIZE(quadIndices));
}

template <>
inline std::unique_ptr<StaticGeometry<VertexPositionTexture>> GeometryBuilder::ConstructQuad(
    DirectX::SimpleMath::Vector2 origin, float size)
{
    using namespace DirectX::SimpleMath;

    const VertexPositionTexture    quadVerts[] = {
        // Front face
        {{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
        {{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},

        // Back face
        //{{size, size, 0.0f}, {0.0f, 0.0f}},
        //{{-size, size, 0.0f}, {1.0f, 0.0f}},
        //{{size, -size, 0.0f}, {0.0f, 1.0f}},
        //{{-size, -size, 0.0f}, {1.0f, 1.0f}},
    };

    constexpr uint16_t quadIndices[] = {
        0, 1, 2, 2, 1, 3,
    }; // 4, 5, 6, 6, 5, 7};

    return std::make_unique<StaticGeometry<VertexPositionTexture>>(m_device, quadVerts, ARRAYSIZE(quadVerts),
                                                                   quadIndices, ARRAYSIZE(quadIndices));
}

template <>
inline std::unique_ptr<StaticGeometry<VertexPositionTexture>> GeometryBuilder::ConstructQuadCulled(float size)
{
    using namespace DirectX::SimpleMath;

    const VertexPositionTexture quadVerts[] = {
        // Front face
        {{-size, size, 0.0f}, {0.0f, 0.0f}},
        {{size, size, 0.0f}, {1.0f, 0.0f}},
        {{-size, -size, 0.0f}, {0.0f, 1.0f}},
        {{size, -size, 0.0f}, {1.0f, 1.0f}},
    };

    constexpr uint16_t quadIndices[] = {0, 1, 2, 2, 1, 3};

    return std::make_unique<StaticGeometry<VertexPositionTexture>>(m_device, quadVerts, ARRAYSIZE(quadVerts),
                                                                   quadIndices, ARRAYSIZE(quadIndices));
}