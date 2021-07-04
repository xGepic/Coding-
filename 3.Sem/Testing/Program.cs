using System;
using System.Collections.Generic;

namespace Testing
{
    class Program
    {
        static void Main()
        {
            LinkedList<string> myLog = new();
            World w = new();
            Character c = new();
            char input = ' ';
            GetInfo();
            Console.WriteLine("There are " + w.GetRelicCount + " Relics to be found!");
            c.PrintStats();
            w.PrintWorld();
            while (c.GetRelicPoints != w.GetRelicCount)
            {
                Console.Write("\nYou are at the 'X' - Where would you like to go?");
                try
                {
                    input = Convert.ToChar(Console.ReadLine());
                }
                catch (FormatException)
                {

                }
                if (input == 'x')
                {
                    Console.WriteLine("\n[Programm Terminated]");
                    break;
                }
                w.Move(w.playingField, c, input, myLog);
            }
            PrintList(myLog);
        }
        public static void GetInfo()
        {
            Console.WriteLine("--|OasisCrawler 2.1 by Stefan Simanek|--\n");
            Console.WriteLine("Welcome to the OasisCrawler!");
            Console.WriteLine("Find all Relics to win the game but be careful there are dangers lurking on the field!\n");
            Console.WriteLine("Move by typing in w, a, s, d");
            Console.WriteLine("If you want to end the game early, type in 'x'.\n");
        }
        public static void PrintList(LinkedList<string> Log)
        {
            int n = 1;
            Console.WriteLine("The game went as follows:");
            foreach (string str in Log)
            {
                Console.WriteLine(n + ". " + str);
                n++;
            }
            Console.WriteLine("\nThank you for playing the Game!");
        }
    }
}
