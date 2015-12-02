using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GraphicControl;
using GraphicControl.DrawObject;

namespace RobotControllerUI
{
    public partial class InteractiveUI : Form
    {
        /// <summary>
        /// View의 프레임을 조절하는 타이머
        /// </summary>
        private FrameTimer VeiwFrameTimer;
         
        public InteractiveUI()
        {
            InitializeComponent();
        }

        private void GraphicView_Paint(object sender, PaintEventArgs e)
        {
            //flickering 문제 때문에 수정
           // GraphicManager.GetManager().Render();
        }
        /// <summary>
        /// Load 되었을때 >> Aplication Init();
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void InteractiveUI_Load(object sender, EventArgs e)
        {
            if (!GraphicManager.GetManager().InitDX(this.GraphicView))
            {
                MessageBox.Show("Could not initialize Direct3D.");
            
            }
            GraphicManager.GetManager().RenderInit();

      
            //60프레임으로 고정
            VeiwFrameTimer = new FrameTimer(500);
            VeiwFrameTimer.AddTickEvent(() =>
                {
                    GraphicManager.GetManager().Render();
                 
                });
            VeiwFrameTimer.Start();
        }
       

        /// <summary>
        /// Test용 Robot UP 함수
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Upbtn_Click(object sender, EventArgs e)
        {
            GraphicManager.GetManager().OnMoveRobot(ModelForDraw.UP);
           
            
        }
        /// <summary>
        /// Test용 Robot Down 함수
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void DownBtn_Click(object sender, EventArgs e)
        {
            GraphicManager.GetManager().OnMoveRobot(ModelForDraw.DOWN);
          
        }
        /// <summary>
        /// Test용 Robot Left 함수
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void LeftBtn_Click(object sender, EventArgs e)
        {
            GraphicManager.GetManager().OnMoveRobot(ModelForDraw.LEFT);
        
        }
        /// <summary>
        /// Test용 Robot Right 함수
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void RightBtn_Click(object sender, EventArgs e)
        {
            GraphicManager.GetManager().OnMoveRobot(ModelForDraw.RIGHT);
      
        }
    }
}
