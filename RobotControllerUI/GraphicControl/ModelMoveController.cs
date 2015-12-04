using System;
using System.Collections.Generic;
using System.Drawing;
using Microsoft.DirectX;
using System.Windows.Forms;
using Microsoft.DirectX.Direct3D;
using GraphicControl.DrawObject;

namespace GraphicControl
{
    /// <summary>
    /// 특정유닛의 움직임을 관리해주는 컨트롤러
    /// </summary>
    public class ModelMoveController
    {
        protected Queue<Vector3> MoveQueue;
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
        public ModelMoveController(DrawObj Unit)
        {
            ManagedUnit = Unit;
            MoveQueue = new Queue<Vector3>();
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
        /// Default Move 함수
        /// </summary>
        /// <param name="Direction"> 방향 상수</param>
        protected void DefaultMoveFunc(int Direction)
        {
            if (ManagedUnit == null) return;
            switch (Direction)
            {
                case UP:
                    MoveQueue.Enqueue(new Vector3(0, 0, 1));
                    break;
                case DOWN:
                    MoveQueue.Enqueue(new Vector3(0, 0, -1));
                    break;
                case LEFT:
                    MoveQueue.Enqueue(new Vector3(-1, 0, 0));
                    break;
                case RIGHT:
                    MoveQueue.Enqueue(new Vector3(1, 0, 0));
                    break;
                default:
                    break;

            }
        }
        /// <summary>
        /// 실제로 관리하는 유닛에 이동을 적용
        /// </summary>
        public void MoveUnit()
        {
            if (ManagedUnit == null || ManagedUnit.bMoving == true) return;

            if (MoveQueue.Count > 0)
            {
                ManagedUnit.bMoving = true;
                ManagedUnit.AddDesireVector(MoveQueue.Dequeue());
            }

        }
    }
}
