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
    /// 실제 객체(저장은 Transform과 모델 이름만)
    /// </summary>
    public class DrawObj
    {
        /// <summary>
        /// World 행렬을 구성하는 3 성분 (위치 , 회전값 , 크기값)
        /// </summary>
        public Vector3 Position;
        /// <summary>
        /// 회전은 Y축으로만 할것 3축 동시에적용 구현안함
        /// </summary>
        public Vector3 Rotation;
        public Vector3 Scale;

        public Matrix ObjWorld;

        protected Device dev = null;

        /// <summary>
        /// 이동중인지 여부
        /// </summary>
        public bool bActing = false;

        private int modelname;
        public int ModelName
        {
            protected set { modelname = value; }
            get { return modelname; }
        }


        protected Vector3 DesireVector;

        public DrawObj(Device dev, int name)
        {
            this.dev = dev;
            ModelName = name;
            GraphicManager.GetManager().AddDrawObbject(this);
            InitTransform();
        }

        public virtual void InitTransform()
        {
            Position = new Vector3(0, 0, 0);
            Rotation = new Vector3(0, 0, 0);
            Scale = new Vector3(1, 1, 1);

            ObjWorld = Matrix.Identity;
        }
        /// <summary>
        /// 움직이는 객체의 움직임 초기화
        /// </summary>
        /// <param name="StartPos"> 초기 위치</param>
        public void ObjectPosInit(Vector3 StartPos)
        {
            Position = StartPos;
            DesireVector = Position;
        }
        /// <summary>
        /// Tick당 실행되는 객체 업데이트 함수 
        /// </summary>
        public virtual void Update()
        {
            if (bActing)
                DynamicMove();
            Matrix mPos = Matrix.Translation(Position.X + 0.5f, Position.Y + 0.5f, Position.Z + 0.5f);
            Matrix mRot = Matrix.RotationY(Rotation.Y);
            Matrix mScale = Matrix.Scaling(Scale);

            // W = S * R * T
            ObjWorld = mScale * mRot * mPos;

        }
        /// <summary>
        /// 자연스러운 이동 (보간)
        /// </summary>
        private void DynamicMove()
        {
            Vector3 MoveVector = DesireVector - Position;
            float Distance = MoveVector.Length();
            if (Distance < 0.001f)
            {
                Position.X = DesireVector.X; Position.Y = DesireVector.Y; Position.Z = DesireVector.Z;
                bActing = false;
                return;
            }
            MoveVector.Normalize();

            // Legacy Code (프레임을 60으로 고정하고 있기때문에 그 기준으로 계산) >> 실제로는 deltatime을 계산하는 타이머를 만들어 계산해야됨
            float DeltaTime = (float)1 / 60;
            Position += MoveVector * DeltaTime;

        }
        /// <summary>
        /// Desire Vector 변경 >> 상대적수치로 변경함
        /// </summary>
        /// <param name="MoveVec">DesireVec += MoveVec</param>
        public void AddDesireVector(Vector3 MoveVec)
        {
            DesireVector += MoveVec;
        }

        /// <summary>
        /// Draw 함수
        /// </summary>
        public virtual void Render(ModelManager Manager)
        {
            dev.Transform.World = ObjWorld;
            Manager.Render(ModelName);

        }
    }
}
