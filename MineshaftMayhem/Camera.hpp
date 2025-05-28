

#pragma once

#include <SimpleMath.h>

class Camera
{
public:
    Camera(DirectX::SimpleMath::Vector3 position,
           DirectX::SimpleMath::Vector3 direction,
           DirectX::SimpleMath::Vector3 up,
           float                        fov,
           float                        aspectRatio,
           float                        nearPlane,
           float                        farPlane,
           float                        viewWidth,
           float                        viewHeight);

    [[nodiscard]] float                        viewWidth() const;

    [[nodiscard]] float                        viewHeight() const;

    [[nodiscard]] DirectX::SimpleMath::Matrix  viewProjection() const;

    [[nodiscard]] DirectX::SimpleMath::Vector3 direction() const;

    [[nodiscard]] DirectX::SimpleMath::Vector3 right() const;

    [[nodiscard]] DirectX::SimpleMath::Vector3 position() const;

    void                                       moveForward(float dt);

    void                                       moveBackward(float dt);

    void                                       strafeLeft(float dt);

    void                                       strafeRight(float dt);

    void                                       rotate(float pitch, float yaw);

    void                                       setPosition(const DirectX::SimpleMath::Vector3& position);

    void                                       setRotation(const DirectX::SimpleMath::Vector3& rotation);

    void                                       setProjection(
                                              float fov, float aspectRatio, float nearPlane, float farPlane, float viewWidth, float viewHeight);

private:
    void                            updateUniforms();

    DirectX::SimpleMath::Quaternion m_orientation;
    DirectX::SimpleMath::Matrix     m_viewProjection;
    DirectX::SimpleMath::Matrix     m_projection;
    DirectX::SimpleMath::Matrix     m_view;
    DirectX::SimpleMath::Vector3    m_position;
    DirectX::SimpleMath::Vector3    m_direction;
    DirectX::SimpleMath::Vector3    m_rotation;
    float                           m_fieldOfView;
    float                           m_aspectRatio;
    float                           m_nearPlane;
    float                           m_farPlane;
    float                           m_speed = 10.0f;
    float                           m_viewWidth = 800.0f;
    float                           m_viewHeight = 600.0f;
};
