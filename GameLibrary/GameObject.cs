using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;
using GameProject;
using GameProject.Enums;
using System.Diagnostics.Eventing.Reader;

namespace GameFrameWorkLibrary
{
    public class GameObject
    {
        public PictureBox PicBox;
        public bool IsGravityEnabled;
        IMovement controller;
        public GameObjectType type;
        public GameObject(GameObjectType type, Image img, int left, int top, IMovement controller, bool IsGravityEnabled = false)
        {
            this.PicBox = new PictureBox();
            this.PicBox.Image = img;
            this.PicBox.Width = img.Width;
            this.PicBox.Height = img.Height;
            this.PicBox.BackColor = Color.Transparent;
            this.PicBox.Left = left;
            this.PicBox.Top = top;

            this.type = type;
            this.IsGravityEnabled = IsGravityEnabled;
            this.controller = controller;
        }
        public void update(int gravity)
        {
            if (IsGravityEnabled)
            {
                PicBox.Top += gravity;
            }
            Point loc = controller.move(PicBox.Location);
            if (loc.X == 0)
                PicBox.Image = null;
            else
                PicBox.Location = loc;
        }
    }
}
