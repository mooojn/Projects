using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DBProject
{
    internal class QueryDL
    {
        public static void ExecuteCommand(SqlCommand cmd)
        {
            Program.connection.Open();
            try {
                cmd.ExecuteNonQuery();
            }
            catch (Exception err)
            {
                MessageBox.Show("One of the attribute exists as a Foreign Key in another Table\nCan't Delete");
            }
            Program.connection.Close();
        }
        public static void DeleteFromTable(string table, string columnName, int idToDelete)
        {
            Program.connection.Open();
            string query = $"DELETE FROM {table} WHERE {columnName} = {idToDelete}";

            SqlCommand cmd = new SqlCommand(query, Program.connection);
            
            Program.connection.Close();
            
            ExecuteCommand(cmd);
        }
        public static int GetIdFromTable(string valueToGet, string table, string columnName, string value)
        {
            int id = -1;
            Program.connection.Open();

            string query = $"SELECT {valueToGet} FROM {table} WHERE {columnName} = '{value}'";

            var cmdForId = new SqlCommand(query, Program.connection);
            var reader = cmdForId.ExecuteReader();

            while (reader.Read())
            {
                id = reader.GetInt32(0);
            }
            Program.connection.Close();
            return id;

        }
        public static void LoadComboBox(ComboBox box, string field, string table, string subQuery = "")
        {
            box.Items.Clear();
            Program.connection.Open();
            string query = $"SELECT {field} FROM {table} {subQuery}";    // subQuery is optional
            SqlCommand command = new SqlCommand(query, Program.connection);
            SqlDataReader data = command.ExecuteReader();
            while (data.Read())
            {
                box.Items.Add(data[0]);
            }
            Program.connection.Close();
        }
        public static float GetFloatField(string query)
        {
            Program.connection.Open();

            SqlCommand command = new SqlCommand(query, Program.connection);
            float field = Convert.ToInt32(command.ExecuteScalar());

            Program.connection.Close();
            return field;
        }
    }
}
