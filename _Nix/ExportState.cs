using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ExportState : MonoBehaviour
{
    public string Name;
    public bool DoWork;
    private Camera cam;

    void Start()
    {
        DoWork = false;
        cam = GetComponent<Camera>();
    }

    void Update()
    {
        if (DoWork)
        {
            DoWork = false;

            var rt = new RenderTexture(2048*3, 4096*2, 0, UnityEngine.Experimental.Rendering.GraphicsFormat.B8G8R8A8_UNorm);
            cam.targetTexture = rt;
            cam.Render();
            RenderTexture.active = rt;
            var capture = new Texture2D(rt.width, rt.height, TextureFormat.RGB24, false);
            capture.ReadPixels(new Rect(0, 0, rt.width, rt.height), 0, 0);
            RenderTexture.active = null;
            cam.targetTexture = null;
            var bytes = capture.EncodeToPNG();
            System.IO.File.WriteAllBytes(Name, bytes);
            Destroy(rt);
            Destroy(capture);
        }
    }
}
