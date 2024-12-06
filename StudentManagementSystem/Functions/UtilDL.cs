using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DBProject.Functions
{
    internal class UtilDL
    {
        public static void hideUD_Btns(Button add, Button update, Button delete, Button ud)
        {
            add.Show();

            ud.Hide();
            update.Hide();
            delete.Hide();
        }
        public static void showUD_Btns(Button add, Button update, Button delete, Button ud)
        {
            ud.Show();
            update.Show();
            delete.Show();

            add.Hide();
        }
    }
}
