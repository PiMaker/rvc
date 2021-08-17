Shader "Nix/console"
{
    Properties
    {
        _BGColor ("Background Color", Color) = (0, 0, 0, 1)
        _FGColor ("Foreground Color", Color) = (0, 1, 0, 1)

        _Font ("Font Atlas", 2D) = "white" {}
        _RVC ("The RVC state texture", 2D) = "black" {}

        _FB_Width ("Framebuffer width (chars)", Int) = 80
        _FB_Height ("Framebuffer height (chars)", Int) = 60

        _Atlas_Width ("Atlas width (chars)", Int) = 64
        _Atlas_Height ("Atlas height (chars)", Int) = 8

        _CharBorder ("Character Border", Range(0, 1)) = 0.1
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
            Texture2D<uint4> _RVC;
            #define STATE_TEX _RVC
            uint _FB_Width, _FB_Height;
            uint _Atlas_Width, _Atlas_Height;
            float _CharBorder;

            #include "helpers.cginc"
            #include "src/types.h"

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

            static uint2 s_dim;

            float4 frag(v2f i) : SV_Target {
                STATE_TEX.GetDimensions(s_dim.x, s_dim.y);

                uint2 fb_idx = uint2(_FB_Width * i.uv.x, _FB_Height * i.uv.y);
                float2 char_pos = frac(i.uv * float2(_FB_Width, _FB_Height));

                char_pos *= 1.0 + _CharBorder;
                char_pos -= _CharBorder * 0.5;

                if (char_pos.x < 0.04 || char_pos.y < 0.04 || char_pos.x > 0.96 || char_pos.y > 0.96)
                    return _BGColor;

                /* uint c = get_fb_char(fb_idx); */
                uint c = '7';

                float2 atlas_offset = float2(c % _Atlas_Width, (c / _Atlas_Width) + 1) *
                                      float2(1.0/_Atlas_Width, 1.0/_Atlas_Height);
                atlas_offset.y = 1 - atlas_offset.y;
                float2 true_uv = atlas_offset + (char_pos * float2(1.0/_Atlas_Width, 1.0/_Atlas_Height));

                float4 font_mask = tex2D(_Font, true_uv);

                return lerp(_BGColor, _FGColor, font_mask.r);
            }
            ENDCG
        }
    }
}
