using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.Security.AccessControl;
using System.util;
using DBProject.Functions;

namespace DBProject.Main
{
    public partial class RubricLevel : Form
    {
        public string subQuery = "(SELECT Id FROM Rubric WHERE Details = @Rubric)";
        public RubricLevel()
        {
            InitializeComponent();
        }
        private void RubricLevel_Load(object sender, EventArgs e)
        {
            MainDL.LoadDataOnGridTable(dataGridView1, "RubricLevel");
            QueryDL.LoadComboBox(RubricIdComboBox, "Details", "Rubric");
            UtilDL.hideUD_Btns(addBtn, updateBtn, deleteBtn, udBtn);
        }
        private void Cell_Click(object sender, DataGridViewCellEventArgs e)
        {
            var row = dataGridView1.SelectedRows[0];
            RubricIdComboBox.Text = row.Cells[1].Value.ToString();
            textBox1.Text = row.Cells[2].Value.ToString();
            RubricLevelComboBox.Text = row.Cells[3].Value.ToString();
            UtilDL.showUD_Btns(addBtn, updateBtn, deleteBtn, udBtn);
        }
        private void Add_Data(object sender, EventArgs e)
        {
            if (MainDL.IsAnyBoxNull(this.panel1)) {
                MsgDL.TextBoxEmptyError();
                return;
            }
            string query = $"INSERT INTO RubricLevel VALUES ({subQuery}, @Details, @MeasurementLevel)";
            
            SqlCommand cmd = new SqlCommand(query, Program.connection);
            loadParameters(cmd);
            
            QueryDL.ExecuteCommand(cmd);

            MainDL.LoadDataOnGridTable(dataGridView1, "RubricLevel");
        }
        private void Update_Data(object sender, EventArgs e)
        {
            if (MainDL.IsAnyBoxNull(this.panel1))
            {
                MsgDL.TextBoxEmptyError();
                return;
            }
            int id = Convert.ToInt32(dataGridView1.SelectedRows[0].Cells[0].Value);
            string query = $"UPDATE RubricLevel SET RubricId = ({subQuery}, Details = @Details, MeasurementLevel = @MeasurementLevel WHERE Id = {id}";
            
            SqlCommand cmd = new SqlCommand(query, Program.connection);
            loadParameters(cmd);
            
            QueryDL.ExecuteCommand(cmd);

            MainDL.LoadDataOnGridTable(dataGridView1, "RubricLevel");
        }
        private void Delete_Data(object sender, EventArgs e)
        {
            if (MainDL.IsAnyBoxNull(this.panel1)) {
                MsgDL.TextBoxEmptyError();
                return;
            }            
            int id = Convert.ToInt32(dataGridView1.SelectedRows[0].Cells[0].Value);
            
            QueryDL.DeleteFromTable("RubricLevel", "Id", id);

            MainDL.LoadDataOnGridTable(dataGridView1, "RubricLevel");
        }
        private void loadParameters(SqlCommand cmd)
        {
            cmd.Parameters.AddWithValue("@Rubric", RubricIdComboBox.Text);
            cmd.Parameters.AddWithValue("@Details", textBox1.Text);
            cmd.Parameters.AddWithValue("@MeasurementLevel", getRubricLevelInteger());
        }
        private int getRubricLevelInteger()
        {
            int level = -1;
            string text = RubricLevelComboBox.Text;

            if (text == "Unsatisfactory")
                level = 1;
            else if (text == "Fair")
                level = 2;
            else if (text == "Good")
                level = 3;
            else if (text == "Exceptional")
                level = 4;

            return level;
        }

        private void udBtn_Click(object sender, EventArgs e)
        {
            UtilDL.hideUD_Btns(addBtn, updateBtn, deleteBtn, udBtn);
        }
    }
}
