static bool is_ortho = unity_OrthoParams.w;

uint2 prev_pos(in uint2 pos, in uint2 dim) {
    return uint2(
        (pos.x == 0 ? dim.x : pos.x) - 1,
        (pos.x == 0 ? ((pos.y == 0 ? dim.y : pos.y) - 1) : pos.y)
    );
}

uint2 next_pos(in uint2 pos, in uint2 dim) {
    return uint2(
        pos.x == (dim.x - 1) ? 0 : dim.x + 1,
        pos.x == (dim.x - 1) ? (pos.y == (dim.y - 1) ? 0 : dim.y - 1) : pos.y
    );
}

uint idx_uint4(uint4 data, uint idx) {
    [flatten]
    switch (idx) {
        case 0:
            return data.x;
        case 1:
            return data.y;
        case 2:
            return data.z;
        default:
            return data.w;
    }
}

struct v2f {
    float4 vertex : SV_Position;
    float2 uv : TEXCOORD0;
};

v2f vert_ortho_fullscreen(appdata_base v) {
    v2f o;

    o.vertex = is_ortho ?
        float4((v.texcoord.xy-0.5f)*2, 0, 1) :
        UnityObjectToClipPos(v.vertex);

    o.uv = v.texcoord.xy;
    #if UNITY_UV_STARTS_AT_TOP
    o.uv.y = 1 - o.uv.y;
    #endif

    return o;
}

uint4 color_to_uint(float4 col) {
    float m = (float)(~(uint)0);
    return uint4(
        col.r * m,
        col.g * m,
        col.b * m,
        col.a * m
    );
}

float4 uint_to_color(uint4 data) {
    float div = (float)(~(uint)0);
    float4 conv = float4(
        data.r / div,
        data.g / div,
        data.b / div,
        data.a / div
    );
    return conv;
}

#define PACK_MASK 0xFF
#define PACK_SHIFT 8
void pack_uint4(in uint4 data, out float3 result[6]) {
    result[0] = (data.rgb & PACK_MASK) / 255.0f;
    result[1] = ((data.rgb >> PACK_SHIFT) & PACK_MASK) / 255.0f;
    result[2] = ((data.rgb >> (PACK_SHIFT*2)) & PACK_MASK) / 255.0f;
    result[3] = ((data.rgb >> (PACK_SHIFT*3)) & PACK_MASK) / 255.0f;
    result[4].r = (data.a & PACK_MASK) / 255.0f;
    result[4].g = ((data.a >> PACK_SHIFT) & PACK_MASK) / 255.0f;
    result[4].b = ((data.a >> (PACK_SHIFT*2)) & PACK_MASK) / 255.0f;
    result[5].r = ((data.a >> (PACK_SHIFT*3)) & PACK_MASK) / 255.0f;
    result[5].gb = 0;
}
#undef PACK_SHIFT
#undef PACK_MASK

uint unpack_raw_float4(in float4 data) {
    uint res = 0;
    res |= uint(data.a*255.0f+0.5f) << 24;
    res |= uint(data.b*255.0f+0.5f) << 16;
    res |= uint(data.g*255.0f+0.5f) << 8;
    res |= uint(data.r*255.0f+0.5f);
    return res;
}
