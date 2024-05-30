using System;
using System.Linq;

namespace PasswordSafeConsole
{
    public class Program
    {
        //Here we use the new Method to get the new Path
        private readonly static MasterPasswordRepository masterRepository = new(Tools.GetMasterPath());
        private static PasswordSafeEngine passwordSafeEngine = null;
        public static void Main()
        {
            Console.WriteLine("Welcome to Passwordsafe");
            bool abort = false;
            bool unlocked = false;
            while (!abort)
            {
                Console.WriteLine("Enter master (1), show all (2), show single (3), add (4), delete(5), set new master (6), Abort (0)");
                if (!int.TryParse(Console.ReadLine(), out int input))
                {
                    input = -1;
                }
                switch (input)
                {
                    case 0:
                        {
                            abort = true;
                            break;
                        }
                    case 1:
                        {
                            Console.WriteLine("Enter master password");
                            String masterPw = Console.ReadLine();
                            unlocked = masterRepository.MasterPasswordIsEqualTo(masterPw);
                            if (unlocked)
                            {   //Here we use the new Method to get the new Path
                                passwordSafeEngine = new PasswordSafeEngine(Tools.GetPasswordPath(), new CipherFacility(masterPw));
                                Console.WriteLine("unlocked");
                            }
                            else
                            {
                                Console.WriteLine("master password did not match ! Failed to unlock.");
                            }
                            break;
                        }
                    case 2:
                        {
                            if (unlocked)
                            {
                                passwordSafeEngine.GetStoredPasswords().ToList().ForEach(pw => Console.WriteLine(pw));
                            }
                            else
                            {
                                Console.WriteLine("Please unlock first by entering the master password.");
                            }
                            break;
                        }
                    case 3:
                        {
                            if (unlocked)
                            {
                                Console.WriteLine("Enter password name");
                                String passwordName = Console.ReadLine();
                                Console.WriteLine(passwordSafeEngine.GetPassword(passwordName));
                            }
                            else
                            {
                                Console.WriteLine("Please unlock first by entering the master password.");
                            }
                            break;
                        }
                    case 4:
                        {
                            if (unlocked)
                            {
                                Console.WriteLine("Enter new name of password");
                                String passwordName = Console.ReadLine();
                                string password = Tools.DoubleCheck();//By setting a new password, it should be entered twice and checked for equality before writing to file.
                                passwordSafeEngine.AddNewPassword(new PasswordInfo(password, passwordName));
                            }
                            else
                            {
                                Console.WriteLine("Please unlock first by entering the master password.");
                            }
                            break;
                        }
                    case 5:
                        {
                            if (unlocked)
                            {
                                Console.WriteLine("Enter password name");
                                String passwordName = Console.ReadLine();
                                passwordSafeEngine.DeletePassword(passwordName);
                            }
                            else
                            {
                                Console.WriteLine("Please unlock first by entering the master password.");
                            }
                            break;
                        }
                    case 6:
                        {
                            unlocked = false;
                            passwordSafeEngine = null;
                            Console.WriteLine("Enter new master password ! (Warning you will loose all already stored passwords)");
                            String masterPw = Tools.DoubleCheck();//By setting a new password, it should be entered twice and checked for equality before writing to file.
                            masterRepository.SetMasterPassword(masterPw);
                            Tools.DeleteAll();//Here we use the new Method to delete all existing passwords
                            break;
                        }
                    default:
                        {
                            Console.WriteLine("Invalid input");
                            break;
                        }
                }
            }
            Console.WriteLine("Good bye !");
        }
    }
}