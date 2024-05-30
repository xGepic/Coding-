using System;
using System.Security.Cryptography;
using Microsoft.AspNetCore.Cryptography.KeyDerivation;
using Npgsql;

namespace MonsterTradingCardGame
{
    public partial class DBConnector
    {
        public void UpdatePassword(string username, string password)
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
            NpgsqlCommand insertCmd = new("UPDATE player SET password = @pw, salt = @salt WHERE username = @name", connection);
            insertCmd.Parameters.AddWithValue("pw", hashed);
            insertCmd.Parameters.AddWithValue("salt", mySalt);
            insertCmd.Parameters.AddWithValue("name", username);
            insertCmd.ExecuteNonQuery();
            Close();
        }
    }
}
