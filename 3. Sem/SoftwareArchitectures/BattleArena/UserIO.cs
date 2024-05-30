using BattleArena.Pawn;
using System;

namespace BattleArena
{
    public class UserIO
    {
        public UserIO()
        {
            LoggingSystem myLog = LoggingSystem.GetLoggingSystem();
            myLog.LogSomething($"UserIO Created at {myLog.GetTimeStamp()}");
        }
        public void PrintFightMenu(string name)
        {
            Console.WriteLine("+--------------------------------------->  ");
            Console.WriteLine("| Your turn: " + name + "                  ");
            Console.WriteLine("|                                          ");
            Console.WriteLine("| 0: End game                              ");
            Console.WriteLine("| 1: Fight the enemy                       ");
            Console.WriteLine("| 2: Create a new leprechaun    ( 2 Coins )");
            Console.WriteLine("| 3: Create a new tiny goblin   ( 1 Coin  )");
            Console.WriteLine("| 4: Create a new medium goblin ( 3 Coins )");
            Console.WriteLine("| 5: Create a new big goblin    ( 6 Coins )");
            Console.WriteLine("+--------------------------------------->  ");
        }
        public void PrintPlayerInformation(Hero[] playerList)
        {
            Console.WriteLine("####################################################################");
            foreach (Hero player in playerList)
            {

                Console.WriteLine("## " + player.Name + " | Health: " + player.Health + " | Coins: "
                        + player.Coins + " | Leprechaun: " + player.Leprechaun + " | Goblins: "
                        + player.NumberOfGoblins);
            }
            Console.WriteLine("####################################################################\n");
        }
        public int GetUserIput()
        {
            return int.Parse(Console.ReadLine());
        }
        public void EndGame(String name)
        {
            ClearScreen();
            Console.WriteLine(name + " lost the game!");
        }
        public void ExitGame()
        {
            ClearScreen();
            Console.WriteLine("Bye\n");
            LoggingSystem myLog = LoggingSystem.GetLoggingSystem();
            myLog.WriteListToFile();
            myLog.PrintLog();
        }
        public void ClearScreen()
        {
            Console.Clear();
        }
    }
}