using UdonSharp;
using UnityEngine;
using VRC.SDKBase;
using VRC.Udon;

public class NixStep : UdonSharpBehaviour
{
    public Material vm_mat;
	public bool Off;
	
    void Start()
    {
    }

    public override void Interact()
    {
        vm_mat.SetInt("_DoTick", Off ? 0 : vm_mat.GetInt("_DoTick") + 1);
    }
}
