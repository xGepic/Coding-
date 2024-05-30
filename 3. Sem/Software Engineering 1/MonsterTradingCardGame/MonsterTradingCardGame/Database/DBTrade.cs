using System;
using System.Collections.Generic;
using Npgsql;

namespace MonsterTradingCardGame
{
    public partial class DBConnector
    {
        public List<string> GetTradeCards()
        {
            int index = 1;
            List<string> cardList = new();
            Open();
            NpgsqlCommand cmd = new("SELECT * FROM card ORDER BY RANDOM() LIMIT 4;", connection);
            using NpgsqlDataReader reader = cmd.ExecuteReader();
            if (reader != null)
            {
                Console.Clear();
                Console.WriteLine("Pick the Card you would like to have:\n");
                while (reader.Read())
                {
                    if (reader.IsDBNull(4))
                    {
                        Console.WriteLine(index + ". Name: {0}, Damage: {1}, CardType: {2}, ElementType: {3}\n", reader.GetString(0), reader.GetInt32(1), (CardType)reader.GetInt32(2), (ElementType)reader.GetInt32(3));
                        cardList.Add(reader.GetString(0));
                        index++;
                    }
                    else
                    {
                        Console.WriteLine(index + ". Name: {0}, Damage: {1}, CardType: {2}, ElementType: {3}, MonsterType: {4}\n", reader.GetString(0), reader.GetInt32(1), (CardType)reader.GetInt32(2), (ElementType)reader.GetInt32(3), (MonsterType)reader.GetInt32(4));
                        cardList.Add(reader.GetString(0));
                        index++;
                    }
                }
                Close();
                return cardList;
            }
            Close();
            return null;
        }
        public int CountPlayerStack(string username)
        {
            Open();
            NpgsqlCommand cmd = new("SELECT COUNT(*) FROM stackcards WHERE username = @name;", connection);
            cmd.Parameters.AddWithValue("name", username);
            int rows = Convert.ToInt32(cmd.ExecuteScalar());
            Close();
            return rows;
        }
        public void TradeCard(string username, List<string> cardlist, int cardToAdd, int cardToRemove)
        {
            Open();

            NpgsqlCommand checkCmd = new("SELECT * FROM stackcards WHERE cardname = @name", connection);
            checkCmd.Parameters.AddWithValue("name", cardlist[cardToAdd - 1]);
            Object checkResponse = checkCmd.ExecuteScalar();
            if (checkResponse != null)
            {
                Console.Clear();
                Console.WriteLine("You already have that Card!");
                Close();
                return;
            }

            NpgsqlCommand getCmd = new("SELECT cardname FROM stackcards WHERE username = @name LIMIT 1 OFFSET @offset;", connection);
            getCmd.Parameters.AddWithValue("name", username);
            getCmd.Parameters.AddWithValue("offset", cardToRemove - 1);
            string response = getCmd.ExecuteScalar().ToString();

            NpgsqlCommand removeCmd = new("DELETE FROM stackcards WHERE cardname = @name;", connection);
            removeCmd.Parameters.AddWithValue("name", response);
            removeCmd.ExecuteScalar();

            NpgsqlCommand addCmd = new("INSERT INTO stackcards (username, cardname) VALUES (@username, @cardname);", connection);
            addCmd.Parameters.AddWithValue("username", username);
            addCmd.Parameters.AddWithValue("cardname", cardlist[cardToAdd - 1]);
            addCmd.ExecuteNonQuery();

            Console.Clear();
            Console.WriteLine($"You traded away the {response} and received the {cardlist[cardToAdd - 1]}!");
            Close();
        }
        public void RemoveCardsForTrading(string username)
        {
            Open();
            NpgsqlCommand cmd = new("DELETE FROM deckcards WHERE username = @name", connection);
            cmd.Parameters.AddWithValue("name", username);
            cmd.ExecuteScalar();
            Close();
        }
        public bool IsStackEmpty(string username)
        {
            Open();
            NpgsqlCommand cmd = new("SELECT * FROM stackcards WHERE username = @name", connection);
            cmd.Parameters.AddWithValue("name", username);
            Object response = cmd.ExecuteScalar();
            if (response == null)
            {
                Close();
                return true;
            }
            Close();
            return false;
        }
    }
}
