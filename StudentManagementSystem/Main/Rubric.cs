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
using DBProject.Functions;

namespace DBProject
{
    public partial class Rubric : Form
    {
        public Rubric()
        {
            InitializeComponent();
        }
        private void Rubric_Load(object sender, EventArgs e)
        {
            MainDL.LoadDataOnGridTable(dataGridView1, "Rubric");
            QueryDL.LoadComboBox(Clo_IDComboBox, "Name", "Clo");
            UtilDL.hideUD_Btns(addBtn, updateBtn, deleteBtn, udBtn);
        }
        private void Cell_Click(object sender, DataGridViewCellEventArgs e)
        {
            DataGridViewRow row = dataGridView1.SelectedRows[0];
            textBox1.Text = row.Cells[1].Value.ToString();
            Clo_IDComboBox.Text = row.Cells[2].Value.ToString();
            UtilDL.showUD_Btns(addBtn, updateBtn, deleteBtn, udBtn);
        }
        private void Add_Data(object sender, EventArgs e)
        {
            if (MainDL.IsAnyBoxNull(this.panel1))
            {
                MsgDL.TextBoxEmptyError();
                return;
            }
            string query = "INSERT INTO Rubric values (@Details, (SELECT Id FROM Clo WHERE Name = @CloId))";
            
            SqlCommand command = new SqlCommand(query, Program.connection);
            loadParameters(command);

            QueryDL.ExecuteCommand(command);

            MainDL.LoadDataOnGridTable(dataGridView1, "Rubric");
        }
        private void Update_Data(object sender, EventArgs e)
        {
            if (MainDL.IsAnyBoxNull(this.panel1))
            {
                MsgDL.TextBoxEmptyError();
                return;
            }
            int id = Convert.ToInt32(dataGridView1.SelectedRows[0].Cells[0].Value);
            string query = $"UPDATE Rubric SET Details = @Details, CloId = @CloId WHERE Id = {id}";
            
            SqlCommand command = new SqlCommand(query, Program.connection);
            loadParameters(command);

            QueryDL.ExecuteCommand(command);

            MainDL.LoadDataOnGridTable(dataGridView1, "Rubric");
        }

        private void Delete_Data(object sender, EventArgs e)
        {
            if (MainDL.IsAnyBoxNull(this.panel1))
            {
                MsgDL.TextBoxEmptyError();
                return;
            }
            int id = Convert.ToInt32(dataGridView1.SelectedRows[0].Cells[0].Value);
            
            QueryDL.DeleteFromTable("Rubric", "Id", id);
            
            MainDL.LoadDataOnGridTable(dataGridView1, "Rubric");
        }
        private void loadParameters(SqlCommand cmd)
        {
            cmd.Parameters.AddWithValue("@Details", textBox1.Text);
            cmd.Parameters.AddWithValue("@CloId", Clo_IDComboBox.Text);
        }
        private void udBtn_Click(object sender, EventArgs e)
        {
            UtilDL.hideUD_Btns(addBtn, updateBtn, deleteBtn, udBtn);
        }
        
    }
}
