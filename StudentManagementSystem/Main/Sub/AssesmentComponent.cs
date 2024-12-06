using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.Runtime.InteropServices;
using DBProject.Functions;

namespace DBProject
{
    public partial class AssesmentComponent : Form
    {
        public AssesmentComponent()
        {
            InitializeComponent();
        }

        private void AssesmentComponent_Load(object sender, EventArgs e)
        {
            MainDL.LoadDataOnGridTable(dataGridView1, "AssessmentComponent");
            UtilDL.hideUD_Btns(addBtn, updateBtn, deleteBtn, udBtn);

            QueryDL.LoadComboBox(AssessmentNameComboBox, "Title", "Assessment");
            QueryDL.LoadComboBox(RubricNameComboBox, "Details", "Rubric");
        }
        private void Cell_Click(object sender, DataGridViewCellEventArgs e)
        {
            var rows = dataGridView1.SelectedRows[0];
            textBox1.Text = rows.Cells[1].Value.ToString();
            textBox2.Text = rows.Cells[3].Value.ToString();
            UtilDL.showUD_Btns(addBtn, updateBtn, deleteBtn, udBtn);
        }
        private void Add_Data(object sender, EventArgs e)
        {
            if (MainDL.IsAnyBoxNull(this.panel1)) {
                MsgDL.TextBoxEmptyError();
                return;
            }
            int assessmentId = QueryDL.GetIdFromTable("Id", "Assessment", "Title", AssessmentNameComboBox.Text);
            int rubricId = QueryDL.GetIdFromTable("Id", "Rubric", "Details", RubricNameComboBox.Text);
            string query = $"INSERT INTO AssessmentComponent VALUES (@Name, {rubricId}, @TotalMarks, @DateCreated, @DateUpdated, {assessmentId})";
            
            SqlCommand command = new SqlCommand(query, Program.connection);
            command.Parameters.AddWithValue("@DateCreated", DateTime.Now);
            loadParameters(command);
            
            QueryDL.ExecuteCommand(command);
            
            MainDL.LoadDataOnGridTable(dataGridView1, "AssessmentComponent");
        }
        private void Update_Data(object sender, EventArgs e)
        {
            if (MainDL.IsAnyBoxNull(this.panel1)) {
                MsgDL.TextBoxEmptyError();
                return;
            }
            int id = Convert.ToInt32(dataGridView1.SelectedRows[0].Cells[0].Value);
            int assessmentId = QueryDL.GetIdFromTable("Id", "Assessment", "Title", AssessmentNameComboBox.Text);
            int rubricId = QueryDL.GetIdFromTable("Id", "Rubric", "Details", RubricNameComboBox.Text);
            string query = $"UPDATE AssessmentComponent SET Name = @Name, RubricId = {rubricId}, TotalMarks = @TotalMarks, DateUpdated = @DateUpdated, AssessmentId = {assessmentId} WHERE Id = {id}";

            SqlCommand command = new SqlCommand(query, Program.connection);
            loadParameters(command);
            
            QueryDL.ExecuteCommand(command);

            MainDL.LoadDataOnGridTable(dataGridView1, "AssessmentComponent");
        }
        private void Delete_Data(object sender, EventArgs e)
        {
            if (MainDL.IsAnyBoxNull(this.panel1))
            {
                MsgDL.TextBoxEmptyError();
                return;
            }
            int id = Convert.ToInt32(dataGridView1.SelectedRows[0].Cells[0].Value);

            QueryDL.DeleteFromTable("AssessmentComponent", "Id", id);

            MainDL.LoadDataOnGridTable(dataGridView1, "AssessmentComponent");
        }
        private void loadParameters(SqlCommand command)
        {
            command.Parameters.AddWithValue("@Name", textBox1.Text);
            command.Parameters.AddWithValue("@TotalMarks", textBox2.Text);
            command.Parameters.AddWithValue("@DateUpdated", DateTime.Now);
        }
        private void udBtn_Click(object sender, EventArgs e)
        {
            UtilDL.hideUD_Btns(addBtn, updateBtn, deleteBtn, udBtn);
        }
    }
}
