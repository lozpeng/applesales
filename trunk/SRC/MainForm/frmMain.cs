using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.IO;
using System.Diagnostics;
using DevExpress.XtraEditors;
using DevExpress.Skins;
using DevExpress.XtraBars.Ribbon;
using DevExpress.XtraBars.Ribbon.Gallery;
using DevExpress.Utils.Drawing;
using DevExpress.Utils;
using DevExpress.Tutorials.Controls;
using MapAndPageLayoutSynch;
using HYMain;

namespace DevExpress.XtraBars.Demos.RibbonSimplePad {
	public partial class frmMain : DevExpress.XtraBars.Ribbon.RibbonForm {
		public frmMain() {
			InitializeComponent();
            CreateColorPopup(popupControlContainer1);
			InitSkinGallery();
			InitFontGallery();
        }

		int documentIndex = 0;
        ColorPopup cp;
        frmReplace dlgReplace = null;
        GalleryItem fCurrentFontItem, fCurrentColorItem;
		string DocumentName { get { return string.Format("New Document {0}", documentIndex); } }
		
		private void CreateNewDocument() 
        {
			CreateNewDocument(null);
		}
      //  protected virtual void Dispose(Boolean )

        void CreateNewDocument(string fileName) 
        {
            //documentIndex++;
            //frmPad pad = new frmPad();
            //if(fileName != null) 
            //    pad.LoadDocument(fileName);
            //else 
            //    pad.DocName = DocumentName;
            //pad.MdiParent = this;
            //pad.Closed += new EventHandler(Pad_Closed);
            //pad.ShowPopupMenu += new EventHandler(Pad_ShowPopupMenu);
            //pad.Show();
            //InitNewDocument(pad.RTBMain);
		}

		void Pad_Closed(object sender, EventArgs e) 
        {
			
		}
        void Pad_ShowPopupMenu(object sender, EventArgs e) 
        {
			pmMain.ShowPopup(Control.MousePosition);
		}

		private void CreateColorPopup(PopupControlContainer container) 
        {
			cp = new ColorPopup(container, iFontColor, this);
		}
		#region File
		void idNew_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
			CreateNewDocument();
		}

		void iClose_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
		}

		void OpenFile() {
			OpenFileDialog dlg = new OpenFileDialog();
			dlg.Filter = "Rich Text Files (*.rtf)|*.rtf";
			dlg.Title = "Open";
			if (dlg.ShowDialog() == DialogResult.OK) {
				OpenFile(dlg.FileName);
			}
		}

        void OpenFile(string name) {
            CreateNewDocument(name);
            
        }

		void iOpen_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
			OpenFile();
		}

		private void iPrint_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
            XtraMessageBox.Show(this, "Note that you can use the XtraPrinting Library to print the contents of the standard RichTextBox control.\r\nFor more information, see the main XtraPrinting demo.", this.Text, MessageBoxButtons.OK, MessageBoxIcon.Information);
		}

		void iSave_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
		}
		void iSaveAs_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
		}
		private void iExit_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
			Close();
		}
		private void frmMain_Closing(object sender, System.ComponentModel.CancelEventArgs e) {
		}
		private void ribbonPageGroup1_CaptionButtonClick(object sender, DevExpress.XtraBars.Ribbon.RibbonPageGroupEventArgs e) {
			OpenFile();
		}
		#endregion
		
		#region SkinGallery
		void InitSkinGallery() {
			SimpleButton imageButton = new SimpleButton();
			foreach(SkinContainer cnt in SkinManager.Default.Skins) {
				imageButton.LookAndFeel.SetSkinStyle(cnt.SkinName);
				GalleryItem gItem = new GalleryItem();
				int groupIndex = 0;
                if(cnt.SkinName.IndexOf("Office") > -1) groupIndex = 1;
				rgbiSkins.Gallery.Groups[groupIndex].Items.Add(gItem);
				gItem.Caption = cnt.SkinName;
				
				gItem.Image = GetSkinImage(imageButton, 32, 17, 2);
				gItem.HoverImage = GetSkinImage(imageButton, 70, 36, 5);
				gItem.Caption = cnt.SkinName;
                gItem.Hint = cnt.SkinName;
                rgbiSkins.Gallery.Groups[1].Visible = false;
			}
		}
		Bitmap GetSkinImage(SimpleButton button, int width, int height, int indent) {
			Bitmap image = new Bitmap(width, height);
            using(Graphics g = Graphics.FromImage(image)) {
                StyleObjectInfoArgs info = new StyleObjectInfoArgs(new GraphicsCache(g));
			info.Bounds = new Rectangle(0, 0, width, height);
			button.LookAndFeel.Painter.GroupPanel.DrawObject(info);
			button.LookAndFeel.Painter.Border.DrawObject(info);
			info.Bounds = new Rectangle(indent, indent, width - indent * 2, height - indent * 2);
			button.LookAndFeel.Painter.Button.DrawObject(info);
            }
			return image;
		}
		private void rgbiSkins_Gallery_ItemClick(object sender, DevExpress.XtraBars.Ribbon.GalleryItemClickEventArgs e) {
			DevExpress.LookAndFeel.UserLookAndFeel.Default.SetSkinStyle(e.Item.Caption);
		}

		private void rgbiSkins_Gallery_InitDropDownGallery(object sender, DevExpress.XtraBars.Ribbon.InplaceGalleryEventArgs e) {
			e.PopupGallery.CreateFrom(rgbiSkins.Gallery);
			e.PopupGallery.AllowFilter = false;
			e.PopupGallery.ShowItemText = true;
			e.PopupGallery.ShowGroupCaption = true;
			e.PopupGallery.AllowHoverImages = false;
            foreach(GalleryItemGroup galleryGroup in e.PopupGallery.Groups)
			    foreach(GalleryItem item in galleryGroup.Items)
				    item.Image = item.HoverImage;
			e.PopupGallery.ColumnCount = 2;
			e.PopupGallery.ImageSize = new Size(70, 36);
		}
		#endregion
		#region FontGallery
		Image GetFontImage(int width, int height, string fontName, int fontSize) {
			Rectangle rect = new Rectangle(0, 0, width, height);
			Image fontImage = new Bitmap(width, height);
			try {
				using(Font fontSample = new Font(fontName, fontSize)) {
					Graphics g = Graphics.FromImage(fontImage);
					g.FillRectangle(Brushes.White, rect);
					using(StringFormat fs = new StringFormat()) {
						fs.Alignment = StringAlignment.Center;
						fs.LineAlignment = StringAlignment.Center;
						g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAlias;
						g.DrawString("Aa", fontSample, Brushes.Black, rect, fs);
						g.Dispose();
					}
				}
			}
			catch { }
			return fontImage;
		}
		void InitFont(GalleryItemGroup groupDropDown, GalleryItemGroup galleryGroup) {
			FontFamily[] fonts = FontFamily.Families;
			for(int i = 0; i < fonts.Length; i++) {
				string fontName = fonts[i].Name;
				GalleryItem item = new GalleryItem();
				item.Caption = fontName;
				item.Image = GetFontImage(32, 28, fontName, 12);
				item.HoverImage = item.Image;
				item.Description = fontName;
				item.Hint = fontName;
				try {
					item.Tag = new Font(fontName, 9);
					if(DevExpress.Utils.ControlUtils.IsSymbolFont((Font)item.Tag)) {
						item.Tag = new Font(DevExpress.Utils.AppearanceObject.DefaultFont.FontFamily, 9);
						item.Description += " (Symbol Font)";
					}
				}
				catch {
					continue;
				}
				groupDropDown.Items.Add(item);
				galleryGroup.Items.Add(item);
			}
		}
		void InitFontGallery() {
			
		}
	
		private void gddFont_Gallery_CustomDrawItemText(object sender, GalleryItemCustomDrawEventArgs e) {
			DevExpress.XtraBars.Ribbon.ViewInfo.GalleryItemViewInfo itemInfo = e.ItemInfo as DevExpress.XtraBars.Ribbon.ViewInfo.GalleryItemViewInfo;
			itemInfo.PaintAppearance.ItemDescription.DrawString(e.Cache, e.Item.Description, itemInfo.DescriptionBounds);
			AppearanceObject app = itemInfo.PaintAppearance.ItemCaption.Clone() as AppearanceObject;
			app.Font = (Font)e.Item.Tag;
			e.Cache.Graphics.DrawString(e.Item.Caption, app.Font, app.GetForeBrush(e.Cache), itemInfo.CaptionBounds);
			e.Handled = true;
		}
		#endregion
        private void pagebuttonsVisible(bool bVisible)
        {
            if (bVisible)
                ribbonPageLayoutPage.Visible = true;
            else
                ribbonPageLayoutPage.Visible = false;

        }

		private void iAbout_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) 
        {
			//DevExpress.Utils.About.frmAbout dlg = new DevExpress.Utils.About.frmAbout("Ribbon Demo for the XtraBars by Developer Express Inc.");
            AboutForm dlg = new AboutForm();
            dlg.ShowDialog();
		}

		string TextByCaption(string caption) 
        {
			return caption.Replace("&", "");
		}



        void OnPaintStyleClick(object sender, ItemClickEventArgs e) 
        {
			defaultLookAndFeel1.LookAndFeel.SetSkinStyle(e.Item.Tag.ToString());
		}

		private void iPaintStyle_Popup(object sender, System.EventArgs e) 
        {
			foreach(BarItemLink link in iPaintStyle.ItemLinks)
				((BarCheckItem)link.Item).Checked = link.Item.Caption == defaultLookAndFeel1.LookAndFeel.ActiveSkinName;
		}
		#region GalleryItemsChecked
		
		GalleryItem GetColorItemByColor(Color color, BaseGallery gallery) {
			foreach(GalleryItemGroup galleryGroup in gallery.Groups)
				foreach(GalleryItem item in galleryGroup.Items)
					if(item.Caption == color.Name)
						return item;
			return null;
		}
		GalleryItem GetFontItemByFont(string fontName, BaseGallery gallery) {
			foreach(GalleryItemGroup galleryGroup in gallery.Groups)
				foreach(GalleryItem item in galleryGroup.Items)
					if(item.Caption == fontName)
						return item;
			return null;
		}
		GalleryItem CurrentFontItem {
			get { return fCurrentFontItem; }
			set {
				if(fCurrentFontItem == value) return;
				if(fCurrentFontItem != null) fCurrentFontItem.Checked = false;
				fCurrentFontItem = value;
				if(fCurrentFontItem != null) {
					fCurrentFontItem.Checked = true;
					MakeFontVisible(fCurrentFontItem);
				}
			}
		}
		void MakeFontVisible(GalleryItem item) {
			//gddFont.Gallery.MakeVisible(fCurrentFontItem);
			//rgbiFont.Gallery.MakeVisible(fCurrentFontItem);
		}
		GalleryItem CurrentColorItem {
			get { return fCurrentColorItem; }
			set {
				if(fCurrentColorItem == value) return;
				if(fCurrentColorItem != null) fCurrentColorItem.Checked = false;
				fCurrentColorItem = value;
				if(fCurrentColorItem != null) {
					fCurrentColorItem.Checked = true;
					MakeColorVisible(fCurrentColorItem);
				}
			}
		}
		void MakeColorVisible(GalleryItem item) {
			//gddFontColor.Gallery.MakeVisible(fCurrentColorItem);
			//rgbiFontColor.Gallery.MakeVisible(fCurrentColorItem);
		}
		void CurrentFontChanged() {
			//if(CurrentRichTextBox == null || CurrentRichTextBox.SelectionFont == null) return;
			//CurrentFontItem = GetFontItemByFont(CurrentRichTextBox.SelectionFont.Name, rgbiFont.Gallery);
			//CurrentColorItem = GetColorItemByColor(CurrentRichTextBox.SelectionColor, rgbiFontColor.Gallery);
		}
		private void gddFont_Popup(object sender, System.EventArgs e) {
			MakeFontVisible(CurrentFontItem);
		}

		private void gddFontColor_Popup(object sender, System.EventArgs e) {
			MakeColorVisible(CurrentColorItem);
		}
		#endregion
        #region MostRecentFiles
     
        private void frmMain_FormClosing(object sender, FormClosingEventArgs e) {
            //SaveMostRecentFiles(arMRUList);
        }
  

        void OnLabelClicked(object sender, EventArgs e) {
            pmAppMain.HidePopup();
            this.Refresh();
            OpenFile(sender.ToString());
        }
        class MRUArrayList : ArrayList {
            PanelControl container;
            int maxRecentFiles = 9;
            Image imgChecked, imgUncheked;
            public event EventHandler LabelClicked;
            public MRUArrayList(PanelControl cont, Image iChecked, Image iUnchecked) : base() {
                this.imgChecked = iChecked;
                this.imgUncheked = iUnchecked;
                this.container = cont;
            }
            public void InsertElement(object value) {
                string[] names = value.ToString().Split(',');
                string name = names[0];
                bool checkedLabel = false;
                if(names.Length > 1) checkedLabel = names[1].ToLower().Equals("true");
                foreach(AppMenuFileLabel ml in container.Controls) {
                    if(ml.Tag.Equals(name)) {
                        checkedLabel = ml.Checked;
                        base.Remove(name);
                        ml.LabelClick -= new EventHandler(OnLabelClick);
                        ml.Dispose();
                        break;
                    }
                }
                bool access = true;
                if(base.Count >= maxRecentFiles)
                    access = RemoveLastElement();
                if(access) {
                    base.Insert(0, name);
                    AppMenuFileLabel ml = new AppMenuFileLabel();
                    container.Controls.Add(ml);
                    ml.Tag = name;
                    ml.Text = GetFileName(name);
                    ml.Checked = checkedLabel;
                    ml.AutoHeight = true;
                    ml.Dock = DockStyle.Top;
                    ml.Image = imgUncheked;
                    ml.SelectedImage = imgChecked;
                    ml.LabelClick += new EventHandler(OnLabelClick);
                    SetElementsRange();
                }
            }
            void OnLabelClick(object sender, EventArgs e) {
                if(LabelClicked != null)
                    LabelClicked(((AppMenuFileLabel)sender).Tag.ToString(), e);
            }
            public bool RemoveLastElement() {
                for(int i = 0; i < container.Controls.Count; i++) {
                    AppMenuFileLabel ml = container.Controls[i] as AppMenuFileLabel;
                    if(!ml.Checked) {
                        base.Remove(ml.Tag);
                        ml.LabelClick -= new EventHandler(OnLabelClick);
                        ml.Dispose();
                        return true;
                    }
                }
                return false;
            }
            string GetFileName(object obj) {
                FileInfo fi = new FileInfo(obj.ToString());
                return fi.Name;
            }
            void SetElementsRange() { 
                int i = 0;
                foreach(AppMenuFileLabel ml in container.Controls) {
                    ml.Caption = string.Format("&{0}", container.Controls.Count - i);
                    i++;
                }
            }
            public bool GetLabelChecked(string name) {
                foreach(AppMenuFileLabel ml in container.Controls) {
                    if(ml.Tag.Equals(name)) return ml.Checked;
                }
                return false;
            }
        }
        #endregion

        private void ribbonControl1_ApplicationButtonDoubleClick(object sender, EventArgs e) 
        {
            this.Close();
        }

        private void barEditItem1_ItemPress(object sender, ItemClickEventArgs e) 
        {
            System.Diagnostics.Process.Start("http://www.devexpress.com");
        }

        //hhz 主程序初始化

        private void frmMain_Load(object sender, System.EventArgs e)
        {
            ribbonControl1.ForceInitialize();
            foreach (DevExpress.Skins.SkinContainer skin in DevExpress.Skins.SkinManager.Default.Skins)
            {
                BarCheckItem item = ribbonControl1.Items.CreateCheckItem(skin.SkinName, false);
                item.Tag = skin.SkinName;
                item.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(OnPaintStyleClick);
                iPaintStyle.ItemLinks.Add(item);
            }
            CreateNewDocument();
            //barEditItem1.EditValue = (Bitmap)DevExpress.Utils.Controls.ImageHelper.CreateImageFromResources("RibbonSimplePad.online.gif", typeof(frmMain).Assembly);

            //hhz 调整鹰眼大小
            this.dockPanel_Overview.Height = this.dockPanel_Overview.Width;

            // toc与Mainmap 绑定
           // this.axotMapTreeControl1.SetFriendControl(this.axotMapControl_MainMap.Object);
            //this.axotMapTreeControl1.SetFriendControl(this.axotMapControl_Overview.Object);

            //面板初始化
            this.dockPanel_Drawing.Visibility = DevExpress.XtraBars.Docking.DockVisibility.Hidden;
            this.dockPanel_ImageAnalyse.Visibility = DevExpress.XtraBars.Docking.DockVisibility.Hidden;

            //影像分析 参数初始化
            

            //状态栏 初始化
            int staticTextWidth = this.ribbonStatusBar1.Width/3;
            barStaticItem_ScreenCoord.Width = staticTextWidth;
            this.barStaticItem_MapCoord.Width = staticTextWidth;
            this.barStaticItem_Reference.Width = staticTextWidth/2;
            this.barStaticItem_Unit.Width = staticTextWidth/2;

        }
  
        #region hhz 加载地理数据
        //hhz 加载影像数据
        private void barButtonItem_AddImageData_ItemClick(object sender, ItemClickEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "影像数据(*.tif;*.img;*.tiff;*.bmp)|*.tif;*.img;*.tiff;*.bmp|All Files(*.*)|*.*||";
            dlg.Title = "打开影像数据";
            if (dlg.ShowDialog() == DialogResult.OK)
            {
            }
        }
        //hhz 加载矢量数据
        private void barButtonItem_AddVectorData_ItemClick(object sender, ItemClickEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "矢量数据(*.shp)|*.shp|All Files(*.*)|*.*||";
            dlg.Title = "打开矢量数据";
            if (dlg.ShowDialog() == DialogResult.OK)
            {
               
            }
        }
        #endregion
        #region  hhz 视图浏览
        private void barButtonItem_Select_ItemClick(object sender, ItemClickEventArgs e)
        {
        }

        private void barButtonItem_ZoomIn_ItemClick(object sender, ItemClickEventArgs e)
        {
        }

        private void barButtonItem_ZoomOut_ItemClick(object sender, ItemClickEventArgs e)
        {
        }

        private void barButtonItem_Pan_ItemClick(object sender, ItemClickEventArgs e)
        {

        }

        private void barButtonItem_ProView_ItemClick(object sender, ItemClickEventArgs e)
        {
        }

        private void barButtonItem_NextView_ItemClick(object sender, ItemClickEventArgs e)
        {
        }

        private void barButtonItem_FullView_ItemClick(object sender, ItemClickEventArgs e)
        {
        }
        //1:1大小
        private void barButtonItem_SrcView_ItemClick(object sender, ItemClickEventArgs e)
        {
        }

        private void barButtonItem_Identify_ItemClick(object sender, ItemClickEventArgs e)
        {
          //  axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionIdentifyFeature;
        }
        private void barButtonItem_Attribute_ItemClick(object sender, ItemClickEventArgs e)
        {
        }
        private void barButtonItem_Find_ItemClick(object sender, ItemClickEventArgs e)
        {
          //  IotRasterLayer otLayer = new otcCarto.otRasterLayer();
            //this.axotMapControl_MainMap.Map.GetLayer(0);
        }
        private void barButtonItem_Refresh_ItemClick(object sender, ItemClickEventArgs e)
        {
        }
        #endregion
        //调用工具箱
        private void barButtonItem_DrawingToolBox_ItemClick(object sender, ItemClickEventArgs e)
        {
            this.dockPanel_Drawing.Visibility = DevExpress.XtraBars.Docking.DockVisibility.Visible;
        }

        private void barButtonItem_ImageAnalyseToolbox_ItemClick(object sender, ItemClickEventArgs e)
        {
            this.dockPanel_ImageAnalyse.Visibility = DevExpress.XtraBars.Docking.DockVisibility.Visible;
        }
        #region 影像分析工具箱
        private void trackBarControl_Bright_EditValueChanged(object sender, EventArgs e)
        {
            //spinEdit_Bright.Value = this.trackBarControl_Bright.Value;
            
            ////得到第一层
            //otcCarto.IotRasterLayer layer = this.axotMapControl_MainMap.Map.GetLayer(0) as otcCarto.IotRasterLayer;
            //if (layer != null)
            //{
            //    layer.SetBrightAndContrast(trackBarControl_Bright.Value, trackBarControl_Contrast.Value);
            //    axotMapControl_MainMap.Refresh();

            //}
        }

        private void spinEdit_Bright_EditValueChanged(object sender, EventArgs e)
        {
            this.trackBarControl_Bright.Value = (int)spinEdit_Bright.Value;
            this.trackBarControl_Bright.Invalidate(true);
        }

        private void trackBarControl_Contrast_EditValueChanged(object sender, EventArgs e)
        {
            //this.spinEdit_Contrast.Value = this.trackBarControl_Contrast.Value;

            ////得到第一层
            //otcCarto.IotRasterLayer layer = this.axotMapControl_MainMap.Map.GetLayer(0) as otcCarto.IotRasterLayer;
            //if (layer != null)
            //{
            //    layer.SetBrightAndContrast(trackBarControl_Bright.Value, trackBarControl_Contrast.Value);
            //    axotMapControl_MainMap.Refresh();

            //}
        }

        private void spinEdit_Contrast_EditValueChanged(object sender, EventArgs e)
        {
            this.trackBarControl_Contrast.Value = (int)this.spinEdit_Contrast.Value;
        }


        private void spinEdit_Transparency_EditValueChanged(object sender, EventArgs e)
        {
            //this.trackBarControl_Transparency.Value = (int)this.spinEdit_Transparency.Value;

           

            ////得到第一层
            //otcCarto.IotRasterLayer layer = this.axotMapControl_MainMap.Map.GetLayer(0) as otcCarto.IotRasterLayer;
            //if (layer != null)
            //{
            //    //layer.TransparentValue = trackBarControl_Transparency.Value;
            //    axotMapControl_MainMap.Refresh();

            //}
        }
        private void trackBarControl_Transparency_EditValueChanged(object sender, EventArgs e)
        {
            this.spinEdit_Transparency.Value = this.trackBarControl_Transparency.Value;
        }
        private void trackBarControl_Gamma_EditValueChanged(object sender, EventArgs e)
        {
            int val = this.trackBarControl_Gamma.Value;
            if (val <= 10)
            {
                this.spinEdit_Gamma.Value = (decimal)(val / 10.0);
            }
            else this.spinEdit_Gamma.Value = this.trackBarControl_Gamma.Value - 9;
        }

        private void spinEdit_Gamma_EditValueChanged(object sender, EventArgs e)
        {
            //this.trackBarControl_Gamma.Value = (int)this.spinEdit_Gamma.Value;
        }

        #endregion

        #region 标绘工具
        private void simpleButton_SelectElement_Click(object sender, EventArgs e)
        {
           // axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionSelectElement;
        }

        private void simpleButton_DrawPoint_Click(object sender, EventArgs e)
        {
           // axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionDrawSimpleMarkerElement;
        }

        private void simpleButton_DrawLine_Click(object sender, EventArgs e)
        {
          //  axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionDrawPolylineElement;
        }

        private void simpleButton_DrawElement_Polygon_Click(object sender, EventArgs e)
        {
          //  axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionDrawPolygonElement;
        }

        private void simpleButton_DrawCurve_Click(object sender, EventArgs e)
        {
           // axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionDrawBezierCurveElement;
        }

        private void simpleButton_Rect_Click(object sender, EventArgs e)
        {
          //  axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionDrawRectElement;
        }

        private void simpleButton_Text_Click(object sender, EventArgs e)
        {
          //  axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionDrawTextElement;
        }

        private void simpleButton_DrawAny_Click(object sender, EventArgs e)
        {
          //  axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionDrawFreehandLineElement;
        }
        #endregion

        //bool S_bLayout = false;
        //制图与地图切换
        private void xtraTabControl1_SelectedPageChanged(object sender, DevExpress.XtraTab.TabPageChangedEventArgs e)
        {
        }

        private void comboBoxEdit1_SelectedIndexChanged(object sender, EventArgs e)
        {
          
        }

        //mapcontrol的鼠标事件
    

        //bool bIsFlashLayer = false;
        private void checkButton_FlashLayer_Click(object sender, EventArgs e)
        {
            //if (bIsFlashLayer == false)
            //{
            //    bIsFlashLayer = true;
            //    int flashTime = (int)spinEdit_FlashTime.Value;
            //    axotMapControl_MainMap.FlashLayer(0, flashTime);
            //}
            //else
            //{
            //    bIsFlashLayer = false;
            //    axotMapControl_MainMap.StopFlashLayer();
            //}
        }

        private void axLicenseControl1_Enter(object sender, EventArgs e)
        {

        }

        private void barEditItem_layer_EditValueChanged(object sender, EventArgs e)
        {
            BarEditItem barItem = (BarEditItem)sender;
        }
        
        private void frmMain_Shown(object sender, EventArgs e)
        {
           // m_controlSynchronizer.ActivateMap();
        }

        private void openTemplate_ItemClick(object sender, ItemClickEventArgs e)
        {
        }

        private void pageZoomIn_ItemClick(object sender, ItemClickEventArgs e)
        {
          
        }

        private void pageZoomOut_ItemClick(object sender, ItemClickEventArgs e)
        {

        }

        private void pagePan_ItemClick(object sender, ItemClickEventArgs e)
        {
        }

        private void pagePreView_ItemClick(object sender, ItemClickEventArgs e)
        {
          
        }

        private void pageAfterView_ItemClick(object sender, ItemClickEventArgs e)
        {
           
        }

        private void commonPoint_ItemClick(object sender, ItemClickEventArgs e)
        {
        }

        private void commonLine_ItemClick(object sender, ItemClickEventArgs e)
        {
        
        }

        private void commonPolygon_ItemClick(object sender, ItemClickEventArgs e)
        {
     
        }

        private void selectMarkTool_ItemClick(object sender, ItemClickEventArgs e)
        {
        
        }

        private void textMark_ItemClick(object sender, ItemClickEventArgs e)
        {

        }

      
        private void pageFullExtent_ItemClick(object sender, ItemClickEventArgs e)
        {
        
        }

        private void pageRealSize_ItemClick(object sender, ItemClickEventArgs e)
        {
        
        }

    

        private void frmMain_FormClosed(object sender, FormClosedEventArgs e)
        {
        }
    }
}
