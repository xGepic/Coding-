using System;
using System.Collections.Generic;

namespace MonsterTradingCardGame
{
    static class CraftYourDeck
    {
        public static void PrintDeckCraftingMenu()
        {
            Console.WriteLine("CRAFT YOUR DECK\n");
            Console.WriteLine("1 - Craft your Deck");
            Console.WriteLine("2 - Clear your Deck");
            Console.WriteLine("3 - View your Deck");
            Console.WriteLine("4 - View your Stack");
            Console.WriteLine("5 - Go Back");
            Console.Write("\nInput: ");
        }
        public static int GetDeckCraftingInput()
        {
            int input;
            try
            {
                input = Convert.ToInt32(Console.ReadLine());
                if (input < 1 || input > 5)
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
        public static void DeckCraftingMenu(string username)
        {
            List<int> CardList;
            while (true)
            {
                PrintDeckCraftingMenu();
                int DeckCraftingInput = GetDeckCraftingInput();
                if (DeckCraftingInput == 1)
                {
                    Console.Clear();
                    DBConnector myDB = DBConnector.GetInstance();
                    if (!myDB.IsDeckEmpty(username))
                    {
                        Console.WriteLine("You already have Cards in your Deck!\n");
                        Tools.PressAnyKey();
                        return;
                    }
                    myDB.PrintPlayerStack(username);
                    CardList = CraftYourDeck.GetCardsForDeck(username);
                    if (CardList == null)
                    {
                        Tools.PressToContinue();
                        return;
                    }
                    myDB.AddCardsToDeck(username, CardList);
                }
                if (DeckCraftingInput == 2)
                {
                    DBConnector myDB = DBConnector.GetInstance();
                    myDB.ClearDeck(username);
                }
                if (DeckCraftingInput == 3)
                {
                    Console.Clear();
                    DBConnector myDB = DBConnector.GetInstance();
                    myDB.PrintDeck(username);
                    Tools.PressAnyKey();
                    Console.Clear();
                }
                if (DeckCraftingInput == 4)
                {
                    Console.Clear();
                    DBConnector myDB = DBConnector.GetInstance();
                    myDB.PrintPlayerStack(username);
                    Tools.PressAnyKey();
                    Console.Clear();
                }
                if (DeckCraftingInput == 5)
                {
                    Console.Clear();
                    break;
                }
            }
        }
        public static List<int> GetCardsForDeck(string username)
        {
            DBConnector myDB = DBConnector.GetInstance();
            if (myDB.CountPlayerStack(username) < 4)
            {
                Console.WriteLine("You dont have enough Cards!");
                return null;
            }
            int index = 4;
            List<int> cardlist = new();
            try
            {
                Console.WriteLine($"Which Card would you like to add to your Deck? - {index} remaining!");
                Console.Write("Input:");
                int Card1 = Convert.ToInt32(Console.ReadLine());
                cardlist.Add(Card1);
                index--;
                Console.WriteLine($"Which Card would you like to add to your Deck? - {index} remaining!");
                Console.Write("Input:");
                int Card2 = Convert.ToInt32(Console.ReadLine());
                cardlist.Add(Card2);
                index--;
                Console.WriteLine($"Which Card would you like to add to your Deck? - {index} remaining!");
                Console.Write("Input:");
                int Card3 = Convert.ToInt32(Console.ReadLine());
                cardlist.Add(Card3);
                index--;
                Console.WriteLine($"Which Card would you like to add to your Deck? - {index} remaining!");
                Console.Write("Input:");
                int Card4 = Convert.ToInt32(Console.ReadLine());
                cardlist.Add(Card4);
                index--;
                Console.Clear();
                Console.WriteLine("Cards have been added to your Deck!\n");
                return cardlist;
            }
            catch (Exception e)
            {
                Console.WriteLine("\n[Error] " + e.Message + "\n\n");
                return null;
            }
        }
    }
}