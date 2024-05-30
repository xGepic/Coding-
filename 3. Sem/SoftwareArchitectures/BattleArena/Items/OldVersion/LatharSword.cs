using System;

namespace BattleArena.Items.OldVersion
{
    //Service Class
    public class LatharSword
    {
        private const int percentageVariable = 4;
        private const int strenght = 5;
        private readonly Random randomNumberGenerator;
        public LatharSword(Random randomNumberGenerator)
        {
            this.randomNumberGenerator = randomNumberGenerator;
            LoggingSystem myLog = LoggingSystem.GetLoggingSystem();
            myLog.LogSomething($"LatharSword Created at {myLog.GetTimeStamp()}");
        }
        public int Hit()
        {
            return this.randomNumberGenerator.Next(10) < percentageVariable ? strenght : 0;
        }
    }
}