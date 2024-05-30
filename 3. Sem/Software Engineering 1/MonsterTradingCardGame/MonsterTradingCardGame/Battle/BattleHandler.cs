using System;
using System.Collections.Generic;

namespace MonsterTradingCardGame
{
    class BattleHandler
    {
        private readonly User Player1;
        private readonly User Bot;
        private readonly List<ICard> BattleDeck1 = new();
        private readonly List<ICard> BattleDeck2 = new();
        private List<ICard> LoserDeck = new();
        private List<ICard> WinnerDeck = new();
        private const int player1Won = 1;
        private const int player2Won = 2;
        private const int maxRoundCounter = 100;
        private const int kValue = 30;
        private int roundCounter = 1;
        public BattleHandler(User User1, User User2)
        {
            Player1 = User1;
            Bot = User2;
        }
        public void StartBattle()
        {
            Random rand = new();
            int Player1DeckCount = Player1.MyDeck.CountCards();
            int Player2DeckCount = Bot.MyDeck.CountCards();
            for (int i = 0; i < Player1DeckCount; i++)
            {
                BattleDeck1.Add(Player1.MyDeck.GetCard(i));
            }
            LoserDeck = new List<ICard>(BattleDeck1);
            Player1.MyDeck.ClearCards();
            for (int i = 0; i < Player2DeckCount; i++)
            {
                BattleDeck2.Add(Bot.MyDeck.GetCard(i));
            }
            WinnerDeck = new List<ICard>(BattleDeck2);
            Bot.MyDeck.ClearCards();
            while (true)
            {
                if (BattleDeck1.Count == 0 || BattleDeck2.Count == 0)
                {
                    break;
                }
                Console.WriteLine($"          Round {roundCounter}");
                int p1Card = rand.Next(0, BattleDeck1.Count);
                int p2Card = rand.Next(0, BattleDeck2.Count);
                int whoWon = Battle.DamageCalc(BattleDeck1[p1Card], BattleDeck2[p2Card]);
                if (whoWon == player1Won)
                {
                    BattleDeck1.Add(BattleDeck2[p2Card]);
                    BattleDeck2.RemoveAt(p2Card);
                }
                if (whoWon == player2Won)
                {
                    BattleDeck2.Add(BattleDeck1[p1Card]);
                    BattleDeck1.RemoveAt(p1Card);
                }
                if (roundCounter == maxRoundCounter)
                {
                    Console.WriteLine("Round Limit exceeded!");
                    return;
                }
                roundCounter++;
            }
            if (BattleDeck1.Count == 0)
            {
                Console.WriteLine("Bot is the Winner!\n");
                DBConnector myDB = DBConnector.GetInstance();
                myDB.PlayerLostDeck(Player1.Username);
                myDB.PlayerLostStack(Player1.Username, LoserDeck);
                float probablilityPlayer1 = Probability(Bot.Elo, Player1.Elo);
                float probablilityPlayer2 = Probability(Player1.Elo, Bot.Elo);
                Player1.Elo += (int)Math.Round(kValue * (0 - probablilityPlayer1));
                Bot.Elo += (int)Math.Round(kValue * (1 - probablilityPlayer2));
                Console.WriteLine($"Your new Elo is : {Player1.Elo}");
                myDB.UpdatePlayerElo(Player1.Username, Player1.Elo);
            }
            if (BattleDeck2.Count == 0)
            {
                Console.WriteLine($"{Player1.Username} is the Winner!\n");
                DBConnector myDB = DBConnector.GetInstance();
                myDB.PlayerWinsCards(Player1.Username, WinnerDeck);
                float probablilityPlayer1 = Probability(Bot.Elo, Player1.Elo);
                float probablilityPlayer2 = Probability(Player1.Elo, Bot.Elo);
                Player1.Elo += (int)Math.Round(kValue * (1 - probablilityPlayer1));
                Bot.Elo += (int)Math.Round(kValue * (0 - probablilityPlayer2));
                Console.WriteLine($"Your new Elo is : {Player1.Elo}");
                myDB.UpdatePlayerElo(Player1.Username, Player1.Elo);
            }
        }
        public static float Probability(float rating1, float rating2)
        {
            //This returns the Winning Probability of rating2
            return 1.0f * 1.0f / (1 + 1.0f * (float)(Math.Pow(10, 1.0f * (rating1 - rating2) / 400)));
        }
    }
}