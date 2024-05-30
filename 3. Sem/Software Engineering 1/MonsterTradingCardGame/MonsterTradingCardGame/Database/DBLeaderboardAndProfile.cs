using System;
using Npgsql;

namespace MonsterTradingCardGame
{
    public partial class DBConnector
    {
        public bool GetLeaderboard()
        {
            int index = 1;
            Open();
            NpgsqlCommand myCommand = new("SELECT * FROM player ORDER BY elo DESC", connection);
            using NpgsqlDataReader reader = myCommand.ExecuteReader();
            if (reader != null)
            {
                while (reader.Read())
                {
                    Console.WriteLine(index + ". Name: {0} ELO: {1}\n", reader.GetString(0).PadRight(10, ' '), reader.GetInt32(2).ToString().PadRight(10, ' '));
                    index++;
                }
                Close();
                return true;
            }
            Close();
            return false;
        }
        public bool GetProfile(string username)
        {
            Open();
            NpgsqlCommand myCommand = new("SELECT * FROM player WHERE username = @name;", connection);
            myCommand.Parameters.AddWithValue("name", username);
            using NpgsqlDataReader reader = myCommand.ExecuteReader();
            if (reader != null)
            {
                reader.Read();
                Console.WriteLine("Name: {0}\nELO: {1}\nCoins: {2}", reader.GetString(0), reader.GetInt32(2), reader.GetInt32(3));
                Close();
                return true;
            }
            Close();
            return false;
        }
    }
}