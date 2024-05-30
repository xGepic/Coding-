using BattleArena.Items;
using System;
using System.Collections.Generic;

namespace BattleArena.Pawn
{
    public class Hero : ISubject
    {
        //List for the Observers
        private List<IObserver> observers = new();
        private readonly IEquipment weapon;
        private List<Goblin> goblins = new();
        public int Health { get; private set; } = 100;
        private int _Coins = 1;
        //Here we Alert every time the Value gets changed
        public int Coins
        {
            get { return _Coins; }
            set
            {
                _Coins = value;
                Alert();
            }
        }
        public int NumberOfGoblins => this.goblins.Count;
        private int _Leprechaun = 0;
        //Here we Alert every time the Value gets changed
        public int Leprechaun
        {
            get { return _Leprechaun; }
            set
            {
                _Leprechaun = value;
                Alert();
            }
        }
        public string Name { get; private set; }
        public Hero(string name, IEquipment equipment)
        {
            this.Name = name;
            this.weapon = equipment;
            LoggingSystem myLog = LoggingSystem.GetLoggingSystem();
            myLog.LogSomething($"Hero Created at {myLog.GetTimeStamp()}");
        }
        public bool Action(Hero other)
        {
            this.weapon.Use(other);
            return true;
        }
        public void UpdateCoins()
        {
            this.Coins += this._Leprechaun + 1;
        }
        public void UseGoblins(Hero other)
        {
            foreach (Goblin tmpGoblin in this.goblins)
            {
                tmpGoblin.Action(other);
            }
        }
        public void ReduceHealth(int hitPoints)
        {
            this.Health -= hitPoints;
        }
        public bool AddLeprechaun()
        {
            if (this.Coins > 1)
            {
                this.Coins -= 2;
                this._Leprechaun++;
                return true;
            }
            return false;
        }
        public bool AddTinyGoblin(Random randomNumberGenerator)
        {
            if (this.Coins > 0)
            {
                this.Coins -= 1;
                this.goblins.Add(new Goblin(1, randomNumberGenerator));
                return true;
            }
            return false;
        }
        public bool AddMediumGoblin(Random randomNumberGenerator)
        {
            if (this.Coins > 2)
            {
                this.Coins -= 3;
                this.goblins.Add(new Goblin(2, randomNumberGenerator));
                return true;
            }
            return false;
        }
        public bool AddBigGoblin(Random randomNumberGenerator)
        {
            if (this.Coins > 5)
            {
                this.Coins -= 6;
                this.goblins.Add(new Goblin(3, randomNumberGenerator));
                return true;
            }
            return false;
        }

        //Observer
        public void Subscribe(IObserver observer)
        {
            observers.Add(observer);
        }
        public void Alert()
        {
            observers.ForEach(o =>
            {
                o.Update(this);
            });
        }
    }
}