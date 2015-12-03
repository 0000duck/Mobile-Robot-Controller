using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace GraphicControl.DrawObject
{
    /// <summary>
    /// Map을 그리기 위한 객체
    /// </summary>
    class MapforDraw : MySprite
    {
        public Vector2 MapSize;
        public MapforDraw(Device dev , float Width, float Height  ) : base(dev)
        {
            MapSize = new Vector2(Width , Height);
            Scale.X = Width; Scale.Z = Height;

        }
        public override void InitTransform()
        {
            base.InitTransform();
            // Legacy Code
            Scale.X = 10; Scale.Z = 10;
        }
        /// <summary>
        /// X축 기준으로 90 회전 시킴
        /// </summary>
        /// 

        public override void Update()
        {
            Matrix mPos = Matrix.Translation(Position);
             Matrix mScale = Matrix.Scaling(Scale);

            // W = S * R * T
            World = mScale * mPos;
        }
    
        
        protected override void SetTextureSetting()
        {
            base.SetTextureSetting();
            dev.SamplerState[0].AddressU = TextureAddress.Wrap;
            dev.SamplerState[0].AddressV = TextureAddress.Wrap;
        }

        /// <summary>
        /// Texture Address 설정을 Default로 되돌림
        /// </summary>
        protected override void ReleaseTextureSetting()
        {
            base.ReleaseTextureSetting();
            dev.SamplerState[0].AddressU = TextureAddress.Clamp;
            dev.SamplerState[0].AddressV = TextureAddress.Clamp;
        }
        /// <summary>
        /// 버퍼 재정의 >> 형태가 다르므로
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        public override void OnCreateVertexBuffer(object sender, EventArgs e)
        {

            VertexBuffer vb = (VertexBuffer)sender;
            GraphicsStream stm = vb.Lock(0, 0, 0);
            CustomVertex.PositionNormalTextured[] verts =
                new CustomVertex.PositionNormalTextured[4];

            verts[0].X = 1; verts[0].Y =0; verts[0].Z = 0f;
            verts[0].Nx = 0; verts[0].Ny = 0; verts[0].Nz = -1;
            verts[0].Tu = Scale.X; verts[0].Tv = Scale.Y;

            verts[1].X = 0; verts[1].Y = 0; verts[1].Z = 0;
            verts[1].Nx = 0; verts[1].Ny = 0; verts[1].Nz = -1;
            verts[1].Tu = 0; verts[1].Tv = Scale.Y;

            verts[2].X = 1; verts[2].Y = 0; verts[2].Z = 1;
            verts[2].Nx = 0; verts[2].Ny = 0; verts[2].Nz = -1;
            verts[2].Tu = Scale.X; verts[2].Tv = 0;

            verts[3].X = 0; verts[3].Y = 0; verts[3].Z = 1;
            verts[3].Nx = 0; verts[3].Ny = 0; verts[3].Nz = -1;
            verts[3].Tu = 0; verts[3].Tv = 0;
            stm.Write(verts);
            vb.Unlock();
        }
    }
}
