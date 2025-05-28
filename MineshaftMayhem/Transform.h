#pragma once

#include <SimpleMath.h>

struct Transform
{
    explicit Transform(DirectX::SimpleMath::Vector3 position,
                       DirectX::SimpleMath::Vector3 rotation = DirectX::SimpleMath::Vector3::Zero,
                       DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3::One)
        : Position(position), Rotation(rotation), Scale(scale)
    {
    }

    DirectX::SimpleMath::Vector3 Position;
    DirectX::SimpleMath::Vector3 Rotation;
    DirectX::SimpleMath::Vector3 Scale;
};
