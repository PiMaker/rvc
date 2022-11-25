#ifndef FB_H
#define FB_H

<?:include header.p ?>

#define BUFFER_MAX <?= $uart_buffer_max ?>
uint getbuf(uart_buffer buffer, uint index) {
    [forcecase]
    switch (index) {
        <?
        for my $i (0..$uart_buffer_max) {
            print "case $i: return buffer.buf$i;\n";
        }
        ?>
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