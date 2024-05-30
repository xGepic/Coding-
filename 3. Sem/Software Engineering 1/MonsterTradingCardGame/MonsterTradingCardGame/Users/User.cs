using System;

namespace MonsterTradingCardGame
{
    public class User
    {
        public readonly string Username;
        public Deck MyDeck = new();
        public int Coins { get; set; }
        public int Elo { get; set; }
        public User(string myUsername, Deck userDeck, int eloPoints, int coins)
        {
            Username = myUsername;
            MyDeck = userDeck;
            Coins = coins;
            Elo = eloPoints;
        }
        public static String GetPassword()
        {
            string pwd = "";
            while (true)
            {
                ConsoleKeyInfo i = Console.ReadKey(true);
                if (i.Key == ConsoleKey.Enter)
                {
                    break;
                }
                else if (i.Key == ConsoleKey.Backspace)
                {
                    if (pwd.Length > 0)
                    {
                        pwd = pwd.Remove(pwd.Length - 1);
                        Console.Write("\b \b");
                    }
                }
                else if (i.KeyChar != '\u0000')
                {
                    pwd += (i.KeyChar);
                    Console.Write("*");
                }
            }
            return pwd;
        }
    }
}