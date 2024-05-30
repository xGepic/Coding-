using System;

namespace BattleArena.Pawn
{
    internal class Goblin
    {
        private const int percentageVariable = 3;
        private int strength;
        private Random randomNumberGenerator;
        public Goblin(int strength, Random randomNumberGenerator)
        {
            this.strength = strength;
            this.randomNumberGenerator = randomNumberGenerator;
            LoggingSystem myLog = LoggingSystem.GetLoggingSystem();
            myLog.LogSomething($"Goblin Created at {myLog.GetTimeStamp()}");
        }
        internal void Action(Hero other)
        {
            if (this.randomNumberGenerator.Next(10) < percentageVariable)
            {
                other.ReduceHealth(strength);
            }
        }
    }
}