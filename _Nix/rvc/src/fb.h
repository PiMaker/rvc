#ifndef FB_H
#define FB_H



#define RAM_ADDR(lin) uint2(lin % 2048, 64 + (lin / 2048))
#define RAM_MAX (2048 * (4096 - 64) * 4 * 4)


/* shift by two to ignore byte offset */
#define RAM_L1_ARRAY_IDX(a) (((a >> 2) & 127) | (((a >> 11) & 0x3) << 7))


#define BUFFER_MAX 63
uint getbuf(uart_buffer buffer, uint index) {
    [forcecase]
    switch (index) {
        case 0: return buffer.buf0;
case 1: return buffer.buf1;
case 2: return buffer.buf2;
case 3: return buffer.buf3;
case 4: return buffer.buf4;
case 5: return buffer.buf5;
case 6: return buffer.buf6;
case 7: return buffer.buf7;
case 8: return buffer.buf8;
case 9: return buffer.buf9;
case 10: return buffer.buf10;
case 11: return buffer.buf11;
case 12: return buffer.buf12;
case 13: return buffer.buf13;
case 14: return buffer.buf14;
case 15: return buffer.buf15;
case 16: return buffer.buf16;
case 17: return buffer.buf17;
case 18: return buffer.buf18;
case 19: return buffer.buf19;
case 20: return buffer.buf20;
case 21: return buffer.buf21;
case 22: return buffer.buf22;
case 23: return buffer.buf23;
case 24: return buffer.buf24;
case 25: return buffer.buf25;
case 26: return buffer.buf26;
case 27: return buffer.buf27;
case 28: return buffer.buf28;
case 29: return buffer.buf29;
case 30: return buffer.buf30;
case 31: return buffer.buf31;
case 32: return buffer.buf32;
case 33: return buffer.buf33;
case 34: return buffer.buf34;
case 35: return buffer.buf35;
case 36: return buffer.buf36;
case 37: return buffer.buf37;
case 38: return buffer.buf38;
case 39: return buffer.buf39;
case 40: return buffer.buf40;
case 41: return buffer.buf41;
case 42: return buffer.buf42;
case 43: return buffer.buf43;
case 44: return buffer.buf44;
case 45: return buffer.buf45;
case 46: return buffer.buf46;
case 47: return buffer.buf47;
case 48: return buffer.buf48;
case 49: return buffer.buf49;
case 50: return buffer.buf50;
case 51: return buffer.buf51;
case 52: return buffer.buf52;
case 53: return buffer.buf53;
case 54: return buffer.buf54;
case 55: return buffer.buf55;
case 56: return buffer.buf56;
case 57: return buffer.buf57;
case 58: return buffer.buf58;
case 59: return buffer.buf59;
case 60: return buffer.buf60;
case 61: return buffer.buf61;
case 62: return buffer.buf62;
case 63: return buffer.buf63;

    }
    return 0;
}

float4 tex_get_fb(uint2 px) {
    if (px.y >= 25) return (float4)0; // init empty newlines with 0
    px.y = 25 - px.y - 1;
    px.x += 1;
    return _SelfTexture2D[px];
}

#define NO_CHAR 0x80000000
struct fbupd {
    uint2 pos;
    uint upshift;
    uint char;
};
static fbupd fblog[BUFFER_MAX];

void interpret(inout uint4 ctrlSeq, inout uint2 cursor_pos, inout uint char) {
    if (ctrlSeq.x == '\b') {
        // backspace
        if (cursor_pos.x > 0) {
            cursor_pos.x -= 1;
        } else {
            cursor_pos.x = 0;
            // if (cursor_pos.y > 0) {
            //     cursor_pos.y -= 1;
            // }
        }
        char = 0;
    } else if (ctrlSeq.x == '\n') {
        cursor_pos.y += 1;
    } else if (ctrlSeq.x == '\r') {
        cursor_pos.x = 0;
    } else if (ctrlSeq.x == '\t') {
        cursor_pos.x = (cursor_pos.x & 0xf8) + 8;
    } else if (ctrlSeq.x == 0x1b) {
        // ANSI escape sequence
        if (ctrlSeq.y == 0x9b) {
            // CSI
            if (ctrlSeq.z == 'A') {
                // up
                if (cursor_pos.y > 0) {
                    cursor_pos.y -= 1;
                }
            } else if (ctrlSeq.z == 'B') {
                // down
                if (cursor_pos.y < 25) {
                    cursor_pos.y += 1;
                }
            } else if (ctrlSeq.z == 'C') {
                // right
                if (cursor_pos.x < 80) {
                    cursor_pos.x += 1;
                }
            } else if (ctrlSeq.z == 'D') {
                // left
                if (cursor_pos.x > 0) {
                    cursor_pos.x -= 1;
                }
            } else if (ctrlSeq.z == 'H') {
                // home
                cursor_pos.x = 0;
                cursor_pos.y = 0;
            } else if (ctrlSeq.z == 'F') {
                // end
                cursor_pos.x = 80;
                cursor_pos.y = 25;
            } else if (!all(ctrlSeq.zw)) { // detect and reset on unknown sequence
                return;
            }
        } else if (ctrlSeq.y == 0) {
            return;
        }
    }
    // unrecognized or single-char control will reset
    ctrlSeq = (uint4)0;
}

float4 update_fb(uint2 pos, uart_buffer buffer, inout uint4 scratch1, inout uint4 scratch2) {
    [branch]
    if (buffer.ptr == 0xffffffff) {
        // no update, keep everything the same
        float4 cur = tex_get_fb(pos);
        return cur;
    }

    uint2 cursor_pos = uint2(scratch1.x, scratch1.y);
    uint2 orig_cursor_pos = cursor_pos;

    uint4 ctrlSeq = uint4(scratch1.z, scratch2.x, scratch2.y, scratch2.z);

    uint upshifts = 0;
    uint bufidx;

    // generate log and upshift value
    [loop]
    for (bufidx = 0; bufidx <= buffer.ptr; bufidx++) {
        uint c = getbuf(buffer, bufidx);

        fbupd upd;
        upd.pos = cursor_pos;
        upd.upshift = upshifts;

        if (any(ctrlSeq)) {
            upd.char = NO_CHAR;
            if (ctrlSeq.y == 0) ctrlSeq.y = c;
            else if (ctrlSeq.z == 0) ctrlSeq.z = c;
            else ctrlSeq.w = c; // FIXME: longer ctrl sequences?
            interpret(ctrlSeq, cursor_pos, upd.char);
        } else if (c == '\n' || c == '\t' || c == '\r' || c == '\b' || c == 0x1b) {
            upd.char = NO_CHAR;
            ctrlSeq = uint4(c, 0, 0, 0);
            interpret(ctrlSeq, cursor_pos, upd.char);
        } else {
            cursor_pos += uint2(1, 0);
            upd.char = c;
        }

        fblog[bufidx] = upd;

        [branch]
        if (cursor_pos.x >= 80) {
            cursor_pos.x = 0;
            cursor_pos.y += 1;
        }
        [loop]
        while (cursor_pos.y >= 25) {
            cursor_pos.y--;
            upshifts++;
        }
    }

    uint2 new_cursor_pos = cursor_pos;
    uint2 active_pos = pos + uint2(0, upshifts);
    float4 active = tex_get_fb(active_pos);

    // apply log
    [loop]
    for (bufidx = 0; bufidx <= buffer.ptr; bufidx++) {
        fbupd upd = fblog[bufidx];
        if (upd.char == NO_CHAR) continue;
        uint backshift = upshifts - upd.upshift;
        upd.pos -= uint2(0, backshift);
        [branch]
        if (upd.pos.x == pos.x && upd.pos.y == pos.y) {
            active = float4(upd.char / 255.0f, 0, 0, 0);
        }
    }

    scratch1.x = new_cursor_pos.x;
    scratch1.y = new_cursor_pos.y;
    scratch1.z = ctrlSeq.x;
    scratch2.x = ctrlSeq.y;
    scratch2.y = ctrlSeq.z;
    scratch2.z = ctrlSeq.w;
    scratch2.w = 0;
    scratch1.w = 0;
    return active;
}

#endif