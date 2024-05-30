using NUnit.Framework;
using MonsterTradingCardGame;
using System.Collections.Generic;

namespace mtcgUnitTests
{
    class BattleTests2
    {
        private readonly string username = "BattleTester";
        private readonly string pw = "unit123";
        private readonly int elo = 1000;
        private readonly int coins = 20;
        private readonly MonsterCard card1 = new("GrassDragon", 10, ElementType.Fire, MonsterType.Knight);
        private readonly MonsterCard card2 = new("TheKraken", 25, ElementType.Water, MonsterType.Kraken);
        [OneTimeTearDown]
        public void TearDown()
        {
            DBConnector cmd = DBConnector.GetInstance();
            cmd.RemoveCardFromStack(card1.Name);
            cmd.RemoveCardFromStack(card2.Name);
            cmd.RemoveUser(username);
        }
        [Test]
        public void TestGetBotDeck()
        {
            // ARRANGE
            DBConnector cmd = DBConnector.GetInstance();

            // ACT 
            var testDeck = cmd.GetBotDeck();
            var result = testDeck.CountCards();

            // ASSERT 
            Assert.AreEqual(result, 4);
        }
        [Test]
        public void TestPlayerWinsCards()
        {
            // ARRANGE
            DBConnector cmd = DBConnector.GetInstance();
            List<ICard> tempList = new();
            tempList.Add(card1);
            tempList.Add(card2);

            // ACT 
            cmd.RegisterUser(username, pw, elo, coins);
            cmd.PlayerWinsCards(username, tempList);
            var result = cmd.CheckIfCardIsThere(card1.Name);

            // ASSERT 
            Assert.AreEqual(result, true);
        }
    }
}
