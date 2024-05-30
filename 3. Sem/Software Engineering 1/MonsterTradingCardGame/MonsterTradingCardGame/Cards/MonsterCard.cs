namespace MonsterTradingCardGame
{
    public class MonsterCard : ICard
    {
        public string Name { get; set; }
        public int Damage { get; set; }
        public CardType MyCardtype { get; set; }
        public ElementType MyElementType { get;set;}
        public MonsterType MyMonsterType { get; set; }
        public MonsterCard(string name, int dmg, ElementType eType, MonsterType mType)
        {
            Name = name;
            Damage = dmg;
            MyElementType = eType;
            MyMonsterType = mType;
            MyCardtype = CardType.Monster;
        }
    }
}