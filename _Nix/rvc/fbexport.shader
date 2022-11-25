Shader "Nix/FB Export"
{
    Properties
    {
        _Tex ("Texture", 2D) = "white" {}
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" "Queue"="Geometry" }
        Cull Off

        Pass
        {
            CGPROGRAM
            #include "UnityCG.cginc"
            #include "helpers.cginc"
            #pragma target 5.0
            #pragma vertex vert_ortho_fullscreen
            #pragma fragment frag

            Texture2D<float4> _Tex;

            float4 frag(v2f i) : SV_Target {
                uint2 dim;
                _Tex.GetDimensions(dim.x, dim.y);

                if (is_ortho) {
                    uint2 pos = i.uv * dim;
                    float4 data = _Tex[pos];
                    return data;
                } else {
                    uint2 pos = i.uv * dim;
                    float4 data = _Tex[pos];
                    return data;
                }
            }
            ENDCG
        }
    }
}
