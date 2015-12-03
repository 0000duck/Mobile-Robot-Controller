using System;
using System.Collections.Generic;
using System.Drawing;
using Microsoft.DirectX;
using System.Windows.Forms;
using Microsoft.DirectX.Direct3D;
using GraphicControl.DrawObject;

namespace GraphicControl
{
    /// <summary>
    /// DirectX Device를 가지고 있는 그리기 전용 클래스
    /// 싱글톤 클래스
    /// </summary>
    public class GraphicManager
    {
        Camera MainCamera;
       
        ModelForDraw TestSprite;
        MapforDraw Map;
        Grid BasicGrid;
        private Device dx_Device = null;
        private static GraphicManager Instance = null;
        protected List<ModelForDraw> DrawObjectList;
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

        private GraphicManager()
        {
            DrawObjectList = new List<ModelForDraw>();
        }

        /// <summary>
        /// Draw Object를 추가 한다.
        /// </summary>
        /// <param name="obj"></param>
        public void AddDrawObbject(ModelForDraw obj)
        {
            if (obj == null) return;

            DrawObjectList.Add(obj);

        }
        /// <summary>
        /// Robot 움직임 Callback 시작
        /// </summary>
        /// <param name="Direction">바양</param>
        public void OnMoveRobot(int Direction)
        {
            TestSprite.OnMove(Direction);
        }
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
        /// Object들을 그리는 Render함수 등록된 Object들을 그린다
        /// Draw순서 맵 >> Grid >> Object 유지할것
        /// </summary>
        private void ObjectsRender()
        {
            if(Map != null)Map.Render();
            if (BasicGrid != null) BasicGrid.DrawGird();
            foreach (ModelForDraw obj in DrawObjectList)
            {
                obj.Render();
            }
        }
        /// <summary>
        /// Object들의 동작처리
        /// </summary>
        private void ObjectAction()
        {
            if (Map != null) Map.Update();

            foreach (ModelForDraw obj in DrawObjectList)
            {
                
                obj.Update();
            }

            TestSprite.Update();
        }
        /// <summary>
        /// Rendering 초기화작업
        /// </summary>
        public void RenderInit()
        {
            TestSprite = new ModelForDraw(dx_Device);
            TestSprite.TextureLoad("Memo.dds" );
            //움직임 초기화
            TestSprite.MoveInit();
            MainCamera = new Camera(dx_Device);
           
        }

        public void MapLoad(int SizeX , int SizeY)
        {
            Map = new MapforDraw(dx_Device, SizeX, SizeY);
            Map.TextureLoad("Dirt.jpg");
            BasicGrid = new Grid(dx_Device, 1, 1, SizeX, SizeY, 0.01f);
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


            MainCamera.CameraUpdate(TestSprite.Position);
            dx_Device.Transform.Projection = Matrix.PerspectiveFovLH(
                (float)Math.PI / 4,
                1.0f,
                1.0f,
                1000.0f);

            //Object 동작 처리
     
            ObjectAction();

            // Object들 그리기
            ObjectsRender();
          

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
            dev.RenderState.SourceBlend = Blend.SourceAlpha;
            dev.RenderState.DestinationBlend = Blend.InvSourceAlpha;
            dev.RenderState.AlphaBlendEnable = true;
           // dev.RenderState.BlendOperation = BlendOperation.Add;

            dev.RenderState.AlphaTestEnable = true;

            
        }
    }
}