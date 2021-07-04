using System;
using System.Collections.Generic;

namespace Testing
{
    class World
    {
        public char[,] playingField = new char[10, 10];
        public char guy = 'X';
        public bool tmp = false;
        private readonly int relicCount = 0;
        public int GetRelicCount
        {
            get { return relicCount; }
        }
        public World()
        {
            while (tmp != true)
            {
                for (int x = 0; x < 10; x++)
                {
                    for (int y = 0; y < 10; y++)
                    {
                        playingField[x, y] = Rcg();
                        if (playingField[x, y] == 'R')
                        {
                            relicCount++;
                        }
                    }
                }
                if (relicCount > 0)
                {
                    tmp = true;
                }
            }
            playingField[0, 0] = guy;
        }
        public void PrintWorld()
        {
            Console.WriteLine("+=====================+");
            for (int k = 0; k < 10; k++)
            {
                Console.Write("|" + " ");
                for (int l = 0; l < 10; l++)
                {
                    Console.Write(playingField[k, l] + " ");
                }
                Console.Write("|" + " ");
                Console.WriteLine();
            }
            Console.WriteLine("+=====================+");
        }
        private static char Rcg()
        {
            Random rand = new();
            int n = rand.Next(1, 100);
            if (n <= 40)
            {
                return 'E';
            }
            if (n <= 80)
            {
                return 'D';
            }
            if (n <= 90)
            {
                return 'F';
            }
            return 'R';
        }
        public void Move(char[,] arr, Character C, char direction, LinkedList<string> Log)
        {
            if (direction == 'w')
            {
                if (C.X - 1 < 0)
                {
                    ThrowError();
                    return;
                }
                this.playingField[C.X, C.Y] = 'E';
                C.X--;
                Console.WriteLine("You took a step north!\n");
                Log.AddLast("You took a step north!");
                Console.Clear();
                Activate(arr, C);
                if (GetRelicCount == C.GetRelicPoints)
                {
                    return;
                }
                this.playingField[C.X, C.Y] = guy;
                C.PrintStats();
                PrintWorld();
            }
            if (direction == 'a')
            {
                if (C.Y - 1 < 0)
                {
                    ThrowError();
                    return;
                }
                this.playingField[C.X, C.Y] = 'E';
                C.Y--;
                Console.WriteLine("You took a step west!\n");
                Log.AddLast("You took a step west!");
                Console.Clear();
                Activate(arr, C);
                if (GetRelicCount == C.GetRelicPoints)
                {
                    return;
                }
                this.playingField[C.X, C.Y] = guy;
                C.PrintStats();
                PrintWorld();
            }
            if (direction == 's')
            {
                if (C.X + 1 > 9)
                {
                    ThrowError();
                    return;
                }
                this.playingField[C.X, C.Y] = 'E';
                C.X++;
                Console.WriteLine("You took a step south!\n");
                Log.AddLast("You took a step south!");
                Console.Clear();
                Activate(arr, C);
                if (GetRelicCount == C.GetRelicPoints)
                {
                    return;
                }
                this.playingField[C.X, C.Y] = guy;
                C.PrintStats();
                PrintWorld();
            }
            if (direction == 'd')
            {
                if (C.Y + 1 > 9)
                {
                    ThrowError();
                    return;
                }
                this.playingField[C.X, C.Y] = 'E';
                C.Y++;
                Console.WriteLine("You took a step east!\n");
                Log.AddLast("You took a step east!");
                Console.Clear();
                Activate(arr, C);
                if (GetRelicCount == C.GetRelicPoints)
                {
                    return;
                }
                this.playingField[C.X, C.Y] = guy;
                C.PrintStats();
                PrintWorld();
            }
            else
            {
                ThrowError();
                return;
            }
        }
        public void Activate(char[,] arr, Character C)
        {
            Random rand = new();
            int m = rand.Next(1, 5);
            int i = rand.Next(1, 6);
            char n;
            if (arr[C.X, C.Y] == 'E')
            {
                Console.WriteLine("You stepped on an empty field, nothing happens!\n\n");
                if (m == 4)
                {
                    Console.WriteLine("You stumble past a Tavern! - Here you can improve 1 of your Skills!\n");
                    while (true)
                    {
                        Console.Write("Which Attribute whould you like to improve? [Strength(s), Agility(a) or Intelligence(i)");
                        try
                        {
                            n = Convert.ToChar(Console.ReadLine());
                            if (n == 's' || n == 'a' || n == 'i')
                            {
                                C.CampFire(n);
                                break;
                            }
                            else
                            {
                                ThrowError();
                            }
                        }
                        catch (FormatException)
                        {
                            ThrowError();
                        }
                    }
                }
            }
            if (arr[C.X, C.Y] == 'D')
            {
                Console.Write("You stepped on a danger field... ");
                if (i == 2)
                {
                    if (C.GetStrength >= 2)
                    {
                        Console.Write("but through your hard training you managed to defeat the Enemy!\n");
                    }
                    else
                    {
                        Console.Write("and got damaged! [-1 LifePoint]\n\n");
                        C.Damage();
                    }
                }
                else
                {
                    Console.Write("but nothing happend!\n\n");
                }
            }
            if (arr[C.X, C.Y] == 'F')
            {
                Console.Write("You stepped on a Fountain! - ");
                if (C.GetIntelligence >= 2)
                {
                    C.Heal();
                    C.Heal();
                    Console.WriteLine("With one of your spells you make the fountain more productive! [+2 LifePoints]\n");
                }
                else
                {
                    C.Heal();
                    Console.WriteLine("Take a rest and heal yourself! [+1 LifePoint]\n");
                }
            }
            if (arr[C.X, C.Y] == 'R')
            {
                Console.WriteLine("You stepped on a Relic! [+1 RelicPoint]\n");
                C.FindRelic();
                if (GetRelicCount == C.GetRelicPoints)
                {
                    Console.WriteLine("Congratulations you won the Game!\n");
                    return;
                }
            }
        }
        public static void ThrowError()
        {
            Console.WriteLine();
            Console.WriteLine("That is not possible!");
        }
    }
}
