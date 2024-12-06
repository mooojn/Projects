using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GameProject.Enums;
using GameFrameWorkLibrary;
using System.Windows.Forms;

namespace GameProject
{
    public class CollisionDetection
    {
        GameObjectType player;
        GameObjectType obstacle;
        GameAction action;
        public CollisionDetection(GameObjectType player, GameObjectType obstacle, GameAction action)
        {
            this.player = player;
            this.obstacle = obstacle;
            this.action = action;
        }
        public bool IsCollide(PictureBox obj1, PictureBox obj2)
        {
            bool flag = false;
            if (obj1.Bounds.IntersectsWith(obj2.Bounds))
                flag = true;
            return flag;
        }
        public void Collide(GameObjectType action)
        {
            if (action == GameObjectType.SmallObstacle)
            {
                Game.score -= 5;
            }
            else if (action == GameObjectType.MidObstacle)
            {
                Game.score -= 10;
            }
            else if (action == GameObjectType.BigObstacle)
            {
                Game.score -= 20;
            }
        }
        public GameAction getAction()
        {
            return action;
        }
    }
}
