using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GraphicControl;

namespace RobotControllerUI
{
    /// <summary>
    /// Flickering Issue 를 제거하기위한 Pannel
    /// </summary>
    class MyDxPannel : System.Windows.Forms.Panel
    {
        /// <summary>
        /// 기본 생성자에 DubbleBuffering 추가
        /// </summary>
        ///

        
        public MyDxPannel() 
        {
            this.SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
                    

        }
                
    

    }
}
