using System;
using System.Collections.Generic;
using Npgsql;

namespace MonsterTradingCardGame
{
    public partial class DBConnector
    {
        public void PrintPlayerDeck(string username)
        {
            int index = 1;
            Open();
            NpgsqlCommand cmd = new("SELECT * FROM deckcards WHERE username = @name", connection);
            cmd.Parameters.AddWithValue("name", username);
            Object response = cmd.ExecuteScalar();
            if (response == null)
            {
                Console.Clear();
                Console.WriteLine("You have no Cards!\n");
                Close();
                Tools.PressAnyKey();
            }
            else
            {
                using NpgsqlDataReader reader = cmd.ExecuteReader();
                if (reader != null)
                {
                    Console.Clear();
                    Console.WriteLine("You will enter the Arena with the following Cards:\n");
                    while (reader.Read())
                    {
                        Console.WriteLine(index + ". " + reader.GetString(1) + "\n");
                        index++;
                    }
                    Close();
                }
            }
        }
        public Deck GetPlayerDeck(string username)
        {
            Open();
            List<string> tempList = new();
            Deck myDeck = new();
            NpgsqlCommand seachCmd = new("SELECT * FROM deckcards WHERE username = @name", connection);
            seachCmd.Parameters.AddWithValue("name", username);
            using NpgsqlDataReader reader = seachCmd.ExecuteReader();
            if (reader != null)
            {
                while (reader.Read())
                {
                    string temp = reader.GetString(1);
                    tempList.Add(temp);
                }
            }
            Close();
            Open();
            NpgsqlCommand getCardCmd = new("SELECT * FROM card WHERE name = @cardname", connection);
            for (int i = 0; i < tempList.Count; i++)
            {
                getCardCmd.Parameters.Clear();
                getCardCmd.Parameters.AddWithValue("cardname", tempList[i]);
                using NpgsqlDataReader reader2 = getCardCmd.ExecuteReader();
                if (reader2 != null)
                {
                    while (reader2.Read())
                    {
                        if (reader2.IsDBNull(4))
                        {
                            myDeck.AddCard(new SpellCard(reader2.GetString(0), reader2.GetInt32(1), (ElementType)reader2.GetInt32(3)));
                        }
                        else
                        {
                            myDeck.AddCard(new MonsterCard(reader2.GetString(0), reader2.GetInt32(1), (ElementType)reader2.GetInt32(3), (MonsterType)reader2.GetInt32(4)));
                        }
                    }
                }
            }
            Close();
            return myDeck;
        }
        public Deck GetBotDeck()
        {
            Deck myDeck = new();
            Open();
            NpgsqlCommand cmd = new("SELECT * FROM card ORDER BY RANDOM() LIMIT 4;", connection);
            using NpgsqlDataReader reader = cmd.ExecuteReader();
            if (reader != null)
            {
                while (reader.Read())
                {
                    if (reader.IsDBNull(4))
                    {
                        myDeck.AddCard(new SpellCard(reader.GetString(0), reader.GetInt32(1), (ElementType)reader.GetInt32(3)));
                    }
                    else
                    {
                        myDeck.AddCard(new MonsterCard(reader.GetString(0), reader.GetInt32(1), (ElementType)reader.GetInt32(3), (MonsterType)reader.GetInt32(4)));
                    }
                }
            }
            Close();
            return myDeck;
        }
        public void PlayerLostStack(string username, List<ICard> cardList)
        {
            Open();
            NpgsqlCommand deleteCmd = new("DELETE FROM stackcards WHERE cardname = @card AND username = @name", connection);
            for (int i = 0; i < cardList.Count; i++)
            {
                deleteCmd.Parameters.Clear();
                deleteCmd.Parameters.AddWithValue("name", username);
                deleteCmd.Parameters.AddWithValue("card", cardList[i].Name);
                deleteCmd.ExecuteScalar();
            }
            Close();
        }
        public void PlayerLostDeck(string username)
        {
            Open();
            NpgsqlCommand cmd = new("DELETE FROM deckcards WHERE username = @name", connection);
            cmd.Parameters.AddWithValue("name", username);
            cmd.ExecuteScalar();
            Close();
        }
        public void UpdatePlayerElo(string username, int elo)
        {
            Open();
            NpgsqlCommand cmd = new("UPDATE player SET elo = @points WHERE username = @name", connection);
            cmd.Parameters.AddWithValue("points", elo);
            cmd.Parameters.AddWithValue("name", username);
            cmd.ExecuteNonQuery();
            Close();
        }
        public void PlayerWinsCards(string username, List<ICard> cardList)
        {
            Open();
            NpgsqlCommand cmd = new("INSERT INTO stackcards (username, cardname) SELECT * FROM (SELECT @name AS username, @card AS cardname) AS temp WHERE NOT EXISTS (SELECT cardname FROM stackcards WHERE cardname = @card2);", connection);
            for (int i = 0; i < cardList.Count; i++)
            {
                cmd.Parameters.Clear();
                cmd.Parameters.AddWithValue("name", username);
                cmd.Parameters.AddWithValue("card", cardList[i].Name);
                cmd.Parameters.AddWithValue("card2", cardList[i].Name);
                cmd.ExecuteNonQuery();
            }
            Close();
        }
        public int GetPlayerElo(string username)
        {
            Open();
            NpgsqlCommand cmd = new("SELECT elo FROM player WHERE username = @name", connection);
            cmd.Parameters.AddWithValue("name", username);
            Object elo = cmd.ExecuteScalar();
            if (elo != null)
            {
                int playerElo = Convert.ToInt32(elo);
                Close();
                return playerElo;
            }
            Close();
            return 0;
        }
    }
}
