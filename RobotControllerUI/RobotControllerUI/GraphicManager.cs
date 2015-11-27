using System;
using System.Drawing;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using RobotControllerUI.DrawObject;

namespace RobotControllerUI
{
    /// <summary>
    /// DirectX Device를 가지고 있는 그리기 전용 클래스
    /// 싱글톤 클래스
    /// </summary>
    public class GraphicManager
    {
        MySprite TestSprite;

        private Device dx_Device = null;
        private static GraphicManager Instance = null;

        /// <summary>
        /// 싱글톤 클래스 접근자
        /// </summary>
        /// <returns>인스턴스 반환</returns>
        public static GraphicManager GetManager()
        {
            if (Instance == null)
            {
                Instance = new GraphicManager();
            }
            return Instance;
        }

        private GraphicManager() { }


        /// <summary>
        /// 다이렉트 X 초기화 함수
        /// </summary>
        /// <param name="hViewControl"> DirectX를 이용해서 Draw할 Control</param>
        public bool InitDX(Control hViewControl)
        {
            try
            {
                PresentParameters pp = new PresentParameters();
                pp.Windowed = true;
                pp.SwapEffect = SwapEffect.Discard;
                pp.EnableAutoDepthStencil = true;
                pp.AutoDepthStencilFormat = DepthFormat.D16;

                dx_Device = new Device(0, DeviceType.Hardware, hViewControl,
                                        CreateFlags.SoftwareVertexProcessing, pp);
                return true;
            }
            catch (Exception)
            {
                return false;
            } 
        }
        /// <summary>
        /// Object들을 그리는 Render함수 등록된 Object들을 그리게 할것
        /// </summary>
        private void ObjectsRender()
        { }
        /// <summary>
        /// Object들의 동작처리
        /// </summary>
        private void ObjectAction()
        { }
        /// <summary>
        /// Rendering 초기화작업
        /// </summary>
        public void RenderInit()
        {
            TestSprite = new MySprite(dx_Device);
            TestSprite.TextureLoad("Memo.jpg");
        }
        public void Render()
        {
            //배경 클리어
            dx_Device.Clear(ClearFlags.Target,
                            System.Drawing.Color.FromArgb(0,0, 255).ToArgb(),
                            1.0f,
                            0);
            //Depth 클리어

            dx_Device.Clear(ClearFlags.ZBuffer, 0, 1.0f, 0);
            OnResetDevice(dx_Device, null);
            dx_Device.BeginScene();
           
            dx_Device.Transform.View = Matrix.LookAtLH(
                new Vector3(0.0f , 3.0f , -5.0f),
                new Vector3(0.0f, 0.0f, 0.0f),
                new Vector3(0.0f, 1.0f, 0.0f)
                );

            dx_Device.Transform.Projection = Matrix.PerspectiveFovLH(
                (float)Math.PI / 4,
                1.0f,
                1.0f,
                100.0f);

            //Object 동작 처리
       
            // Object들 그리기
            TestSprite.Render();

            dx_Device.EndScene();
            dx_Device.Present();
        }
        /// <summary>
        /// 랜더링 상대를 결정함
        /// </summary>
        /// <param name="Sender"> Device</param>
        /// <param name="e"></param>
        public void OnResetDevice(object Sender, EventArgs e)
        {
            Device dev = (Device)Sender;
            dev.RenderState.CullMode = Cull.None;
            dev.RenderState.Lighting = false;
            dev.RenderState.ZBufferEnable = true;
            
        }
    }
}