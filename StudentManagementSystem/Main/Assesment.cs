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
    public partial class Assesment : Form
    {
        public Assesment()
        {
            InitializeComponent();
        }

        private void Assesment_Load(object sender, EventArgs e)
        {
            MainDL.LoadDataOnGridTable(dataGridView1, "Assessment");
            UtilDL.hideUD_Btns(addBtn, updateBtn, deleteBtn, udBtn);
        }
        private void Cell_Click(object sender, DataGridViewCellEventArgs e)
        {
            var row = dataGridView1.SelectedRows[0];
            textBox1.Text = row.Cells[1].Value.ToString();
            textBox2.Text = row.Cells[3].Value.ToString();
            textBox3.Text = row.Cells[4].Value.ToString();
            UtilDL.showUD_Btns(addBtn, updateBtn, deleteBtn, udBtn);
        }
        private void Add_Data(object sender, EventArgs e)
        {
            if (MainDL.IsAnyBoxNull(this.panel1)) {
                MsgDL.TextBoxEmptyError();
                return;
            }
            string query = "INSERT INTO Assessment values (@Title, @DateCreated, @TotalMarks, @TotalWeightage)";
            
            SqlCommand command = new SqlCommand(query, Program.connection);
            command.Parameters.AddWithValue("@DateCreated", DateTime.Now);
            loadParameters(command);
            
            QueryDL.ExecuteCommand(command);
            
            MainDL.LoadDataOnGridTable(dataGridView1, "Assessment");
        }

        private void Update_Data(object sender, EventArgs e)
        {
            if (MainDL.IsAnyBoxNull(this.panel1)) {
                MsgDL.TextBoxEmptyError();
                return;
            }
            int id = Convert.ToInt32(dataGridView1.SelectedRows[0].Cells[0].Value);   
            string query = $"UPDATE Assessment SET Title = @Title, TotalMarks = @TotalMarks, TotalWeightage = @TotalWeightage WHERE Id = {id}";
            
            SqlCommand command = new SqlCommand(query, Program.connection);
            loadParameters(command);

            QueryDL.ExecuteCommand(command);

            MainDL.LoadDataOnGridTable(dataGridView1, "Assessment");
        }
        private void Delete_Data(object sender, EventArgs e)
        {
            if (MainDL.IsAnyBoxNull(this.panel1))
            {
                MsgDL.TextBoxEmptyError();
                return;
            }
            int id = Convert.ToInt32(dataGridView1.SelectedRows[0].Cells[0].Value);
            
            QueryDL.DeleteFromTable("Assessment", "Id", id);

            MainDL.LoadDataOnGridTable(dataGridView1, "Assessment");
        }

        private void Open_Componenet_Form(object sender, EventArgs e)
        {
            AssesmentComponent form = new AssesmentComponent();
            form.StartPosition = FormStartPosition.CenterScreen;
            form.Show();
        }
        private void loadParameters(SqlCommand cmd)
        {
            cmd.Parameters.AddWithValue("@Title", textBox1.Text);
            cmd.Parameters.AddWithValue("@TotalMarks", textBox2.Text);
            cmd.Parameters.AddWithValue("@TotalWeightage", textBox3.Text);
        }
        private void udBtn_Click(object sender, EventArgs e)
        {
            UtilDL.hideUD_Btns(addBtn, updateBtn, deleteBtn, udBtn);
        }
    }
}
