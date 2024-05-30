using System;
using System.Collections.Generic;
using System.IO;

namespace BattleArena
{
    //Singleton
    //I chose Singleton + lazy implementation because I found it very straightfoward to use.
    //It perfectly controls the access to the logger which is the shared resource.
    //I call it in all of the constructers, a very easy way to keep track of the instantiations of all the classes.
    sealed class LoggingSystem
    {
        private readonly static LoggingSystem instance = new();
        private readonly LinkedList<string> myLog = new();
        private int PrintLogCounter = 1;
        private int WriteListToFileCounter = 1;
        private LoggingSystem()
        {

        }
        public static LoggingSystem GetLoggingSystem()
        {
            return instance;
        }
        public void LogSomething(string message)
        {
            myLog.AddLast(message);
        }
        public void PrintLog()
        {
            Console.WriteLine("\n\nFull Log:\n");
            foreach (var item in myLog)
            {
                Console.WriteLine($"{PrintLogCounter}. {item}");
                PrintLogCounter++;
            }
        }
        public void WriteListToFile()
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
