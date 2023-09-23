using System;
using System.Diagnostics;
using System.Linq;

namespace WowBot
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Dfs.StartDfs();

            bool useBloogBot = false;
            if (useBloogBot)
            {

            }
            else
            {
                WowBot wowBot = new WowBot();
                wowBot.StartBot("", "");
            }

            //string processName = "notepad";
            string processName = "wow";
            if (!IsProcessRunning(processName))
            {
                //StartProcess("notepad.exe");
                Console.WriteLine($"Proces {processName} is not running!");
            }
            else
                Console.WriteLine($"Proces {processName} is running!");
        }

        static bool IsProcessRunning(string processName)
        {
            return Process.GetProcessesByName(processName).Any();
        }

        static void StartProcess(string processPath)
        {
            try
            {
                Process.Start(processPath);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Failed to start process. Error: {ex.Message}");
            }
        }
    }
}
