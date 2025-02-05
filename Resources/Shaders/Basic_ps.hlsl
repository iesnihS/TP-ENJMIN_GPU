struct Input {
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};

Texture2D tex : register(t0);
SamplerState samplerState : register(s0);

float4 main(Input input) : SV_TARGET {
    float2 uv = input.uv;
    double dist = sqrt(pow(0.5f - uv.x, 2) + pow(0.5f - uv.y, 2));
    int mask = step(dist, .4f);
    float4 color = tex.Sample(samplerState, uv);
    //clip(mask - 0.1f);
    
    return color;
}