// OverrideEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ResolveSudoko.h"
#include "OverrideEdit.h"


// COverrideEdit

IMPLEMENT_DYNAMIC(COverrideEdit, CEdit)

COverrideEdit::COverrideEdit()
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	EnableAutomation();
}

COverrideEdit::~COverrideEdit()
{
}

void COverrideEdit::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CEdit::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(COverrideEdit, CEdit)
	//ON_NOTIFY(WM_NCPAINT, this->GetDlgCtrlID(), &COverrideEdit::OnNcPaint)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(COverrideEdit, CEdit)
END_DISPATCH_MAP()

// Note: we add support for IID_IOverrideEdit to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {51467DB4-36CD-4256-A988-934AED5A9AD7}
static const IID IID_IOverrideEdit =
{ 0x51467DB4, 0x36CD, 0x4256, { 0xA9, 0x88, 0x93, 0x4A, 0xED, 0x5A, 0x9A, 0xD7 } };

BEGIN_INTERFACE_MAP(COverrideEdit, CEdit)
	INTERFACE_PART(COverrideEdit, IID_IOverrideEdit, Dispatch)
END_INTERFACE_MAP()


// COverrideEdit message handlers

void COverrideEdit::OnNcPaint() 
{
	CWindowDC dc(this);
	CRect rect;
	GetWindowRect(&rect);

	dc.Draw3dRect(0,0,rect.Width(),rect.Height(), RGB(0,0,255) , RGB(255,0,0) );
}
