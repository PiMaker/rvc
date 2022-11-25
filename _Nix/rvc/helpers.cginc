static bool is_ortho = unity_OrthoParams.w;

#define OFFSET_UINT2_POS(x, y, w, h, n) uint2((x + n) % w, y + ((n + x) / h))

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
    return data[idx];
    /* [flatten] */
    /* switch (idx) { */
    /*     case 0: */
    /*         return data.x; */
    /*     case 1: */
    /*         return data.y; */
    /*     case 2: */
    /*         return data.z; */
    /*     default: // 3 */
    /*         return data.w; */
    /* } */
}

void set_idx_uint4(inout uint4 data, uint value, uint idx) {
    [flatten]
    switch (idx) {
        case 0:
            data.x = value;
            break;
        case 1:
            data.y = value;
            break;
        case 2:
            data.z = value;
            break;
        default: // 3
            data.w = value;
            break;
    }
}

struct v2f {
    float4 vertex : SV_Position;
    centroid float2 uv : TEXCOORD0;
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
uint4 unpack_uint4(in float3 data[6]) {
    uint4 result;
    result.x = uint(data[0].r * 255.0f + 0.5f) |
               (uint(data[1].r * 255.0f + 0.5f) << 8) |
               (uint(data[2].r * 255.0f + 0.5f) << 16) |
               (uint(data[3].r * 255.0f + 0.5f) << 24);
    result.y = uint(data[0].g * 255.0f + 0.5f) |
               (uint(data[1].g * 255.0f + 0.5f) << 8) |
               (uint(data[2].g * 255.0f + 0.5f) << 16) |
               (uint(data[3].g * 255.0f + 0.5f) << 24);
    result.z = uint(data[0].b * 255.0f + 0.5f) |
               (uint(data[1].b * 255.0f + 0.5f) << 8) |
               (uint(data[2].b * 255.0f + 0.5f) << 16) |
               (uint(data[3].b * 255.0f + 0.5f) << 24);
    result.w = uint(data[4].r * 255.0f + 0.5f) |
               (uint(data[4].g * 255.0f + 0.5f) << 8) |
               (uint(data[4].b * 255.0f + 0.5f) << 16) |
               (uint(data[5].r * 255.0f + 0.5f) << 24);
    return result;
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

uint xorshift(uint seed) {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}