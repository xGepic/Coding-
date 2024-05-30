using System;
using System.Collections.Generic;
using Npgsql;

namespace MonsterTradingCardGame
{
    public partial class DBConnector
    {
        public void DecreaseCoinsofPlayer(string username)
        {
            Open();
            NpgsqlCommand myCommand = new("UPDATE player SET coins=coins-5 WHERE username = @name;", connection);
            myCommand.Parameters.AddWithValue("name", username);
            myCommand.ExecuteNonQuery();
            Close();
        }
        public void BuyACardPack(string username)
        {
            int index = 1;
            List<string> CardList = new();
            Open();
            NpgsqlCommand myCommand = new("SELECT * FROM card ORDER BY RANDOM() LIMIT 5;", connection);
            using NpgsqlDataReader reader = myCommand.ExecuteReader();
            if (reader != null)
            {
                Console.Clear();
                Console.WriteLine("You acquired the following cards:\n");
                while (reader.Read())
                {
                    if (reader.IsDBNull(4))
                    {
                        Console.WriteLine(index + ". Name: {0}, Damage: {1}, CardType: {2}, ElementType: {3}\n", reader.GetString(0), reader.GetInt32(1), (CardType)reader.GetInt32(2), (ElementType)reader.GetInt32(3));
                        CardList.Add(reader.GetString(0));
                        index++;
                    }
                    else
                    {
                        Console.WriteLine(index + ". Name: {0}, Damage: {1}, CardType: {2}, ElementType: {3}, MonsterType: {4}\n", reader.GetString(0), reader.GetInt32(1), (CardType)reader.GetInt32(2), (ElementType)reader.GetInt32(3), (MonsterType)reader.GetInt32(4));
                        CardList.Add(reader.GetString(0));
                        index++;
                    }
                }
                Console.WriteLine("\nAll new Cards have been added to your Stack!\n\n");
                Close();
                AddCardToStack(username, CardList);
            }
            Close();
        }
        public void AddCardToStack(string username, List<string> cardList)
        {
            List<string> tempList = new(cardList);
            foreach (var item in tempList)
            {
                if (CheckIfCardIsThere(item))
                {
                    cardList.Remove(item);
                }
            }
            Open();
            NpgsqlCommand searchCommand = new("SELECT cardname FROM stackcards WHERE username = @name AND cardname = @name2", connection);
            NpgsqlCommand insertCommand = new("INSERT INTO stackcards (username, cardname) VALUES (@username, @cardname);", connection);
            for (int i = 0; i < cardList.Count; i++)
            {
                searchCommand.Parameters.Clear();
                searchCommand.Parameters.AddWithValue("name", username);
                searchCommand.Parameters.AddWithValue("name2", cardList[i]);
                Object response = searchCommand.ExecuteScalar();
                if (response == null)
                {
                    insertCommand.Parameters.Clear();
                    insertCommand.Parameters.AddWithValue("username", username);
                    insertCommand.Parameters.AddWithValue("cardname", cardList[i]);
                    insertCommand.ExecuteNonQuery();
                }
            }
            Close();
        }
        public bool CheckIfCardIsThere(string cardname)
        {
            Open();
            NpgsqlCommand checkCmd = new("SELECT * FROM stackcards WHERE cardname = @card", connection);
            checkCmd.Parameters.AddWithValue("card", cardname);
            Object response = checkCmd.ExecuteScalar();
            if (response == null)
            {
                Close();
                return false;
            }
            Close();
            return true;
        }
        public int GetPlayerCoins(string username)
        {
            Open();
            NpgsqlCommand myCommand = new("SELECT coins FROM player WHERE username = @name;", connection);
            myCommand.Parameters.AddWithValue("name", username);
            Object coins = myCommand.ExecuteScalar();
            if (coins != null)
            {
                int playerCoins = Convert.ToInt32(coins);
                Close();
                return playerCoins;
            }
            Close();
            return 0;
        }
    }
}
