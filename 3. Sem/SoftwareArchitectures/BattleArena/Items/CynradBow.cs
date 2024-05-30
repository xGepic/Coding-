using BattleArena.Pawn;
using System;

namespace BattleArena.Items
{
    public class CynradBow : IEquipment
    {
        private const int percentageVariable = 2;
        private const int strenght = 10;
        private readonly Random randomNumberGenerator;
        public CynradBow(Random randomNumberGenerator)
        {
            this.randomNumberGenerator = randomNumberGenerator;
            LoggingSystem myLog = LoggingSystem.GetLoggingSystem();
            myLog.LogSomething($"CynradBow Created at {myLog.GetTimeStamp()}");
        }
        public void Use(Hero other)
        {
            if (this.randomNumberGenerator.Next(10) < percentageVariable)
            {
                other.ReduceHealth(strenght);
            }
        }
    }
}