# Microsoft Developer Studio Project File - Name="DSP" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DSP - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DSP.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DSP.mak" CFG="DSP - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DSP - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# Begin Target

# Name "DSP - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DftParaInput.cpp
# End Source File
# Begin Source File

SOURCE=.\DifFFTInput.cpp
# End Source File
# Begin Source File

SOURCE=.\DSP.cpp
# End Source File
# Begin Source File

SOURCE=.\DSP.rc
# End Source File
# Begin Source File

SOURCE=.\DSPDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\DSPView.cpp
# End Source File
# Begin Source File

SOURCE=.\FilterInput.cpp
# End Source File
# Begin Source File

SOURCE=.\IIRAPInput.cpp
# End Source File
# Begin Source File

SOURCE=.\IIRHPInput.cpp
# End Source File
# Begin Source File

SOURCE=.\IIRLPInput.cpp
# End Source File
# Begin Source File

SOURCE=.\inputPara.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DftParaInput.h
# End Source File
# Begin Source File

SOURCE=.\DifFFTInput.h
# End Source File
# Begin Source File

SOURCE=.\DSP.h
# End Source File
# Begin Source File

SOURCE=.\DSPDoc.h
# End Source File
# Begin Source File

SOURCE=.\DSPView.h
# End Source File
# Begin Source File

SOURCE=.\FilterInput.h
# End Source File
# Begin Source File

SOURCE=.\IIRAPInput.h
# End Source File
# Begin Source File

SOURCE=.\IIRHPInput.h
# End Source File
# Begin Source File

SOURCE=.\IIRLPInput.h
# End Source File
# Begin Source File

SOURCE=.\inputPara.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\DSP.ico
# End Source File
# Begin Source File

SOURCE=.\res\DSP.rc2
# End Source File
# Begin Source File

SOURCE=.\res\DSPDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
