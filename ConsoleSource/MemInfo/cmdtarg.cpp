#include "_afxwin.h"

const AFX_MSGMAP* CCmdTarget::GetMessageMap() const
{
	return &CCmdTarget::messageMap;
}

const AFX_MSGMAP CCmdTarget::messageMap =
{ NULL, &CCmdTarget::_messageEntries[0] };

const AFX_MSGMAP_ENTRY CCmdTarget::_messageEntries[] = 
{
	{0,0,0,0,0,(AFX_PMSG)0}
};

CCmdTarget::CCmdTarget()
{

}

IMPLEMENT_DYNCREATE(CCmdTarget, CObject)