using System;
using System.Collections.Generic;

namespace Testing
{
    class Character
    {
        private int LifePoints;
        public int GetLifePoints
        {
            get { return LifePoints; }
        }
        private int RelicPoints;
        public int GetRelicPoints
        {
            get { return RelicPoints; }
        }
        private int Strength;
        public int GetStrength
        {
            get { return Strength; }
        }
        private int Agility;
        public int GetAgility
        {
            get { return Agility; }
        }
        private int Intelligence;
        public int GetIntelligence
        {
            get { return Intelligence; }
        }
        public int X;
        public int Y;
        public Character()
        {
            LifePoints = 5;
            RelicPoints = 0;
            Strength = 0;
            Agility = 0;
            Intelligence = 0;
            X = 0;
            Y = 0;
        }
        public void PrintStats()
        {
            Console.WriteLine("|Stats| - RelicPoints: " + RelicPoints);
            Console.WriteLine("|Stats| - Lifepoints: " + LifePoints);
            Console.WriteLine("|Stats| - Strength: " + Strength);
            Console.WriteLine("|Stats| - Agility: " + Agility);
            Console.WriteLine("|Stats| - Intelligence: " + Intelligence);
            Console.WriteLine();
        }
        public void Damage()
        {
            this.LifePoints -= 1;
            if (this.LifePoints == 0)
            {
                Console.WriteLine("\nUnfortunately you died!\n");
                return;
            }
        }
        public void Heal()
        {
            this.LifePoints++;
        }
        public void FindRelic()
        {
            this.RelicPoints++;
        }
        public void CampFire(char n)
        {
            if (n == 's')
            {
                Console.WriteLine("After hours of training you feel a lot stronger![+1 Strength]\n");
                this.Strength++;
            }
            if (n == 'a')
            {
                Console.WriteLine("You find green herbs that make you feel refreshed and rejuvenated! [+1 Agility]\n");
                this.Agility++;
            }
            if (n == 'i')
            {
                Console.WriteLine("From your Spellbook you study new sorceries! [+1 Intelligence]\n");
                this.Intelligence++;
            }
        }
    }
}
