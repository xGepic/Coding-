using System;

namespace MonsterTradingCardGame
{
    static class LoggedInUser
    {
        public static void LoggedInMenu(string userName)
        {
            while (true)
            {
                UI.PrintUserMenu(userName);
                int input = UI.GetUserMenuInput();

                if (input == 1)
                {
                    Console.Clear();
                    BattleMenu.GetBattleMenu(userName);
                }
                if (input == 2)
                {
                    Console.Clear();
                    Shop.ShopMenu(userName);
                    Console.Clear();
                }
                if (input == 3)
                {
                    Console.Clear();
                    CraftYourDeck.DeckCraftingMenu(userName);
                    Console.Clear();
                }
                if (input == 4)
                {
                    Console.Clear();
                    Console.WriteLine("LEADERBOARD\n");
                    DBConnector myDB = DBConnector.GetInstance();
                    myDB.GetLeaderboard();
                    Tools.PressAnyKey();
                    Console.Clear();
                }
                if (input == 5)
                {
                    Console.Clear();
                    ProfileMenu.GetProfileMenu(userName);
                    Console.Clear();
                }
                if (input == 6)
                {
                    Console.Clear();
                    TradeMenu.GetTradeMenu(userName);
                    Console.Clear();
                }
                if (input == 7)
                {
                    Console.Clear();
                    return;
                }
                if (input == 8)
                {
                    Console.Clear();
                    Console.WriteLine("GoodBye!");
                    Environment.Exit(0);
                }
                if(input == 9)
                {
                    Console.Clear();
                    DBConnector myDB = DBConnector.GetInstance();
                    myDB.EmergencyCoins(userName);
                    Tools.PressAnyKey();
                    Console.Clear();
                }
            }
        }
    }
}