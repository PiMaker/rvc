Shader "Nix/console"
{
    Properties
    {
        _BGColor ("Background Color", Color) = (0, 0, 0, 1)
        _FGColor ("Foreground Color", Color) = (0, 1, 0, 1)

        _Font ("Font Atlas", 2D) = "white" {}

        _FBTex ("The FB state texture", 2D) = "black" {}
        [ToggleUI] _UseUniformData ("Use Uniform Data", Float) = 0

        _FB_Width ("Framebuffer width (chars)", Int) = 80
        _FB_Height ("Framebuffer height (chars)", Int) = 25

        _Atlas_Width ("Atlas width (chars)", Int) = 32
        _Atlas_Height ("Atlas height (chars)", Int) = 8

        _CharBorder ("Character Border", Range(0, 1)) = 0.1

        _BlinkRate ("Blink Rate", Float) = 1.0
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        Cull Off
        Blend One Zero

        Pass
        {
            CGPROGRAM
            #pragma target 5.0
            #pragma vertex vert
            #pragma fragment frag

            #include "UnityCG.cginc"

            float4 _BGColor, _FGColor;
            sampler2D _Font;
            Texture2D<float4> _FBTex;
            uint _FB_Width, _FB_Height;
            uint _Atlas_Width, _Atlas_Height;
            float _CharBorder;
            float _BlinkRate;

            float _UseUniformData;
            cbuffer UniformExpansionBuffer {
                float4 _UniformData[1023*2] : packoffset(c0);
                float4 _UniformData0[1023] : packoffset(c0);
                float4 _UniformData1[1023] : packoffset(c1023);
            };

            #include "helpers.cginc"

            struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };

            v2f vert (appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = v.uv;
                return o;
            }

            float4 get_fb_char(uint2 pos)
            {
                pos.x += 1;
                if (_UseUniformData) {
                    uint lin = pos.x + pos.y * (_FB_Width + 1);
                    return _UniformData[lin % (25*81)];
                } else {
                    return _FBTex[pos];
                }
            }

            // x-dotshare ANSI color scheme
            static const float3 PALETTE[16] =
            {
                float3(16,16,16), // 0 black  dark
                float3(64,64,64), //          bright
                float3(232,79,79), // 1 red
                float3(210,61,61),
                float3(184,214,140), // 2 green
                float3(160,207,93),
                float3(225,170,93), // 3 yellow
                float3(243,157,33),
                float3(125,193,207), // 4 blue
                float3(78,159,177),
                float3(155,100,251), // 5 magenta
                float3(133,66,255),
                float3(109,135,141), // 6 cyan
                float3(66,113,123),
                float3(221,221,221), // 7 white
                float3(221,221,221),
            };

            uint unpack_float(float data)
            {
                return (uint)(data*255.0f+0.5f);
            }

            float4 frag(v2f i) : SV_Target
            {
                i.uv.xy *= float2(1.025, 1.025);
                i.uv.xy -= float2(0.0125, 0.0125);
                if (any(abs(i.uv.xy-.5)>.5)) {
                    return _BGColor;
                }

                // Hack to prevent unity from deleting aliased cbuffer. Branch will never be hit
                if (i.uv.x < -0.5f) i.uv.x += _UniformData0[0] + _UniformData1[0];

                uint2 fb_idx = uint2(_FB_Width * i.uv.x, _FB_Height * i.uv.y);
                float2 char_pos = frac(i.uv * float2(_FB_Width, _FB_Height));

                char_pos *= 1.0 + _CharBorder;
                char_pos -= _CharBorder * 0.5;

                if (char_pos.x < 0.02 || char_pos.y < 0.02 || char_pos.x > 0.98 || char_pos.y > 0.98)
                    return _BGColor;

                float4 scratch = get_fb_char(uint2(-1, 0));
                uint2 cursor_pos = uint2(unpack_float(scratch.x), unpack_float(scratch.y));

                if (_UseUniformData)
                    _BlinkRate = 2; // FIXME: hardcoded value...
                bool isCursor = _BlinkRate
                    &&(cursor_pos.x == fb_idx.x && ((uint)_FB_Height - cursor_pos.y - 1) == fb_idx.y)
                    && ((uint)(_Time.y * _BlinkRate) % 2 == 0);

                float4 data = get_fb_char(fb_idx);
                uint c = unpack_float(data.x);
                uint fg = unpack_float(data.y);
                uint bg = unpack_float(data.z);
                float4 fgcolor = float4(PALETTE[((fg & 0xf)*2 + (fg & 0xf0 ? 1 : 0))], 1);
                uint bgidx = ((bg & 0xf)*2 + (bg & 0xf0 ? 1 : 0));
                float4 bgcolor = float4(PALETTE[bgidx], 1);
                if (bgidx == 0)
                    bgcolor = _BGColor;

                if (isCursor) {
                    float4 tmp = fgcolor;
                    fgcolor = bgcolor;
                    bgcolor = tmp;
                }

                float2 atlas_offset = float2(c % _Atlas_Width, (c / _Atlas_Width) + 1) *
                                      float2(1.0/_Atlas_Width, 1.0/_Atlas_Height);
                atlas_offset.y = 1 - atlas_offset.y;
                float2 true_uv = atlas_offset + (char_pos * float2(1.0/_Atlas_Width, 1.0/_Atlas_Height));

                float4 font_mask = tex2Dlod(_Font, float4(true_uv, 0, 0));

                return lerp(bgcolor, _FGColor * fgcolor, font_mask.r);
            }
            ENDCG
        }
    }
}
