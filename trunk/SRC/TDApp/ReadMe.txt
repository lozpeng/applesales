================================================================================
    MICROSOFT FOUNDATION CLASS LIBRARY : TDApp Project Overview
===============================================================================

The application wizard has created this TDApp application for 
you.  This application not only demonstrates the basics of using the Microsoft 
Foundation Classes but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your TDApp application.

TDApp.vcproj
    This is the main project file for VC++ projects generated using an application wizard. 
    It contains information about the version of Visual C++ that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    application wizard.

TDApp.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CTDAppApp application class.

TDApp.cpp
    This is the main application source file that contains the application
    class CTDAppApp.

TDApp.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
    Visual C++. Your project resources are in 1033.

res\TDApp.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file TDApp.rc.

res\TDApp.rc2
    This file contains resources that are not edited by Microsoft 
    Visual C++. You should place all resources not editable by
    the resource editor in this file.

/////////////////////////////////////////////////////////////////////////////

For the main frame window:
    The project includes a standard MFC interface.

MainFrm.h, MainFrm.cpp
    These files contain the frame class CMainFrame, which is derived from
    CFrameWnd and controls all SDI frame features.

res\Toolbar.bmp
    This bitmap file is used to create tiled images for the toolbar.
    The initial toolbar and status bar are constructed in the CMainFrame
    class. Edit this toolbar bitmap using the resource editor, and
    update the IDR_MAINFRAME TOOLBAR array in TDApp.rc to add
    toolbar buttons.
/////////////////////////////////////////////////////////////////////////////

The application wizard creates one document type and one view:

TDAppDoc.h, TDAppDoc.cpp - the document
    These files contain your CTDAppDoc class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via CTDAppDoc::Serialize).

TDAppView.h, TDAppView.cpp - the view of the document
    These files contain your CTDAppView class.
    CTDAppView objects are used to view CTDAppDoc objects.



/////////////////////////////////////////////////////////////////////////////

The application wizard has also created classes specific to OLE

CntrItem.h, CntrItem.cpp
    These files contain your CTDAppCntrItem class. This class is used to 
    manipulate OLE objects.  OLE objects are usually displayed by your
    CTDAppView class and serialized as part of your CTDAppDoc class.

    The project has support for Compound files. The Compound-file format stores a document 
    that contains one or more Automation objects to one file and still allows access to 
    the it for the individual objects.

/////////////////////////////////////////////////////////////////////////////

Help Support:

hlp\TDApp.hhp
    This file is a help project file. It contains the data needed to
    compile the help files into a .chm file.

hlp\TDApp.hhc
    This file lists the contents of the help project.

hlp\TDApp.hhk
    This file contains an index of the help topics.

hlp\afxcore.htm
    This file contains the standard help topics for standard MFC
    commands and screen objects. Add your own help topics to this file.

hlp\afxprint.htm
    This file contains the help topics for the printing commands.

makehtmlhelp.bat
    This file is used by the build system to compile the help files.

hlp\Images\*.gif
    These are bitmap files required by the standard help file topics for
    Microsoft Foundation Class Library standard commands.


/////////////////////////////////////////////////////////////////////////////

Other Features:

ActiveX Controls
    The application includes support to use ActiveX controls.

Printing and Print Preview support
    The application wizard has generated code to handle the print, print setup, and print preview
    commands by calling member functions in the CView class from the MFC library.

Split Window
    The application wizard has added support for splitter windows for your application documents.

/////////////////////////////////////////////////////////////////////////////

Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named TDApp.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

TDApp.manifest
	Application manifest files are used by Windows XP to describe an applications 
	dependency on specific versions of Side-by-Side assemblies. The loader uses this 
	information to load the appropriate assembly from the assembly cache or private 
	from the application. The Application manifest  maybe included for redistribution 
	as an external .manifest file that is installed in the same folder as the application 
	executable or it may be included in the executable in the form of a resource. 
/////////////////////////////////////////////////////////////////////////////

Other notes:

The application wizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, you will need 
to redistribute the MFC DLLs. If your application is in a language 
other than the operating system's locale, you will also have to 
redistribute the corresponding localized resources MFC80XXX.DLL. 
For more information on both of these topics, please see the section on 
redistributing Visual C++ applications in MSDN documentation. 

/////////////////////////////////////////////////////////////////////////////
