using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
namespace GraphicControl.DrawObject
{
    /// <summary>
    /// Texture를 포함 하고 있는 정 사각형의 평면
    /// </summary>
    public class MySprite
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

        protected Matrix World;
        /// <summary>
        /// Vertex를 담고 있는 Buffer
        /// </summary>
        public  VertexBuffer VBuffer { get; protected set; }
        protected Texture ImageTexture = null;
        protected Device dev = null;
        /// <summary>
        /// 생성자 
        /// </summary>
        /// <param name="Dev"> Direct Device</param>
        public MySprite(Device Dev)
        {

            dev = Dev;

            InitTransform();

            VBuffer = new VertexBuffer(
                typeof(CustomVertex.PositionNormalTextured), 4 , Dev , Usage.WriteOnly,
                VertexFormats.PositionNormal | VertexFormats.Texture1, Pool.Default);
            

            VBuffer.Created +=
                new System.EventHandler(this.OnCreateVertexBuffer);
            this.OnCreateVertexBuffer(VBuffer, null);
        }
        public virtual void InitTransform()
        {
            Position = new Vector3(0, 0, 0);
            Rotation = new Vector3(0, 0, 0);
            Scale = new Vector3(1, 1, 1);

            World = Matrix.Identity;
        } 
        /// <summary>
        /// 생성 이벤트 처리 Mesh의 기본 형태 결정
        /// </summary>
        /// <param name="sender">VertexBuffer</param>
        /// <param name="e"></param>
        public virtual void OnCreateVertexBuffer(object sender, EventArgs e)
        {
          
            VertexBuffer vb = (VertexBuffer)sender;
            GraphicsStream stm = vb.Lock(0, 0, 0);
            CustomVertex.PositionNormalTextured[] verts =
                new CustomVertex.PositionNormalTextured[4];

            verts[0].X = 0.5f; verts[0].Y = -0.5f; verts[0].Z =0;
            verts[0].Nx = 0; verts[0].Ny = 0; verts[0].Nz = -1;
            verts[0].Tu = Scale.X; verts[0].Tv = Scale.Y;

            verts[1].X = -0.5f; verts[1].Y = -0.5f; verts[1].Z = 0;
            verts[1].Nx = 0; verts[1].Ny = 0; verts[1].Nz = -1;
            verts[1].Tu = 0; verts[1].Tv = Scale.Y;

            verts[2].X = 0.5f; verts[2].Y = 0.5f; verts[2].Z = 0;
            verts[2].Nx = 0; verts[2].Ny = 0; verts[2].Nz = -1;
            verts[2].Tu = Scale.X; verts[2].Tv = 0;

            verts[3].X = -0.5f; verts[3].Y = 0.5f; verts[3].Z =0;
            verts[3].Nx = 0; verts[3].Ny = 0; verts[3].Nz = -1;
            verts[3].Tu = 0; verts[3].Tv = 0;
            stm.Write(verts);
            vb.Unlock();
        }
        /// <summary>
        /// Tick당 실행되는 객체 업데이트 함수 
        /// </summary>
        public virtual void Update()
        {
            Matrix mPos = Matrix.Translation(Position.X , Position.Y , Position.Z);
            Matrix mRot = Matrix.RotationY(Rotation.Y);
            Matrix mScale = Matrix.Scaling(Scale);

            // W = S * R * T
            World = mScale * mRot * mPos;
           
        }
      
        /// <summary>
        /// Sprite Draw 함수
        /// </summary>
        public virtual void Render()
        {
            SetVB();
            dev.Transform.World = World;
            dev.DrawPrimitives(PrimitiveType.TriangleStrip, 0, 2);
            ReleaseTextureSetting();
        }
        /// <summary>
        /// Vertex buffer 즉 도형을 셋팅 하는함수 
        /// </summary>
        public virtual void SetVB()
        {
            SetTextureSetting();
            dev.SetStreamSource(0, VBuffer, 0);
            dev.VertexFormat = VertexFormats.PositionNormal | VertexFormats.Texture1;
        }
        /// <summary>
        /// Texture와 TextureStage를 셋팅해주는 함수
        /// </summary>
        protected virtual void SetTextureSetting()
        {
            dev.SetTexture(0, ImageTexture);
            dev.TextureState[0].ColorOperation = TextureOperation.Modulate;
            dev.TextureState[0].ColorArgument1 = TextureArgument.TextureColor;
            dev.TextureState[0].ColorArgument2 = TextureArgument.Diffuse;

            dev.TextureState[0].ColorOperation = TextureOperation.SelectArg1;
            dev.TextureState[0].ColorArgument1 = TextureArgument.TextureColor;
            dev.TextureState[0].ColorArgument2 = TextureArgument.Diffuse;


        }
        /// <summary>
        /// Texture Setting을 Default로 되돌린다.
        /// </summary>
        protected virtual void ReleaseTextureSetting()
        {
            //현재설정이 디폴트
            dev.SetTexture(0,null);
        }
        /// <summary>
        /// Texture폴더에 있는 이미지를 Load해 주는 함수
        /// </summary>
        /// <param name="FileName"></param>
        public void TextureLoad(string FileName )
        {
            //라이브러리로 바꾸면서 상대경로로 이용
  
            ImageTexture = TextureLoader.FromFile(dev,Application.StartupPath + @"\..\..\Texture\" + FileName);
        }
    }
}
