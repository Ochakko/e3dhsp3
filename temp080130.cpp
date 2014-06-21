	int ret;

	if( m_numTLV < 3 ){
		DbgOut( "d3ddisp : CreateSkinMatTex : tlvnum less than 3 ; skip\n" );
		return 0;//!!!!!!!!!
	}

	ret = CreateSkinMat( lpsh );
	if( ret ){
		DbgOut( "d3ddisp : CreateSkinMatTex : CreateSkinMat error !!!\n" );
		_ASSERT( 0 );
		return 1;
	}

///////
	int rblocknum = 0;
	int skinno, curskinstart, curskinend;
	TEXTUREBLOCK* curtexblock;
	RENDERBLOCK* currenderblock;
	int curstart;
	int texblockno = 0;


	curtexblock = texblock;

	for( skinno = 0; skinno < mskinblocknum; skinno++ ){


		curskinstart = (mskinblock + skinno)->startface;
		curskinend = (mskinblock + skinno)->endface;
		
		curstart = curskinstart;

		while( curskinend >= curtexblock->endface ){
			rblocknum++;
			mrenderblock = (RENDERBLOCK*)realloc( mrenderblock, sizeof( RENDERBLOCK ) * rblocknum );
			if( !mrenderblock ){
				DbgOut( "d3ddisp : CreateSkinMatTex : renderblock alloc error !!!\n" );
				_ASSERT( 0 );
				return 1;
			}

			currenderblock = mrenderblock + rblocknum - 1;
			currenderblock->skinno = skinno;
			//currenderblock->materialno = curtexblock->materialno;
			currenderblock->materialno = 0;
			currenderblock->startface = curstart;
			currenderblock->endface = curtexblock->endface;
			currenderblock->texname = curtexblock->texname;

			texblockno++;
			if( texblockno < texblocknum ){
				curtexblock = texblock + texblockno;
				curstart = curtexblock->startface;
			}else{
				break;
			}

		}
		if( curskinend < curtexblock->endface ){
			rblocknum++;
			mrenderblock = (RENDERBLOCK*)realloc( mrenderblock, sizeof( RENDERBLOCK ) * rblocknum );
			if( !mrenderblock ){
				DbgOut( "d3ddisp : CreateSkinMatTex : renderblock alloc error !!!\n" );
				_ASSERT( 0 );
				return 1;
			}

			currenderblock = mrenderblock + rblocknum - 1;
			currenderblock->skinno = skinno;
			//currenderblock->materialno = curtexblock->materialno;
			currenderblock->materialno = 0;
			currenderblock->startface = curstart;
			currenderblock->endface = curskinend;//!!!
			currenderblock->texname = curtexblock->texname;

		}

	}

	mrenderblocknum = rblocknum;

/***
// for dbg
	int blno;
	for( blno = 0; blno < mrenderblocknum; blno++ ){
		RENDERBLOCK* currb;
		currb = mrenderblock + blno;

		DbgOut( "check renderblock : no %d : materialno %d, skinno %d, texname %s, startface %d, endface %d\r\n",
			blno, currb->materialno, currb->skinno, currb->texname, currb->startface, currb->endface );
	}
	DbgOut( "\r\n" );
***/

	return 0;
