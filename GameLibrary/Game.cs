using GameFrameWorkLibrary;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;
using GameProject.Enums;

namespace GameProject
{
    public class Game
    {
        // attributes
        public static int score;
        int gravity;
        List<GameObject> gameObjects;
        List<CollisionDetection> collisions;
        Form container;
        int gameObjectsCount;
        // singleton instance
        private static Game instance = null;
        public static Game getInstance(Form container, int gravity = 10)
        {
            if (instance == null)
            {
                instance = new Game(container, gravity);
            }
            return instance;
        }
        private Game(Form container, int gravity)
        {
            this.gravity = gravity;
            this.container = container;
            this.gameObjects = new List<GameObject>();
            this.collisions = new List<CollisionDetection>();
        }
        public void setForm(Form f)
        {
            this.container = f; 
        }
        // constructor
        public void addGameObject(GameObject obj)
        {
            if (gameObjectsCount > 20)      // factory pattern
                return;
            gameObjects.Add(obj);
            container.Controls.Add(obj.PicBox);
            gameObjectsCount++;
        }   
        public void removeGameObject(GameObject obj)
        {
            gameObjects.Remove(obj);
            container.Controls.Remove(obj.PicBox);
            gameObjectsCount--;
            score++;
        }
        public void addCollision(CollisionDetection collision)
        {
            collisions.Add(collision);
        }
        public void update()
        {
            for (int i = 0; i < gameObjects.Count; i++)
            {
                GameObject obj = gameObjects[i];
                obj.update(gravity);
                if (obj.PicBox.Image == null)
                {
                    removeGameObject(obj);
                }

                if (obj.type == GameObjectType.Player)
                {
                    for (int j = 0; j < gameObjects.Count; j++)
                    {
                        if (i != j) // Avoid self-collision check
                        {
                            GameObject obj2 = gameObjects[j];
                            if (obj2.type != GameObjectType.Player)
                            {
                                foreach (CollisionDetection c in collisions)
                                {
                                    if (c.IsCollide(obj.PicBox, obj2.PicBox))
                                    {
                                        c.Collide(obj2.type);
                                        removeGameObject(obj2);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        public GameObject getPlayer()
        {
            foreach (GameObject obj in gameObjects)
            {
                if (obj.type == GameObjectType.Player)
                {
                    return obj; 
                }
            }
            return null;
        }

        public int GetObjectsCount()
        {
            return gameObjectsCount;
        }
        public void Restart()
        {
            score = 0;
            gameObjectsCount = 0;
            gameObjects.Clear();
            collisions.Clear();
            container.Controls.Clear();
        }
        //public int GetScore()
        //{
        //    return score;
        //}
        //public void SetScore(int score)
        //{
        //    this.score = score;
        //}
    }
}
