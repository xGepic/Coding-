namespace MonsterTradingCardGame
{
    public interface ICard
    {
        string Name { get; set; }
        int Damage { get; set; }
        CardType MyCardtype { get; set; }
        public ElementType MyElementType { get; set; }
        public MonsterType MyMonsterType { get; set; }
    }
}
