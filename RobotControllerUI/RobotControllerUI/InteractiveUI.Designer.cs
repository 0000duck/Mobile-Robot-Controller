namespace RobotControllerUI
{
    partial class InteractiveUI
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.InputMapBtn = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.MapTxtInput = new System.Windows.Forms.TextBox();
            this.StartTxtInput = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.SearchSpotList = new System.Windows.Forms.ListBox();
            this.HarzardList = new System.Windows.Forms.ListBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.Spot = new System.Windows.Forms.GroupBox();
            this.SpotDeleteBtn = new System.Windows.Forms.Button();
            this.SpotAddBtn = new System.Windows.Forms.Button();
            this.HarzardDeletetn = new System.Windows.Forms.Button();
            this.HarzardAddBtn = new System.Windows.Forms.Button();
            this.Hazard = new System.Windows.Forms.GroupBox();
            this.StartBtn = new System.Windows.Forms.Button();
            this.Upbtn = new System.Windows.Forms.Button();
            this.DownBtn = new System.Windows.Forms.Button();
            this.LeftBtn = new System.Windows.Forms.Button();
            this.RightBtn = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.ZoomInBtn = new System.Windows.Forms.Button();
            this.ZoomOutBtn = new System.Windows.Forms.Button();
            this.GraphicView = new RobotControllerUI.MyDxPannel();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.Spot.SuspendLayout();
            this.Hazard.SuspendLayout();
            this.SuspendLayout();
            // 
            // InputMapBtn
            // 
            this.InputMapBtn.Location = new System.Drawing.Point(719, 146);
            this.InputMapBtn.Name = "InputMapBtn";
            this.InputMapBtn.Size = new System.Drawing.Size(106, 35);
            this.InputMapBtn.TabIndex = 1;
            this.InputMapBtn.Text = "Input Map";
            this.InputMapBtn.UseVisualStyleBackColor = true;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(707, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(128, 128);
            this.pictureBox1.TabIndex = 2;
            this.pictureBox1.TabStop = false;
            // 
            // MapTxtInput
            // 
            this.MapTxtInput.Location = new System.Drawing.Point(740, 200);
            this.MapTxtInput.Name = "MapTxtInput";
            this.MapTxtInput.Size = new System.Drawing.Size(100, 25);
            this.MapTxtInput.TabIndex = 3;
            // 
            // StartTxtInput
            // 
            this.StartTxtInput.Location = new System.Drawing.Point(740, 238);
            this.StartTxtInput.Name = "StartTxtInput";
            this.StartTxtInput.Size = new System.Drawing.Size(100, 25);
            this.StartTxtInput.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(681, 203);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 15);
            this.label1.TabIndex = 7;
            this.label1.Text = "Map";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(681, 241);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 15);
            this.label2.TabIndex = 8;
            this.label2.Text = "Strart";
            // 
            // SearchSpotList
            // 
            this.SearchSpotList.FormattingEnabled = true;
            this.SearchSpotList.HorizontalScrollbar = true;
            this.SearchSpotList.ItemHeight = 15;
            this.SearchSpotList.Location = new System.Drawing.Point(60, 50);
            this.SearchSpotList.MultiColumn = true;
            this.SearchSpotList.Name = "SearchSpotList";
            this.SearchSpotList.Size = new System.Drawing.Size(100, 49);
            this.SearchSpotList.TabIndex = 11;
            // 
            // HarzardList
            // 
            this.HarzardList.FormattingEnabled = true;
            this.HarzardList.ItemHeight = 15;
            this.HarzardList.Location = new System.Drawing.Point(59, 49);
            this.HarzardList.Name = "HarzardList";
            this.HarzardList.Size = new System.Drawing.Size(100, 49);
            this.HarzardList.TabIndex = 12;
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(60, 19);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 25);
            this.textBox1.TabIndex = 13;
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(59, 20);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(100, 25);
            this.textBox2.TabIndex = 14;
            // 
            // Spot
            // 
            this.Spot.Controls.Add(this.SpotDeleteBtn);
            this.Spot.Controls.Add(this.SpotAddBtn);
            this.Spot.Controls.Add(this.textBox1);
            this.Spot.Controls.Add(this.SearchSpotList);
            this.Spot.Location = new System.Drawing.Point(679, 265);
            this.Spot.Name = "Spot";
            this.Spot.Size = new System.Drawing.Size(194, 110);
            this.Spot.TabIndex = 15;
            this.Spot.TabStop = false;
            this.Spot.Text = "Spot";
            // 
            // SpotDeleteBtn
            // 
            this.SpotDeleteBtn.Location = new System.Drawing.Point(165, 50);
            this.SpotDeleteBtn.Name = "SpotDeleteBtn";
            this.SpotDeleteBtn.Size = new System.Drawing.Size(23, 23);
            this.SpotDeleteBtn.TabIndex = 17;
            this.SpotDeleteBtn.Text = "-";
            this.SpotDeleteBtn.UseVisualStyleBackColor = true;
            // 
            // SpotAddBtn
            // 
            this.SpotAddBtn.Location = new System.Drawing.Point(165, 19);
            this.SpotAddBtn.Name = "SpotAddBtn";
            this.SpotAddBtn.Size = new System.Drawing.Size(23, 23);
            this.SpotAddBtn.TabIndex = 16;
            this.SpotAddBtn.Text = "+";
            this.SpotAddBtn.UseVisualStyleBackColor = true;
            // 
            // HarzardDeletetn
            // 
            this.HarzardDeletetn.Location = new System.Drawing.Point(164, 51);
            this.HarzardDeletetn.Name = "HarzardDeletetn";
            this.HarzardDeletetn.Size = new System.Drawing.Size(23, 23);
            this.HarzardDeletetn.TabIndex = 19;
            this.HarzardDeletetn.Text = "-";
            this.HarzardDeletetn.UseVisualStyleBackColor = true;
            // 
            // HarzardAddBtn
            // 
            this.HarzardAddBtn.Location = new System.Drawing.Point(164, 20);
            this.HarzardAddBtn.Name = "HarzardAddBtn";
            this.HarzardAddBtn.Size = new System.Drawing.Size(23, 23);
            this.HarzardAddBtn.TabIndex = 18;
            this.HarzardAddBtn.Text = "+";
            this.HarzardAddBtn.UseVisualStyleBackColor = true;
            // 
            // Hazard
            // 
            this.Hazard.Controls.Add(this.HarzardDeletetn);
            this.Hazard.Controls.Add(this.HarzardAddBtn);
            this.Hazard.Controls.Add(this.textBox2);
            this.Hazard.Controls.Add(this.HarzardList);
            this.Hazard.Location = new System.Drawing.Point(681, 387);
            this.Hazard.Name = "Hazard";
            this.Hazard.Size = new System.Drawing.Size(192, 113);
            this.Hazard.TabIndex = 20;
            this.Hazard.TabStop = false;
            this.Hazard.Text = "Hazard";
            // 
            // StartBtn
            // 
            this.StartBtn.Location = new System.Drawing.Point(740, 515);
            this.StartBtn.Name = "StartBtn";
            this.StartBtn.Size = new System.Drawing.Size(75, 23);
            this.StartBtn.TabIndex = 21;
            this.StartBtn.Text = "Start";
            this.StartBtn.UseVisualStyleBackColor = true;
            // 
            // Upbtn
            // 
            this.Upbtn.Location = new System.Drawing.Point(12, 544);
            this.Upbtn.Name = "Upbtn";
            this.Upbtn.Size = new System.Drawing.Size(39, 34);
            this.Upbtn.TabIndex = 22;
            this.Upbtn.Text = "Up";
            this.Upbtn.UseVisualStyleBackColor = true;
            this.Upbtn.Click += new System.EventHandler(this.Upbtn_Click);
            // 
            // DownBtn
            // 
            this.DownBtn.Location = new System.Drawing.Point(57, 544);
            this.DownBtn.Name = "DownBtn";
            this.DownBtn.Size = new System.Drawing.Size(56, 34);
            this.DownBtn.TabIndex = 23;
            this.DownBtn.Text = "Down";
            this.DownBtn.UseVisualStyleBackColor = true;
            this.DownBtn.Click += new System.EventHandler(this.DownBtn_Click);
            // 
            // LeftBtn
            // 
            this.LeftBtn.Location = new System.Drawing.Point(119, 544);
            this.LeftBtn.Name = "LeftBtn";
            this.LeftBtn.Size = new System.Drawing.Size(56, 34);
            this.LeftBtn.TabIndex = 24;
            this.LeftBtn.Text = "Left";
            this.LeftBtn.UseVisualStyleBackColor = true;
            this.LeftBtn.Click += new System.EventHandler(this.LeftBtn_Click);
            // 
            // RightBtn
            // 
            this.RightBtn.Location = new System.Drawing.Point(181, 544);
            this.RightBtn.Name = "RightBtn";
            this.RightBtn.Size = new System.Drawing.Size(56, 34);
            this.RightBtn.TabIndex = 25;
            this.RightBtn.Text = "Right";
            this.RightBtn.UseVisualStyleBackColor = true;
            this.RightBtn.Click += new System.EventHandler(this.RightBtn_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(284, 554);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(56, 15);
            this.label3.TabIndex = 26;
            this.label3.Text = "Camera";
            // 
            // ZoomInBtn
            // 
            this.ZoomInBtn.Location = new System.Drawing.Point(357, 550);
            this.ZoomInBtn.Name = "ZoomInBtn";
            this.ZoomInBtn.Size = new System.Drawing.Size(75, 23);
            this.ZoomInBtn.TabIndex = 27;
            this.ZoomInBtn.Text = "ZoomIn";
            this.ZoomInBtn.UseVisualStyleBackColor = true;
            // 
            // ZoomOutBtn
            // 
            this.ZoomOutBtn.Location = new System.Drawing.Point(438, 550);
            this.ZoomOutBtn.Name = "ZoomOutBtn";
            this.ZoomOutBtn.Size = new System.Drawing.Size(84, 23);
            this.ZoomOutBtn.TabIndex = 28;
            this.ZoomOutBtn.Text = "ZoomOut";
            this.ZoomOutBtn.UseVisualStyleBackColor = true;
            // 
            // GraphicView
            // 
            this.GraphicView.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.GraphicView.Location = new System.Drawing.Point(2, 3);
            this.GraphicView.Name = "GraphicView";
            this.GraphicView.Size = new System.Drawing.Size(671, 535);
            this.GraphicView.TabIndex = 0;
            this.GraphicView.Paint += new System.Windows.Forms.PaintEventHandler(this.GraphicView_Paint);
            // 
            // InteractiveUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(885, 590);
            this.Controls.Add(this.ZoomOutBtn);
            this.Controls.Add(this.ZoomInBtn);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.RightBtn);
            this.Controls.Add(this.LeftBtn);
            this.Controls.Add(this.DownBtn);
            this.Controls.Add(this.Upbtn);
            this.Controls.Add(this.StartBtn);
            this.Controls.Add(this.Hazard);
            this.Controls.Add(this.Spot);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.StartTxtInput);
            this.Controls.Add(this.MapTxtInput);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.InputMapBtn);
            this.Controls.Add(this.GraphicView);
            this.Name = "InteractiveUI";
            this.Text = "AddON";
            this.Load += new System.EventHandler(this.InteractiveUI_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.Spot.ResumeLayout(false);
            this.Spot.PerformLayout();
            this.Hazard.ResumeLayout(false);
            this.Hazard.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button InputMapBtn;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.TextBox MapTxtInput;
        private System.Windows.Forms.TextBox StartTxtInput;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ListBox SearchSpotList;
        private System.Windows.Forms.ListBox HarzardList;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.GroupBox Spot;
        private System.Windows.Forms.Button SpotDeleteBtn;
        private System.Windows.Forms.Button SpotAddBtn;
        private System.Windows.Forms.Button HarzardDeletetn;
        private System.Windows.Forms.Button HarzardAddBtn;
        private System.Windows.Forms.GroupBox Hazard;
        private System.Windows.Forms.Button StartBtn;
        private System.Windows.Forms.Button Upbtn;
        private System.Windows.Forms.Button DownBtn;
        private System.Windows.Forms.Button LeftBtn;
        private System.Windows.Forms.Button RightBtn;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button ZoomInBtn;
        private System.Windows.Forms.Button ZoomOutBtn;
        private MyDxPannel GraphicView;
    }
}

