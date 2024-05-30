using System;
using System.Collections.Generic;

namespace MonsterTradingCardGame
{
    static class TradeMenu
    {
        private const int TradeCardCount = 4;
        public static void PrintTradeMenu()
        {
            Console.WriteLine("TRADE MENU\n");
            Console.WriteLine("1 - Trade Cards");
            Console.WriteLine("2 - Go Back");
            Console.Write("\nInput: ");
        }
        public static int GetTradeInput()
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
        public static void GetTradeMenu(string username)
        {
            while (true)
            {
                PrintTradeMenu();
                int tradeInput = GetTradeInput();
                if (tradeInput == 1)
                {
                    DBConnector myDB = DBConnector.GetInstance();
                    if (myDB.IsStackEmpty(username))
                    {
                        Console.Clear();
                        Console.WriteLine("You have no Cards!\n");
                        Tools.PressAnyKey();
                        return;
                    }
                    myDB.RemoveCardsForTrading(username);
                    List<string> tradeCards = myDB.GetTradeCards();
                    int cardToAdd = GetTradeCard();
                    int cardToRemove = GetRemoveCard(username);
                    myDB.TradeCard(username, tradeCards, cardToAdd, cardToRemove);
                    Tools.PressToContinue();
                    Console.Clear();
                }
                if (tradeInput == 2)
                {
                    Console.Clear();
                    break;
                }
            }
        }
        public static int GetTradeCard()
        {
            Console.Write("\nInput: ");
            int input;
            try
            {
                input = Convert.ToInt32(Console.ReadLine());
                if (input > TradeCardCount || input < 1)
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
                Console.WriteLine("\n[Error] " + e.Message + "\n\n");
                return 0;
            }
        }
        public static int GetRemoveCard(string username)
        {
            DBConnector myDB = DBConnector.GetInstance();
            myDB.PrintPlayerStack(username);
            Console.WriteLine("\nWhich Card would you like to trade away?: ");
            int input;
            try
            {
                input = Convert.ToInt32(Console.ReadLine());
                if (input > myDB.CountPlayerStack(username) || input < 1)
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
                Console.WriteLine("\n[Error] " + e.Message + "\n\n");
                return 0;
            }
        }
    }
}
