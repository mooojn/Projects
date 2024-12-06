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
    public partial class Student : Form
    {
        public Student()
        {
            InitializeComponent();
        }
        private void Students_Load(object sender, EventArgs e)
        {
            MainDL.LoadDataOnGridTable(dataGridView1, "Student");
            UtilDL.hideUD_Btns(addBtn, updateBtn, deleteBtn, udBtn);
        }
        private void Data_Table_Click(object sender, DataGridViewCellEventArgs e)
        {
            // data type 
            var row = dataGridView1.SelectedRows[0];
            
            stdFirstNameBox.Text = row.Cells[1].Value.ToString();
            stdLastNameBox.Text = row.Cells[2].Value.ToString();
            stdContactBox.Text = row.Cells[3].Value.ToString();
            stdEmailBox.Text = row.Cells[4].Value.ToString();    
            stdRegNoBox.Text = row.Cells[5].Value.ToString();

            UtilDL.showUD_Btns(addBtn, updateBtn, deleteBtn, udBtn);
        }
        private void Add_Student(object sender, EventArgs e)
        {
            if (MainDL.IsAnyBoxNull(this.addStudentPanel))
            {
                MsgDL.TextBoxEmptyError();
                return;
            }
            string query = "INSERT INTO Student VALUES (@F_Name, @L_Name, @Contact, @Email, @RegNo, @Status)";
            
            SqlCommand command = new SqlCommand(query, Program.connection);
            loadParameters(command);

            QueryDL.ExecuteCommand(command);

            MainDL.LoadDataOnGridTable(dataGridView1, "Student");
        }
        private void Update_Student(object sender, EventArgs e)
        {
            if (MainDL.IsAnyBoxNull(this.addStudentPanel))
            {
                MsgDL.TextBoxEmptyError();
                return;
            }
            int id = MainDL.GetIdFromGridTable(dataGridView1);
            string query = "UPDATE Student SET FirstName = @F_Name, LastName = @L_Name, Contact = @Contact, Email = @Email, RegistrationNumber = @RegNo, Status = @Status WHERE Id = @id";
            
            SqlCommand command = new SqlCommand(query, Program.connection);    
            command.Parameters.AddWithValue("@id", id);
            loadParameters(command);  // gets all the other parameters
            
            QueryDL.ExecuteCommand(command);

            MainDL.LoadDataOnGridTable(dataGridView1, "Student");
        }
        private void Delete_Student(object sender, EventArgs e)
        {
            if (MainDL.IsAnyBoxNull(this.addStudentPanel))
            {
                MsgDL.TextBoxEmptyError();
                return;
            }
            int id = MainDL.GetIdFromGridTable(dataGridView1);

            QueryDL.DeleteFromTable("StudentAttendance", "StudentId" ,id);
            QueryDL.DeleteFromTable("Student", "Id" ,id);

            MainDL.LoadDataOnGridTable(dataGridView1, "Student");
        }
        private void loadParameters(SqlCommand cmd)
        {
            cmd.Parameters.AddWithValue("@F_Name", stdFirstNameBox.Text);
            cmd.Parameters.AddWithValue("@L_Name", stdLastNameBox.Text);
            cmd.Parameters.AddWithValue("@Contact", stdContactBox.Text);
            cmd.Parameters.AddWithValue("@Email", stdEmailBox.Text);
            cmd.Parameters.AddWithValue("@RegNo", stdRegNoBox.Text);
            cmd.Parameters.AddWithValue("@Status", status.Checked ? 5 : 6);
        }
        private void hideUdBtn_Click(object sender, EventArgs e)
        {
            UtilDL.hideUD_Btns(addBtn, updateBtn, deleteBtn, udBtn);
        }
        private void Mark_Attendance(object sender, EventArgs e)
        {
            Form form = new Attendance();
            form.StartPosition = FormStartPosition.CenterScreen;
            form.Show();
        }
        private void addStudentPanel_Paint(object sender, PaintEventArgs e)
        {
            
        }

        private void status_CheckedChanged(object sender, EventArgs e)
        {
            
        }
    }
}
