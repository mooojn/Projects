using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using iTextSharp.text;
using iTextSharp.text.pdf;

namespace DBProject.Main
{
    public partial class Home : Form
    {
        public Home()
        {
            InitializeComponent();
        }
        private void Home_Load(object sender, EventArgs e)
        {

        }
        public void Generate_PDF(object sender, EventArgs e)
        {
            // query to use to fetch data
            string query = "SELECT CONCAT(s.FirstName, ' ', s.LastName) AS Name, s.RegistrationNumber AS RegNo, " +
                "ac.Name AS AssessmentName, rl.MeasurementLevel AS RubricLevel, rl.Details AS RubricDetail FROM StudentResult AS sr " +
                "JOIN AssessmentComponent AS ac ON ac.Id = sr.AssessmentComponentId JOIN RubricLevel AS rl ON rl.Id = sr.RubricMeasurementId " +
                "JOIN Student AS s ON s.Id = sr.StudentId;";

            // path to save pdf
            string filePath = "C:\\users\\moon\\Downloads\\table_records.pdf";

            try
            {
                Document doc = new Document();
                
                createMetaData(doc);   // extra 
                
                PdfWriter.GetInstance(doc, new FileStream(filePath, FileMode.Create));
                
                doc.Open();
                Program.connection.Open();

                SqlCommand command = new SqlCommand(query, Program.connection);
                SqlDataReader reader = command.ExecuteReader();

                // font styles
                var fontBold = FontFactory.GetFont(FontFactory.TIMES_BOLD, 16, BaseColor.BLACK);
                var tableHeader = FontFactory.GetFont(FontFactory.TIMES_BOLD, 13, BaseColor.BLACK);
                
                // table styles
                var table = new PdfPTable(5);
                table.SpacingBefore = 20f; 
                table.WidthPercentage = 100; 

                // header
                doc.Add(new Paragraph("Student Result Records", fontBold) { Alignment = Element.ALIGN_CENTER });
                
                // table attributes
                table.AddCell(new PdfPCell(new Phrase("StudentId", tableHeader)));
                table.AddCell(new PdfPCell(new Phrase("RegNo", tableHeader)));
                table.AddCell(new PdfPCell(new Phrase("AssessmentName", tableHeader)));
                table.AddCell(new PdfPCell(new Phrase("RubricLevel", tableHeader)));
                table.AddCell(new PdfPCell(new Phrase("RubricDetail", tableHeader)));

                // table fields
                while (reader.Read())
                {    
                    table.AddCell((reader["Name"].ToString()));
                    table.AddCell(reader["RegNo"].ToString());
                    table.AddCell(reader["AssessmentName"].ToString());
                    table.AddCell(reader["RubricLevel"].ToString());
                    table.AddCell(reader["RubricDetail"].ToString());
                }
                doc.Add(table);

                Program.connection.Close();
                doc.Close();

                MessageBox.Show("PDF generated successfully...", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
                // open file
                System.Diagnostics.Process.Start(filePath);
            }
            catch (Exception err)
            {
                MessageBox.Show("Error: " + err.Message, "Failed", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        private void createMetaData(Document doc)
        {
            doc.AddLanguage("en-us");
            doc.AddHeader("Student Result Records", "Student Result Records");
            doc.AddTitle("Student Result Records");
            doc.AddCreator("Moon");
            doc.AddAuthor("Moon");
            doc.AddCreationDate();
        }
    }
}
