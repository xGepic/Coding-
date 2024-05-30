using System;
using System.Collections.Generic;
using System.IO;

namespace BattleArena
{
    //Static Implementation - unused because I choose lazy Implementation
    static class StaticLoggingSystem
    {
        private readonly static LinkedList<string> myLog = new();
        private static int PrintLogCounter = 1;
        private static int WriteListToFileCounter = 1;
        public static void LogSomething(string message)
        {
            myLog.AddLast(message);
        }
        public static void PrintLog()
        {
            Console.WriteLine("\n\nFull Log:\n");
            foreach (var item in myLog)
            {
                Console.WriteLine($"{PrintLogCounter}. {item}");
                PrintLogCounter++;
            }
        }
        public static void WriteListToFile()
        {
            string folderName = "\\MyLogs";
            string myFileName = "/myLogger.txt";
            string fileName = Directory.GetParent(Directory.GetCurrentDirectory()).Parent.Parent.FullName + folderName + myFileName;
            if (File.Exists(fileName))
            {
                File.Delete(fileName);
            }
            using StreamWriter sw = new(fileName);
            foreach (var item in myLog)
            {
                sw.WriteLine($"{WriteListToFileCounter}. {item}");
                sw.WriteLine();
                WriteListToFileCounter++;
            }
        }
        public static string GetTimeStamp()
        {
            return DateTime.Now.ToString("hh:mm:ss:ffff") + " by " + Environment.UserName.ToString();
        }
    }
}
