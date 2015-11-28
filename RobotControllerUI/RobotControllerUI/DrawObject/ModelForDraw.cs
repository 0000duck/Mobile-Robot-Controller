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
    /// 실제로 그려지는 오브젝트들의 Base클래스
    /// </summary>
    public class ModelForDraw : MySprite
    {
        /// <summary>
        /// 가시성>> 밝혀진 오브젝트인가?
        /// </summary>
        public bool bVisiblity = true;
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
