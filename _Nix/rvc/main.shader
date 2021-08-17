Shader "Nix/rvc"
{
    Properties
    {
        [ToggleUI] _Init ("Init", float) = 0
        [ToggleUI] _InitRaw ("Init directly from _Data_RAM_RAW", float) = 0
        _Ticks ("Ticks per Frame", Int) = 1024
        _TicksDivisor ("Tick Divisor", Int) = 4
        _UdonUARTPtr ("UART ptr on Udon side", Int) = 0

        _UdonUARTInChar ("UART input Udon side", Int) = 0
        _UdonUARTInTag ("UART input unique tag", Int) = 0

        _Data_RAM_R ("RAM Texture R", 2D) = "black" {}
        _Data_RAM_G ("RAM Texture G", 2D) = "black" {}
        _Data_RAM_B ("RAM Texture B", 2D) = "black" {}
        _Data_RAM_A ("RAM Texture A", 2D) = "black" {}

        _Data_RAM_RAW ("RAM Texture RAW", 2D) = "black" {}

        _Data_DTB_R ("Device Tree Binary Texture R", 2D) = "black" {}
        _Data_DTB_G ("Device Tree Binary Texture G", 2D) = "black" {}
        _Data_DTB_B ("Device Tree Binary Texture B", 2D) = "black" {}
        _Data_DTB_A ("Device Tree Binary Texture A", 2D) = "black" {}

        _DoTick ("DEBUG: Perform single step", Int) = 0
        /* _BreakpointLow ("DEBUG: Breakpoint: Enter single step mode at this PC address (low 16)", Int) = 0 */
        /* _BreakpointHigh ("DEBUG: Breakpoint: Enter single step mode at this PC address (high 16)", Int) = 0 */
        /* _BreakpointLowClock ("DEBUG: Breakpoint: Enter single step mode at this clock (low 16)", Int) = 0 */
        /* _BreakpointHighClock ("DEBUG: Breakpoint: Enter single step mode at this clock (high 16)", Int) = 0 */
        /* _CheckCSR ("DEBUG: Display CSR", Int) = 0 */
        /* _CheckMEM ("DEBUG: Display RAM", Int) = 0 */
        /* [ToggleUI] _CheckMEMraw ("DEBUG: Display RAM raw (not | 0x80000000)", Int) = 0 */
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
            Name "CPUTick"

            CGPROGRAM
            #pragma target 5.0
            #pragma vertex CustomRenderTextureVertexShader
            #pragma fragment frag

            #define PASS_TICK

            // custom crt include w/ Texture2D<uint4> self-reference
            #include "crt.cginc"
            #include "UnityCG.cginc"

            uniform uint _Init, _InitRaw;
            uniform uint _Ticks, _TicksDivisor;
            uniform uint _UdonUARTPtr, _UdonUARTInChar, _UdonUARTInTag;
            uniform uint _DoTick;
            /* uniform uint _BreakpointLow, _BreakpointHigh; */
            /* uniform uint _BreakpointLowClock, _BreakpointHighClock; */
            /* uniform uint _CheckCSR; //, _CheckMEM, _CheckMEMraw; */
            /* static uint _Breakpoint, _BreakpointClock; */

            Texture2D<float4> _Data_DTB_R;
            Texture2D<float4> _Data_DTB_G;
            Texture2D<float4> _Data_DTB_B;
            Texture2D<float4> _Data_DTB_A;

            #define STATE_TEX _SelfTexture2D

            static uint2 s_dim;

            #include "helpers.cginc"

            #include "src/types.h"
            #include "src/ins.h"
            #include "src/uart.h"
            #include "src/emu.h" // includes mmu.h, csr.h, mem.h, trap.h
            #include "src/cpu.h"

            uint4 frag(v2f_customrendertexture i) : SV_Target {
                STATE_TEX.GetDimensions(s_dim.x, s_dim.y);

                uint2 pos = i.globalTexcoord.xy * s_dim;

                _Ticks /= max(_TicksDivisor, 1);
                _Ticks = max(_Ticks, 2);

                /* _Breakpoint = _BreakpointLow | (_BreakpointHigh << 16); */
                /* _BreakpointClock = _BreakpointLowClock | (_BreakpointHighClock << 16); */

                if (_Init) {
                    if (!_InitRaw) {
                        cpu = cpu_init();
                    }
                } else {
                    if (!pixel_has_state(pos)) {
                        return STATE_TEX[pos];
                    }

                    decode(_UdonUARTPtr);

                    [fastopt]
                    for (uint i = 0; i < _Ticks && !cpu.stall; i++) {
                        cpu_tick();
                    }
                }

                /* cpu.debug_csr_val = read_csr_raw(_CheckCSR); */
                /* cpu.debug_mem_val = mem_get_word(_CheckMEM | (_CheckMEMraw ? 0 : 0x80000000)); */

                return encode(pos);
                /* return uint4(mem_get_word(0x80000000), 0, 0, 0); */
                /* return uint4(uint(pos.x + 128*pos.y) % 256, 0, 0, 0); */
            }
            ENDCG
        }

        Pass
        {
            Name "Commit"

            CGPROGRAM
            #pragma target 5.0
            #pragma vertex CustomRenderTextureVertexShader
            #pragma fragment frag

            #define PASS_COMMIT

            // custom crt include
            #include "crt.cginc"
            #include "UnityCG.cginc"

            float _Init, _InitRaw;

            Texture2D<float4> _Data_RAM_R;
            Texture2D<float4> _Data_RAM_G;
            Texture2D<float4> _Data_RAM_B;
            Texture2D<float4> _Data_RAM_A;
            Texture2D<uint4> _Data_RAM_RAW;

            #define STATE_TEX _SelfTexture2D

            static uint2 s_dim;

            #include "helpers.cginc"

            #include "src/types.h"

            uint4 frag(v2f_customrendertexture i) : SV_Target {
                STATE_TEX.GetDimensions(s_dim.x, s_dim.y);

                uint2 pos = i.globalTexcoord.xy * s_dim;

                if (_Init && _InitRaw) {
                    return _Data_RAM_RAW[pos];
                }

                decode_for_commit();
                return commit(pos);
            }
            ENDCG
        }
    }
}
