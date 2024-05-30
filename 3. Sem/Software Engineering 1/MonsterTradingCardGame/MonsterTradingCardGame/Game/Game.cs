using System;

namespace MonsterTradingCardGame
{
    static class Game
    {
        public static void GameLoop()
        {
            while (true)
            {
                UI.PrintWelcomeMessage();
                int getMenu = Menu.PrintStartingMenu();
                if (getMenu == 1)
                {
                    Menu.PrintLogIn();
                }
                else if(getMenu == 2)
                {
                    Menu.PrintSignUp();
                }
                else if (getMenu == 3)
                {
                    Console.Clear();
                    Console.WriteLine("GoodBye!");
                    return;
                }
            }
        }
    }
}
