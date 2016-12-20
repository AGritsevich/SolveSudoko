#pragma once


// COverrideEdit

class COverrideEdit : public CEdit
{
	DECLARE_DYNAMIC(COverrideEdit)

public:
	COverrideEdit();
	virtual ~COverrideEdit();

	virtual void OnFinalRelease();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	afx_msg void OnNcPaint(); 
};


