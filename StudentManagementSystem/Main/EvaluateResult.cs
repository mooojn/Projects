﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.ListView;
using System.Security.Cryptography;

namespace DBProject
{
    public partial class EvaluateResult : Form
    {
        public EvaluateResult()
        {
            InitializeComponent();
        }
        private void EvaluateResult_Load(object sender, EventArgs e)
        {
            createCol();
            loadData();
            QueryDL.LoadComboBox(StudentComboBox, "FirstName", "Student");
            QueryDL.LoadComboBox(AssessmentComboBox, "Title", "Assessment");
        }
        private void Add_Data(object sender, EventArgs e)
        {
            if (MainDL.IsAnyBoxNull(this.panel1))
            {
                MsgDL.TextBoxEmptyError();
                return;
            }
            int stdId = QueryDL.GetIdFromTable("Id", "Student", "FirstName", StudentComboBox.Text);
            int assessmentId = QueryDL.GetIdFromTable("Id", "AssessmentComponent", "Name", ComponentComboBox.Text);
            int rubricId = QueryDL.GetIdFromTable("Id", "RubricLevel", "MeasurementLevel", RubricLevelComboBox.Text);
            string query = "INSERT INTO StudentResult VALUES (@StudentId, @AssessmentComponentId, @RubricMeasurementId, @EvaluationDate)";
            
            SqlCommand command = new SqlCommand(query, Program.connection);
            command.Parameters.AddWithValue("@StudentId", stdId);
            command.Parameters.AddWithValue("@AssessmentComponentId", assessmentId);
            command.Parameters.AddWithValue("@RubricMeasurementId", rubricId);
            command.Parameters.AddWithValue("@EvaluationDate", dateTimePicker1.Value);

            QueryDL.ExecuteCommand(command);

            loadData();
        }
        private void loadData()
        {
            dataGridView1.Rows.Clear();

            Program.connection.Open();
            string query = "SELECT * FROM StudentResult";


            SqlDataAdapter SDA = new SqlDataAdapter(query, Program.connection);
            DataTable dt = new DataTable();
            SDA.Fill(dt);

            Program.connection.Close();
            if (dt.Rows.Count > 0)
            {
                foreach (DataRow row in dt.Rows)
                {
                    int stdId = Convert.ToInt32(row["StudentId"]);
                    int assessmentId = Convert.ToInt32(row["AssessmentComponentId"]);
                    int rubricId = Convert.ToInt32(row["RubricMeasurementId"]);
                    int totalMarks = QueryDL.GetIdFromTable("TotalMarks", "AssessmentComponent", "Id", assessmentId.ToString());

                    float obtainedMarks = CalculateMarks(assessmentId, rubricId);

                    dataGridView1.Rows.Add(stdId, assessmentId, rubricId, totalMarks, obtainedMarks);
                }
            }
        }
        private void createCol()
        {
            dataGridView1.Columns.Add("Student", "Student");
            dataGridView1.Columns.Add("Assessment", "Assessment");
            dataGridView1.Columns.Add("Rubric Level", "Rubric Level");

            dataGridView1.Columns.Add("Total Marks", "Total Marks");
            dataGridView1.Columns.Add("Obtained Marks", "Obtained Marks");
        }
        private float CalculateMarks(int assesmentId, int rubricId)
        {
            float componentMarks = QueryDL.GetFloatField($"SELECT TotalMarks FROM AssessmentComponent WHERE Id = {assesmentId}");
            float maxRubricLevel = QueryDL.GetFloatField($"SELECT MAX(MeasurementLevel) FROM RubricLevel WHERE RubricId = (SELECT RubricId FROM RubricLevel WHERE Id = {rubricId})");
            float currentRubricLevel = QueryDL.GetFloatField($"SELECT MeasurementLevel FROM RubricLevel WHERE Id = {rubricId}");

            return (currentRubricLevel / maxRubricLevel) * componentMarks;
        }
        private void AssessmentComboBox_SelectedValueChanged(object sender, EventArgs e)
        {
            string subQuery = $" WHERE AssessmentId = (SELECT Id FROM Assessment WHERE Title = '{AssessmentComboBox.Text}')";
            QueryDL.LoadComboBox(ComponentComboBox, "Name", "AssessmentComponent", subQuery);
        }

        private void ComponentComboBox_SelectedValueChanged(object sender, EventArgs e)
        {
            string subQuery = $" WHERE Id = (SELECT RubricId FROM AssessmentComponent WHERE Name = '{ComponentComboBox.Text}')";
            QueryDL.LoadComboBox(RubricDetailComboBox, "Details", "Rubric", subQuery);
        }
        private void RubricDetailComboBox_SelectedValueChanged(object sender, EventArgs e)
        {

            string subQuery = $" WHERE RubricId = (SELECT Id FROM Rubric WHERE Details = '{RubricDetailComboBox.Text}')";
            QueryDL.LoadComboBox(RubricLevelComboBox, "MeasurementLevel", "RubricLevel", subQuery);
        }
    }
}