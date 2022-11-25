using System;
using UdonSharp;
using UnityEngine;
using UnityEngine.UI;
using VRC.SDKBase;
using VRC.Udon;

public class NixDebug : UdonSharpBehaviour
{
    public Texture2D Buffer;
    public Text DbgText;
	public Text UartOut;
    public Toggle EnableToggle;
	public Material vm_mat;
	public int UpdateEveryXFrames = 90;

    public GameObject[] DebugObj;
    private bool prevIsOn;
	
	[HideInInspector]
	public int UartPtr = 0;

    private Camera cam;
	private int lastUpdate = 0;

    [HideInInspector]
    public int newlines = 0;
    [HideInInspector]
    public int linelength = 0;

    public int UartTag = 0;

    public KeyboardManager2 Keyboard;

    public string LocalText = "";

    [UdonSynced]
    public string MasterText;

    public Text MasterTextbox;

    private bool caret = false;

    void Start()
    {
        cam = this.GetComponent<Camera>();
        DbgText.supportRichText = true;
		UartOut.supportRichText = false;
        prevIsOn = !EnableToggle.isOn;

        if (Networking.LocalPlayer.isMaster) {
            MasterTextbox.text = "<you're master!>";
        }

        DebugSelectUpdate();
    }

    private const float MULT = 255.0f;
	private const float ADD = 0.5f;
    private uint decodePackedData(int x, int y, int c)
    {
        // TODO: add hart selection
        //x *= 2;
        //y *= 2;

        Color[] col = new Color[6] {
            Buffer.GetPixel(x, y),
            Buffer.GetPixel(x + STATE_WIDTH, y),
            Buffer.GetPixel(x + STATE_WIDTH*2, y),
            Buffer.GetPixel(x + STATE_WIDTH*3, y),
            Buffer.GetPixel(x + STATE_WIDTH*4, y),
            Buffer.GetPixel(x + STATE_WIDTH*5, y)
        };

        switch (c) {
            case 0:
                return (
                    (uint)(col[0].r * MULT + ADD) |
                    ((uint)(col[1].r * MULT + ADD) << 8) |
                    ((uint)(col[2].r * MULT + ADD) << 16) |
                    ((uint)(col[3].r * MULT + ADD) << 24)
                );
            case 1:
                return (
                    (uint)(col[0].g * MULT + ADD) |
                    ((uint)(col[1].g * MULT + ADD) << 8) |
                    ((uint)(col[2].g * MULT + ADD) << 16) |
                    ((uint)(col[3].g * MULT + ADD) << 24)
                );
            case 2:
                return (
                    (uint)(col[0].b * MULT + ADD) |
                    ((uint)(col[1].b * MULT + ADD) << 8) |
                    ((uint)(col[2].b * MULT + ADD) << 16) |
                    ((uint)(col[3].b * MULT + ADD) << 24)
                );
            case 3:
                return (
                (uint)(col[4].r * MULT + ADD) |
                ((uint)(col[4].g * MULT + ADD) << 8) |
                ((uint)(col[4].b * MULT + ADD) << 16) |
                ((uint)(col[5].r * MULT + ADD) << 24)
            );
        }

        return 0;
    }

    private const int ANSI_SM_NONE = 0;
    private const int ANSI_SM_ESC_RECEIVED = 1;
    private const int ANSI_SM_CTRL_RECEIVED = 2;
    private int ansi_escape_sm = 0;

    public void DebugSelectUpdate()
    {
        if (EnableToggle.isOn != prevIsOn) {
            foreach (var o in DebugObj)
            {
                o.SetActive(EnableToggle.isOn);
            }
            if (!EnableToggle.isOn) {
                DbgText.text = "<disabled>";
            } else {
                DbgText.text = "Waiting for data...";
            }
            prevIsOn = EnableToggle.isOn;
        }
    }

    public void OnPostRender()
    {
        Buffer.ReadPixels(new Rect(0, 0, STATE_WIDTH*6, STATE_HEIGHT), 0, 0);
		
		var newUartPtrRaw = load_uart_buffer__ptr();
		var newUartPtr = (newUartPtrRaw >= 0U && newUartPtrRaw < (uint)UART_BUFFER_SIZE) ? (int)newUartPtrRaw : 0;

        if (EnableToggle.isOn) {
            // Enter single step mode when breakpoint detected
            var dbgTick = load_debug_do_tick();
            if (dbgTick == 0xffffffffU) {
                vm_mat.SetInt("_DoTick", 1);
            }

            // var load_debug_arb_0x = load_debug_arb_0();
            // var load_debug_arb_1x = load_debug_arb_1();
            // var load_debug_arb_2x = load_debug_arb_2();
            // var load_debug_arb_3x = load_debug_arb_3();
            // var load_debug_arb_4x = load_debug_arb_4();
            // var load_debug_arb_5x = load_debug_arb_5();
            // var load_debug_arb_6x = load_debug_arb_6();
            // var load_debug_arb_7x = load_debug_arb_7();

            var pc = load_pc();
            
            DbgText.text =
$@"pc      : 0x{pc.ToString("X8")}
instr.  : 0x{load_debug_last_ins().ToString("X8")}
clock   : {load_clock()}
stall   : {load_debug_last_stall()}
#stall  : {load_stall_count()}
#trap   : {load_trap_count()}
#commit : {load_commits()}
priv.   : {load_csr__privilege()}
uartptr : {UartPtr.ToString("X2")}/{newUartPtr.ToString("X2")}
mstatus : 0x{load_csr(0x300).ToString("X8")}" +
//mm_src  : phy=0x{load_memop_src_p().ToString("X8")} virt=0x{load_memop_src_v().ToString("X8")}
//mm_dst  : phy=0x{load_memop_dst_p().ToString("X8")} virt=0x{load_memop_dst_v().ToString("X8")}
//mm_n    : {load_memop_n()}
$@"
dbgtick : {dbgTick}
dbgarb0 : {load_debug_arb_0()}"
/*chkcsr  : 0x{load_debug_csr_val().ToString("X8")}"
/*chkmem  : 0x{load_debug_mem_val().ToString("X8")}*/ + $@"

<size=24>
zz=0x{load_xreg0().ToString("X8")} ra=0x{load_xreg1().ToString("X8")} sp=0x{load_xreg2().ToString("X8")} gp=0x{load_xreg3().ToString("X8")}
tp=0x{load_xreg4().ToString("X8")} t0=0x{load_xreg5().ToString("X8")} t1=0x{load_xreg6().ToString("X8")} t2=0x{load_xreg7().ToString("X8")}
fp=0x{load_xreg8().ToString("X8")} s1=0x{load_xreg9().ToString("X8")} a0=0x{load_xreg10().ToString("X8")} a1=0x{load_xreg11().ToString("X8")}
a2=0x{load_xreg12().ToString("X8")} a3=0x{load_xreg13().ToString("X8")} a4=0x{load_xreg14().ToString("X8")} a5=0x{load_xreg15().ToString("X8")}
a6=0x{load_xreg16().ToString("X8")} a7=0x{load_xreg17().ToString("X8")} s2=0x{load_xreg18().ToString("X8")} s3=0x{load_xreg19().ToString("X8")}
s4=0x{load_xreg20().ToString("X8")} s5=0x{load_xreg21().ToString("X8")} s6=0x{load_xreg22().ToString("X8")} s7=0x{load_xreg23().ToString("X8")}
s8=0x{load_xreg24().ToString("X8")} s9=0x{load_xreg25().ToString("X8")} 10=0x{load_xreg26().ToString("X8")} 11=0x{load_xreg27().ToString("X8")}
t3=0x{load_xreg28().ToString("X8")} t4=0x{load_xreg29().ToString("X8")} t5=0x{load_xreg30().ToString("X8")} t6=0x{load_xreg31().ToString("X8")}"
/*
arb0=0x{load_debug_arb_0x.ToString("X8")} arb1=0x{load_debug_arb_1x.ToString("X8")} arb2=0x{load_debug_arb_2x.ToString("X8")} arb3=0x{load_debug_arb_3x.ToString("X8")}
arb4=0x{load_debug_arb_4x.ToString("X8")} arb5=0x{load_debug_arb_5x.ToString("X8")} arb6=0x{load_debug_arb_6x.ToString("X8")} arb7=0x{load_debug_arb_7x.ToString("X8")}*/ + $@"
</size>
";

            // ARB=0x{(load_debug_arb_0x ^ load_debug_arb_1x ^ load_debug_arb_2x ^ load_debug_arb_3x ^ load_debug_arb_4x ^ load_debug_arb_5x ^ load_debug_arb_6x ^ load_debug_arb_7x ^ pc).ToString("X8")}
        }

        if (vm_mat.GetFloat("_Init") > 0 && vm_mat.GetFloat("_InitRaw") > 0) {
            UartPtr = newUartPtr;
        }

        var changed = false;
		while (newUartPtr != UartPtr) {
			UartPtr++;
			if (UartPtr == UART_BUFFER_SIZE) { UartPtr = 0; }
			var tmp = getUartBuffer(UartPtr);
            if (tmp == 0) continue;

            if (tmp == 8) { // backspace
                if (linelength == 0) {
                    linelength = 79;
                    newlines--;
                } else {
                    linelength--;
                }
                LocalText = LocalText.Substring(0, LocalText.Length - 1);
                changed = true;
                continue;
            }

            // Basic ANSI escape support
            // TODO: implement correctly...
            if (tmp == 27) { // ASCII ESC
                ansi_escape_sm = ANSI_SM_ESC_RECEIVED;
                continue;
            }

            if (ansi_escape_sm == ANSI_SM_ESC_RECEIVED) {
                if (tmp == ((int)'[')) {
                    ansi_escape_sm = ANSI_SM_CTRL_RECEIVED;
                } else {
                    ansi_escape_sm = ANSI_SM_NONE;
                }
                continue;
            }

            if (ansi_escape_sm == ANSI_SM_CTRL_RECEIVED) {
                if (tmp >= 0x20 && tmp <= 0x3F) {
                    // data, ignored for now
                } else {
                    // termination (or invalid)
                    ansi_escape_sm = ANSI_SM_NONE;
                }
                continue;
            }

            var c = (char)tmp;
			LocalText += c;
            changed = true;
            if (c == '\n') {
                newlines++;
                linelength = 0;
            } else {
                linelength++;
                if (linelength >= 80) {
                    linelength = 0;
                    newlines++;
                    LocalText += '\n';
                }
            }
            if (newlines > 30) {
                LocalText = LocalText.Substring(LocalText.IndexOf('\n') + 1);
                newlines--;
            }
		}
		vm_mat.SetInt("_UdonUARTPtr", UartPtr);

        if (Networking.LocalPlayer.isMaster && changed) {
            MasterText = LocalText;
            this.RequestSerialization();
            MasterTextbox.text = MasterText;
        }

        var caretStr = caret ? "█" : "";
        caret = !caret;
        UartOut.text = LocalText + caretStr;

        var curTag = load_uart__input_tag();
        if (curTag == UartTag) {
            Keyboard.CharToVM();
        }

        // BUG DEBUG PLZ REMOVE
        /*if (load_debug_last_stall() == 7) {
            Debug.Log("Cache:");
            for (int i = 0; i < 256*4; i++)
            {
                Debug.Log($"{i/4}/{i%4}: {load_l1_cache(i).ToString("X8")}");
            }
            RenderCam = false;
        }*/
		
		// DEBUG
		
		//Debug.Log("TRACE: 0x" + load_debug_last_ins().ToString("X8") + " @ " + load_pc().ToString("X8"));
		
		// Debug.Log("TEST begin");
		// int prev = -1;
		// for (int i = 0; i < 256; i++) {
			// px = decodePackedColor(i % 128, i / 128); // FIXME: 128 hardcoded!
			// if (px[0] != prev + 1) {
				// Debug.Log("DISCREPANCY! @" + i + " got: " + px[0] + " wanted: " + (prev + 1) + " dbg: " + prev2);
			// }
			// prev = (int)px[0];
		// }
		// Debug.Log("TEST done");
    }

    public bool RenderCam = false;
    void Update()
    {
        if (cam.enabled)
        {
            cam.enabled = false;
        }

        lastUpdate--;
        if (lastUpdate <= 0)
        {
            cam.enabled = RenderCam;
			lastUpdate = UpdateEveryXFrames;
        }
    }

    public override void OnDeserialization()
    {
        MasterTextbox.text = MasterText;
    }
	
	// auto-generated in 'types.h':
	
    #region LOAD
    private const int STATE_WIDTH = 64;
    private const int STATE_HEIGHT = 64;
    private const int TOTAL_WIDTH = 2048;
    private const int TOTAL_HEIGHT = 4096;
    private const int UART_BUFFER_SIZE = 32;
    private int[] addr_lin(int lin) {
        int[] ret = new int[3];
        ret[2] = lin & 0x3; // c
        lin = lin >> 2;
        ret[0] = lin % 64; // x
        ret[1] = lin / 64; // y
        return ret;
    }
    private uint load_csr__privilege() { return decodePackedData(6, 0, 2); }
    private uint load_uart__rbr_thr_ier_iir() { return decodePackedData(6, 0, 3); }
    private uint load_uart__lcr_mcr_lsr_scr() { return decodePackedData(7, 0, 0); }
    private uint load_uart__thre_ip() { return decodePackedData(7, 0, 1); }
    private uint load_uart__interrupting() { return decodePackedData(7, 0, 2); }
    private uint load_uart__input_tag() { return decodePackedData(7, 0, 3); }
    private uint load_clint__msip() { return decodePackedData(8, 0, 0); }
    private uint load_clint__mtimecmp_lo() { return decodePackedData(8, 0, 1); }
    private uint load_clint__mtimecmp_hi() { return decodePackedData(8, 0, 2); }
    private uint load_clint__mtime_lo() { return decodePackedData(8, 0, 3); }
    private uint load_clint__mtime_hi() { return decodePackedData(9, 0, 0); }
    private uint load_uart_buffer__ptr() { return decodePackedData(9, 0, 1); }
    private uint load_mmu__mode() { return decodePackedData(17, 0, 2); }
    private uint load_mmu__ppn() { return decodePackedData(17, 0, 3); }
    private uint load_stall() { return decodePackedData(18, 0, 0); }
    private uint load_clock() { return decodePackedData(18, 0, 1); }
    private uint load_commits() { return decodePackedData(18, 0, 2); }
    private uint load_xreg0() { return decodePackedData(18, 0, 3); }
    private uint load_xreg1() { return decodePackedData(19, 0, 0); }
    private uint load_xreg2() { return decodePackedData(19, 0, 1); }
    private uint load_xreg3() { return decodePackedData(19, 0, 2); }
    private uint load_xreg4() { return decodePackedData(19, 0, 3); }
    private uint load_xreg5() { return decodePackedData(20, 0, 0); }
    private uint load_xreg6() { return decodePackedData(20, 0, 1); }
    private uint load_xreg7() { return decodePackedData(20, 0, 2); }
    private uint load_xreg8() { return decodePackedData(20, 0, 3); }
    private uint load_xreg9() { return decodePackedData(21, 0, 0); }
    private uint load_xreg10() { return decodePackedData(21, 0, 1); }
    private uint load_xreg11() { return decodePackedData(21, 0, 2); }
    private uint load_xreg12() { return decodePackedData(21, 0, 3); }
    private uint load_xreg13() { return decodePackedData(22, 0, 0); }
    private uint load_xreg14() { return decodePackedData(22, 0, 1); }
    private uint load_xreg15() { return decodePackedData(22, 0, 2); }
    private uint load_xreg16() { return decodePackedData(22, 0, 3); }
    private uint load_xreg17() { return decodePackedData(23, 0, 0); }
    private uint load_xreg18() { return decodePackedData(23, 0, 1); }
    private uint load_xreg19() { return decodePackedData(23, 0, 2); }
    private uint load_xreg20() { return decodePackedData(23, 0, 3); }
    private uint load_xreg21() { return decodePackedData(24, 0, 0); }
    private uint load_xreg22() { return decodePackedData(24, 0, 1); }
    private uint load_xreg23() { return decodePackedData(24, 0, 2); }
    private uint load_xreg24() { return decodePackedData(24, 0, 3); }
    private uint load_xreg25() { return decodePackedData(25, 0, 0); }
    private uint load_xreg26() { return decodePackedData(25, 0, 1); }
    private uint load_xreg27() { return decodePackedData(25, 0, 2); }
    private uint load_xreg28() { return decodePackedData(25, 0, 3); }
    private uint load_xreg29() { return decodePackedData(26, 0, 0); }
    private uint load_xreg30() { return decodePackedData(26, 0, 1); }
    private uint load_xreg31() { return decodePackedData(26, 0, 2); }
    private uint load_pc() { return decodePackedData(26, 0, 3); }
    private uint load_reservation_en() { return decodePackedData(27, 0, 0); }
    private uint load_reservation_addr() { return decodePackedData(27, 0, 1); }
    private uint load_memop_src_v() { return decodePackedData(27, 0, 2); }
    private uint load_memop_dst_v() { return decodePackedData(27, 0, 3); }
    private uint load_memop_src_p() { return decodePackedData(28, 0, 0); }
    private uint load_memop_dst_p() { return decodePackedData(28, 0, 1); }
    private uint load_memop_n() { return decodePackedData(28, 0, 2); }
    private uint load_stall_count() { return decodePackedData(28, 0, 3); }
    private uint load_trap_count() { return decodePackedData(29, 0, 0); }
    private uint load_debug_do_tick() { return decodePackedData(29, 0, 1); }
    private uint load_debug_last_ins() { return decodePackedData(29, 0, 2); }
    private uint load_debug_last_stall() { return decodePackedData(29, 0, 3); }
    private uint load_debug_arb_0() { return decodePackedData(30, 0, 0); }
    private uint load_csr(int addr) {
        int lin = (addr >> 2) + 32;
        return decodePackedData(lin % 64, lin / 64, addr & 0x3);
    }
    private uint load_l1_cache(int addr) {
        int lin = (addr >> 2) + 1056;
        return decodePackedData(lin % 64, lin / 64, addr & 0x3);
    }
    private uint getUartBuffer(int idx) {
        
        int lin = idx + 38;
        int[] acc = addr_lin(lin);
        return decodePackedData(acc[0], acc[1], acc[2]);
    }
    #endregion
}
