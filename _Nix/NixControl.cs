using UdonSharp;
using VRC.SDKBase;
using VRC.Udon;
using UnityEngine;
using UnityEngine.UI;

public class NixControl : UdonSharpBehaviour
{
    public CustomRenderTexture CRT;

    public UdonBehaviour Dial, Debug;
    public Text StatusText;
    public Text UartOut;

    public Camera DebugCam;

    private int curSec;
    private int fps; // ups, really
    private int frameCount;
    private bool run;

    public Slider TickSlider;

    public Dropdown ProgramSelect;

    public KeyboardManager2 Keyboard;

    public NixProgramLoader[] Programs;
    private NixProgramLoader CurProgram;

    private int disableInit = 0;

    void Start()
    {
        curSec = (int)Time.time;
        fps = 0;
        frameCount = 0;

        CurProgram = Programs[0];

        StatusText.supportRichText = true;

        CRT.updateMode = CustomRenderTextureUpdateMode.OnDemand;
        CRT.material.SetInt("_Init", 1);
		CRT.material.SetInt("_DoTick", 1);
		CRT.material.SetInt("_Ticks", (int)TickSlider.value);
        run = false;

        TickSliderChange();
    }

    void Update()
    {
        var sec = (int)Time.time;
        if (sec != curSec)
        {
            fps = frameCount;
            frameCount = 0;
        }
        curSec = sec;
        frameCount++;

        if (disableInit > 0) {
            disableInit--;
            if (disableInit == 0) {
                CRT.material.SetInt("_Init", 0);
            }
        }

        var stateT = !run ? "<color=yellow>reset/load</color>" : "<color=green>running</color>";
        StatusText.text = $"State: {stateT}\n";
        if (run)
        {
            var ticks = (int)TickSlider.value;
            var fpsCol = fps < 40 ? "red" : "green";
            StatusText.text += $"<i>{ticks}</i> (ticks) * " +
                $"<i><color={fpsCol}>{fps}</color></i> (UPS/FPS) = <b>{ticks * fps}</b> IPS";
        }
		
		// DEBUG
		// CRT.material.SetInt("_DoTick", CRT.material.GetInt("_DoTick") + 1);
    }

    public void DialEnable()
    {
        var state = (int)Dial.GetProgramVariable("NextState");
        run = state == 1;

        if (!run)
        {
            CurProgram.ApplyTexture();
            CRT.material.SetInt("_DoTick", 1);
            CRT.material.SetInt("_Init", 1);
            Debug.SetProgramVariable("RenderCam", false);
            Debug.SetProgramVariable("UartPtr", 0);
            Debug.SetProgramVariable("UartTag", 0);
            Debug.SetProgramVariable("newlines", 0);
            Debug.SetProgramVariable("linelength", 0);
            Debug.SetProgramVariable("LocalText", "");
            CRT.material.SetInt("_UdonUARTInChar", 0);
            CRT.material.SetInt("_UdonUARTInTag", 0);
            CRT.material.SetInt("_UdonUARTPtr", 0);
            UartOut.text = "";
            Keyboard.queue = "";
            CRT.updateMode = CustomRenderTextureUpdateMode.OnDemand;
        }
        else
        {
            CurProgram.ApplyTexture();
            Debug.SetProgramVariable("RenderCam", true);
            CRT.material.SetInt("_Init", 1);
            disableInit = 2;
            CRT.material.SetInt("_DoTick", 0);
            CRT.updateMode = CustomRenderTextureUpdateMode.Realtime;
        }
    }

    public void TickSliderChange()
    {
        CRT.material.SetInt("_Ticks", (int)TickSlider.value);
    }

    public void ProgramSelectChanged()
    {
        CurProgram.TurnOff();
        CurProgram = Programs[ProgramSelect.value];
        CurProgram.TurnOn();
        CurProgram.ApplyTexture();
    }
}
