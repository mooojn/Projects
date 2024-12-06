using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace GameProject.Movements
{
    public class HorizontalPatrol : IMovement
    {
        private int speed;
        private Direction direction;
        private Point boundary;
        private int offset = 90;    
        public HorizontalPatrol(int speed, Direction direction, Point boundary)
        {
            this.speed = speed;
            this.direction = direction;
            this.boundary = boundary;
        }
        public Point move(Point location)
        {
            if ((location.X + offset) >= boundary.X)
            {
                direction = Direction.Left;
            }
            else if (location.X + speed <= 0)
            {
                direction = Direction.Right;
            }
            if (direction == Direction.Left)
            {
                location.X -= speed;
            }
            else
            {
                //location.X += speed;
                location.X = 0;
            }
            return location;
        }
        public void setSpeed(int speed)
        {
            this.speed = speed;
        }
    }
}
