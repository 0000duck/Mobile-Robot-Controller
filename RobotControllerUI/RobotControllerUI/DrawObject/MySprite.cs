using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
namespace RobotControllerUI.DrawObject
{
    /// <summary>
    /// Texture를 포함 하고 있는 정 사각형의 평면
    /// </summary>
    public class MySprite
    {
        /// <summary>
        /// Vertex를 담고 있는 Buffer
        /// </summary>
        public VertexBuffer VBuffer { get; }
        Texture ImageTexture = null;
        Device dev = null;
        /// <summary>
        /// 생성자 
        /// </summary>
        /// <param name="Dev"> Direct Device</param>
        public MySprite(Device Dev)
        {

            dev = Dev;
            VBuffer = new VertexBuffer(
                typeof(CustomVertex.PositionNormalTextured), 4 , Dev , Usage.WriteOnly,
                VertexFormats.PositionNormal | VertexFormats.Texture1, Pool.Default);
            

            VBuffer.Created +=
                new System.EventHandler(this.OnCreateVertexBuffer);
            this.OnCreateVertexBuffer(VBuffer, null);
        }
        /// <summary>
        /// 생성 이벤트 처리 
        /// </summary>
        /// <param name="sender">VertexBuffer</param>
        /// <param name="e"></param>
        public void OnCreateVertexBuffer(object sender, EventArgs e)
        {
          
            VertexBuffer vb = (VertexBuffer)sender;
            GraphicsStream stm = vb.Lock(0, 0, 0);
            CustomVertex.PositionNormalTextured[] verts =
                new CustomVertex.PositionNormalTextured[4];

            verts[0].X = 0.5f; verts[0].Y = -0.5f; verts[0].Z = 0.5f;
            verts[0].Nx = 0; verts[0].Ny = 0; verts[0].Nz = -1;
            verts[0].Tu = 1; verts[0].Tv = 1;

            verts[1].X = -0.5f; verts[1].Y = -0.5f; verts[1].Z = 0.5f;
            verts[1].Nx = 0; verts[1].Ny = 0; verts[1].Nz = -1;
            verts[1].Tu = 0; verts[1].Tv = 1;

            verts[2].X = 0.5f; verts[2].Y = 0.5f; verts[2].Z = 0.5f;
            verts[2].Nx = 0; verts[2].Ny = 0; verts[2].Nz = -1;
            verts[2].Tu = 1; verts[2].Tv = 0;

            verts[3].X = -0.5f; verts[3].Y = 0.5f; verts[3].Z = 0.5f;
            verts[3].Nx = 0; verts[3].Ny = 0; verts[3].Nz = -1;
            verts[3].Tu = 0; verts[3].Tv = 0;
            stm.Write(verts);
            vb.Unlock();
        }
        /// <summary>
        /// Sprite Draw 함수
        /// </summary>
        public void Render()
        {
            SetTextureStage();
            dev.SetStreamSource(0, VBuffer, 0);
            dev.VertexFormat = VertexFormats.PositionNormal | VertexFormats.Texture1;
            dev.DrawPrimitives(PrimitiveType.TriangleStrip, 0, 2);
        }
        /// <summary>
        /// Texture와 TextureStage를 셋팅해주는 함수
        /// </summary>
        protected virtual void SetTextureStage()
        {
            dev.SetTexture(0, ImageTexture);
            dev.TextureState[0].ColorOperation = TextureOperation.Modulate;
            dev.TextureState[0].ColorArgument1 = TextureArgument.TextureColor;
            dev.TextureState[0].ColorArgument2 = TextureArgument.Diffuse;
            dev.TextureState[0].AlphaOperation = TextureOperation.Disable;


        }
        public void TextureLoad(string FileName)
        {
            ImageTexture = TextureLoader.FromFile(dev,
                Application.StartupPath + @"\..\..\Texture\"+FileName);

        }
    }
}
