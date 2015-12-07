using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RobotControllerUI
{


    public class Spot
    {
        public float x;
        public float y;

        public Spot()
        { }
        public Spot(string str)
        {
            StringToSpot(str);
        }
        public Spot(float x, float y)
        {
            this.x = x; this.y = y;
        }
        /// <summary>
        /// Static Method Spot의 내용물을 String으로 바꿔줌
        /// </summary>
        public override string ToString()
        {
            string str = x.ToString() + " " + y.ToString();
            return str;
        }

        public void StringToSpot(string str)
        {
            if (str == null || str == "") return;
            var parts = str.Split(' ');
            x = Convert.ToInt32(parts[0]);
            y = Convert.ToInt32(parts[1]);

        }
    }
}