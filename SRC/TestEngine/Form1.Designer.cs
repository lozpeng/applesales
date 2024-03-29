﻿namespace TestEngine
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.AddShp = new System.Windows.Forms.ToolStripButton();
            this.MapPan = new System.Windows.Forms.ToolStripButton();
            this.ZoomIn = new System.Windows.Forms.ToolStripButton();
            this.ZoomOut = new System.Windows.Forms.ToolStripButton();
            this.axusMapControl1 = new AxusMapControlLib.AxusMapControl();
            this.AddImage = new System.Windows.Forms.ToolStripButton();
            this.toolStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.axusMapControl1)).BeginInit();
            this.SuspendLayout();
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.AddShp,
            this.AddImage,
            this.MapPan,
            this.ZoomIn,
            this.ZoomOut});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(599, 25);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // AddShp
            // 
            this.AddShp.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.AddShp.Image = ((System.Drawing.Image)(resources.GetObject("AddShp.Image")));
            this.AddShp.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.AddShp.Name = "AddShp";
            this.AddShp.Size = new System.Drawing.Size(23, 22);
            this.AddShp.Text = "加载矢量数据";
            this.AddShp.Click += new System.EventHandler(this.AddShp_Click);
            // 
            // MapPan
            // 
            this.MapPan.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.MapPan.Image = ((System.Drawing.Image)(resources.GetObject("MapPan.Image")));
            this.MapPan.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.MapPan.Name = "MapPan";
            this.MapPan.Size = new System.Drawing.Size(23, 22);
            this.MapPan.Text = "平移";
            this.MapPan.Click += new System.EventHandler(this.MapPan_Click);
            // 
            // ZoomIn
            // 
            this.ZoomIn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.ZoomIn.Image = ((System.Drawing.Image)(resources.GetObject("ZoomIn.Image")));
            this.ZoomIn.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.ZoomIn.Name = "ZoomIn";
            this.ZoomIn.Size = new System.Drawing.Size(23, 22);
            this.ZoomIn.Text = "放大";
            this.ZoomIn.Click += new System.EventHandler(this.ZoomIn_Click);
            // 
            // ZoomOut
            // 
            this.ZoomOut.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.ZoomOut.Image = ((System.Drawing.Image)(resources.GetObject("ZoomOut.Image")));
            this.ZoomOut.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.ZoomOut.Name = "ZoomOut";
            this.ZoomOut.Size = new System.Drawing.Size(23, 22);
            this.ZoomOut.Text = "缩小";
            this.ZoomOut.Click += new System.EventHandler(this.ZoomOut_Click);
            // 
            // axusMapControl1
            // 
            this.axusMapControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.axusMapControl1.Enabled = true;
            this.axusMapControl1.Location = new System.Drawing.Point(0, 25);
            this.axusMapControl1.Name = "axusMapControl1";
            this.axusMapControl1.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axusMapControl1.OcxState")));
            this.axusMapControl1.Size = new System.Drawing.Size(599, 436);
            this.axusMapControl1.TabIndex = 1;
            // 
            // AddImage
            // 
            this.AddImage.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.AddImage.Image = ((System.Drawing.Image)(resources.GetObject("AddImage.Image")));
            this.AddImage.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.AddImage.Name = "AddImage";
            this.AddImage.Size = new System.Drawing.Size(23, 22);
            this.AddImage.Text = "加载影像";
            this.AddImage.Click += new System.EventHandler(this.AddImage_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(599, 461);
            this.Controls.Add(this.axusMapControl1);
            this.Controls.Add(this.toolStrip1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.axusMapControl1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStrip toolStrip1;
        private AxusMapControlLib.AxusMapControl axusMapControl1;
        private System.Windows.Forms.ToolStripButton AddShp;
        private System.Windows.Forms.ToolStripButton MapPan;
        private System.Windows.Forms.ToolStripButton ZoomIn;
        private System.Windows.Forms.ToolStripButton ZoomOut;
        private System.Windows.Forms.ToolStripButton AddImage;

    }
}

