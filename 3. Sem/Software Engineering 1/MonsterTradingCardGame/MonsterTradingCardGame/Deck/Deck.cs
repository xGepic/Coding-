using System.Collections.Generic;
using System.Linq;

namespace MonsterTradingCardGame
{
    public class Deck
    {
        public Dictionary<string, ICard> MyCards;
        private const int maxCardCount = 5;
        public Deck()
        {
            MyCards = new Dictionary<string, ICard>();
        }
        public int AddCard(ICard Card)
        {
            if (MyCards.Count < maxCardCount)
            {
                MyCards.Add(Card.Name, Card);
                return 0;
            }
            else
            {
                return -1;
            }
        }
        public ICard GetCard(int id)
        {
            return MyCards.ElementAt(id).Value;
        }
        public int CountCards()
        {
            return MyCards.Count;
        }
        public void ClearCards()
        {
            MyCards.Clear();
        }
    }
}