//////////////////////////////////////////////////
// CMDTARG.CPP�ļ�

#include "_afxwin.h"
#include "_afximpl.h"



CCmdTarget::CCmdTarget()
{ }


/////////////////////////////////
// ʵ����Ϣӳ��Ĵ���
const AFX_MSGMAP* CCmdTarget::GetMessageMap () const
{
	return &CCmdTarget::messageMap ;
}
const AFX_MSGMAP CCmdTarget::messageMap =
	{ NULL, &CCmdTarget::_messageEntries[0] };
const AFX_MSGMAP_ENTRY CCmdTarget::_messageEntries[] = 
{
	// һ����ϢҲ������
	{ 0, 0, 0, 0, 0, (AFX_PMSG)0 }
};

/////////////////////////////////
// ֧����������Ϣ�Ĵ���
IMPLEMENT_DYNCREATE(CCmdTarget, CObject)