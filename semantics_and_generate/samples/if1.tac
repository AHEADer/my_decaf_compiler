main:
	BeginFunc 24 ;
	_tmp0 = 1 ;
	IfZ _tmp0 Goto _L0 ;
	_tmp1 = 1 ;
	PushParam _tmp1 ;
	LCall _PrintInt ;
	PopParams 4 ;
	Goto _L1 ;
_L0:
	_tmp2 = 2 ;
	PushParam _tmp2 ;
	LCall _PrintInt ;
	PopParams 4 ;
_L1:
	_tmp3 = 3 ;
	PushParam _tmp3 ;
	LCall _PrintInt ;
	PopParams 4 ;
	_tmp4 = 1 ;
	IfZ _tmp4 Goto _L2 ;
	_tmp5 = 4 ;
	PushParam _tmp5 ;
	LCall _PrintInt ;
	PopParams 4 ;
	Goto _L3 ;
_L2:
_L3:
	EndFunc ;
