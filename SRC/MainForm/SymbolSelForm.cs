using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
namespace HYMain
{
    public partial class SymbolSelForm : DevExpress.XtraEditors.XtraForm
    {
        private string[] m_styleFiles;
        private bool m_bset = false;
        public SymbolSelForm()
        {
            InitializeComponent();
        }
        private void update_pre_view()
        {

        }

        private void InitialStyleClass()
        {
        
        }
        
        private void SymbolSelForm_Load(object sender, EventArgs e)
        {
           
            update_pre_view();
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            m_bset = true;
            this.DialogResult = DialogResult.OK;
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            m_bset = false;
            this.DialogResult = DialogResult.Cancel;
        }
        private void symColor_EditValueChanged(object sender, EventArgs e)
        {
            
            update_pre_view();
        }

        private void symSize_EditValueChanged(object sender, EventArgs e)
        {
         
        }

        private void otherSize_EditValueChanged(object sender, EventArgs e)
        {
            
        }

        private void otherColor_EditValueChanged(object sender, EventArgs e)
        {
          
        }
    }
}