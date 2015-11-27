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
    /// Map을 그리기 위한 객체
    /// </summary>
    class MapforDraw : ModelForDraw
    {
        public Vector2 MapSize;
        public MapforDraw(Device dev , float Width, float Height  ) : base(dev)
        {
            MapSize = new Vector2(Width , Height);
            

        }
        public override void InitTransform()
        {
            base.InitTransform();
            // Legacy Code
            Scale.X = 10; Scale.Y = 10;
        }
        /// <summary>
        /// X축 기준으로 90 회전 시킴
        /// </summary>
        /// 

        public override void Update()
        {
            Matrix mPos = Matrix.Translation(Position);
            Matrix mRot = Matrix.RotationX(90);
            Matrix mScale = Matrix.Scaling(Scale);

            // W = S * R * T
            World = mScale * mRot * mPos;
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
    }
}
