using UnityEngine;
using UnityEditor;
using System.IO;
using System.Collections.Generic;

// increment to reimport: 6

#if UNITY_EDITOR
[InitializeOnLoad]
public static class AutoImport
{
    private static List<string> FilesToWatch = new List<string>() {
        "Assets\\_Nix\\rvc\\*",
		"Assets\\_Nix\\rvc\\src\\*",
    };

    private static FileSystemWatcher[] watchers;
    private static bool[] hasChange;

    public static string PathToPerlPP = "Perl\\strawberry-perl-5.32.1.1-64bit-portable\\perl\\bin\\perl.exe Perl\\perlpp";

    static AutoImport()
    {
        if (EditorApplication.isPlaying) return;
        if (Application.isPlaying) return;

        // resolve *
        for (int i = 0; i < FilesToWatch.Count; i++)
        {
            var cur = FilesToWatch[i];
            if (cur.EndsWith("*"))
            {
                FilesToWatch.RemoveAt(i);
                i--;
                foreach (var file in Directory.GetFiles(Path.GetDirectoryName(cur)))
                {
                    if (file.EndsWith(".meta")) continue;
                    FilesToWatch.Add(file);
                }
            }
        }

        hasChange = new bool[FilesToWatch.Count];
        watchers = new FileSystemWatcher[FilesToWatch.Count];
        for (int i = 0; i < FilesToWatch.Count; i++)
        {
            hasChange[i] = false;

            if (FilesToWatch[i].EndsWith(".h")) continue;

            if (File.Exists(FilesToWatch[i] + ".pp"))
            {
                FilesToWatch[i] = FilesToWatch[i] + ".pp";
            }
            if (!File.Exists(FilesToWatch[i]))
            {
                Debug.LogWarning("[AutoImport] File doesn't exist: " + FilesToWatch[i]);
                continue;
            }
            var path = Path.GetDirectoryName(FilesToWatch[i]);
            var file = Path.GetFileName(FilesToWatch[i]);

            Debug.Log("[AutoImport] Watching: " + path + "\\" + file);
            watchers[i] = new FileSystemWatcher(path, file);
            watchers[i].NotifyFilter = NotifyFilters.LastWrite;
            watchers[i].Changed += createEventHandler(i);
            watchers[i].EnableRaisingEvents = true;
        }
        EditorApplication.update += OnUpdate;
    }

    private static FileSystemEventHandler createEventHandler(int i)
    {
        return (object sender, FileSystemEventArgs args) =>
        {
            if (args.ChangeType == WatcherChangeTypes.Changed)
            {
                hasChange[i] = true;
            }
        };
    }

    static void OnUpdate()
    {
        if (EditorApplication.isPlaying) return;
        if (Application.isPlaying) return;

        for (int i = 0; i < hasChange.Length; i++)
        {
            if (hasChange[i])
            {
                Debug.Log("[AutoImport] Asset changed: " + FilesToWatch[i]);
                hasChange[i] = false;

                if (FilesToWatch[i].EndsWith(".pp"))
                {
                    var gen = FilesToWatch[i].Substring(0, FilesToWatch[i].Length - 3);
                    RunPerlPP(FilesToWatch[i], gen);
                    AssetDatabase.ImportAsset(gen);
                }
                else
                {
                    AssetDatabase.ImportAsset(FilesToWatch[i]);
                }
            }
        }
    }

    static void RunPerlPP(string input, string output)
    {
        Debug.Log("[AutoImport] Running perlpp in " + System.Environment.CurrentDirectory);

        var args = $"/C {PathToPerlPP} -o {output} {input}";
        var p = new System.Diagnostics.Process
        {
            StartInfo = new System.Diagnostics.ProcessStartInfo(
                @"cmd.exe",
                args
            )
            {
                WorkingDirectory = System.Environment.CurrentDirectory,
                UseShellExecute = false,
                RedirectStandardOutput = true,
                RedirectStandardError = true
            }
        };
        p.Start();
        p.WaitForExit();
        Debug.Log("[AutoImport] perlpp out: " + p.StandardOutput.ReadToEnd());
        Debug.Log("[AutoImport] perlpp err: " + p.StandardError.ReadToEnd());
    }
}
#endif