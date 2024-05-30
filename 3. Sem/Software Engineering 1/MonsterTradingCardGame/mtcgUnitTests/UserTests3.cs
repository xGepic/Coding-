using NUnit.Framework;
using MonsterTradingCardGame;

namespace mtcgUnitTests
{
    class UserTests3
    {
        private readonly string username = "UserTester3";
        private readonly string pw = "unit123";
        private readonly int elo = 1200;
        private readonly int coins = 20;
        [OneTimeTearDown]
        public void TearDown()
        {
            DBConnector cmd = DBConnector.GetInstance();
            cmd.RemoveUser(username);
        }
        [Test]
        public void TestGetLeaderboard()
        {
            // ARRANGE
            DBConnector cmd = DBConnector.GetInstance();

            // ACT 
            var result = cmd.GetLeaderboard();

            // ASSERT
            Assert.AreEqual(result, true);
        }
        [Test]
        public void TestGetProfile()
        {
            // ARRANGE
            DBConnector cmd = DBConnector.GetInstance();

            // ACT 
            cmd.RegisterUser(username, pw, elo, coins);
            var result = cmd.GetProfile(username);

            // ASSERT
            Assert.AreEqual(result, true);
        }
    }
}