struct Input {
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};

float4 main(Input input) : SV_TARGET {
    
    double dist = sqrt(pow(0.5f - input.uv.x, 2) + pow(0.5f - input.uv.y, 2));
    int mask = step(dist, .4f);
    //clip(mask - 0.1f);
    
    return float4(input.uv,0,1);
}