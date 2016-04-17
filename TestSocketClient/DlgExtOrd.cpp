// DlgExtOrd.cpp : implementation file
//

#include "stdafx.h"
#include "DlgExtOrd.h"

#include "Order.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgExtOrd dialog


CDlgExtOrd::CDlgExtOrd( Order* order, CWnd* pParent /*=NULL*/ )
	: CDialog( CDlgExtOrd::IDD, pParent )
	, m_order( order )
{
	//{{AFX_DATA_INIT(CDlgExtOrd)
	//}}AFX_DATA_INIT
	getAttribsFromOrder();
}


void CDlgExtOrd::getAttribsFromOrder()
{

#define GET_PROP(Prop) \
   m_##Prop = m_order->Prop;

	// extended order fields
	GET_PROP( tif );
	GET_PROP( ocaGroup );
	GET_PROP( ocaType );
	GET_PROP( orderRef );
	GET_PROP( transmit );
	GET_PROP( parentId );
	GET_PROP( blockOrder );
	GET_PROP( sweepToFill );
	GET_PROP( displaySize );
	GET_PROP( triggerMethod );
	GET_PROP( outsideRth );
	GET_PROP( hidden );

	GET_PROP( overridePercentageConstraints );
	GET_PROP( rule80A );
	GET_PROP( allOrNone );
	GET_PROP( minQty );
	GET_PROP( percentOffset );
	GET_PROP( trailStopPrice );

	GET_PROP( openClose );
	GET_PROP( origin );
	GET_PROP( shortSaleSlot );
	GET_PROP( designatedLocation );

	// SMART routing only
	GET_PROP( discretionaryAmt );
	GET_PROP( eTradeOnly );
	GET_PROP( firmQuoteOnly );
	GET_PROP( nbboPriceCap );

	// BOX or VOL orders only
	GET_PROP( auctionStrategy );

	// BOX order only
	GET_PROP( startingPrice );
	GET_PROP( stockRefPrice );
	GET_PROP( delta );

	// pegged to stock or VOL orders
	GET_PROP( stockRangeLower );
	GET_PROP( stockRangeUpper );

	// VOLATILITY orders only
	GET_PROP( volatility );
	GET_PROP( volatilityType );
	GET_PROP( continuousUpdate );
	GET_PROP( referencePriceType );
	GET_PROP( deltaNeutralOrderType );
	GET_PROP( deltaNeutralAuxPrice );

	// SCALE orders only
	GET_PROP( scaleInitLevelSize );
	GET_PROP( scaleSubsLevelSize );
	GET_PROP( scalePriceIncrement );

	// Clearing info
	GET_PROP( account );
	GET_PROP( settlingFirm );
	GET_PROP( clearingAccount );
	GET_PROP( clearingIntent );

#undef GET_PROP

}

void CDlgExtOrd::setAttribsToOrder()
{

#define PUT_PROP(Prop) \
   m_order->Prop = m_##Prop;

#define PUT_PROP_BOOL(Prop) \
   m_order->Prop = m_##Prop != FALSE;

	// extended order fields
	PUT_PROP( tif );
	PUT_PROP( ocaGroup );
	PUT_PROP( ocaType );
	PUT_PROP( orderRef );
	PUT_PROP_BOOL( transmit );
	PUT_PROP( parentId );
	PUT_PROP_BOOL( blockOrder );
	PUT_PROP_BOOL( sweepToFill );
	PUT_PROP( displaySize );
	PUT_PROP( triggerMethod );
	PUT_PROP_BOOL( outsideRth );
	PUT_PROP_BOOL( hidden );

	PUT_PROP_BOOL( overridePercentageConstraints );
	PUT_PROP( rule80A );
	PUT_PROP_BOOL( allOrNone );
	PUT_PROP( minQty );
	PUT_PROP( percentOffset );
	PUT_PROP( trailStopPrice );

	PUT_PROP( openClose );
	//PUT_PROP(origin);
	m_order->origin = ( Origin )m_origin;

	PUT_PROP( shortSaleSlot );
	PUT_PROP( designatedLocation );

	// SMART routing only
	PUT_PROP( discretionaryAmt );
	PUT_PROP_BOOL( eTradeOnly );
	PUT_PROP_BOOL( firmQuoteOnly );
	PUT_PROP( nbboPriceCap );

	// BOX or VOL orders only
	PUT_PROP( auctionStrategy );

	// BOX order only
	PUT_PROP( startingPrice );
	PUT_PROP( stockRefPrice );
	PUT_PROP( delta );

	// pegged to stock or VOL orders
	PUT_PROP( stockRangeLower );
	PUT_PROP( stockRangeUpper );

	// VOLATILITY orders only
	PUT_PROP( volatility );
	PUT_PROP( volatilityType );
	PUT_PROP_BOOL( continuousUpdate );
	PUT_PROP( referencePriceType );
	PUT_PROP( deltaNeutralOrderType );
	PUT_PROP( deltaNeutralAuxPrice );

	// SCALE orders only
	PUT_PROP( scaleInitLevelSize );
	PUT_PROP( scaleSubsLevelSize );
	PUT_PROP( scalePriceIncrement );

	// Clearing info
	PUT_PROP( account );
	PUT_PROP( settlingFirm );
	PUT_PROP( clearingAccount );
	PUT_PROP( clearingIntent );

#undef PUT_PROP
}

void DDX_TextMax( CDataExchange* pDX, int ctrlID, int &value )
{
	CWnd *dlg = pDX->m_pDlgWnd;
	CEdit *editCtrl = ( CEdit* )dlg->GetDlgItem( ctrlID );
	CString temp;
	if ( pDX->m_bSaveAndValidate )
	{
		editCtrl->GetWindowText( temp );
		value = ( temp.GetLength() ? atoi( temp ) : INT_MAX );
	}
	else
	{
		if ( value != INT_MAX )
		{
			temp.Format( "%d", value );
		}
		else
		{
			temp.Empty();
		}
		editCtrl->SetWindowText( temp );
	}
}

void DDX_TextMax( CDataExchange* pDX, int ctrlID, double &value )
{
	CWnd *dlg = pDX->m_pDlgWnd;
	CEdit *editCtrl = ( CEdit* )dlg->GetDlgItem( ctrlID );
	CString temp;
	if ( pDX->m_bSaveAndValidate )
	{
		editCtrl->GetWindowText( temp );
		value = ( temp.GetLength() ? atof( temp ) : DBL_MAX );
	}
	else
	{
		if ( value != DBL_MAX )
		{
			temp.Format( "%lf", value );
		}
		else
		{
			temp.Empty();
		}
		editCtrl->SetWindowText( temp );
	}
}

void CDlgExtOrd::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange( pDX );
	//{{AFX_DATA_MAP(CDlgExtOrd)

	DDX_Text( pDX, IDC_TIME_IN_FORCE, m_tif );
	DDX_Text( pDX, IDC_OCA_GROUP, m_ocaGroup );
	DDX_Text( pDX, IDC_OCA_TYPE, m_ocaType );
	DDX_Text( pDX, IDC_ORDER_REF, m_orderRef );

	DDX_Text( pDX, IDC_ACCOUNT, m_account );
	DDX_Text( pDX, IDC_SETTLING_FIRM, m_settlingFirm );
	DDX_Text( pDX, IDC_CLEARING_ACCOUNT, m_clearingAccount );
	DDX_Text( pDX, IDC_CLEARING_INTENT, m_clearingIntent );

	DDX_Text( pDX, IDC_OPEN_CLOSE, m_openClose );
	DDX_Text( pDX, IDC_ORIGIN, m_origin );

	DDX_Text( pDX, IDC_TRANSMIT, m_transmit );
	DDX_Text( pDX, IDC_PARENT_ID, m_parentId );
	DDX_Text( pDX, IDC_BLOCKORDER, m_blockOrder );
	DDX_Text( pDX, IDC_DISPLAY_SIZE, m_displaySize );
	DDX_Text( pDX, IDC_OUTSIDE_RTH, m_outsideRth );
	DDX_Text( pDX, IDC_SWEEP_TO_FILL, m_sweepToFill );
	DDX_Text( pDX, IDC_TRIGGER_MTH, m_triggerMethod );
	DDX_Text( pDX, IDC_HIDDEN, m_hidden );
	DDX_Text( pDX, IDC_DISCRET_AMT, m_discretionaryAmt );
	DDX_Text( pDX, IDC_SHORT_SALE_SLOT, m_shortSaleSlot );
	DDX_Text( pDX, IDC_DESIGNATED_LOCATION, m_designatedLocation );

	DDX_Text( pDX, IDC_RULE_80A, m_rule80A );
	DDX_Text( pDX, IDC_ALL_OR_NONE, m_allOrNone );
	DDX_TextMax( pDX, IDC_MIN_QTY, m_minQty );
	DDX_TextMax( pDX, IDC_PERCENT_OFFSET, m_percentOffset );
	DDX_Text( pDX, IDC_ETRADE_ONLY, m_eTradeOnly );
	DDX_Text( pDX, IDC_FIRM_QUOTE_ONLY, m_firmQuoteOnly );
	DDX_TextMax( pDX, IDC_NBBO_PRICE_CAP, m_nbboPriceCap );
	DDX_TextMax( pDX, IDC_AUCTION_STRATEGY, m_auctionStrategy );
	DDX_TextMax( pDX, IDC_STARTING_PRICE, m_startingPrice );
	DDX_TextMax( pDX, IDC_STOCK_REF_PRICE, m_stockRefPrice );
	DDX_TextMax( pDX, IDC_DELTA, m_delta );
	DDX_TextMax( pDX, IDC_STOCK_RANGE_LOWER, m_stockRangeLower );
	DDX_TextMax( pDX, IDC_STOCK_RANGE_UPPER, m_stockRangeUpper );
	DDX_Text( pDX, IDC_OVERRIDE_PERCENTAGE_CONSTRAINTS, m_overridePercentageConstraints );
	DDX_TextMax( pDX, IDC_VOLATILITY, m_volatility );
	DDX_TextMax( pDX, IDC_VOLATILITY_TYPE, m_volatilityType );
	DDX_Text( pDX, IDC_DELTA_NEUTRAL_ORDER_TYPE, m_deltaNeutralOrderType );
	DDX_TextMax( pDX, IDC_DELTA_NEUTRAL_AUX_PRICE, m_deltaNeutralAuxPrice );
	DDX_TextMax( pDX, IDC_CONTINUOUS_UPDATE, m_continuousUpdate );
	DDX_TextMax( pDX, IDC_REFERENCE_PRICE_TYPE, m_referencePriceType );
	DDX_TextMax( pDX, IDC_TRAIL_STOP_PRICE, m_trailStopPrice );
	DDX_TextMax( pDX, IDC_EDIT_ORDER_SCALE_INIT_LEVEL_SIZE, m_scaleInitLevelSize );
	DDX_TextMax( pDX, IDC_EDIT_ORDER_SCALE_SUBS_LEVEL_SIZE, m_scaleSubsLevelSize );
	DDX_TextMax( pDX, IDC_EDIT_ORDER_SCALE_PRICE_INCR, m_scalePriceIncrement );

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP( CDlgExtOrd, CDialog )
	//{{AFX_MSG_MAP(CDlgExtOrd)
	// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED( IDOK, &CDlgExtOrd::OnOk )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgExtOrd message handlers

void CDlgExtOrd::OnOk()
{
	CDialog::OnOK();
	setAttribsToOrder();
}
