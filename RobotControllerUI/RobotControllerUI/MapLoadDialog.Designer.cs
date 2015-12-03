namespace RobotControllerUI
{
    partial class MapLoadDialog
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.MapPreview = new System.Windows.Forms.PictureBox();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.XTbox = new System.Windows.Forms.TextBox();
            this.YTBox = new System.Windows.Forms.TextBox();
            this.HazardTBox = new System.Windows.Forms.TextBox();
            this.ImportantTBox = new System.Windows.Forms.TextBox();
            this.LoadBtn = new System.Windows.Forms.Button();
            this.CancleBtn = new System.Windows.Forms.Button();
            this.OkBtn = new System.Windows.Forms.Button();
            this.FilePathTBox = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.MapPreview)).BeginInit();
            this.SuspendLayout();
            // 
            // MapPreview
            // 
            this.MapPreview.Location = new System.Drawing.Point(12, 12);
            this.MapPreview.Name = "MapPreview";
            this.MapPreview.Size = new System.Drawing.Size(321, 323);
            this.MapPreview.TabIndex = 0;
            this.MapPreview.TabStop = false;
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(348, 39);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(36, 15);
            this.label1.TabIndex = 1;
            this.label1.Text = "Size";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(348, 89);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 15);
            this.label2.TabIndex = 2;
            this.label2.Text = "Hazard";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(348, 145);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(66, 15);
            this.label3.TabIndex = 3;
            this.label3.Text = "Important";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(433, 12);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(16, 15);
            this.label4.TabIndex = 4;
            this.label4.Text = "X";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(510, 12);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(15, 15);
            this.label5.TabIndex = 5;
            this.label5.Text = "Y";
            // 
            // XTbox
            // 
            this.XTbox.Location = new System.Drawing.Point(415, 36);
            this.XTbox.Name = "XTbox";
            this.XTbox.ReadOnly = true;
            this.XTbox.Size = new System.Drawing.Size(52, 25);
            this.XTbox.TabIndex = 6;
            // 
            // YTBox
            // 
            this.YTBox.Location = new System.Drawing.Point(492, 36);
            this.YTBox.Name = "YTBox";
            this.YTBox.ReadOnly = true;
            this.YTBox.Size = new System.Drawing.Size(52, 25);
            this.YTBox.TabIndex = 7;
            // 
            // HazardTBox
            // 
            this.HazardTBox.Location = new System.Drawing.Point(415, 86);
            this.HazardTBox.Name = "HazardTBox";
            this.HazardTBox.ReadOnly = true;
            this.HazardTBox.Size = new System.Drawing.Size(129, 25);
            this.HazardTBox.TabIndex = 8;
            // 
            // ImportantTBox
            // 
            this.ImportantTBox.Location = new System.Drawing.Point(415, 142);
            this.ImportantTBox.Name = "ImportantTBox";
            this.ImportantTBox.ReadOnly = true;
            this.ImportantTBox.Size = new System.Drawing.Size(129, 25);
            this.ImportantTBox.TabIndex = 9;
            // 
            // LoadBtn
            // 
            this.LoadBtn.Location = new System.Drawing.Point(469, 231);
            this.LoadBtn.Name = "LoadBtn";
            this.LoadBtn.Size = new System.Drawing.Size(75, 23);
            this.LoadBtn.TabIndex = 10;
            this.LoadBtn.Text = "불러오기";
            this.LoadBtn.UseVisualStyleBackColor = true;
            this.LoadBtn.Click += new System.EventHandler(this.LoadBtn_Click);
            // 
            // CancleBtn
            // 
            this.CancleBtn.Location = new System.Drawing.Point(469, 307);
            this.CancleBtn.Name = "CancleBtn";
            this.CancleBtn.Size = new System.Drawing.Size(75, 23);
            this.CancleBtn.TabIndex = 11;
            this.CancleBtn.Text = "취소";
            this.CancleBtn.UseVisualStyleBackColor = true;
            this.CancleBtn.Click += new System.EventHandler(this.CancleBtn_Click);
            // 
            // OkBtn
            // 
            this.OkBtn.Location = new System.Drawing.Point(363, 307);
            this.OkBtn.Name = "OkBtn";
            this.OkBtn.Size = new System.Drawing.Size(75, 23);
            this.OkBtn.TabIndex = 12;
            this.OkBtn.Text = "확인";
            this.OkBtn.UseVisualStyleBackColor = true;
            this.OkBtn.Click += new System.EventHandler(this.OkBtn_Click);
            // 
            // FilePathTBox
            // 
            this.FilePathTBox.Location = new System.Drawing.Point(351, 200);
            this.FilePathTBox.Name = "FilePathTBox";
            this.FilePathTBox.ReadOnly = true;
            this.FilePathTBox.Size = new System.Drawing.Size(195, 25);
            this.FilePathTBox.TabIndex = 13;
            // 
            // MapLoadDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(565, 350);
            this.Controls.Add(this.FilePathTBox);
            this.Controls.Add(this.OkBtn);
            this.Controls.Add(this.CancleBtn);
            this.Controls.Add(this.LoadBtn);
            this.Controls.Add(this.ImportantTBox);
            this.Controls.Add(this.HazardTBox);
            this.Controls.Add(this.YTBox);
            this.Controls.Add(this.XTbox);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.MapPreview);
            this.Name = "MapLoadDialog";
            this.Text = "MapLoadDialog";
            ((System.ComponentModel.ISupportInitialize)(this.MapPreview)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox MapPreview;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox XTbox;
        private System.Windows.Forms.TextBox YTBox;
        private System.Windows.Forms.TextBox HazardTBox;
        private System.Windows.Forms.TextBox ImportantTBox;
        private System.Windows.Forms.Button LoadBtn;
        private System.Windows.Forms.Button CancleBtn;
        private System.Windows.Forms.Button OkBtn;
        private System.Windows.Forms.TextBox FilePathTBox;
    }
}