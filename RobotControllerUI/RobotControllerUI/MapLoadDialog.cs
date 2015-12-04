using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RobotControllerUI
{
    public partial class MapLoadDialog : Form
    {
        Bitmap map;
        string imagefile;
        public List<Spot> LoadedHazardList;
        public string ImageFile
        {
            get
            {
                return imagefile;
            }
            set
            {
                imagefile = value;
                OnFilePathChange();
            }
        } 


        /// <summary>
        ///Map 의 속성
        /// </summary>
        public int XMax { get; protected set; }
        public int YMax { get; protected set; }

        public int HazardCnt = 0;
        public int ImportantCnt = 0;


        public MapLoadDialog()
        {
            InitializeComponent();
            LoadedHazardList = new List<Spot>();
        }
        /// <summary>
        /// ImageFile 탐색 버튼
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void LoadBtn_Click(object sender, EventArgs e)
        {
            DialogResult result = openFileDialog1.ShowDialog();
            if (result == DialogResult.OK)
            {
                ImageFile = openFileDialog1.FileName;
                FilePathTBox.Text = ImageFile;
            }
  
        }
        /// <summary>
        /// ImageFile 변수가 변경될때 호출
        /// </summary>
        private void OnFilePathChange()
        {
            if (map != null) map.Dispose();

            map = new Bitmap(ImageFile);
            //MapPreview.Load(@ImageFile);
            MapPreview.Image = map;
            MapPreview.SizeMode = PictureBoxSizeMode.StretchImage;
            MapAnalysis();
        }
        /// <summary>
        /// Map 분석(Harzard와 맵크기를 찾아냄) 
        /// </summary>
        private void MapAnalysis()
        {
            XMax = map.Size.Width;
            YMax = map.Size.Height;
            HazardCnt = 0;

            for (int x = 0; x < XMax; x++)
            {
                for (int y = 0; y < YMax; y++)
                {
                    // y가 0베이스
                     Color col =  map.GetPixel(x, YMax-y-1);
                    if (col.R > 240
                        && col.G < 60
                        && col.B < 60)
                    {
                        HazardCnt++;
                        LoadedHazardList.Add(new Spot(x, y));
                    }

                    else if (col.G > 240
                        && col.R < 60
                        && col.B < 60)
                        ImportantCnt++;

                }
            }

            HazardTBox.Text = HazardCnt.ToString();
            ImportantTBox.Text = ImportantCnt.ToString();
            XTbox.Text = XMax.ToString();
            YTBox.Text = YMax.ToString();
               
        }
        /// <summary>
        /// OK butoon Handle
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OkBtn_Click(object sender, EventArgs e)
        {
            if (ImageFile == null)
                return;
            DialogResult = DialogResult.OK;
            this.Close();
        }

        /// <summary>
        /// Cancle Btn Handle
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CancleBtn_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            this.Close();
        }
    }
}
