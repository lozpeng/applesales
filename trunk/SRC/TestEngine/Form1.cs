using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace TestEngine
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void AddShp_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();

            dlg.Filter = "shape files (*.shp)|*.shp|All files (*.*)|*.*";


            if (dlg.ShowDialog() == DialogResult.OK)
            {
                string filename = dlg.FileName;
                axusMapControl1.AddShpfile(filename);

            }
        }

        private void MapPan_Click(object sender, EventArgs e)
        {
            axusMapControl1.CurTool = usMapControlLib.usToolType.PanTool;
        }

        private void ZoomIn_Click(object sender, EventArgs e)
        {
            axusMapControl1.CurTool = usMapControlLib.usToolType.ZoomInTool;
        }

        private void ZoomOut_Click(object sender, EventArgs e)
        {
            axusMapControl1.CurTool = usMapControlLib.usToolType.ZoomOutTool;
        }

        private void AddImage_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();

            dlg.Filter = "影像数据(*.tif;*.img;*.tiff;*.bmp)|*.tif;*.img;*.tiff;*.bmp|All Files(*.*)|*.*";


            if (dlg.ShowDialog() == DialogResult.OK)
            {
                string filename = dlg.FileName;
                axusMapControl1.AddImagefile(filename);

            }
        }
    }
}