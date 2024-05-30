using System;
using System.Threading;

namespace MonsterTradingCardGame
{
    static class Menu
    {
        private const int startingElo = 1000;
        private const int startingCoins = 20;
        public static int PrintStartingMenu()
        {
            int input;
            Console.WriteLine("What would you like to do?:");
            Console.WriteLine("1 - LOGIN");
            Console.WriteLine("2 - SIGNUP");
            Console.WriteLine("3 - QUIT");
            Console.Write("\nInput: ");
            try
            {
                input = Convert.ToInt32(Console.ReadLine());
                if (input != 1 && input != 2 && input != 3)
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
        public static void PrintLogIn()
        {
            string username;
            string pwd;
            Console.Clear();
            Console.WriteLine("--| LOGIN |--\n");
            Console.WriteLine("Username: ");
            username = Console.ReadLine();
            Console.WriteLine("Password: ");
            pwd = User.GetPassword();

            DBConnector myDB = DBConnector.GetInstance();
            if (myDB.LogInUser(username, pwd))
            {
                Console.WriteLine("\n\nSuccess! - You will be taken to the Menu in 3 Seconds!");
                Thread.Sleep(3000);
                Console.Clear();
                LoggedInUser.LoggedInMenu(username);
            }
            else
            {
                Console.Clear();
                Console.WriteLine("[Error] Invalid Credentials!\n");
                Tools.PressAnyKey();
                Console.Clear();
                return;
            }
        }
        public static void PrintSignUp()
        {
            string username;
            string pwd1;
            string pwd2;
            Console.Clear();
            Console.WriteLine("--| SIGN UP |--\n");
            Console.WriteLine("Username: ");
            username = Console.ReadLine();
            do
            {
                Console.WriteLine("Password: ");
                pwd1 = Console.ReadLine();
                Console.WriteLine("Please repeat the Password: ");
                pwd2 = Console.ReadLine();
                if (pwd1 != pwd2)
                {
                    Console.WriteLine("\n[ERROR] Passwords are not equal!\n\n");
                }
            } while (pwd1 != pwd2);

            DBConnector myDB = DBConnector.GetInstance();
            if (myDB.RegisterUser(username, pwd1, startingElo, startingCoins))
            {
                Console.WriteLine("\nSignup Successful! - You will be taken to the Menu in 3 Seconds!");
                Thread.Sleep(3000);
                Console.Clear();
            }
            else
            {
                Console.WriteLine("\nSignup Failed!");
            }
        }

    }
}