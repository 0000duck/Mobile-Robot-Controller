using System;
using System.Collections.Generic;
using System.Drawing;
using Microsoft.DirectX;
using System.Windows.Forms;
using Microsoft.DirectX.Direct3D;
using GraphicControl.DrawObject;
using System.Runtime.InteropServices;
using GraphicControl.Interface;

namespace GraphicControl
{

    /// <summary>
    /// DirectX Device를 가지고 있는 그리기 전용 클래스
    /// 싱글톤 클래스
    /// </summary>
  
    public class GraphicManager 
    {
        Camera MainCamera;

        ModelManager DrawModelManager;
        DrawObj RobotObj;
        ModelMoveController RobotMover;

        MapforDraw Map;

        Grid BasicGrid;
        private Device dx_Device = null;
        private static GraphicManager Instance = null;
        protected List<DrawObj> DrawObjectList;
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
            DrawObjectList = new List<DrawObj>();
            
        }

        /// <summary>
        /// Draw Object를 추가 한다.
        /// </summary>
        /// <param name="obj"></param>
        public void AddDrawObbject(DrawObj obj)
        {
            if (obj == null) return;

            DrawObjectList.Add(obj);

        }
        /// <summary>
        /// Robot 움직임 Callback 시작
        /// </summary>
        /// <param name="Direction">바양</param>
        public void MoveRobot(int Direction)
        {
            RobotMover.OnMove(Direction);
        }
        /// <summary>
        /// type을 받아서 객체 생성
        /// </summary>
        /// <param name="KindObj"></param>
        public void CreateObj(int KindObj , float X2d, float Y2d)
        { }
        /// <summary>
        /// 탐색이 시작됨을 알려줌
        /// </summary>
        public void Start()
        { }
        /// <summary>
        /// 탐색이 종료됨을 알려줌
        /// </summary>
        public void End()
        { }
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
            foreach (DrawObj obj in DrawObjectList)
            {
                obj.Render(DrawModelManager);
            }
        }
        /// <summary>
        /// Object들의 동작처리
        /// </summary>
        private void ObjectAction()
        {
            if (Map != null) Map.Update();

            foreach (DrawObj obj in DrawObjectList)
            {
                
                obj.Update();
            }

            RobotMover.MoveUnit();
        }
        /// <summary>
        /// Rendering 초기화작업
        /// </summary>
        public void RenderInit()
        {
            DrawModelManager = new ModelManager(dx_Device);
            DrawModelManager.CreateDrawModel(dx_Device, ModelManager.ROBOT, "Robot.dds");
            DrawModelManager.CreateDrawModel(dx_Device, ModelManager.HAZARD, "Hazard.jpg");


            RobotObj = new DrawObj(dx_Device, ModelManager.ROBOT);
            
            //움직임 초기화
            RobotMover = new ModelMoveController(RobotObj);

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


            MainCamera.CameraUpdate(RobotObj.Position);
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
            dev.RenderState.AlphaFunction = Compare.Greater;
            dev.RenderState.ReferenceAlpha = 0;


        }
        public void CreateHazard(float x, float y)
        {
            DrawObj Newobj = new DrawObj(dx_Device, ModelManager.HAZARD);
            Newobj.ObjectPosInit(new Vector3(x,0,y));
        }
    }
}