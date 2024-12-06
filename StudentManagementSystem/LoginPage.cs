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
using System.Media;
using DBProject.Main;

namespace DBProject
{
    public partial class Uet : Form
    {
        public Uet()
        {
            InitializeComponent();   
            this.StartPosition = FormStartPosition.CenterScreen;
        }


        private void Uet_Load(object sender, EventArgs e)
        { 
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            
            string pass = textBox1.Text;
            if (pass == "admin")
            {
                this.Hide();
                Dashboard f = new Dashboard();
                f.Show();
            }
            else
            {
                MessageBox.Show("Invalid Password", "Authentication Failed", MessageBoxButtons.OK, MessageBoxIcon.Error);   
            }
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }
    }
}
