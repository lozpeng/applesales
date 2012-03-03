namespace HYMain
{
    partial class SymbolSelForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SymbolSelForm));
            this.symColor = new DevExpress.XtraEditors.ColorEdit();
            this.otherColor = new DevExpress.XtraEditors.ColorEdit();
            this.labelOne = new DevExpress.XtraEditors.LabelControl();
            this.labelTwo = new DevExpress.XtraEditors.LabelControl();
            this.labelThree = new DevExpress.XtraEditors.LabelControl();
            this.preViewPic = new DevExpress.XtraEditors.PictureEdit();
            this.simpleButton1 = new DevExpress.XtraEditors.SimpleButton();
            this.btnOK = new DevExpress.XtraEditors.SimpleButton();
            this.btnCancel = new DevExpress.XtraEditors.SimpleButton();
            this.otherSize = new DevExpress.XtraEditors.SpinEdit();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.symSize = new DevExpress.XtraEditors.SpinEdit();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            ((System.ComponentModel.ISupportInitialize)(this.symColor.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.otherColor.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.preViewPic.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.otherSize.Properties)).BeginInit();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.symSize.Properties)).BeginInit();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // axSymbologyControl1
            // 
            // 
            // symColor
            // 
            this.symColor.EditValue = System.Drawing.Color.Empty;
            this.symColor.Location = new System.Drawing.Point(91, 141);
            this.symColor.Name = "symColor";
            this.symColor.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.symColor.Properties.ColorAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.symColor.Size = new System.Drawing.Size(100, 21);
            this.symColor.TabIndex = 1;
            this.symColor.EditValueChanged += new System.EventHandler(this.symColor_EditValueChanged);
            // 
            // otherColor
            // 
            this.otherColor.EditValue = System.Drawing.Color.Empty;
            this.otherColor.Location = new System.Drawing.Point(91, 211);
            this.otherColor.Name = "otherColor";
            this.otherColor.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.otherColor.Properties.ColorAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.otherColor.Size = new System.Drawing.Size(100, 21);
            this.otherColor.TabIndex = 2;
            this.otherColor.EditValueChanged += new System.EventHandler(this.otherColor_EditValueChanged);
            // 
            // labelOne
            // 
            this.labelOne.Location = new System.Drawing.Point(15, 141);
            this.labelOne.Name = "labelOne";
            this.labelOne.Size = new System.Drawing.Size(70, 14);
            this.labelOne.TabIndex = 3;
            this.labelOne.Text = "labelControl1";
            // 
            // labelTwo
            // 
            this.labelTwo.Location = new System.Drawing.Point(15, 173);
            this.labelTwo.Name = "labelTwo";
            this.labelTwo.Size = new System.Drawing.Size(70, 14);
            this.labelTwo.TabIndex = 4;
            this.labelTwo.Text = "labelControl2";
            // 
            // labelThree
            // 
            this.labelThree.Location = new System.Drawing.Point(15, 214);
            this.labelThree.Name = "labelThree";
            this.labelThree.Size = new System.Drawing.Size(70, 14);
            this.labelThree.TabIndex = 5;
            this.labelThree.Text = "labelControl3";
            // 
            // preViewPic
            // 
            this.preViewPic.Location = new System.Drawing.Point(15, 26);
            this.preViewPic.Name = "preViewPic";
            this.preViewPic.Size = new System.Drawing.Size(176, 89);
            this.preViewPic.TabIndex = 7;
            // 
            // simpleButton1
            // 
            this.simpleButton1.Location = new System.Drawing.Point(27, 264);
            this.simpleButton1.Name = "simpleButton1";
            this.simpleButton1.Size = new System.Drawing.Size(164, 23);
            this.simpleButton1.TabIndex = 8;
            this.simpleButton1.Text = "添加符号";
            // 
            // btnOK
            // 
            this.btnOK.Location = new System.Drawing.Point(27, 321);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(68, 23);
            this.btnOK.TabIndex = 9;
            this.btnOK.Text = "确定";
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.Location = new System.Drawing.Point(116, 321);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(75, 23);
            this.btnCancel.TabIndex = 10;
            this.btnCancel.Text = "取消";
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // otherSize
            // 
            this.otherSize.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.otherSize.Location = new System.Drawing.Point(91, 237);
            this.otherSize.Name = "otherSize";
            this.otherSize.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.otherSize.Properties.MaxValue = new decimal(new int[] {
            180,
            0,
            0,
            0});
            this.otherSize.Properties.MinValue = new decimal(new int[] {
            180,
            0,
            0,
            -2147483648});
            this.otherSize.Size = new System.Drawing.Size(100, 21);
            this.otherSize.TabIndex = 11;
            this.otherSize.EditValueChanged += new System.EventHandler(this.otherSize_EditValueChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.symSize);
            this.groupBox1.Controls.Add(this.preViewPic);
            this.groupBox1.Controls.Add(this.otherSize);
            this.groupBox1.Controls.Add(this.symColor);
            this.groupBox1.Controls.Add(this.btnCancel);
            this.groupBox1.Controls.Add(this.otherColor);
            this.groupBox1.Controls.Add(this.btnOK);
            this.groupBox1.Controls.Add(this.labelOne);
            this.groupBox1.Controls.Add(this.simpleButton1);
            this.groupBox1.Controls.Add(this.labelTwo);
            this.groupBox1.Controls.Add(this.labelThree);
            this.groupBox1.Location = new System.Drawing.Point(355, 24);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(204, 358);
            this.groupBox1.TabIndex = 12;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "属性";
            // 
            // symSize
            // 
            this.symSize.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.symSize.Location = new System.Drawing.Point(91, 170);
            this.symSize.Name = "symSize";
            this.symSize.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.symSize.Properties.MaxValue = new decimal(new int[] {
            180,
            0,
            0,
            0});
            this.symSize.Properties.MinValue = new decimal(new int[] {
            180,
            0,
            0,
            -2147483648});
            this.symSize.Size = new System.Drawing.Size(100, 21);
            this.symSize.TabIndex = 12;
            // 
            // groupBox2
            // 
            this.groupBox2.Location = new System.Drawing.Point(12, 24);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(337, 358);
            this.groupBox2.TabIndex = 13;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "符号选择";
            // 
            // SymbolSelForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 14F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(584, 400);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "SymbolSelForm";
            this.Text = "SymbolSelForm";
            this.Load += new System.EventHandler(this.SymbolSelForm_Load);

            ((System.ComponentModel.ISupportInitialize)(this.symColor.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.otherColor.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.preViewPic.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.otherSize.Properties)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.symSize.Properties)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private DevExpress.XtraEditors.ColorEdit symColor;
        private DevExpress.XtraEditors.ColorEdit otherColor;
        private DevExpress.XtraEditors.LabelControl labelOne;
        private DevExpress.XtraEditors.LabelControl labelTwo;
        private DevExpress.XtraEditors.LabelControl labelThree;
        private DevExpress.XtraEditors.PictureEdit preViewPic;
        private DevExpress.XtraEditors.SimpleButton simpleButton1;
        private DevExpress.XtraEditors.SimpleButton btnOK;
        private DevExpress.XtraEditors.SimpleButton btnCancel;
        private DevExpress.XtraEditors.SpinEdit otherSize;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private DevExpress.XtraEditors.SpinEdit symSize;
    }
}