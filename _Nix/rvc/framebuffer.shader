Shader "Nix/fb"
{
    Properties
    {
        [ToggleUI] _Init ("Init", float) = 0
        
        _Data ("Data CRT", 2D) = "black" {}
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" "IgnoreProjector"="true" }
        Cull Off
        ZTest Off
        Lighting Off
        Blend One Zero

        Pass
        {
            Name "Update"

            CGPROGRAM
            #pragma target 5.0
            #pragma vertex CustomRenderTextureVertexShader
            #pragma fragment frag

            // Cache buster: 6

            // custom crt include
            #include "crt_float4.cginc"
            #include "UnityCG.cginc"

            float _Init;
            Texture2D<uint4> _Data;

            #define STATE_TEX_HART(pos, hartidx) (_Data[uint2(pos) + uint2(hartidx % 2, hartidx / 2)])
            #define STATE_TEX(pos) (_Data[pos])

            static uint2 s_dim;

            #define PASS_FB

            #include "helpers.cginc"
            #include "src/types.h"
            #include "src/fb.h"

            float4 frag(v2f_customrendertexture i) : SV_Target {
                _SelfTexture2D.GetDimensions(s_dim.x, s_dim.y);
                uint2 pos = i.globalTexcoord.xy * s_dim;

                if (_Init) {
                    return float4(0, 0, 0, 0);
                }

                decode_for_commit();
                float4 scratchraw = _SelfTexture2D[uint2(0, 0)];
                uint4 scratch1 = uint4(scratchraw*255.0f+0.5f);
                scratchraw = _SelfTexture2D[uint2(0, 1)];
                uint4 scratch2 = uint4(scratchraw*255.0f+0.5f);
                bool isScratch = pos.x == 0;

                if (!isScratch) {
                    pos -= uint2(1, 0);
                }

                pos.y = 25 - pos.y - 1;
                float4 result = update_fb(pos, cpu.uart_buffer, scratch1, scratch2);

                if (isScratch) {
                    if (pos.y == 24) {
                        return float4(scratch1.rgb / 255.0f, 1);
                    } else if (pos.y == 23) {
                        return float4(scratch2.rgb / 255.0f, 1);
                    } else {
                        return 0;
                    }
                }

                // I think alpha must be 1 for successful Udon readback...
                return float4(result.rgb, 1);
            }
            ENDCG
        }
    }
}
