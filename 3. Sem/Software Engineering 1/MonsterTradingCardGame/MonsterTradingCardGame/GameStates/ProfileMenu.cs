using System;
using System.Threading;

namespace MonsterTradingCardGame
{
    static class ProfileMenu
    {
        public static void PrintProfileMenu()
        {
            Console.WriteLine();
            Console.WriteLine("1 - Change Password");
            Console.WriteLine("2 - Go Back");
            Console.Write("\nInput: ");
        }
        public static int GetProfileInput()
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
                Tools.PressAnyKey();
                Console.Clear();
                return 0;
            }
        }
        public static void GetProfileMenu(string username)
        {
            string pwd1;
            string pwd2;
            DBConnector myDB = DBConnector.GetInstance();
            while (true)
            {
                Console.WriteLine("MY PROFILE\n");
                myDB.GetProfile(username);
                PrintProfileMenu();
                int profileInput = GetProfileInput();
                if (profileInput == 1)
                {
                    Console.Clear();
                    Console.Write("Enter your old password: ");
                    string oldPW = Console.ReadLine();
                    if (myDB.LogInUser(username, oldPW))
                    {
                        do
                        {
                            Console.Write("Password: ");
                            pwd1 = Console.ReadLine();
                            Console.Write("Please repeat the Password: ");
                            pwd2 = Console.ReadLine();
                            if (pwd1 != pwd2)
                            {
                                Console.WriteLine("\n[ERROR] Passwords are not equal!\n\n");
                            }
                        } while (pwd1 != pwd2);
                        myDB.UpdatePassword(username, pwd1);
                        Console.WriteLine("\nNew Password has been set! - You will be taken to the Menu in 3 Seconds!");
                        Thread.Sleep(3000);
                        Console.Clear();
                    }
                    else
                    {
                        Console.WriteLine("\n\nPassword Incorrect!");
                        Tools.PressAnyKey();
                        Console.Clear();
                    }
                }
                if (profileInput == 2)
                {
                    Console.Clear();
                    break;
                }
            }
        }
    }
}
