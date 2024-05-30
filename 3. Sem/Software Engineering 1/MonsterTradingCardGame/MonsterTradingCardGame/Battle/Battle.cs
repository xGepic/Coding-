using System;

namespace MonsterTradingCardGame
{
    public class Battle
    {
        private const int HalfOrDouble = 2;
        public static int DamageCalc(ICard Card1, ICard Card2)
        {
            Console.WriteLine("##############################");
            if ((Card1.MyCardtype == CardType.Monster && Card2.MyCardtype == CardType.Spell) || Card1.MyCardtype == CardType.Spell && Card2.MyCardtype == CardType.Monster)
            {
                int DmgFromC1 = Card1.Damage;
                int DmgFromC2 = Card2.Damage;
                Console.WriteLine("    Monster vs Spell Fight\n");

                if (Card1.MyMonsterType == MonsterType.Knight && Card2.MyCardtype == CardType.Spell && Card2.MyElementType == ElementType.Water)
                {
                    Console.WriteLine($"{Card1.Name} ({DmgFromC1}) vs {Card2.Name} ({DmgFromC2})\n");
                    Console.WriteLine("The armor of Knights is so heavy that WaterSpells make them drown them instantly!");
                    Console.WriteLine($"{Card2.Name} defeats {Card1.Name}");
                    PrintLine();
                    return 2;
                }
                if (Card2.MyMonsterType == MonsterType.Knight && Card1.MyCardtype == CardType.Spell && Card1.MyElementType == ElementType.Water)
                {
                    Console.WriteLine($"{Card1.Name} ({DmgFromC1}) vs {Card2.Name} ({DmgFromC2})\n");
                    Console.WriteLine("The armor of Knights is so heavy that WaterSpells make them drown them instantly!");
                    Console.WriteLine($"{Card1.Name} defeats {Card2.Name}");
                    PrintLine();
                    return 1;
                }
                if (Card1.MyMonsterType == MonsterType.Kraken && Card2.MyCardtype == CardType.Spell)
                {
                    Console.WriteLine($"{Card1.Name} ({DmgFromC1}) vs {Card2.Name} ({DmgFromC2})\n");
                    Console.WriteLine("The Kraken is immune against spells!");
                    Console.WriteLine($"{Card1.Name} defeats {Card2.Name}");
                    PrintLine();
                    return 1;
                }
                if (Card2.MyMonsterType == MonsterType.Kraken && Card1.MyCardtype == CardType.Spell)
                {
                    Console.WriteLine($"{Card1.Name} ({DmgFromC1}) vs {Card2.Name} ({DmgFromC2})\n");
                    Console.WriteLine("The Kraken is immune against spells!");
                    Console.WriteLine($"{Card2.Name} defeats {Card1.Name}");
                    PrintLine();
                    return 2;
                }
                if (Card1.MyElementType == ElementType.Grass && Card2.MyElementType == ElementType.Fire)
                {
                    DmgFromC1 /= HalfOrDouble;
                    DmgFromC2 *= HalfOrDouble;
                }
                if (Card1.MyElementType == ElementType.Fire && Card2.MyElementType == ElementType.Water)
                {
                    DmgFromC1 /= HalfOrDouble;
                    DmgFromC2 *= HalfOrDouble;
                }
                if (Card1.MyElementType == ElementType.Water && Card2.MyElementType == ElementType.Grass)
                {
                    DmgFromC1 /= HalfOrDouble;
                    DmgFromC2 *= HalfOrDouble;
                }
                if (Card1.MyElementType == ElementType.Fire && Card2.MyElementType == ElementType.Grass)
                {
                    DmgFromC1 *= HalfOrDouble;
                    DmgFromC2 /= HalfOrDouble;
                }
                if (Card1.MyElementType == ElementType.Grass && Card2.MyElementType == ElementType.Water)
                {
                    DmgFromC1 *= HalfOrDouble;
                    DmgFromC2 /= HalfOrDouble;
                }
                if (Card1.MyElementType == ElementType.Water && Card2.MyElementType == ElementType.Fire)
                {
                    DmgFromC1 *= HalfOrDouble;
                    DmgFromC2 /= HalfOrDouble;
                }
                Console.WriteLine($"{Card1.Name} ({DmgFromC1}) vs {Card2.Name} ({DmgFromC2})\n");
                if (DmgFromC1 < DmgFromC2)
                {
                    Console.WriteLine($"\n{Card2.Name} defeats {Card1.Name}");
                    PrintLine();
                    return 2;
                }
                else if (DmgFromC2 < DmgFromC1)
                {
                    Console.WriteLine($"\n{Card1.Name} defeats {Card2.Name}");
                    PrintLine();
                    return 1;
                }
                else
                {
                    Console.WriteLine("\n       Its a Draw!");
                    PrintLine();
                    return 3;
                }
            }
            if (Card1.MyCardtype == CardType.Monster && Card2.MyCardtype == CardType.Monster)
            {
                int DmgFromC1 = Card1.Damage;
                int DmgFromC2 = Card2.Damage;
                Console.WriteLine("        MonsterFight\n");
                Console.WriteLine($"{Card1.Name} ({DmgFromC1}) vs {Card2.Name} ({DmgFromC2})\n");
                if (Card1.MyMonsterType == MonsterType.Goblin && Card2.MyMonsterType == MonsterType.Dragon)
                {
                    Console.WriteLine("Goblins are too afraid of Dragons to attack!");
                    Console.WriteLine($"{Card2.Name} defeats {Card1.Name}");
                    PrintLine();
                    return 2;
                }
                if (Card2.MyMonsterType == MonsterType.Goblin && Card1.MyMonsterType == MonsterType.Dragon)
                {
                    Console.WriteLine("Goblins are too afraid of Dragons to attack!");
                    Console.WriteLine($"{Card1.Name} defeats {Card2.Name}");
                    PrintLine();
                    return 1;
                }
                if (Card1.MyMonsterType == MonsterType.Ork && Card2.MyMonsterType == MonsterType.Wizzard)
                {
                    Console.WriteLine("Wizzard can control Orks so they are not able to damage them!");
                    Console.WriteLine($"{Card2.Name} defeats {Card1.Name}");
                    PrintLine();
                    return 2;
                }
                if (Card2.MyMonsterType == MonsterType.Ork && Card1.MyMonsterType == MonsterType.Wizzard)
                {
                    Console.WriteLine("Wizzard can control Orks so they are not able to damage them!");
                    Console.WriteLine($"{Card1.Name} defeats {Card2.Name}");
                    PrintLine();
                    return 1;
                }
                if (Card1.MyMonsterType == MonsterType.Dragon && Card2.MyMonsterType == MonsterType.Elf)
                {
                    Console.WriteLine("The FireElves know Dragons since they were little and can evade their attacks!");
                    Console.WriteLine($"{Card2.Name} defeats {Card1.Name}");
                    PrintLine();
                    return 2;
                }
                if (Card2.MyMonsterType == MonsterType.Dragon && Card1.MyMonsterType == MonsterType.Elf)
                {
                    Console.WriteLine("The FireElves know Dragons since they were little and can evade their attacks!");
                    Console.WriteLine($"{Card1.Name} defeats {Card2.Name}");
                    PrintLine();
                    return 1;
                }
                if (DmgFromC1 < DmgFromC2)
                {
                    Console.WriteLine($"\n{Card2.Name} defeats {Card1.Name}");
                    PrintLine();
                    return 2;
                }
                else if (DmgFromC2 < DmgFromC1)
                {
                    Console.WriteLine($"\n{Card1.Name} defeats {Card2.Name}");
                    PrintLine();
                    return 1;
                }
                else
                {
                    Console.WriteLine("\n       Its a Draw!");
                    PrintLine();
                    return 3;
                }
            }
            if (Card1.MyCardtype == CardType.Spell && Card2.MyCardtype == CardType.Spell)
            {
                int DmgFromC1 = Card1.Damage;
                int DmgFromC2 = Card2.Damage;
                Console.WriteLine("         SpellFight!\n");
                if (Card1.MyElementType == ElementType.Grass && Card2.MyElementType == ElementType.Fire)
                {
                    DmgFromC1 /= HalfOrDouble;
                    DmgFromC2 *= HalfOrDouble;
                }
                if (Card1.MyElementType == ElementType.Fire && Card2.MyElementType == ElementType.Water)
                {
                    DmgFromC1 /= HalfOrDouble;
                    DmgFromC2 *= HalfOrDouble;
                }
                if (Card1.MyElementType == ElementType.Water && Card2.MyElementType == ElementType.Grass)
                {
                    DmgFromC1 /= HalfOrDouble;
                    DmgFromC2 *= HalfOrDouble;
                }
                if (Card1.MyElementType == ElementType.Fire && Card2.MyElementType == ElementType.Grass)
                {
                    DmgFromC1 *= HalfOrDouble;
                    DmgFromC2 /= HalfOrDouble;
                }
                if (Card1.MyElementType == ElementType.Grass && Card2.MyElementType == ElementType.Water)
                {
                    DmgFromC1 *= HalfOrDouble;
                    DmgFromC2 /= HalfOrDouble;
                }
                if (Card1.MyElementType == ElementType.Water && Card2.MyElementType == ElementType.Fire)
                {
                    DmgFromC1 *= HalfOrDouble;
                    DmgFromC2 /= HalfOrDouble;
                }
                if (DmgFromC1 < DmgFromC2)
                {
                    Console.WriteLine($"{Card1.Name} ({DmgFromC1}) vs {Card2.Name} ({DmgFromC2})\n");
                    Console.WriteLine($"\n{Card2.Name} defeats {Card1.Name}");
                    PrintLine();
                    return 2;
                }
                else if (DmgFromC2 < DmgFromC1)
                {
                    Console.WriteLine($"{Card1.Name} ({DmgFromC1}) vs {Card2.Name} ({DmgFromC2})\n");
                    Console.WriteLine($"\n{Card1.Name} defeats {Card2.Name}");
                    PrintLine();
                    return 1;
                }
                else
                {
                    Console.WriteLine($"{Card1.Name} ({DmgFromC1}) vs {Card2.Name} ({DmgFromC2})\n");
                    Console.WriteLine("\n       Its a Draw!");
                    PrintLine();
                    return 3;
                }
            }
            return -1;
        }
        private static void PrintLine()
        {
            Console.WriteLine("##############################\n");
        }
    }
}