using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using GraphicControl;

namespace GraphicControl.DrawObject
{
    /// <summary>
    /// 실제로 그려지는 오브젝트들의 Base클래스
    /// </summary>
    public class ModelForDraw : MySprite
    {
        /// <summary>
        /// 가시성>> 밝혀진 오브젝트인가?
        /// </summary>
        public bool bVisiblity = true;
        public bool bMoveable = false;
        public Action<int> MoveCallBack;
        
        // 방향 상수
        public const int UP = 0;
        public const int DOWN = 1;
        public const int LEFT = 2;
        public const int RIGHT = 3;

        protected Vector3 DisireVector;
        
        /// <summary>
        /// 컨트롤 가능한 객체로 전환 해주는 함수
        /// </summary>
        /// <param name="MoveCallBackFunc">움직임을 제어할 콜백 함수</param>
        public void MoveInit(Action<int> MoveCallBackFunc)
        {
            MoveCallBack = MoveCallBackFunc;
            bMoveable = true;
            DisireVector = new Vector3(Position.X, Position.Y, Position.Z);
        }

        /// <summary>
        /// Default MoveFunction으로 객체를 움직일 수있게 초기화
        /// </summary>
        public void MoveInit()
        {
            bMoveable = true;
            MoveCallBack = DefaultMoveFunc;    
        }

        public override void Update()
        {
            if (bMoveable)
                DynamicMove();
  Matrix mPos = Matrix.Translation(Position.X + 0.5f, Position.Y + 0.5f, Position.Z + 0.5f);
            Matrix mRot = Matrix.RotationY(Rotation.Y);
            Matrix mScale = Matrix.Scaling(Scale);

            // W = S * R * T
            World = mScale * mRot * mPos;

        }
        private void DynamicMove()
        {
            Vector3 MoveVector = DisireVector - Position;
            float Distance = MoveVector.Length();
            if (Distance < 0.001f)
            {
                DisireVector.X = Position.X; DisireVector.Y = Position.Y; DisireVector.Z = Position.Z;
                return;
            }
            MoveVector.Normalize();

            // Legacy Code (프레임을 60으로 고정하고 있기때문에 그 기준으로 계산) >> 실제로는 deltatime을 계산하는 타이머를 만들어 계산해야됨
            float DeltaTime = (float)1 / 60;
            Position += MoveVector*DeltaTime;

        }
        /// <summary>
        /// Default Move 함수
        /// </summary>
        /// <param name="Direction"> 방향 상수</param>
        protected void DefaultMoveFunc(int Direction)
        {
            switch (Direction)
            {
                case UP:
                    DisireVector.Z += 1;
                    break;
                case DOWN:
                    DisireVector.Z -= 1;
                    break;
                case LEFT:
                    DisireVector.X -= 1;
                    break;
                case RIGHT:
                    DisireVector.X += 1;
                    break;
                default:
                    break;

            }
        }

        /// <summary>
        /// 실제 움직이는 함수
        /// </summary>
        /// <param name="Direction"> 정의 된 방향</param>
        public void OnMove(int Direction)
        {
            if (bMoveable == false || MoveCallBack == null) return;

            MoveCallBack(Direction); 
        }
        /// <summary>
        /// 생성자
        /// </summary>
        /// <param name="dev">device</param>
        public ModelForDraw(Device dev) : base(dev)
        {

            GraphicManager.GetManager().AddDrawObbject(this);
        }
        public override void Render()
        {
            if (bVisiblity == false) return;

            base.Render();
        }
        protected override void SetTextureSetting()
        {
            base.SetTextureSetting();
        }
        protected override void ReleaseTextureSetting()
        {
            base.ReleaseTextureSetting();
        }

    }
}
