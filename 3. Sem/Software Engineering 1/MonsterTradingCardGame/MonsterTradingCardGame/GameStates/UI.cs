using System;

namespace MonsterTradingCardGame
{
    static class UI
    {
        public static void PrintWelcomeMessage()
        {
            Console.WriteLine("Monster Trading Card Game by Stefan Simanek\n\n");
        }
        public static void PrintUserMenu(string userName)
        {
            Console.WriteLine($"Logged in as {userName}\n\n");
            Console.WriteLine("What would you like to do?:\n");
            Console.WriteLine("1 - Play");
            Console.WriteLine("2 - Shop");
            Console.WriteLine("3 - Craft your Deck");
            Console.WriteLine("4 - View the Leaderboard");
            Console.WriteLine("5 - View your Profile");
            Console.WriteLine("6 - Trade");
            Console.WriteLine("7 - Logout");
            Console.WriteLine("8 - Quit");
            Console.WriteLine("9 - Emergency Coins");
            Console.Write("\nInput: ");
        }
        public static int GetUserMenuInput()
        {
            int input;
            try
            {
                input = Convert.ToInt32(Console.ReadLine());
                if (input < 1 || input > 9)
                {
                    throw new ArgumentException("Invalid Input");
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
                Tools.PressAnyKey();
                Console.Clear();
                return 0;
            }
        }
    }
}
