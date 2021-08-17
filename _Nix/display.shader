Shader "Nix/Display"
{
    Properties
    {
        _Tex ("Texture", 2D) = "white" {}
    }
    SubShader
    {
        Tags { "RenderType"="Transparent" "Queue"="Transparent" }
        Blend SrcAlpha OneMinusSrcAlpha
        Cull Off

        Pass
        {
            CGPROGRAM
            #include "UnityCG.cginc"
            #include "rvc/helpers.cginc"
            #pragma target 5.0
            #pragma vertex vert_ortho_fullscreen
            #pragma fragment frag

            Texture2D<uint4> _Tex;

            float4 frag(v2f i) : SV_Target {
                uint2 dim;
                _Tex.GetDimensions(dim.x, dim.y);

                if (is_ortho) {
                    // FIXME: state size is hardcoded here...
                    uint2 pos = (i.uv * (uint2(128, 128) * uint2(6, 1))) % uint2(128, 128);
                    uint4 data = _Tex[pos];

                    // output packed values, stretched along x
                    float3 res[6];
                    pack_uint4(data, res);

                    uint idx = (uint)(i.uv.x * 6);
                    return float4(res[idx], 1);
                } else {
                    uint2 pos = i.uv * dim;
                    uint4 data = _Tex[pos];
                    return float4(uint_to_color(data).rgb, 1);
                }
            }
            ENDCG
        }
    }
}
