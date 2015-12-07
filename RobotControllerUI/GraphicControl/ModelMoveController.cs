using System;
using System.Collections.Generic;
using System.Drawing;
using Microsoft.DirectX;
using System.Windows.Forms;
using Microsoft.DirectX.Direct3D;
using GraphicControl.DrawObject;
using GraphicControl.Interface;

namespace GraphicControl
{
    /// <summary>
    /// 특정유닛의 움직임을 관리해주는 컨트롤러
    /// </summary>
    public class ModelActionController
    {
        protected Queue<IActionObject> ActionBuffer;
        protected DrawObj ManagedUnit;


        // 방향 상수
        public const int UP = 0;
        public const int DOWN = 1;
        public const int LEFT = 2;
        public const int RIGHT = 3;

        /// <summary>
        /// 콜백함수
        /// </summary>
        public Action<int> MoveCallBack;
        /// <summary>
        /// 생성자
        /// </summary>
        /// <param name="Unit"></param>
        public ModelActionController(DrawObj Unit)
        {
            ManagedUnit = Unit;
            ActionBuffer = new Queue<IActionObject>();
            MoveCallBack = DefaultMoveFunc;
        }

        /// <summary>
        /// 실제 움직이는 함수
        /// </summary>
        /// <param name="Direction"> 정의 된 방향</param>
        public void OnMove(int Direction)
        {
            if (MoveCallBack == null) return;

            MoveCallBack(Direction);
        }

        /// <summary>
        /// 액션을 추가
        /// </summary>
        /// <param name="Act"></param>
        public void EnqueueAction(IActionObject Act)
        {
            ActionBuffer.Enqueue(Act);
        }
        /// <summary>
        /// 등록되있는 다음 액션을 실행
        /// </summary>
        public void Act()
        {
            if (ManagedUnit.bActing == true) return;
            if (ActionBuffer == null || ActionBuffer.Count <= 0) return;
            ActionBuffer.Dequeue().DoAction();
        }
        /// <summary>
        /// Default Move 함수
        /// </summary>
        /// <param name="Direction"> 방향 상수</param>
        protected void DefaultMoveFunc(int Direction)
        {
            if (ManagedUnit == null || ManagedUnit.bActing == true) return;
            if (ActionBuffer.Count > 0)
            {
                ManagedUnit.bActing = true;
                switch (Direction)
                {
                    case UP:
                        ManagedUnit.AddDesireVector(new Vector3(0, 0, 1));
                        break;
                    case DOWN:
                        ManagedUnit.AddDesireVector(new Vector3(0, 0, -1));
                        break;
                    case LEFT:
                        ManagedUnit.AddDesireVector(new Vector3(-1, 0, 0));
                        break;
                    case RIGHT:
                        ManagedUnit.AddDesireVector(new Vector3(1, 0, 0));
                        break;
                    default:
                        break;

                }
            }
        }
      
    }
}
