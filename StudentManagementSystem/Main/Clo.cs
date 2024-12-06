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
using System.Net;
using DBProject.Functions;

namespace DBProject
{
    public partial class Clo : Form
    {
        public Clo()
        {
            InitializeComponent();
            MainDL.LoadDataOnGridTable(dataGridView1, "CLO");
        }
        
        private void Clos_Load(object sender, EventArgs e)
        {
            UtilDL.hideUD_Btns(addBtn, updateBtn, deleteBtn, udBtn);
        }

        private void dataGridView1_CellContentClick_1(object sender, DataGridViewCellEventArgs e)
        {
            var row = dataGridView1.SelectedRows[0];
            textBox1.Text = row.Cells[1].Value.ToString();
            UtilDL.showUD_Btns(addBtn, updateBtn, deleteBtn, udBtn);
        }
        private void Add_Data(object sender, EventArgs e)
        {
            if (MainDL.IsAnyBoxNull(this.panel1))
            {
                MsgDL.TextBoxEmptyError();
                return;
            }            
            string query = "INSERT INTO CLO VALUES (@Name, @DateCreated, @DateCreated)";   

            SqlCommand command = new SqlCommand(query, Program.connection);
            command.Parameters.AddWithValue("@Name", textBox1.Text);
            command.Parameters.AddWithValue("@DateCreated", DateTime.Now);

            QueryDL.ExecuteCommand(command);

            MainDL.LoadDataOnGridTable(dataGridView1, "CLO");
        }
        private void Update_Data(object sender, EventArgs e)
        {
            if (MainDL.IsAnyBoxNull(this.panel1))
            {
                MsgDL.TextBoxEmptyError();
                return;
            }

            string query = "UPDATE CLO SET Name = @NewName, DateUpdated = @NewTime WHERE Id = @Id";
            int id = MainDL.GetIdFromGridTable(dataGridView1);

            SqlCommand command = new SqlCommand(query, Program.connection);
            command.Parameters.AddWithValue("@Id", id);
            command.Parameters.AddWithValue("@NewName", textBox1.Text);
            command.Parameters.AddWithValue("@NewTime", DateTime.Now);

            QueryDL.ExecuteCommand(command);

            MainDL.LoadDataOnGridTable(dataGridView1, "CLO");
        }

        private void Delete_Data(object sender, EventArgs e)
        {
            if (MainDL.IsAnyBoxNull(this.panel1))
            {
                MsgDL.TextBoxEmptyError();
                return;
            }
            int id = MainDL.GetIdFromGridTable(dataGridView1);
            
            QueryDL.DeleteFromTable("CLO", "Id", id);
            
            MainDL.LoadDataOnGridTable(dataGridView1, "CLO");
        }
        private void UD_Btn_Click(object sender, EventArgs e)
        {
            UtilDL.hideUD_Btns(addBtn, updateBtn, deleteBtn, udBtn);
        }
    }
}
