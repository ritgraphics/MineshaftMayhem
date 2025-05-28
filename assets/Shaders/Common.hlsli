
struct CameraTransform
{
    float4x4 ViewProjection;
};

struct ModelTransform
{
    float4x4 Model;
    float2 TexCoord[4];
};

struct DrawConstants
{
    float DeltaTime;
    float Time;
};

struct VertexPositionTextureInput
{
    float3 Position : POSITION;
    float2 TexCoord : TEXCOORD;
};

struct VertexPositionTextureOutput
{
    float4 Position : SV_Position;
    float2 TexCoord : TEXCOORD;
};