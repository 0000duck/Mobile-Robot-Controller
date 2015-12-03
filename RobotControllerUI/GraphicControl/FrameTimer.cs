using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading.Tasks;

namespace GraphicControl
{
    /// <summary>
    /// Draw Frme을 관리하는 Timer 클래스
    /// </summary>
    public class FrameTimer
    {
        private Timer ticktimer;
        private Action TickEvent;
        /// <summary>
        /// Timer 생성자 (초기화 포함)
        /// </summary>
        /// <param name="FramePerSec"> 초당 프레임</param>
        public FrameTimer(int FramePerSec)
        {
            ticktimer = new Timer();
            ticktimer.Interval = 1000 / FramePerSec;
            ticktimer.Tick += new EventHandler(TimerTick);
        }
        /// <summary>
        /// Frame당 이벤트 추가
        /// </summary>
        /// <param name="Event"></param>
        public void AddTickEvent(Action Event)
        {
            TickEvent += Event;
        }
        /// <summary>
        /// Event Handler
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void TimerTick(object sender, EventArgs e)
        {
           
            if (TickEvent == null) return;
            TickEvent();
        }
        public void Start()
        {
            ticktimer.Start();
        }
    }
}
