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
    public partial class InteractiveUI : Form
    {
        public InteractiveUI()
        {
            InitializeComponent();
        }

        private void GraphicView_Paint(object sender, PaintEventArgs e)
        {
            GraphicManager.GetManager().Render();
        }

        private void InteractiveUI_Load(object sender, EventArgs e)
        {
            if (!GraphicManager.GetManager().InitDX(this.GraphicView))
            {
                MessageBox.Show("Could not initialize Direct3D.");
            
            }
            GraphicManager.GetManager().RenderInit();
        }
    }
}
