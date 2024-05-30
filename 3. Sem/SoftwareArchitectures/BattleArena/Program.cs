using BattleArena.Items;
using BattleArena.Pawn;
using BattleArena.Items.OldVersion;
using System;

namespace BattleArena
{
    class Program
    {
        static void Main()
        {
            UserIO userinteraction = new();
            Random randomNumberGenerator = new();
            LatharSword latharSword = new(randomNumberGenerator);
            //Here 1 Player gets the latharSword by using the adapter
            Hero[] playerList = { new Hero("Player 1", new CynradBow(randomNumberGenerator)), new Hero("Player 2", new Adapter(latharSword)) };
            //Here we create both achievments
            LuckyAchievment luckyAchievment = new();
            RichAchievment richAchievment = new();
            //And here we subscribe the heros to both of the achievments
            foreach (var item in playerList)
            {
                item.Subscribe(luckyAchievment);
                item.Subscribe(richAchievment);
            }
            bool run = true;
            while (run)
            {
                userinteraction.ClearScreen();
                userinteraction.PrintPlayerInformation(playerList);
                foreach (Hero currentHero in playerList)
                {
                    bool action = false;
                    do
                    {
                        int userinput = -1;
                        do
                        {
                            userinteraction.PrintFightMenu(currentHero.Name);
                            userinput = userinteraction.GetUserIput();
                        } while (userinput < 0 || userinput > 5);
                        switch (userinput)
                        {
                            case 0:
                                // exit game
                                run = false;
                                userinteraction.ExitGame();
                                return;
                            case 1:
                                if (currentHero.Name == "Player 1")
                                {
                                    action = currentHero.Action(playerList[1]);
                                }
                                else
                                {
                                    action = currentHero.Action(playerList[0]);
                                }
                                break;
                            case 2:
                                action = currentHero.AddLeprechaun();
                                break;
                            case 3:
                                action = currentHero.AddTinyGoblin(randomNumberGenerator);
                                break;
                            case 4:
                                action = currentHero.AddMediumGoblin(randomNumberGenerator);
                                break;
                            case 5:
                                action = currentHero.AddBigGoblin(randomNumberGenerator);
                                break;
                            default:
                                break;
                        }
                        if (!action)
                        {
                            userinteraction.ClearScreen();
                            userinteraction.PrintPlayerInformation(playerList);
                            Console.WriteLine("\nNot enought money");
                        }
                    } while (!action);
                    currentHero.UpdateCoins();
                    if (currentHero.Name == "Player 1")
                    {
                        currentHero.UseGoblins(playerList[1]);
                    }
                    else
                    {
                        currentHero.UseGoblins(playerList[0]);
                    }
                }
                // end condition
                if (playerList[0].Health <= 0)
                {
                    userinteraction.EndGame(playerList[0].Name);
                    run = false;
                    LoggingSystem myLog = LoggingSystem.GetLoggingSystem();
                    myLog.WriteListToFile();
                    myLog.PrintLog();
                }
                else if (playerList[1].Health <= 0)
                {
                    userinteraction.EndGame(playerList[1].Name);
                    run = false;
                    LoggingSystem myLog = LoggingSystem.GetLoggingSystem();
                    myLog.WriteListToFile();
                    myLog.PrintLog();
                }
            }
        }
    }
}