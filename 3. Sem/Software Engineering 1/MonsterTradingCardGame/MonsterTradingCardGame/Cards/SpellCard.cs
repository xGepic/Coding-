namespace MonsterTradingCardGame
{
    public class SpellCard : ICard
    {
        public string Name { get; set; }
        public int Damage { get; set; }
        public CardType MyCardtype { get; set; }
        public ElementType MyElementType { get; set; }
        public MonsterType MyMonsterType { get; set; } //Unused
        public SpellCard(string name, int dmg, ElementType eType)
        {
            Name = name;
            Damage = dmg;
            MyElementType = eType;
            MyCardtype = CardType.Spell;
        }
    }
}
