using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using EZInput;

namespace GameProject.Movements
{
    public class KeyboardMovement : IMovement
    {
        private int speed;
        private System.Drawing.Point boundary;
        private int offset;
        public void setSpeed(int speed)
        {
            this.speed = speed;
        }
        public KeyboardMovement(int speed, System.Drawing.Point boundary)
        {
            this.speed = speed;
            this.boundary = boundary;
            this.offset = 50;
        }
        public System.Drawing.Point move(System.Drawing.Point location)
        {
            if (Keyboard.IsKeyPressed(Key.UpArrow))
            {
                if (location.Y + speed > 10)
                {
                    location.Y -= speed;
                }
            }
            if (Keyboard.IsKeyPressed(Key.DownArrow))
            {
                if (location.Y + offset < boundary.Y)
                {
                    location.Y += speed;
                }
            }
            //if (Keyboard.IsKeyPressed(Key.LeftArrow))
            //{
            //    if (location.X + speed > 10)
            //    {
            //        location.X -= speed;
            //    }
            //}
            //if (Keyboard.IsKeyPressed(Key.RightArrow))
            //{
            //    if (location.X + offset < boundary.X)
            //    {
            //        location.X += speed;
            //    }
            //}
            if (Keyboard.IsKeyPressed(Key.Space))
            {
                if (location.Y < boundary.Y)
                {
                    location.Y += 2*speed;
                }

            }
            return location;
        }
    }
}
