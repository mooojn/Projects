using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameProject
{
    public interface IMovement
    {
        Point move(Point location);
    }
}
