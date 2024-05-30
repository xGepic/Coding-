using System;
using System.Threading;

namespace MonsterTradingCardGame
{
    static class BattleMenu
    {
        public static void PrintBattleMenu()
        {
            Console.WriteLine("WELCOME TO THE ARENA\n");
            Console.WriteLine("1 - Battle against the Computer");
            Console.WriteLine("2 - Go Back");
            Console.Write("\nInput: ");
        }
        public static int GetBattleMenuInput()
        {
            int input;
            try
            {
                input = Convert.ToInt32(Console.ReadLine());
                if (input != 1 && input != 2)
                {
                    throw new ArgumentException("Invalid Input!");
                }
                else
                {
                    return input;
                }
            }
            catch (Exception e)
            {
                Console.Clear();
                Console.WriteLine("[Error] " + e.Message + "\n\n");
                return 0;
            }
        }
        public static void GetBattleMenu(string username)
        {
            while (true)
            {
                PrintBattleMenu();
                int battleInput = GetBattleMenuInput();
                if (battleInput == 1)
                {
                    DBConnector myDB = DBConnector.GetInstance();
                    if (myDB.IsDeckEmpty(username))
                    {
                        Console.Clear();
                        Console.WriteLine("Your Deck is empty!\n");
                        Tools.PressAnyKey();
                        Console.Clear();
                        return;
                    }
                    myDB.PrintPlayerDeck(username);
                    Tools.PressToContinue();
                    Console.Clear();
                    User Player1 = GetPlayer(username);
                    User Player2 = GetBot(GetBotStrenght());
                    PrepBattle();
                    BattleHandler myBattle = new(Player1, Player2);
                    myBattle.StartBattle();
                    Tools.PressToContinue();
                    Console.Clear();
                }
                if (battleInput == 2)
                {
                    Console.Clear();
                    break;
                }
            }
        }
        public static User GetPlayer(string username)
        {
            DBConnector myDB = DBConnector.GetInstance();
            Deck tempDeck = myDB.GetPlayerDeck(username);
            int tempElo = myDB.GetPlayerElo(username);
            int tempCoins = myDB.GetPlayerCoins(username);
            User tempUser = new(username, tempDeck, tempElo, tempCoins);
            return tempUser;
        }
        public static User GetBot(int strenght)
        {
            DBConnector myDB = DBConnector.GetInstance();
            Deck tempDeck = myDB.GetBotDeck();
            User bot = new("Bot", tempDeck, strenght, 0);
            return bot;
        }
        public static int GetBotStrenght()
        {
            while (true)
            {
                try
                {
                    Console.Write("Enter Bot Strenght: ");
                    int temp = Convert.ToInt32(Console.ReadLine());
                    return temp;
                }
                catch (Exception e)
                {
                    Console.WriteLine("\n[Error] " + e.Message + "\n\n");
                }
            }
        }
        public static void PrepBattle()
        {
            Console.WriteLine("\nThe Battle will Start in 3 Seconds!");
            Thread.Sleep(3000);
            Console.Clear();
        }
    }
}