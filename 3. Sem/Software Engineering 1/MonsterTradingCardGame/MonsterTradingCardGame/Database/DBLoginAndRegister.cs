using System;
using System.Security.Cryptography;
using Microsoft.AspNetCore.Cryptography.KeyDerivation;
using Npgsql;

namespace MonsterTradingCardGame
{
    public partial class DBConnector
    {
        public bool RegisterUser(string username, string password, int eloPoints, int coins)
        {
            Open();
            RNGCryptoServiceProvider provider = new();
            byte[] mySalt = new byte[128 / 8];
            provider.GetBytes(mySalt);
            string hashed = Convert.ToBase64String(KeyDerivation.Pbkdf2(
              password: password,
              salt: mySalt,
              prf: KeyDerivationPrf.HMACSHA256,
              iterationCount: 100000,
              numBytesRequested: 256 / 8));
            NpgsqlCommand command2 = new("SELECT username FROM player WHERE username = @name", connection);
            command2.Parameters.AddWithValue("name", username);
            Object response2 = command2.ExecuteScalar();
            if (response2 == null)
            {
                NpgsqlCommand insertCommand = new("INSERT INTO player (username, password, elo, coins, salt) VALUES (@name, @password, @elo, @coins, @salt);", connection);
                insertCommand.Parameters.AddWithValue("name", username);
                insertCommand.Parameters.AddWithValue("password", hashed);
                insertCommand.Parameters.AddWithValue("elo", eloPoints);
                insertCommand.Parameters.AddWithValue("coins", coins);
                insertCommand.Parameters.AddWithValue("salt", mySalt);
                insertCommand.ExecuteReader();
                Close();
                return true;
            }
            Close();
            return false;
        }
        public bool LogInUser(string username, string password)
        {
            Open();
            NpgsqlCommand saltCommand = new("SELECT salt FROM player WHERE username = @name;", connection);
            saltCommand.Parameters.AddWithValue("name", username);
            Object salt = saltCommand.ExecuteScalar();
            if (salt != null)
            {
                NpgsqlCommand passwordCommand = new("SELECT password FROM player WHERE username = @name;", connection);
                passwordCommand.Parameters.AddWithValue("name", username);
                string passwordInDB = (string)passwordCommand.ExecuteScalar();
                string hashed = Convert.ToBase64String(KeyDerivation.Pbkdf2(
                    password: password,
                    salt: (byte[])salt,
                    prf: KeyDerivationPrf.HMACSHA256,
                    iterationCount: 100000,
                    numBytesRequested: 256 / 8));
                if (hashed == passwordInDB)
                {
                    Close();
                    return true;
                }
            }
            Close();
            return false;
        }
    }
}
