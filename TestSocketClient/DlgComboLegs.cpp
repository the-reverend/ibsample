// DlgComboLegs.cpp : implementation file
//

#include "stdafx.h"
#include "client2.h"
#include "DlgComboLegs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgComboLegs dialog
CDlgComboLegs::CDlgComboLegs( ComboLegList& comboLegs, const CString& orderExchange,
                              CWnd* pParent /*=NULL*/ )
	: CDialog( CDlgComboLegs::IDD, pParent )
	, m_comboLegs( comboLegs )
{
	//{{AFX_DATA_INIT(CDlgComboLegs)
	m_conId = 0;
	m_ratio = 1;
	m_side = _T( "BUY" );
	m_exchange = orderExchange;
	m_openClose = 0;
	m_shortSaleSlot = 0;
	m_designatedLocation = _T( "" );
	//}}AFX_DATA_INIT
}


void CDlgComboLegs::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange( pDX );
	//{{AFX_DATA_MAP(CDlgComboLegs)
	DDX_Control( pDX, IDC_LST_COMBOLEGS, m_lstComboLegs );
	DDX_Text( pDX, IDC_EDT_CONID, m_conId );
	DDX_Text( pDX, IDC_EDT_RATIO, m_ratio );
	DDX_Text( pDX, IDC_EDT_SIDE, m_side );
	DDX_Text( pDX, IDC_EDT_EXCHANGE, m_exchange );
	DDX_Text( pDX, IDC_EDT_OPENCLOSE, m_openClose );
	DDX_Text( pDX, IDC_EDT_SHORT_SALE_SLOT, m_shortSaleSlot );
	DDX_Text( pDX, IDC_EDT_DESIGNATED_LOCATION, m_designatedLocation );
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP( CDlgComboLegs, CDialog )
	//{{AFX_MSG_MAP(CDlgComboLegs)
	ON_BN_CLICKED( IDC_BTN_ADD_LEG, OnBtnAddLeg )
	ON_BN_CLICKED( IDC_BTN_REMOVE_LEG, OnBtnRemoveLeg )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgComboLegs message handlers

BOOL CDlgComboLegs::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString title;
	title.Format( "Combination Order Legs" );
	SetWindowText( title );

	m_lstComboLegs.InsertColumn( 0, "ConId", LVCFMT_LEFT, 65, -1 );
	m_lstComboLegs.InsertColumn( 1, "Ratio", LVCFMT_LEFT, 40, -1 );
	m_lstComboLegs.InsertColumn( 2, "Side", LVCFMT_LEFT, 40, -1 );
	m_lstComboLegs.InsertColumn( 3, "Exchange", LVCFMT_LEFT, 70, -1 );
	m_lstComboLegs.InsertColumn( 4, "Open/Close", LVCFMT_LEFT, 70, -1 );
	m_lstComboLegs.InsertColumn( 5, "Short Sale Slot", LVCFMT_LEFT, 70, -1 );
	m_lstComboLegs.InsertColumn( 6, "Designated Location", LVCFMT_LEFT, 70, -1 );

	if ( !m_comboLegs.empty() )
	{

		ComboLegList::const_iterator iter = m_comboLegs.begin();
		const ComboLegList::const_iterator iterEnd = m_comboLegs.end();

		size_t insertPos = 0;
		for ( ; iter != iterEnd; ++iter )
		{
			const ComboLeg* comboLeg = *iter;
			if ( !comboLeg )
				continue;

			char buf[20];

			_itoa_s( comboLeg->conId, buf, sizeof( buf ), 10 );
			m_lstComboLegs.InsertItem( insertPos, buf );

			_itoa_s( comboLeg->ratio, buf, sizeof( buf ), 10 );
			m_lstComboLegs.SetItemText( insertPos, 1, buf );

			m_lstComboLegs.SetItemText( insertPos, 2, comboLeg->action );

			m_lstComboLegs.SetItemText( insertPos, 3, comboLeg->exchange );

			_itoa_s( comboLeg->openClose, buf, sizeof( buf ), 10 );
			m_lstComboLegs.SetItemText( insertPos, 4, buf );

			_itoa_s( comboLeg->shortSaleSlot, buf, sizeof( buf ), 10 );
			m_lstComboLegs.SetItemText( insertPos, 5, buf );

			m_lstComboLegs.SetItemText( insertPos, 6, comboLeg->designatedLocation );

			++insertPos;
		}
	}

	UpdateData( false );
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgComboLegs::OnBtnAddLeg()
{
	UpdateData();

	// TODO: Please add any validation here before setting the combo leg details

	int insertPos = m_lstComboLegs.GetItemCount();

	char buf[20];

	_itoa_s( m_conId, buf, sizeof( buf ), 10 );
	m_lstComboLegs.InsertItem( insertPos, buf );

	_itoa_s( m_ratio, buf, sizeof( buf ), 10 );
	m_lstComboLegs.SetItemText( insertPos, 1, buf );

	m_lstComboLegs.SetItemText( insertPos, 2, m_side );

	m_lstComboLegs.SetItemText( insertPos, 3, m_exchange );

	_itoa_s( m_openClose, buf, sizeof( buf ), 10 );
	m_lstComboLegs.SetItemText( insertPos, 4, buf );

	_itoa_s( m_shortSaleSlot, buf, sizeof( buf ), 10 );
	m_lstComboLegs.SetItemText( insertPos, 5, buf );

	m_lstComboLegs.SetItemText( insertPos, 6, m_designatedLocation );
}

void CDlgComboLegs::OnBtnRemoveLeg()
{
	for ( int i = m_lstComboLegs.GetItemCount() - 1; i >= 0 ; i-- )
	{
		if ( m_lstComboLegs.GetItemState( i, LVIS_SELECTED ) )
		{
			m_lstComboLegs.DeleteItem( i );
		}
	}
}

void CDlgComboLegs::OnOK()
{
	UpdateData(); // get the order legs

	CString itemText;

	Contract::CleanupComboLegs( m_comboLegs );

	const size_t itemCount = m_lstComboLegs.GetItemCount();
	for ( size_t i = 0 ; i < itemCount; ++i )
	{

		ComboLeg* pComboLeg = new ComboLeg();

		itemText = m_lstComboLegs.GetItemText( i, 0 );
		pComboLeg->conId = atoi( itemText );

		itemText = m_lstComboLegs.GetItemText( i, 1 );
		pComboLeg->ratio = atoi( itemText );

		itemText = m_lstComboLegs.GetItemText( i, 2 );
		pComboLeg->action = itemText;

		itemText = m_lstComboLegs.GetItemText( i, 3 );
		pComboLeg->exchange = itemText;

		itemText = m_lstComboLegs.GetItemText( i, 4 );
		pComboLeg->openClose = atoi( itemText );

		itemText = m_lstComboLegs.GetItemText( i, 5 );
		pComboLeg->shortSaleSlot = atoi( itemText );

		itemText = m_lstComboLegs.GetItemText( i, 6 );
		pComboLeg->designatedLocation = itemText;

		m_comboLegs.push_back( pComboLeg );
	}

	CDialog::OnOK();
}
