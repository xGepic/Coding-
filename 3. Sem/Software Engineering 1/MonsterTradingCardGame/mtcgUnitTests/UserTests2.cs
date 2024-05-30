using NUnit.Framework;
using MonsterTradingCardGame;

namespace mtcgUnitTests
{
    class UserTests2
    {
        private readonly string username = "UserTester";
        private readonly string username2 = "UserTester2";
        private readonly string pw = "unit123";
        private readonly int elo = 1200;
        private readonly int coins = 20;
        private readonly int newElo = 1000;
        [OneTimeTearDown]
        public void TearDown()
        {
            DBConnector cmd = DBConnector.GetInstance();
            cmd.RemoveUser(username);
            cmd.RemoveUser(username2);
        }
        [Test]
        public void TestUpdateElo()
        {
            // ARRANGE
            DBConnector cmd = DBConnector.GetInstance();

            // ACT
            cmd.RegisterUser(username, pw, elo, coins);
            cmd.UpdatePlayerElo(username, newElo);
            var result = cmd.GetPlayerElo(username);

            // ASSERT 
            Assert.AreEqual(result, newElo);
        }
        [Test]
        public void TestIsDeckEmpty()
        {
            // ARRANGE
            DBConnector cmd = DBConnector.GetInstance();

            // ACT
            var result = cmd.IsDeckEmpty(username);

            // ASSERT 
            Assert.AreEqual(result, true);
        }
        [Test]
        public void TestDecreaseCoins()
        {
            // ARRANGE
            DBConnector cmd = DBConnector.GetInstance();

            // ACT
            cmd.RegisterUser(username2, pw, elo, coins);
            var result1 = cmd.GetPlayerCoins(username2);
            cmd.DecreaseCoinsofPlayer(username2);
            var result2 = cmd.GetPlayerCoins(username2);

            // ASSERT 
            Assert.AreNotEqual(result1, result2);
        }
    }
}
