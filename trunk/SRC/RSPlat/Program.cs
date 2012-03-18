using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace DevExpress.XtraBars.Demos.RibbonSimplePad {
    static class Program {
        [STAThread]
        static void Main() {
            DevExpress.UserSkins.OfficeSkins.Register();
            DevExpress.Skins.SkinManager.EnableFormSkins();
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            Application.Run(new frmMain());
        }

    }
}
