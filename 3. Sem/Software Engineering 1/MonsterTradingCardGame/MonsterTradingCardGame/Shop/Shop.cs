using System;

namespace MonsterTradingCardGame
{
    static class Shop
    {
        public static void PrintShopMenu()
        {
            Console.WriteLine("WELCOME TO THE SHOP\n");
            Console.WriteLine("1 - Buy a Card Pack (5 Coins)");
            Console.WriteLine("2 - Go Back");
            Console.Write("\nInput: ");
        }
        public static int GetShopInput()
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
        public static void ShopMenu(string username)
        {
            while (true)
            {
                PrintShopMenu();
                int shopInput = GetShopInput();
                if (shopInput == 1)
                {
                    DBConnector myDB = DBConnector.GetInstance();
                    if (myDB.GetPlayerCoins(username) >= 5)
                    {
                        myDB.DecreaseCoinsofPlayer(username);
                        myDB.BuyACardPack(username);
                        Tools.PressAnyKey();
                        break;
                    }
                    else
                    {
                        Console.Clear();
                        Console.WriteLine("\n[ERROR] You dont have enough Coins to buy a Card Pack!\n");
                    }
                }
                if (shopInput == 2)
                {
                    Console.Clear();
                    break;
                }
            }
        }
    }
}