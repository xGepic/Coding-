using NUnit.Framework;
using MonsterTradingCardGame;

namespace mtcgUnitTests
{
    public class BattleTests
    {
        [Test]
        public void TestMonsterBattle()
        {
            // ARRANGE
            MonsterCard Monster1 = new("testCard1", 15, ElementType.Fire, MonsterType.Knight);
            MonsterCard Monster2 = new("testCard2", 10, ElementType.Water, MonsterType.Goblin);

            // ACT 
            var result = Battle.DamageCalc(Monster1, Monster2);

            // ASSERT 
            Assert.AreEqual(result, 1);
        }
        [Test]
        public void TestMonsterBattleReversed()
        {
            // ARRANGE
            MonsterCard Monster1 = new("testCard1", 15, ElementType.Fire, MonsterType.Knight);
            MonsterCard Monster2 = new("testCard2", 10, ElementType.Water, MonsterType.Goblin);

            // ACT 
            var result = Battle.DamageCalc(Monster2, Monster1);

            // ASSERT 
            Assert.AreEqual(result, 2);

        }
        [Test]
        public void TestSpellBattle()
        {
            // ARRANGE
            SpellCard Spell1 = new("testCard1", 15, ElementType.Fire);
            SpellCard Spell2 = new("testCard2", 10, ElementType.Water);

            // ACT 
            var result = Battle.DamageCalc(Spell1, Spell2);

            // ASSERT 
            Assert.AreEqual(result, 2);
        }
        [Test]
        public void TestMixBattle()
        {
            // ARRANGE
            MonsterCard Monster1 = new("testCard1", 15, ElementType.Fire, MonsterType.Knight);
            SpellCard Spell1 = new("testCard1", 20, ElementType.Fire);

            // ACT 
            var result = Battle.DamageCalc(Monster1, Spell1);

            // ASSERT 
            Assert.AreEqual(result, 2);
        }
        [Test]
        public void CheckDraw()
        {
            // ARRANGE
            MonsterCard Monster1 = new("testCard1", 15, ElementType.Fire, MonsterType.Knight);
            SpellCard Spell1 = new("testCard1", 15, ElementType.Fire);

            // ACT 
            var result = Battle.DamageCalc(Monster1, Spell1);

            // ASSERT 
            Assert.AreEqual(result, 3);
        }
        [Test]
        public void TestKraken()
        {
            // ARRANGE
            MonsterCard Kraken = new("testCard1", 15, ElementType.Water, MonsterType.Kraken);
            SpellCard Spell = new("testCard1", 15, ElementType.Fire);

            // ACT 
            var result = Battle.DamageCalc(Kraken, Spell);

            // ASSERT 
            Assert.AreEqual(result, 1);
        }
    }
}