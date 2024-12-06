using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SqlClient;
using System.Data;
using System.Windows.Forms;

namespace DBProject
{
    internal class MainDL
    {
        public static void LoadDataOnGridTable(DataGridView dataGridView, string table)
        {
            Program.connection.Open();

            string query = $"SELECT * FROM {table}";
            SqlDataAdapter sda = new SqlDataAdapter(query, Program.connection);
            DataTable dt = new DataTable();
            sda.Fill(dt);
            dataGridView.DataSource = dt;

            Program.connection.Close();
        }
        public static int GetIdFromGridTable(DataGridView dataGrid)
        {
            // as id is always the first column
            return Convert.ToInt32(dataGrid.SelectedRows[0].Cells[0].Value);
        }
        public static bool IsAnyBoxNull(Control container)
        {
            foreach (Control control in container.Controls) {
                if (control is TextBox textBox && string.IsNullOrEmpty(textBox.Text)) {
                    return true;
                }
                else if (control is ComboBox comboBox && string.IsNullOrEmpty(comboBox.Text)) {
                    return true;
                }
            }
            return false;
        }
    }
}
