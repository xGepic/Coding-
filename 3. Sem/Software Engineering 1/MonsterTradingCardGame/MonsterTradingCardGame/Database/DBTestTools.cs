using Npgsql;

namespace MonsterTradingCardGame
{
    public partial class DBConnector
    {
        public void RemoveUser(string username)
        {
            Open();
            NpgsqlCommand cmd = new("DELETE FROM player WHERE username = @name", connection);
            cmd.Parameters.AddWithValue("name", username);
            cmd.ExecuteScalar();
            Close();
        }
        public string GetPWHash(string username)
        {
            Open();
            NpgsqlCommand cmd = new("SELECT password FROM player WHERE username = @name", connection);
            cmd.Parameters.AddWithValue("name", username);
            string response = cmd.ExecuteScalar().ToString();
            Close();
            return response;
        }
        public void ClearStack(string username)
        {
            Open();
            NpgsqlCommand cmd = new("DELETE FROM stackcards WHERE username = @name", connection);
            cmd.Parameters.AddWithValue("name", username);
            cmd.ExecuteScalar();
            Close();
        }
        public void RemoveCardFromStack(string cardname)
        {
            Open();
            NpgsqlCommand cmd = new("DELETE FROM stackcards WHERE cardname = @name", connection);
            cmd.Parameters.AddWithValue("name", cardname);
            cmd.ExecuteScalar();
            Close();
        }
    }
}
