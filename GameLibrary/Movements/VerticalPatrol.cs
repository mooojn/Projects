using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameProject.Movements
{
    public class VerticalPatrol : IMovement
    {
        private int speed;
        private Direction direction;
        private Point boundary;
        private int offset = 90;
        public VerticalPatrol(int speed, Direction direction, Point boundary)
        {
            this.speed = speed;
            this.direction = direction;
            this.boundary = boundary;
        }
        public Point move(Point location)
        {
            if ((location.Y + offset) >= boundary.Y)
            {
                direction = Direction.Up;
            }
            else if (location.Y - speed <= 0)
            {
                direction = Direction.Down;
            }
            if (direction == Direction.Up)
            {
                location.Y -= speed;
            }
            else
            {
                location.Y += speed;
            }
            return location;
        }
        public void setSpeed(int speed)
        {
            this.speed = speed;
        }
    }
}
