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
    /// 보조격자
    /// </summary>
    class Grid
    {
        protected Device dev;
        protected float XOffset;
        protected float ZOffset;
        float XMax;
        float ZMax;
        float Height;

        // 가로 라인
        VertexBuffer HorizontalLinevb;
        //세로 라인
        VertexBuffer VertLinevb;
        /// <summary>
        /// 그리드 생성자
        /// </summary>
        /// <param name="XOffset"> X간격</param>
        /// <param name="ZOffset"> 2D기준 Z간격</param>
        /// <param name="XMax"> </param>
        /// <param name="ZMax"></param>
        /// <param name="Height"> 그리드의 높이</param>
        public Grid(Device _dev, float _XOffset, float _ZOffset, float _XMax, float _ZMax, float _Height)
        {
            dev = _dev;
            XOffset = _XOffset; ZOffset = _ZOffset;
            XMax = _XMax; ZMax = _ZMax;
            Height = _Height;
            InitVertexBuffers();
        }
        /// <summary>
        /// 가로 세로 라인 버퍼들을 초기화 하는 함수 
        /// </summary>
        private void InitVertexBuffers()
        {
            // 가로 라인
            HorizontalLinevb = new VertexBuffer(
                typeof(CustomVertex.PositionColored), 2, dev,
                Usage.WriteOnly, VertexFormats.Position | VertexFormats.Diffuse, Pool.Default);

            GraphicsStream stm = HorizontalLinevb.Lock(0, 0, 0);
            CustomVertex.PositionColored[] HorizonVert =
                new CustomVertex.PositionColored[2];
            HorizonVert[0].X = 1.0f; HorizonVert[0].Y = 0; HorizonVert[0].Z = 0;
            HorizonVert[0].Color = System.Drawing.Color.White.ToArgb();
            
            HorizonVert[1].X = 0; HorizonVert[1].Y = 0; HorizonVert[1].Z = 0;
            HorizonVert[1].Color = System.Drawing.Color.White.ToArgb();

            stm.Write(HorizonVert);
            HorizontalLinevb.Unlock();

            //세로 라인
            VertLinevb = new VertexBuffer(
                typeof(CustomVertex.PositionColored), 2, dev,
                Usage.WriteOnly, VertexFormats.Position | VertexFormats.Diffuse, Pool.Default);
            stm = VertLinevb.Lock(0, 0, 0);
            CustomVertex.PositionColored[] VerticleVert =
                new CustomVertex.PositionColored[2];
            VerticleVert[0].X = 0; VerticleVert[0].Y = 0; VerticleVert[0].Z = 1.0f;
            VerticleVert[0].Color = System.Drawing.Color.White.ToArgb();

            VerticleVert[1].X = 0; VerticleVert[1].Y = 0; VerticleVert[1].Z = 0;
            VerticleVert[1].Color = System.Drawing.Color.White.ToArgb();

            stm.Write(VerticleVert);
            VertLinevb.Unlock();
        }
        /// <summary>
        /// 그리드를 그려주는 함수
        /// </summary>
        public void DrawGird()
        {
            for (float x = -XMax/2 ; x < XMax/2 ; x += XOffset)
            {
                Matrix Scale = Matrix.Scaling(0, 0, ZMax);
                Matrix Pos = Matrix.Translation(x, Height, -ZMax/2);
                dev.Transform.World = Scale * Pos;
                DrawLine(false);
            }

            for (float z = -ZMax/2; z < ZMax/2; z += ZOffset)
            {
                Matrix Scale = Matrix.Scaling(XMax, 0, 0);
                Matrix Pos = Matrix.Translation(-XMax/2, Height, z );
                dev.Transform.World = Scale * Pos;
                DrawLine(true);
            }
            
        }
        private void DrawLine(bool Horizontal)
        {

            dev.SetStreamSource(0, Horizontal? HorizontalLinevb:VertLinevb, 0);
            dev.VertexFormat = VertexFormats.Position | VertexFormats.Diffuse;
            dev.DrawPrimitives(PrimitiveType.LineList, 0, 1);
        }
    }
}
