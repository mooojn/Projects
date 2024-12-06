using DBProject.Main;
using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DBProject
{
    internal static class Program
    {
        public static string connectionString = "Data Source=localhost\\MOOOJN;Initial Catalog=ProjectB;Integrated Security=True";
        public static SqlConnection connection = new SqlConnection(connectionString);
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Uet());
        }
    }
}
