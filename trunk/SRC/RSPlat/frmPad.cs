using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace DevExpress.XtraBars.Demos.RibbonSimplePad {
    /// <summary>
    /// Summary description for frmPad.
    /// </summary>
    public partial class frmPad : DevExpress.XtraEditors.XtraForm {
        public frmPad() {
            //
            // Required for Windows Form Designer support
            //
            InitializeComponent();
            //
            // TODO: Add any constructor code after InitializeComponent call
            //
        }

        bool modified = false;
        bool newDocument = true;
        string docName = "";

        public RichTextBox RTBMain { get { return richTextBox1; } }

        public string DocName {
            get { return docName; }
            set {
                this.docName = value;
                this.Text = DocName;
            }
        }
        public bool Modified {
            get { return modified; }
            set {
                if(value != modified) {
                    modified = value;
                    this.Text = DocName + (Modified ? "*" : "");
                    if(MdiParent != null) ((frmMain)MdiParent).UpdateText();
                }
            }
        }
        public bool NewDocument { get { return this.newDocument; } }
        public void LoadDocument(string fileName) {
            this.newDocument = false;
            try {
                RTBMain.LoadFile(fileName);
            }
            catch { }
            this.DocName = fileName;
        }

        public string SaveAs() {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.Filter = "Rich Text Files (*.rtf)|*.rtf";
            dlg.Title = "Save As";
            if(dlg.ShowDialog() == DialogResult.OK) {
                RTBMain.SaveFile(dlg.FileName, RichTextBoxStreamType.RichText);
                this.DocName = dlg.FileName;
                this.newDocument = false;
                this.Modified = false;
                return this.DocName;
            }
            return string.Empty;
        }

        bool SaveQuestion() {
            if(Modified) {
                switch(DevExpress.XtraEditors.XtraMessageBox.Show("Do you want to save the changes you made to " + DocName + "?", "SimplePad Question", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question)) {
                    case DialogResult.Cancel:
                        return false;
                    case DialogResult.Yes:
                        SaveAs();
                        break;
                }
            }
            return true;
        }

        private void frmPad_Closing(object sender, System.ComponentModel.CancelEventArgs e) {
            e.Cancel = !SaveQuestion();
        }

        private void richTextBox1_MouseUp(object sender, System.Windows.Forms.MouseEventArgs e) {
            if((e.Button & MouseButtons.Right) != 0 && RTBMain.ClientRectangle.Contains(e.X, e.Y))
                RaiseShowPopupMenu();
        }

        public event EventHandler ShowPopupMenu;
        void RaiseShowPopupMenu() {
            if(ShowPopupMenu != null)
                ShowPopupMenu(RTBMain, EventArgs.Empty);
        }
    }
}
