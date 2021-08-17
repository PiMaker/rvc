
using UdonSharp;
using UnityEngine;
using VRC.SDKBase;
using VRC.Udon;

public class NixProgramLoader : UdonSharpBehaviour
{
    public Material vm_mat;

    public Texture2D TexR, TexG, TexB, TexA;

    public GameObject[] InfoObjects;

    public void TurnOn()
    {
        if (InfoObjects != null && InfoObjects.Length > 0) {
            foreach (var obj in InfoObjects)
            {
                obj.SetActive(true);
            }
        }
    }

    public void TurnOff()
    {
        if (InfoObjects != null && InfoObjects.Length > 0) {
            foreach (var obj in InfoObjects)
            {
                obj.SetActive(false);
            }
        }
    }

    public void ApplyTexture()
    {
        vm_mat.SetTexture("_Data_RAM_R", TexR);
        vm_mat.SetTexture("_Data_RAM_G", TexG);
        vm_mat.SetTexture("_Data_RAM_B", TexB);
        vm_mat.SetTexture("_Data_RAM_A", TexA);
    }
}
