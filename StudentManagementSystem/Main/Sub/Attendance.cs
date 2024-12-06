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
using System.Text.RegularExpressions;

namespace DBProject
{
    public partial class Attendance : Form
    {
        public Attendance()
        {
            InitializeComponent();
        }

        private void Attendance_Load(object sender, EventArgs e)
        {
            QueryDL.LoadComboBox(RegNoComboBox, "RegistrationNumber", "Student");
            QueryDL.LoadComboBox(StatusComboBox, "TOP 4 Name", "Lookup");
        }
        private void insertIntoclassAttendance()
        {
            if (MainDL.IsAnyBoxNull(this.panel1))
            {
                MsgDL.TextBoxEmptyError();
                return;
            }
            string query = "INSERT INTO ClassAttendance VALUES (@Date)";

            SqlCommand command = new SqlCommand(query, Program.connection);
            command.Parameters.AddWithValue("@Date", datePicker.Value);
            
            QueryDL.ExecuteCommand(command);
        }

        private void Save_Attendance(object sender, EventArgs e)
        {
            if (MainDL.IsAnyBoxNull(this.panel1))
            {
                MsgDL.TextBoxEmptyError();
                return;
            }
            insertIntoclassAttendance();
            // getting the ids
            int attendanceId = QueryDL.GetIdFromTable("MAX(Id)", "ClassAttendance", "1", "1");   // 1, 1 is extra to make the function work
            int stdId = QueryDL.GetIdFromTable("Id", "Student", "RegistrationNumber", RegNoComboBox.Text);
            int status = QueryDL.GetIdFromTable("Lookupid", "Lookup", "Name", StatusComboBox.Text);

            string query = $"INSERT INTO StudentAttendance VALUES ({attendanceId}, {stdId}, {status})";
            SqlCommand command = new SqlCommand(query, Program.connection);
            
            QueryDL.ExecuteCommand(command);

            MessageBox.Show("Attendance Marked", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }
    }
}
