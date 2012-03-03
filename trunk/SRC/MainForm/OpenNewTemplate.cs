// Copyright 2008 ESRI
// 
// All rights reserved under the copyright laws of the United States
// and applicable international laws, treaties, and conventions.
// 
// You may freely redistribute and use this sample code, with or
// without modification, provided you include the original copyright
// notice and use restrictions.
// 
// See use restrictions at <your ArcGIS install location>/developerkit/userestrictions.txt.
// 

using System;
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace MapAndPageLayoutSynch
{
    /// <summary>
    /// Summary description for OpenNewTemplate.
    /// </summary>

    public sealed class OpenNewTemplate
    {
        private string m_sDocumentPath = string.Empty;

        public OpenNewTemplate()
        {
           
        }

        public string DocumentFileName
        {
            get { return m_sDocumentPath; }
        }
    }
}
