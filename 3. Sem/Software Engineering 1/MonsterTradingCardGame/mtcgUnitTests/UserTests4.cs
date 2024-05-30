using NUnit.Framework;
using MonsterTradingCardGame;

namespace mtcgUnitTests
{
    class UserTests4
    {
        private readonly string username = "UserTester4";
        private readonly string pw = "unit123";
        private readonly int elo = 1000;
        private readonly int coins = 0;
        [OneTimeTearDown]
        public void TearDown()
        {
            DBConnector cmd = DBConnector.GetInstance();
            cmd.RemoveUser(username);
        }
        [Test]
        public void TestEmergencyCoins()
        {
            // ARRANGE
            DBConnector cmd = DBConnector.GetInstance();

            // ACT 
            cmd.RegisterUser(username, pw, elo, coins);
            cmd.EmergencyCoins(username);
            var result = cmd.GetPlayerCoins(username);

            // ASSERT 
            Assert.AreEqual(result, 20);
        }
    }
}
