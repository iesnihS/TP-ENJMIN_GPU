struct Input
{
    float4 pos : POSITION0; // c'est la cementique qui permet de difinir le type de data recu
    float2 uv : TEXCOORD0;
};

cbuffer ModelData : register(b0) //register permet de definir l'input slot
{
    float4x4 Model;
};
cbuffer CameraData : register(b1)
{
    float4x4 View;
    float4x4 Projection;
};

struct Output
{
    float4 pos : SV_POSITION; //System Value notifie le pipeline que c'est pas une valeur anodine
    float2 uv : TEXCOORD0;
};

Output main(Input input)
{
    Output output = (Output) 0;

    output.pos = mul(input.pos, Model);
    output.pos = mul(output.pos, View);
    output.pos = mul(output.pos, Projection);
    output.uv = input.uv;
    
    return output;
}