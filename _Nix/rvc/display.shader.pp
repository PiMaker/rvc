Shader "Nix/Display"
{
    Properties
    {
        _Tex ("Texture", 2D) = "white" {}
        [ToggleUI] _FullData ("Transcode all data", Float) = 0
        [ToggleUI] _VisualizeState ("Visualize Only State", Float) = 0
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
            #include "helpers.cginc"
            #pragma target 5.0
            #pragma vertex vert_ortho_fullscreen
            #pragma fragment frag

            Texture2D<uint4> _Tex;
            float _FullData, _VisualizeState;

            <?:include src/header.p ?>

            float4 frag(v2f i) : SV_Target {
                uint2 dim;
                _Tex.GetDimensions(dim.x, dim.y);

                if (is_ortho) {
                    uint2 pos = _FullData ?
                        (i.uv * (uint2(<?= $total_width ?>, <?= $total_height ?>) * uint2(3, 2))) % uint2(<?= $total_width ?>, <?= $total_height ?>) :
                        (i.uv * (uint2(<?= $width_state ?>, <?= $height_state ?>) * uint2(6, 1))) % uint2(<?= $width_state ?>, <?= $height_state ?>);
                    uint4 data = _Tex[pos];

                    // output packed values, stretched along x
                    float3 res[6];
                    pack_uint4(data, res);

                    uint idx = (uint)(i.uv.x * (_FullData ? 3 : 6));
                    if (_FullData && i.uv.y >= 0.5) {
                        idx += 3;
                    }
                    return float4(res[idx], 1);
                } else {
                    uint2 pos = i.uv * (_VisualizeState ? float2(<?= $width_state ?>, <?= $height_state ?>)*0.995 : dim);
                    uint4 data = _Tex[pos];
                    if (_VisualizeState) {
                        data.rgba = data.garb;
                    }
                    return float4(uint_to_color(data).rgb, 1);
                }
            }
            ENDCG
        }
    }
}
