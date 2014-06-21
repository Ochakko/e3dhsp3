#define		MYMOVEFLAGH		1

// obj inter kind
enum { INTERKICKED, INTERPUSHED, INTERRIDEON, INTERKINDMAX 
};

enum { ZSURI, XSURI, SURIMAX };

enum { EKASA, EBEER, EUTIWA, EKINDMAX };


//EDITPOINT!!!MYCHARMOVE
enum	{
	NONE
	,IDLE0, IDLE1, IDLE2, IDLE3, IDLE4, IDLE5, IDLE6, IDLE7, IDLE8, IDLE9, IDLE10, IDLEMAX
	,WALK0, WALK1, WALK2, WALK3, WALK4, WALK5, WALK6, WALK7, WALK8, WALK9, WALK10, WALKMAX
	,JUMP0, JUMP1, JUMP2, JUMP3, JUMP4, JUMP5, JUMP6, JUMP7, JUMP8, JUMP9, JUMPMAX
	,KICK0, KICK1, KICKMAX
	,RIDE_C0, RIDE_CMAX
	,PUSHOBJ0, PUSHOBJMAX
	,PUSHED0, PUSHEDMAX
	,INTERSECT0, INTERSECTMAX
	,RIDEONIDLE0, RIDEONIDLEMAX
	,RIDEON0, RIDEON1, RIDEONMAX
	,KICKED0, KICKED1, KICKED2, KICKED3, KICKED4, KICKED5, KICKED6, KICKED7, KICKED8, KICKEDMAX
	,MPUSHED0, MPUSHED1, MPUSHEDMAX
	,ZROTL0, ZROTLMAX
	,ZROTR0, ZROTRMAX
	,KANIL0, KANILMAX
	,KANIR0, KANIRMAX
	,DROPHOLE0, DROPHOLE1, DROPHOLE2, DROPHOLE3, DROPHOLE4, DROPHOLEMAX
	,UPFLOOR0, UPFLOOR1, UPFLOOR2, UPFLOOR3, UPFLOORMAX
	,DOWNFLOOR0, DOWNFLOOR1, DOWNFLOOR2, DOWNFLOOR3, DOWNFLOORMAX
	,UMAIDLE0, UMAIDLEMAX
	,UMA0, UMA1, UMA2, UMA3, UMAMAX
	,PIS0, PIS1, PIS2, PIS3, PIS4, PIS5, PIS6, PIS7, PIS8, PISMAX
	,FIRE0, FIRE1, FIRE2, FIRE3, FIRE4, FIREMAX
	,DETH
	,MYFLAGMAX
};
//ENDEDIT

#define	BINDPARAMMAX	200
#define	BINDSTARTNO		(MYFLAGMAX + 1)
#define	MYMOVEMAX		(MYFLAGMAX + BINDPARAMMAX)


// kamechar move
enum { KNONE,
		KIDLE0, KIDLE1, KIDLEMAX,
		KWALK0, KWALKMAX,
		KKICK0, KKICK1, KKICKMAX,
		KPUSHOBJ0, KPUSHOBJMAX,
		KPUSHED0, KPUSHEDMAX,// �K�� �Q�� (���₳�Ȃ� movestep)
		KINTERSECT0, KINTERSECTMAX, //21
		KKICKED0, KKICKED1, KKICKED2, KKICKED3, KKICKED4, 
		KKICKED5, KKICKED6, KKICKED7, KKICKED8, KKICKEDMAX, 
		KMPUSHED0, KMPUSHED1, KMPUSHEDMAX, 	//39
		KZROTL0, KZROTLMAX,
		KZROTR0, KZROTRMAX,
		KKANIL0, KKANILMAX,
		KKANIR0, KKANIRMAX,//47
		KDROPHOLEMAX,//53
		KFIRE0, KFIRE1, KFIRE2, KFIRE3, KFIRE4, KFIREMAX,
		KDETH,
		KAMEFLAGMAX
};




// enemy move
enum { ENONE, 
		EIDLE0, EIDLE1, EIDLE2, EIDLE3, EIDLEMAX, //5
		EWALK0, EWALK1, EWALK2, EWALK3, EWALK4, EWALK5, EWALK6, EWALKMAX, //13
		EKICK0, EKICK1, EKICKMAX,
		EPUSHOBJ0, EPUSHOBJMAX,
		EPUSHED0, EPUSHEDMAX,// intersect�ɂ�� pushed // 20
		EMPUSHED0, EMPUSHED1, EMPUSHEDMAX, // Mychar pushobj�ɂ��pushed
		EMKICKED0, EMKICKED1, EMKICKED2, EMKICKED3, EMKICKED4, 
		EMKICKED5, EMKICKED6, EMKICKED7, EMKICKED8, EMKICKEDMAX,   
		EINTERSECT0, EINTERSECTMAX,
		ERIDEONIDLE0, ERIDEONIDLEMAX,
		ESERCH0, ESERCH1, ESERCH2, ESERCH3, ESERCH4, 
		ESERCH5, ESERCH6, ESERCH7, ESERCH8, ESERCH9,
		ESERCH10, ESERCH11, ESERCH12, ESERCH13, ESERCHMAX, // 52
		EAWAY0, EAWAY1, EAWAY2, EAWAY3, EAWAY4, EAWAY5, EAWAY6, EAWAYMAX, //60 
		EDROPHOLE0, EDROPHOLE1, EDROPHOLE2, EDROPHOLE3, EDROPHOLE4, 
		EDROPHOLE5, EDROPHOLE6, EDROPHOLE7, EDROPHOLE8, EDROPHOLE9, 
		EDROPHOLEMAX,
		EHAIHAI0, EHAIHAI1, EHAIHAI2, EHAIHAI3, EHAIHAIMAX, 
		EUMAIDLE0, EUMAIDLEMAX, // MYCHAR �� �̂���
		EUMA0, EUMA1, EUMA2, EUMA3, EUMAMAX, // �n��� �͂��͂� 
		EMUMAPUSHED0, EMUMAPUSHED1, EMUMAPUSHEDMAX, // Mychar pushobj�ɂ��pushed
		EUMAYEN0, EUMAYEN1, EUMAYEN2, EUMAYEN3, EUMAYENMAX, // �n��蒆�� YEN �E�� 
		EDETH,
		EFLAGMAX 
};


// chair move
enum { CNONE,
		CKICKED0, CKICKED1, CKICKED2, CKICKED3, CKICKED4, CKICKED5, 
		CKICKED6, CKICKED7, CKICKED8, CKICKED9,  
		CKICKED10, CKICKED11, CKICKED12, CKICKED13, CKICKED14, CKICKED15, 
		CKICKED16, CKICKED17, CKICKED18, CKICKED19, CKICKEDMAX, 
		CPUSHED0, CPUSHED1, CPUSHEDMAX,
		CRIDEON0, CRIDEON1, CRIDEONMAX,
		CVIBRATE0, CVIBRATE1, CVIBRATE2, CVIBRATEMAX,
		CDROPHOLE0, CDROPHOLE1, CDROPHOLE2, CDROPHOLE3, CDROPHOLE4, 
		CDROPHOLE5, CDROPHOLE6, CDROPHOLE7, CDROPHOLE8, CDROPHOLE9, 
		CDROPHOLEMAX,
		CDETH,
		CFLAGMAX
};

// desk move
enum { DNONE,
		DPUSHED0, DPUSHED1, DPUSHEDMAX,
		DFLAGMAX
};

// hole move
enum {  HNONE,
		HOPEN0, HOPEN1, HOPEN2, HOPEN3, HOPENMAX,
		HOPENED0, HOPENED1, HOPENEDMAX, 
		HCLOSE0, HCLOSE1, HCLOSEMAX,
		HFLAGMAX
};

// sekizou move
enum { SNONE,
	   SPUSHED0, SPUSHED1, SPUSHED2, SPUSHED3, SPUSHED4,
	   SPUSHED5, SPUSHED6, SPUSHED7, SPUSHED8, SPUSHED9, 
	   SPUSHEDMAX, 
	   SFLAGMAX
};

// Yen move
enum { YNONE,
	   YROT0, YROT1, YROT2, YROT3, YROT4, YROT5, 
	   YROT6, YROT7, YROT8, YROT9, YROT10, YROTMAX, 
	   YKICKED0, YKICKED1, YKICKED2, YKICKED3, YKICKED4, 
	   YKICKED5, YKICKED6, YKICKED7, YKICKED8, YKICKEDMAX, 
	   YDROPHOLE0, YDROPHOLE1, YDROPHOLE2, YDROPHOLE3, YDROPHOLE4, 
	   YDROPHOLE5, YDROPHOLE6, YDROPHOLE7, YDROPHOLE8, YDROPHOLE9, 
	   YDROPHOLEMAX,
	   YDETH,
	   YFLAGMAX
};

// moveposter
enum { MPNONE,
	   MPPHASE0, MPPHASE1, MPPHASE2, MPPHASE3, MPPHASEMAX,  
	   MPFLAGMAX
};

// poster
enum { PNONE,
	   PDOBON0, PDOBON1, PDOBON2, PDOBON3, PDOBON4, PDOBON5, 
	   PDOBON6, PDOBON7, PDOBON8, PDOBON9, PDOBONMAX, 
	   PFLAGMAX
};