using NUnit.Framework;
using MonsterTradingCardGame;

namespace mtcgUnitTests
{
    class UserTests
    {
        private readonly string username = "Unit";
        private readonly string username2 = "Unit2";
        private readonly string pw = "unit123";
        private readonly string newPW = "goodOne";
        private readonly int elo = 1200;
        private readonly int coins = 20;
        [OneTimeTearDown]
        public void TearDown()
        {
            DBConnector cmd = DBConnector.GetInstance();
            cmd.RemoveUser(username);
            cmd.RemoveUser(username2);
        }
        [Test]
        public void TestRegister()
        {
            // ARRANGE
            DBConnector cmd = DBConnector.GetInstance();

            // ACT
            var result = cmd.RegisterUser(username, pw, elo, coins);

            // ASSERT 
            Assert.AreEqual(result, true);
        }
        [Test]
        public void TestSignUp()
        {
            // ARRANGE
            DBConnector cmd = DBConnector.GetInstance();

            // ACT
            var result = cmd.LogInUser(username, pw);

            // ASSERT 
            Assert.AreEqual(result, true);
        }
        [Test]
        public void TestChangePassword()
        {
            // ARRANGE
            DBConnector cmd = DBConnector.GetInstance();

            // ACT
            cmd.RegisterUser(username2, pw, elo, coins);
            var string1 = cmd.GetPWHash(username2);
            cmd.UpdatePassword(username2, newPW);
            var string2 = cmd.GetPWHash(username2);

            // ASSERT
            Assert.AreNotEqual(string1, string2);
        }
    }
}
