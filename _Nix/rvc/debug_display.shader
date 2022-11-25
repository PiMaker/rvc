Shader "Nix/Debug Display"
{
    Properties
    {
        _Background ("Background", Color) = (0, 0, 0, 0)
        _RVC ("Texture", 2D) = "white" {}
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" "Queue"="Geometry" }
        Cull Back

        Pass
        {
            CGPROGRAM
            #include "UnityCG.cginc"
            #include "helpers.cginc"

            #define STATE_TEX_HART(pos, hart) (_RVC[pos])
            #define STATE_TEX(pos) (_RVC[pos])
            Texture2D<uint4> _RVC;

            static uint2 s_dim;

            #define NEEDS_DFC
            #include "src/types.h"

            #include "SmoothPixelFont.cginc"

            #pragma target 5.0
            // too lazy to change lmao enjoy your full screen ortho
            #pragma vertex vert_ortho_fullscreen
            #pragma fragment frag

            float4 _Background;

            float4 frag(v2f i) : SV_Target {
                //_RVC.GetDimensions(s_dim.x, s_dim.y);
                uint2 pos = i.uv * uint2(256, 512);

                decode_for_commit();

                #define SS __SPACE
                float2 charUV = float2(4, 6) - glsl_mod(i.uv.xy * float2(16, 16), 1.0) * float2(4.0, 6.0);
                uint toDisplay = 0xdeadbeef;
                       if (pos.y < 32 * 1) {
                    toDisplay = cpu.clock;
                    if (pos.x < 128) {
                        uint txt[8] = {__C, __L, __O, __C, __K, SS, SS, SS};
                        float num = PrintChar(txt[pos.x/16], charUV, 4.0, 0) * 0.35;
                        return float4(num, num, num, 1);
                    }
                } else if (pos.y < 32 * 2) {
                    toDisplay = cpu.commits;
                    if (pos.x < 128) {
                        uint txt[8] = {__C, __O, __M, __M, __I, __T, __S, SS};
                        float num = PrintChar(txt[pos.x/16], charUV, 4.0, 0) * 0.35;
                        return float4(num, num, num, 1);
                    }
                } else if (pos.y < 32 * 3) {
                    toDisplay = cpu.trap_count;
                    if (pos.x < 128) {
                        uint txt[8] = {__T, __R, __A, __P, __S, SS, SS, SS};
                        float num = PrintChar(txt[pos.x/16], charUV, 4.0, 0) * 0.35;
                        return float4(num, num, num, 1);
                    }
                } else if (pos.y < 32 * 4) {
                    toDisplay = cpu.stall_count;
                    if (pos.x < 128) {
                        uint txt[8] = {__S, __T, __A, __L, __L, __S, SS, SS};
                        float num = PrintChar(txt[pos.x/16], charUV, 4.0, 0) * 0.35;
                        return float4(num, num, num, 1);
                    }
                } else if (pos.y < 32 * 5) {
                    toDisplay = cpu.debug_last_stall;
                    if (pos.x < 128) {
                        uint txt[8] = {__L, __A, __S, __T, SS, __S, __T, __L};
                        float num = PrintChar(txt[pos.x/16], charUV, 4.0, 0) * 0.35;
                        return float4(num, num, num, 1);
                    }
                } else if (pos.y < 32 * 6) {
                    toDisplay = cpu.debug_last_ins;
                    if (pos.x < 128) {
                        uint txt[8] = {__L, __A, __S, __T, SS, __I, __N, __S};
                        float num = PrintChar(txt[pos.x/16], charUV, 4.0, 0) * 0.35;
                        return float4(num, num, num, 1);
                    }
                } else if (pos.y < 32 * 7) {
                    toDisplay = cpu.pc;
                    if (pos.x < 128) {
                        uint txt[8] = {__P, __C, SS, SS, SS, SS, SS, SS};
                        float num = PrintChar(txt[pos.x/16], charUV, 4.0, 0) * 0.35;
                        return float4(num, num, num, 1);
                    }
                } else if (pos.y < 32 * 8) {
                    toDisplay = cpu.mmu.mode;
                    if (pos.x < 128) {
                        uint txt[8] = {__M, __M, __U, SS, __M, __O, __D, __E};
                        float num = PrintChar(txt[pos.x/16], charUV, 4.0, 0) * 0.35;
                        return float4(num, num, num, 1);
                    }
                } else if (pos.y < 32 * 9) {
                    toDisplay = cpu.mmu.ppn;
                    if (pos.x < 128) {
                        uint txt[8] = {__M, __M, __U, SS, __P, __P, __N, SS};
                        float num = PrintChar(txt[pos.x/16], charUV, 4.0, 0) * 0.35;
                        return float4(num, num, num, 1);
                    }
                } else if (pos.y < 32 * 10) {
                    toDisplay = cpu.csr.privilege;
                    if (pos.x < 128) {
                        uint txt[8] = {__P, __R, __I, __V, SS, SS, SS, SS};
                        float num = PrintChar(txt[pos.x/16], charUV, 4.0, 0) * 0.35;
                        return float4(num, num, num, 1);
                    }
                } else if (pos.y < 32 * 11) {
                    toDisplay = cpu.uart.input_tag;
                    if (pos.x < 128) {
                        uint txt[8] = {__U, __A, __R, __T, SS, __T, __A, __G};
                        float num = PrintChar(txt[pos.x/16], charUV, 4.0, 0) * 0.35;
                        return float4(num, num, num, 1);
                    }
                } else if (pos.y < 32 * 12) {
                    toDisplay = cpu.rtc0;
                    if (pos.x < 128) {
                        uint txt[8] = {__R, __T, __C, __0, SS, SS, SS, SS};
                        float num = PrintChar(txt[pos.x/16], charUV, 4.0, 0) * 0.35;
                        return float4(num, num, num, 1);
                    }
                } else if (pos.y < 32 * 13) {
                    toDisplay = cpu.rtc1;
                    if (pos.x < 128) {
                        uint txt[8] = {__R, __T, __C, __1, SS, SS, SS, SS};
                        float num = PrintChar(txt[pos.x/16], charUV, 4.0, 0) * 0.35;
                        return float4(num, num, num, 1);
                    }
                } else if (pos.y < 32 * 14) {
                    toDisplay = cpu.memop_src_p;
                    if (pos.x < 128) {
                        uint txt[8] = {__M, __E, __M, __O, __P, __S, __R, __C};
                        float num = PrintChar(txt[pos.x/16], charUV, 4.0, 0) * 0.35;
                        return float4(num, num, num, 1);
                    }
                } else if (pos.y < 32 * 15) {
                    toDisplay = cpu.memop_dst_p;
                    if (pos.x < 128) {
                        uint txt[8] = {__M, __E, __M, __O, __P, __D, __S, __T};
                        float num = PrintChar(txt[pos.x/16], charUV, 4.0, 0) * 0.35;
                        return float4(num, num, num, 1);
                    }
                } else if (pos.y < 32 * 16) {
                    toDisplay = cpu.debug_arb_0;
                    if (pos.x < 128) {
                        uint txt[8] = {__D, __E, __B, __U, __G, SS, SS, SS};
                        float num = PrintChar(txt[pos.x/16], charUV, 4.0, 0) * 0.35;
                        return float4(num, num, num, 1);
                    }
                }

                pos.x -= 128;
                if (pos.x > (128 + 16)) {
                    return 0;
                }
                uint modx = pos.x % (128 + 16);
                uint val = 16;
                if (modx < 128) {
                    val = (toDisplay >> (((16 * 16) - modx) / 16) * 4) & 0xf;
                }
                uint hex[17] = {__0, __1, __2, __3, __4, __5, __6, __7, __8, __9, __A, __B, __C, __D, __E, __F, __SPACE};
                float num = PrintChar(hex[val], charUV, 4.0, 0) * 0.55;
                return float4(num, num, num, 1);
            }
            ENDCG
        }
    }
}