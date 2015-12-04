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
       
        private int modelname;
        public int ModelName
        {
            protected set { modelname = value; }
            get { return modelname; }
        }

     
        /// <summary>
        /// 생성자
        /// </summary>
        /// <param name="dev">device</param>
        public ModelForDraw(Device dev , int name) : base(dev)
        {

           // GraphicManager.GetManager().AddDrawObbject(this);
            ModelName = name;
        }
        public override void Render()
        {
            if (bVisiblity == false) return;

            SetVB();
           
            dev.DrawPrimitives(PrimitiveType.TriangleStrip, 0, 2);
            ReleaseTextureSetting();
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
