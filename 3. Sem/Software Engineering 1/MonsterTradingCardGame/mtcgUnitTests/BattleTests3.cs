using NUnit.Framework;
using MonsterTradingCardGame;
using System.Collections.Generic;

namespace mtcgUnitTests
{
    class BattleTests3
    {
        private readonly string username = "BattleTester3";
        private readonly string pw = "unit123";
        private readonly int elo = 1000;
        private readonly int coins = 20;
        private readonly MonsterCard card1 = new("FireOrk", 10, ElementType.Fire, MonsterType.Ork);
        private readonly MonsterCard card2 = new("WaterKnight", 15, ElementType.Water, MonsterType.Knight);
        private readonly MonsterCard card3 = new("GrassKnight", 15, ElementType.Grass, MonsterType.Knight);
        [OneTimeSetUp]
        public void SetUp()
        {

        }
        [OneTimeTearDown]
        public void TearDown()
        {
            DBConnector cmd = DBConnector.GetInstance();
            cmd.RemoveUser(username);
        }
        [Test]
        public void TestPlayerLostStack()
        {
            // ARRANGE
            DBConnector cmd = DBConnector.GetInstance();
            cmd.RegisterUser(username, pw, elo, coins);
            List<string> tempList = new();
            tempList.Add(card1.Name);
            tempList.Add(card2.Name);
            tempList.Add(card3.Name);
            cmd.AddCardToStack(username, tempList);
            List<ICard> cardList = new();
            cardList.Add(card1);
            cardList.Add(card2);
            cardList.Add(card3);

            // ACT
            cmd.PlayerLostStack(username, cardList);
            var result = cmd.CountPlayerStack(username);

            // ASSERT
            Assert.AreEqual(result, 0);
        }
    }
}
