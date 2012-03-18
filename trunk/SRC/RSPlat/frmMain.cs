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
using otcCarto;
using otComBase;

namespace DevExpress.XtraBars.Demos.RibbonSimplePad {
	public partial class frmMain : DevExpress.XtraBars.Ribbon.RibbonForm {
		public frmMain() {
			InitializeComponent();
            CreateColorPopup(popupControlContainer1);
			InitSkinGallery();
			InitFontGallery();
			InitColorGallery();
        }

		int documentIndex = 0;
        ColorPopup cp;
        frmFind dlgFind = null;
        frmReplace dlgReplace = null;
        GalleryItem fCurrentFontItem, fCurrentColorItem;
		string DocumentName { get { return string.Format("New Document {0}", documentIndex); } }
		
		void CreateNewDocument() {
			CreateNewDocument(null);
		}
        public void ShowHideFormatCategory() {
            RibbonPageCategory selectionCategory = Ribbon.PageCategories[0] as RibbonPageCategory;
            if(selectionCategory == null) return;
            if(CurrentRichTextBox == null)
                selectionCategory.Visible = false;
            else
                selectionCategory.Visible = CurrentRichTextBox.SelectionLength != 0;
            if(selectionCategory.Visible) Ribbon.SelectedPage = selectionCategory.Pages[0];
        }
        void CreateNewDocument(string fileName) {
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

		void Pad_Closed(object sender, EventArgs e) {
			CloseFind();
		}
        void Pad_ShowPopupMenu(object sender, EventArgs e) {
			pmMain.ShowPopup(Control.MousePosition);
		}
        void CloseFind() {
			if(dlgFind != null && dlgFind.RichText != CurrentRichTextBox) {
				dlgFind.Close();
				dlgFind = null;
			}
			if(dlgReplace != null && dlgReplace.RichText != CurrentRichTextBox) {
				dlgReplace.Close();
				dlgReplace = null;
			}
		}

		private void CreateColorPopup(PopupControlContainer container) {
			cp = new ColorPopup(container, iFontColor, this);
		}
		#region Init
		private void frmMain_Activated(object sender, System.EventArgs e) {
			InitPaste();
		}
		public void UpdateText() {
			ribbonControl1.ApplicationCaption = "Ribbon Simple Pad";
			ribbonControl1.ApplicationDocumentCaption = CurrentDocName + (CurrentModified ? "*" : "");
			//Text = string.Format("Ribbon Simple Pad ({0})", CurrentDocName);
			siDocName.Caption = string.Format("  {0}", CurrentDocName);
		}

		private void frmMain_MdiChildActivate(object sender, System.EventArgs e) {
			UpdateText();
			InitCurrentDocument(CurrentRichTextBox);
			rtPad_SelectionChanged(CurrentRichTextBox, EventArgs.Empty);
			CloseFind();
		}
		void rtPad_SelectionChanged(object sender, System.EventArgs e) {
            ShowHideFormatCategory();
            RichTextBox rtPad = sender as RichTextBox;
			//InitFormat();
			int line = 0, col = 0;

			if(rtPad != null) {
				InitEdit(rtPad.SelectionLength > 0);
				line = rtPad.GetLineFromCharIndex(rtPad.SelectionStart) + 1;
				col = rtPad.SelectionStart + 1;
			} else {
				InitEdit(false);
			}
			siPosition.Caption = string.Format("   Line: {0}  Position: {1}   ", line, col);
			CurrentFontChanged();
		}
		void rtPad_TextChanged(object sender, System.EventArgs e) {
			if(CurrentForm == null) return;
			CurrentForm.Modified = true;
			InitCurrentDocument(CurrentRichTextBox);
		}

	

		protected void InitPaste() {
			bool enabledPase = CurrentRichTextBox != null && CurrentRichTextBox.CanPaste(DataFormats.GetFormat(0));
			iPaste.Enabled = enabledPase;
			sbiPaste.Enabled = enabledPase;
		}

		void InitUndo() {
			iUndo.Enabled = CurrentRichTextBox != null ? CurrentRichTextBox.CanUndo : false;
			iLargeUndo.Enabled = iUndo.Enabled;
		}
		protected void InitEdit(bool enabled) {
			iCut.Enabled = enabled;
			iCopy.Enabled = enabled;
			iClear.Enabled = enabled;
			//iSelectAll.Enabled = CurrentRichTextBox != null ? CurrentRichTextBox.CanSelect : false;
			InitUndo();
		}

		void InitNewDocument(RichTextBox rtbControl) {
			rtbControl.SelectionChanged += new System.EventHandler(this.rtPad_SelectionChanged);
			rtbControl.TextChanged += new System.EventHandler(this.rtPad_TextChanged);
		}

		void InitCurrentDocument(RichTextBox rtbControl) {
			bool enabled = rtbControl != null;
			iSaveAs.Enabled = enabled;
			iClose.Enabled = enabled;
			iPrint.Enabled = enabled;
			sbiSave.Enabled = enabled;
			sbiFind.Enabled = enabled;
			iFind.Enabled = enabled;
			iReplace.Enabled = enabled;
			iSave.Enabled = CurrentModified;
			SetModifiedCaption();
			InitPaste();
			//InitFormat();
		}

		void SetModifiedCaption() {
			if(CurrentForm == null) {
				siModified.Caption = "";
				return;
			}
			siModified.Caption = CurrentModified ? "   Modified   " : "";
		}
		#endregion
		#region Properties
		frmPad CurrentForm {
			get {
				if(this.ActiveMdiChild == null) return null;
				return this.ActiveMdiChild as frmPad;
			}
		}

		public RichTextBox CurrentRichTextBox {
			get {
				if(CurrentForm == null) return null;
				return CurrentForm.RTBMain;
			}
		}

		string CurrentDocName {
			get {
				if(CurrentForm == null) return "";
				return CurrentForm.DocName;
			}
		}

		bool CurrentModified {
			get {
				if(CurrentForm == null) return false;
				return CurrentForm.Modified;
			}
		}
		#endregion
		#region File
		void idNew_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
			CreateNewDocument();
		}

		void iClose_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
			if(CurrentForm != null) CurrentForm.Close();
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
			Save();
		}
		void iSaveAs_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
			SaveAs();	
		}
		void Save() {
			if(CurrentForm == null) return;
			if(CurrentForm.NewDocument) {
				SaveAs();		
			} else {
				CurrentRichTextBox.SaveFile(CurrentDocName, RichTextBoxStreamType.RichText); 
				CurrentForm.Modified = false;
			}
			SetModifiedCaption();
		}
		void SaveAs() {
			if(CurrentForm != null) {
				string s = CurrentForm.SaveAs();
                
				UpdateText();
			}
		}
		private void iExit_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
			Close();
		}
		private void frmMain_Closing(object sender, System.ComponentModel.CancelEventArgs e) {
		}
		private void ribbonPageGroup1_CaptionButtonClick(object sender, DevExpress.XtraBars.Ribbon.RibbonPageGroupEventArgs e) {
			OpenFile();
		}

		private void ribbonPageGroup9_CaptionButtonClick(object sender, DevExpress.XtraBars.Ribbon.RibbonPageGroupEventArgs e) {
			SaveAs();
		}
		#endregion
		
		#region Edit
		private void iUndo_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
			if(CurrentRichTextBox == null) return;
			CurrentRichTextBox.Undo();
			CurrentForm.Modified = CurrentRichTextBox.CanUndo;
			SetModifiedCaption();
			InitUndo();
			//InitFormat();
		}

		private void iCut_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
			if(CurrentRichTextBox == null) return;
			CurrentRichTextBox.Cut();
			InitPaste();
		}

		private void iCopy_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
			if(CurrentRichTextBox == null) return;
			CurrentRichTextBox.Copy();
			InitPaste();
		}

		private void iPaste_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
			if(CurrentRichTextBox == null) return;
			CurrentRichTextBox.Paste();
		}

		private void iClear_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
			if(CurrentRichTextBox == null) return;
			CurrentRichTextBox.SelectedRtf = "";
		}

		private void iSelectAll_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
			if(CurrentRichTextBox == null) return;
			CurrentRichTextBox.SelectAll();
		}
		private void ribbonPageGroup2_CaptionButtonClick(object sender, DevExpress.XtraBars.Ribbon.RibbonPageGroupEventArgs e) {
			pmMain.ShowPopup(ribbonControl1.Manager, MousePosition);
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
		void SetFont(string fontName, GalleryItem item) {
			if(CurrentRichTextBox == null) return;
			//CurrentRichTextBox.SelectionFont = new Font(fontName, Convert.ToInt32(beiFontSize.EditValue), rtPadFontStyle());
			if(item != null) CurrentFontItem = item;
		}
		private void gddFont_Gallery_ItemClick(object sender, DevExpress.XtraBars.Ribbon.GalleryItemClickEventArgs e) {
			SetFont(e.Item.Caption, e.Item);
		}
		private void rpgFont_CaptionButtonClick(object sender, DevExpress.XtraBars.Ribbon.RibbonPageGroupEventArgs e) {
			//ShowFontDialog();
		}
		private void rgbiFont_Gallery_ItemClick(object sender, DevExpress.XtraBars.Ribbon.GalleryItemClickEventArgs e) {
			SetFont(e.Item.Caption, e.Item);
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
		#region ColorGallery
		void InitColorGallery() {
            //gddFontColor.BeginUpdate();
            //foreach(Color color in DevExpress.XtraEditors.Popup.ColorListBoxViewInfo.WebColors) {
            //    if(color == Color.Transparent) continue;
            //    GalleryItem item = new GalleryItem();
            //    item.Caption = color.Name;
            //    item.Tag = color;
            //    item.Hint = color.Name;
            //    gddFontColor.Gallery.Groups[0].Items.Add(item);
            //    rgbiFontColor.Gallery.Groups[0].Items.Add(item);
            //}
            //foreach(Color color in DevExpress.XtraEditors.Popup.ColorListBoxViewInfo.SystemColors) {
            //    GalleryItem item = new GalleryItem();
            //    item.Caption = color.Name;
            //    item.Tag = color;
            //    gddFontColor.Gallery.Groups[1].Items.Add(item);
            //}
            //gddFontColor.EndUpdate();
		}
		private void gddFontColor_Gallery_CustomDrawItemImage(object sender, GalleryItemCustomDrawEventArgs e) {
			Color clr = (Color)e.Item.Tag;
			using(Brush brush = new SolidBrush(clr)) {
				e.Cache.FillRectangle(brush, e.Bounds);
				e.Handled = true;
			}
		}
		void SetResultColor(Color color, GalleryItem item) {
			if(CurrentRichTextBox == null) return;
			cp.ResultColor = color;
			CurrentRichTextBox.SelectionColor = cp.ResultColor;
			if(item != null) CurrentColorItem = item;
		}
		private void gddFontColor_Gallery_ItemClick(object sender, DevExpress.XtraBars.Ribbon.GalleryItemClickEventArgs e) {
			SetResultColor((Color)e.Item.Tag, e.Item);
		}
		private void rpgFontColor_CaptionButtonClick(object sender, DevExpress.XtraBars.Ribbon.RibbonPageGroupEventArgs e) {
			if(CurrentRichTextBox == null) return;
			if(cp == null)
				CreateColorPopup(popupControlContainer1);
			popupControlContainer1.ShowPopup(ribbonControl1.Manager, MousePosition);
		}

		private void rgbiFontColor_Gallery_ItemClick(object sender, DevExpress.XtraBars.Ribbon.GalleryItemClickEventArgs e) {
			SetResultColor((Color)e.Item.Tag, e.Item);
		}
		#endregion
				
		private void iFind_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
			if(CurrentRichTextBox == null) return;
			if(dlgReplace != null) dlgReplace.Close();
			if(dlgFind != null) dlgFind.Close();
			dlgFind = new frmFind(CurrentRichTextBox, Bounds);
			AddOwnedForm(dlgFind);
			dlgFind.Show();
		}

		private void iReplace_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
			if(CurrentRichTextBox == null) return;
			if(dlgReplace != null) dlgReplace.Close();
			if(dlgFind != null) dlgFind.Close();
			dlgReplace = new frmReplace(CurrentRichTextBox, Bounds);
			AddOwnedForm(dlgReplace);
			dlgReplace.Show();
		}

		private void iWeb_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
			Process process = new Process();
			process.StartInfo.FileName = "http://www.devexpress.com";
			process.StartInfo.Verb = "Open";
			process.StartInfo.WindowStyle = ProcessWindowStyle.Normal;
			process.Start();
		}

		private void iAbout_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e) {
			//DevExpress.Utils.About.frmAbout dlg = new DevExpress.Utils.About.frmAbout("Ribbon Demo for the XtraBars by Developer Express Inc.");
            AboutForm dlg = new AboutForm();
            dlg.ShowDialog();
		}

		string TextByCaption(string caption) {
			return caption.Replace("&", "");
		}



        void OnPaintStyleClick(object sender, ItemClickEventArgs e) {
			defaultLookAndFeel1.LookAndFeel.SetSkinStyle(e.Item.Tag.ToString());
		}

		private void iPaintStyle_Popup(object sender, System.EventArgs e) {
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

        private void ribbonControl1_ApplicationButtonDoubleClick(object sender, EventArgs e) {
            this.Close();
        }

        private void barEditItem1_ItemPress(object sender, ItemClickEventArgs e) {
            System.Diagnostics.Process.Start("http://www.devexpress.com");
        }

        //hhzhao 主程序初始化

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

            //hhzhao 调整鹰眼大小
            this.dockPanel_Overview.Height = this.dockPanel_Overview.Width;

            // toc与Mainmap 绑定
            this.axotMapTreeControl1.SetFriendControl(this.axotMapControl_MainMap.Object);
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
  
        #region hhzhao 加载地理数据
        //hhzhao 加载影像数据
        private void barButtonItem_AddImageData_ItemClick(object sender, ItemClickEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "影像数据(*.tif;*.img;*.tiff;*.bmp)|*.tif;*.img;*.tiff;*.bmp|All Files(*.*)|*.*||";
            dlg.Title = "打开影像数据";
            if (dlg.ShowDialog() == DialogResult.OK)
            {

                this.axotMapControl_MainMap.AddImageFile(dlg.FileName);
         
                for (int i = 0 ;i< axotMapControl_MainMap.Map.LayerCount();i++)
                {
                    this.axotMapControl_Overview.Map.AddLayer(this.axotMapControl_MainMap.Map.GetLayer(i));
                }
                axotMapTreeControl1.Update();
                axotMapTreeControl1.Refresh();
                axotMapControl_Overview.Refresh();

            }
        }
        //hhzhao 加载矢量数据
        private void barButtonItem_AddVectorData_ItemClick(object sender, ItemClickEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "矢量数据(*.shp)|*.shp|All Files(*.*)|*.*||";
            dlg.Title = "打开矢量数据";
            if (dlg.ShowDialog() == DialogResult.OK)
            {

                this.axotMapControl_MainMap.AddShpFile(dlg.FileName);
                for (int i = 0; i < axotMapControl_MainMap.Map.LayerCount(); i++)
                {
                    this.axotMapControl_Overview.Map.AddLayer(this.axotMapControl_MainMap.Map.GetLayer(i));
                }
                axotMapTreeControl1.Update();
                axotMapTreeControl1.Refresh();
                axotMapControl_Overview.Refresh();
            }
        }
        #endregion


        #region  hhzhao 视图浏览
        private void barButtonItem_Select_ItemClick(object sender, ItemClickEventArgs e)
        {
            axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionSelectElement;

        }

        private void barButtonItem_ZoomIn_ItemClick(object sender, ItemClickEventArgs e)
        {
            axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionZoomIn;

        }

        private void barButtonItem_ZoomOut_ItemClick(object sender, ItemClickEventArgs e)
        {
            axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionZoomOut;
        }

        private void barButtonItem_Pan_ItemClick(object sender, ItemClickEventArgs e)
        {
            axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionPan;
        }

        private void barButtonItem_ProView_ItemClick(object sender, ItemClickEventArgs e)
        {
            
        }

        private void barButtonItem_NextView_ItemClick(object sender, ItemClickEventArgs e)
        {

        }

        private void barButtonItem_FullView_ItemClick(object sender, ItemClickEventArgs e)
        {
            //axotMapControl_MainMap.Map.ZoomFullExtent();
            axotMapControl_MainMap.Refresh();
        }
        //1:1大小
        private void barButtonItem_SrcView_ItemClick(object sender, ItemClickEventArgs e)
        {
            //axotMapControl_MainMap.Map.ZoomActualSize();
            axotMapControl_MainMap.Refresh();
        }

        private void barButtonItem_Identify_ItemClick(object sender, ItemClickEventArgs e)
        {
            axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionIdentifyFeature;
        }

        private void barButtonItem_Attribute_ItemClick(object sender, ItemClickEventArgs e)
        {

        }

        private void barButtonItem_Find_ItemClick(object sender, ItemClickEventArgs e)
        {
            IotRasterLayer otLayer = new otcCarto.otRasterLayer();
            //this.axotMapControl_MainMap.Map.GetLayer(0);
        }
        private void barButtonItem_Refresh_ItemClick(object sender, ItemClickEventArgs e)
        {
            axotMapControl_MainMap.Refresh();
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
            spinEdit_Bright.Value = this.trackBarControl_Bright.Value;
            
            //得到第一层
            otcCarto.IotRasterLayer layer = this.axotMapControl_MainMap.Map.GetLayer(0) as otcCarto.IotRasterLayer;
            if (layer != null)
            {
                layer.SetBrightAndContrast(trackBarControl_Bright.Value, trackBarControl_Contrast.Value);
                axotMapControl_MainMap.Refresh();

            }


        }

        private void spinEdit_Bright_EditValueChanged(object sender, EventArgs e)
        {
            this.trackBarControl_Bright.Value = (int)spinEdit_Bright.Value;
            this.trackBarControl_Bright.Invalidate(true);
        }

        private void trackBarControl_Contrast_EditValueChanged(object sender, EventArgs e)
        {
            this.spinEdit_Contrast.Value = this.trackBarControl_Contrast.Value;

       

            //得到第一层
            otcCarto.IotRasterLayer layer = this.axotMapControl_MainMap.Map.GetLayer(0) as otcCarto.IotRasterLayer;
            if (layer != null)
            {
                layer.SetBrightAndContrast(trackBarControl_Bright.Value, trackBarControl_Contrast.Value);
                axotMapControl_MainMap.Refresh();

            }
        }

        private void spinEdit_Contrast_EditValueChanged(object sender, EventArgs e)
        {
            this.trackBarControl_Contrast.Value = (int)this.spinEdit_Contrast.Value;
        }

        private void spinEdit_Transparency_EditValueChanged(object sender, EventArgs e)
        {
            this.trackBarControl_Transparency.Value = (int)this.spinEdit_Transparency.Value;

           

            //得到第一层
            otcCarto.IotRasterLayer layer = this.axotMapControl_MainMap.Map.GetLayer(0) as otcCarto.IotRasterLayer;
            if (layer != null)
            {
                //layer.TransparentValue = trackBarControl_Transparency.Value;
                axotMapControl_MainMap.Refresh();

            }
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
            axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionSelectElement;
        }

        private void simpleButton_DrawPoint_Click(object sender, EventArgs e)
        {
            axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionDrawSimpleMarkerElement;
        }

        private void simpleButton_DrawLine_Click(object sender, EventArgs e)
        {
            axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionDrawPolylineElement;
        }

        private void simpleButton_DrawElement_Polygon_Click(object sender, EventArgs e)
        {
            axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionDrawPolygonElement;
        }

        private void simpleButton_DrawCurve_Click(object sender, EventArgs e)
        {
            axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionDrawBezierCurveElement;
        }

        private void simpleButton_Rect_Click(object sender, EventArgs e)
        {
            axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionDrawRectElement;
        }

        private void simpleButton_Text_Click(object sender, EventArgs e)
        {
            axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionDrawTextElement;
        }

        private void simpleButton_DrawAny_Click(object sender, EventArgs e)
        {
            axotMapControl_MainMap.Action = otMapControlLib.otActionType.actionDrawFreehandLineElement;
        }
        #endregion

        bool S_bLayout = false;
        //制图与地图切换
        private void xtraTabControl1_SelectedPageChanged(object sender, DevExpress.XtraTab.TabPageChangedEventArgs e)
        {
            int tabPageIndex = this.xtraTabControl.SelectedTabPageIndex;
            if(tabPageIndex == 0)
            {
                
            }
            else
            {
                //this.axotLayoutControl.PageLayout;BezierCurve
                //axotLayoutControl.ReplaceMaps(axotMapControl_MainMap.Map);
                if (S_bLayout)
                {
                   // S_bLayout = false;
                }
                else
                {
                    S_bLayout = true;
                    string tempPath = Application.StartupPath + "\\" + "china.TMP";
                    //axotLayoutControl.LoadTemplate(axotMapControl_MainMap.Map, tempPath);
                }
            }
        }

        private void comboBoxEdit1_SelectedIndexChanged(object sender, EventArgs e)
        {
            otcCarto.IotRasterLayer layer = this.axotMapControl_MainMap.Map.GetLayer(0) as otcCarto.IotRasterLayer;
            if (layer == null)
            {
                return;

            }
            int index = comboBoxEdit1.SelectedIndex;
            switch (index)
            {
                case 0:
                    layer.Enhance(otcCarto.RasterEnhanceType.LINESTRETCH);
                    break;
                case 1:
                    layer.Enhance(otcCarto.RasterEnhanceType.HISTGRAMNORMAL);
                    break;
                case 2:
                    layer.Enhance(otcCarto.RasterEnhanceType.HISTGRAMEQULIZE);
                    break;
                case 3:
                    layer.Enhance(otcCarto.RasterEnhanceType.LOGENHANCE);
                    break;
                case 4:
                    layer.Enhance(otcCarto.RasterEnhanceType.EXPHANCE);
                    break;
                case 5:
                    layer.Enhance(otcCarto.RasterEnhanceType.StANDARDDEV);
                    break;
                default:
                    break;
            }
            axotMapControl_MainMap.Refresh();
        }

        //mapcontrol的鼠标事件
        private void axotMapControl_MainMap_OnMouseMove(object sender, AxotMapControlLib._DotMapControlEvents_OnMouseMoveEvent e)
        {
            if (axotMapControl_MainMap.Map.LayerCount() < 1)
                return;

           //this.barStaticItem_Reference.Caption = axotMapControl_MainMap.Map.SpatialReference.GetGeogName();

           bool bIsProj = axotMapControl_MainMap.Map.SpatialReference.IsProjected();
          
           if (bIsProj == true)
           {
               this.barStaticItem_Reference.Caption = "地理坐标:"+axotMapControl_MainMap.Map.SpatialReference.GetProjName();
           }
           else
           {

               this.barStaticItem_Reference.Caption = "地理坐标:" + axotMapControl_MainMap.Map.SpatialReference.GetGeogName();
           }


            //地图单位
           otComBase.otUnits mapUnits = axotMapControl_MainMap.Map.MapUnit;
           //this.barStaticItem_Unit.Caption = "地图单位："+mapUnits.ToString();

            //屏幕坐标
            this.barStaticItem_ScreenCoord.Caption = "屏幕坐标："+e.x.ToString()+","+e.y.ToString();
            //地理坐标
            //
           
            this.barStaticItem_MapCoord.Caption = "地理坐标：" + e.mapX.ToString("F2") + "," + e.mapY.ToString("0.## ");
        }

        bool bIsFlashLayer = false;
        private void checkButton_FlashLayer_Click(object sender, EventArgs e)
        {
            if (bIsFlashLayer == false)
            {
                bIsFlashLayer = true;
                int flashTime = (int)spinEdit_FlashTime.Value;
                axotMapControl_MainMap.FlashLayer(0, flashTime);
            }
            else
            {
                bIsFlashLayer = false;
                axotMapControl_MainMap.StopFlashLayer();
            }
        }
    }
}
