using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using GraphicControl;
using GraphicControl.DrawObject;



namespace RobotControllerUI
{
    public partial class InteractiveUI : Form
    {

        private List<Spot> SpotList;
        private List<Spot> HazardList;
        private Spot MapSize;

        /// <summary>
        /// View의 프레임을 조절하는 타이머
        /// </summary>
        private FrameTimer VeiwFrameTimer;
         
        public InteractiveUI()
        {
            InitializeComponent();
            
        }

        private void GraphicView_Paint(object sender, PaintEventArgs e)
        {
            //flickering 문제 때문에 수정
           // GraphicManager.GetManager().Render();
        }
        /// <summary>
        /// Load 되었을때 >> Aplication Init();
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void InteractiveUI_Load(object sender, EventArgs e)
        {
            if (!GraphicManager.GetManager().InitDX(this.GraphicView))
            {
                MessageBox.Show("Could not initialize Direct3D.");
            
            }
            GraphicManager.GetManager().RenderInit();

      
            //60프레임으로 고정
            VeiwFrameTimer = new FrameTimer(500);
            VeiwFrameTimer.AddTickEvent(() =>
                {
                    GraphicManager.GetManager().Render();
                 
                });
            VeiwFrameTimer.Start();


            SpotList = new List<Spot>();
            HazardList = new List<Spot>();

        }
       

        /// <summary>
        /// Test용 Robot UP 함수
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Upbtn_Click(object sender, EventArgs e)
        {
            GraphicManager.GetManager().MoveRobot(ModelMoveController.UP);
           
            
        }
        /// <summary>
        /// Test용 Robot Down 함수
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void DownBtn_Click(object sender, EventArgs e)
        {
            GraphicManager.GetManager().MoveRobot(ModelMoveController.DOWN);
          
        }
        /// <summary>
        /// Test용 Robot Left 함수
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void LeftBtn_Click(object sender, EventArgs e)
        {
             GraphicManager.GetManager().MoveRobot(ModelMoveController.LEFT);
           
        }
        /// <summary>
        /// Test용 Robot Right 함수
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void RightBtn_Click(object sender, EventArgs e)
        {
            GraphicManager.GetManager().MoveRobot(ModelMoveController.RIGHT);
      
        }
        /// <summary>
        /// List 에 아이템을 추가하는 함수
        /// </summary>
        /// <param name="box"> Item을 가져올 textbox</param>
        /// <param name="List">List 박스</param>
        /// <param name="RealList">실제 리스트</param>
        private void HandleAddItemToList(TextBox box, ListBox List, List<Spot> RealList)
        {
            if (box.Text == null) return;
            string StringItem = box.Text;

            Spot NewSpot = new RobotControllerUI.Spot(StringItem);

            RealList.Add(NewSpot);

            List.DataSource = null;
            List.DataSource = RealList;
            box.Text = null;
        }
        /// <summary>
        /// ListBox 에서 아이템을 지우는 함수
        /// </summary>
        /// <param name="RealList"></param>
        /// <param name="LBox"></param>
        private void HandleDeleteItemToList(List<Spot> RealList, ListBox LBox)
        {
            int SelectedIndex = LBox.SelectedIndex;

            try
            {
                RealList.RemoveAt(SelectedIndex);
            }
            catch
            { }

            LBox.DataSource = null;
            LBox.DataSource = RealList;

        }
        /// <summary>
        /// SearchSpot 추가 버튼 이벤트
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void SpotAddBtn_Click(object sender, EventArgs e)
        {

            HandleAddItemToList(SpotTextBox, SpotListBox, SpotList);
            
        }

        /// <summary>
        /// Hazard 추가 버튼 이벤트
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void HarzardAddBtn_Click(object sender, EventArgs e)
        {
            HandleAddItemToList(HazardTxtBox,HazardListBox, HazardList);
        }
        
         
        private void SpotDeleteBtn_Click(object sender, EventArgs e)
        {
            HandleDeleteItemToList(SpotList, SpotListBox);
        }

        private void HarzardDeletetn_Click(object sender, EventArgs e)
        {
            HandleDeleteItemToList(HazardList, HazardListBox);
        }
        /// <summary>
        /// Map 생성 버튼
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void InputMapBtn_Click(object sender, EventArgs e)
        {
            MapLoadDialog MapLoader = new MapLoadDialog();

            var Result =  MapLoader.ShowDialog();
            if (Result == DialogResult.OK)
            {
                //Map Size Load
                MapSizeLoad(MapLoader.XMax, MapLoader.YMax);
                //HazardList 추가
                AddLoadedHazard(MapLoader.LoadedHazardList);

                //SpotList 추가
                AddSearchSpotList(MapLoader.LoadedSearchSpotList);

                string path = MapLoader.ImageFile;
                MapMiniView.Load(@path);
                MapMiniView.SizeMode = PictureBoxSizeMode.StretchImage;

                
                GraphicManager.GetManager().MapLoad(MapLoader.XMax , MapLoader.YMax);
            }
        }
        private void MapSizeLoad(float xmax, float ymax)
        {
            MapSize = new Spot(xmax, ymax);
            MapTxtInput.Text = MapSize.ToString();
        }

        /// <summary>
        /// Map에서 읽어온 HazardList 처리
        /// </summary>
        /// <param name="LoadSpot"></param>
        private void AddLoadedHazard(List<Spot> LoadSpot)
        {
            if (LoadSpot == null || LoadSpot.Count == 0) return;
            HazardList.AddRange(LoadSpot);
            HazardListBox.DataSource = null;
            HazardListBox.DataSource = HazardList;
        }
        /// <summary>
        /// Map에서 읽어온 SpotList 처리
        /// </summary>
        /// <param name="LoadedSerach"></param>
        private void AddSearchSpotList(List<Spot> LoadedSerach)
        {
            if (LoadedSerach == null || LoadedSerach.Count == 0) return;
            SpotList.AddRange(LoadedSerach);
            SpotListBox.DataSource = null;
            SpotListBox.DataSource = SpotList;
        } 
        /// <summary>
        /// Start버튼 눌렀으때
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void StartBtn_Click(object sender, EventArgs e)
        {
            foreach (Spot s in HazardList)
            {
                GraphicManager.GetManager().CreateHazard(s.x, s.y);
            }
        }
    }
}
