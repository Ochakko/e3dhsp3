int CD3DDisp::RenderTriPhong( LPDIRECT3DDEVICE9 pd3dDevice, CShdHandler* lpsh, float* toonparams, float* fogparams, int lightflag,
	DWORD switchno, DWORD swstate, int srcenabletex, CMotionCtrl* srcfirstjoint, int srcframeno, int srcmotid )
{
	HRESULT hres;
	int ret = 0;
	static int dbgcnt = 0;

	
//DbgOut( "d3ddisp : RenderTriPhong\n" );
	hres = g_pEffect->SetValue( "mFogParams", fogparams, sizeof( float ) * 2 );
	if( hres != D3D_OK ){
		DbgOut( "d3ddisp : RenderTriPhong : fogparams set error !!!\n" );
		_ASSERT( 0 );
		return 1;
	}

	hres = g_pEffect->SetMatrix( "mView", &m_matView );
	if( hres != D3D_OK ){
		DbgOut( "d3ddisp : RenderTriPhong : view set error !!!\n" );
		_ASSERT( 0 );
		return 1;
	}
	hres = g_pEffect->SetMatrix( "mProj", &m_matProj );
	if( hres != D3D_OK ){
		DbgOut( "d3ddisp : RenderTriPhong : proj set error !!!\n" );
		_ASSERT( 0 );
		return 1;
	}

	hres = g_pEffect->SetFloat( "mAlpha", m_alpha );
	if( hres != D3D_OK ){
		DbgOut( "d3ddisp : RenderTriPhong : mAlpha SetFloat error !!!\n" );
		_ASSERT( 0 );
		return 1;
	}

//float3 mLightParams[5][7];
//0: x=validflag, y=type, z=divRange
//1: x=cosPhi, y=divCosPhi
//2: xyz=diffuse
//3: xyz=specular
//4: xyz=ambient
//5: xyz=position
//6: xyz=direction

	float tmplparam[5][7][4];
	ZeroMemory( tmplparam, sizeof( float ) * 5 * 7 * 4 );

	CLightData* curl;
	curl = g_lighthead;
	int setlno = 0;
	int lno;
	for( lno = 0; lno < 5; lno++ ){
		if( curl ){
			tmplparam[lno][0][0] = 1.0f;

			tmplparam[lno][2][0] = curl->Diffuse.x;
			tmplparam[lno][2][1] = curl->Diffuse.y;
			tmplparam[lno][2][2] = curl->Diffuse.z;

			tmplparam[lno][3][0] = curl->Specular.x;
			tmplparam[lno][3][1] = curl->Specular.y;
			tmplparam[lno][3][2] = curl->Specular.z;

			tmplparam[lno][4][0] = curl->Ambient.x;
			tmplparam[lno][4][1] = curl->Ambient.y;
			tmplparam[lno][4][2] = curl->Ambient.z;

			switch( curl->Type ){
			case D3DLIGHT_DIRECTIONAL:
				tmplparam[lno][0][1] = 0.0f;

				tmplparam[lno][6][0] = curl->orgDirection.x;
				tmplparam[lno][6][1] = curl->orgDirection.y;
				tmplparam[lno][6][2] = curl->orgDirection.z;

				break;
			case D3DLIGHT_POINT:
				tmplparam[lno][0][1] = 1.0f;

				tmplparam[lno][0][2] = curl->divRange;


				tmplparam[lno][5][0] = curl->orgPosition.x;
				tmplparam[lno][5][1] = curl->orgPosition.y;
				tmplparam[lno][5][2] = curl->orgPosition.z;

				break;
			case D3DLIGHT_SPOT:
				tmplparam[lno][0][1] = 2.0f;

				tmplparam[lno][0][2] = curl->divRange;
				tmplparam[lno][1][0] = curl->cosPhi;
				tmplparam[lno][1][1] = curl->divcosPhi;

				tmplparam[lno][5][0] = curl->orgPosition.x;
				tmplparam[lno][5][1] = curl->orgPosition.y;
				tmplparam[lno][5][2] = curl->orgPosition.z;

				tmplparam[lno][6][0] = curl->orgDirection.x;
				tmplparam[lno][6][1] = curl->orgDirection.y;
				tmplparam[lno][6][2] = curl->orgDirection.z;

				break;
			}
				
			curl = curl->nextlight;
			setlno++;

		}else{
			tmplparam[lno][0][0] = 0.0f;
			tmplparam[lno][0][1] = -1.0f;
		}
	}

	if( (g_chkVS >= 20) || (g_chkVS == 0) ){
		hres = g_pEffect->SetValue( "mLightParams", &(tmplparam[0][0][0]), sizeof( float ) * 5 * 7 * 4 );
		if( hres != D3D_OK ){
			DbgOut( "d3ddisp : RenderTriPhong : mLightParam SetValue error !!!\n" );
			_ASSERT( 0 );
			return 1;
		}
	}else{
		hres = g_pEffect->SetValue( "mLightParams", &(tmplparam[0][0][0]), sizeof( float ) * 1 * 7 * 4 );
		if( hres != D3D_OK ){
			DbgOut( "d3ddisp : RenderTriPhong : mLightParam SetValue error !!!\n" );
			_ASSERT( 0 );
			return 1;
		}
	}

	float fsetlno;
	if( (g_renderstate[D3DRS_LIGHTING] == FALSE) || (lightflag == 0) ){
		fsetlno = -1.0f;//<--- lighting –³Œø‚ÌƒTƒCƒ“
		hres = g_pEffect->SetFloat( "mLightNum", fsetlno );
		if( hres != D3D_OK ){
			DbgOut( "d3ddisp : RenderTriPhong : mLightNum SetFloat error !!!\n" );
			_ASSERT( 0 );
			return 1;
		}
	}else{
		fsetlno = (float)setlno;
		hres = g_pEffect->SetFloat( "mLightNum", fsetlno );
		if( hres != D3D_OK ){
			DbgOut( "d3ddisp : RenderTriPhong : mLightNum SetFloat error !!!\n" );
			_ASSERT( 0 );
			return 1;
		}
	}

	hres = g_pEffect->SetValue( "mEyePos", (void*)(&m_EyePt), sizeof( float ) * 3 );
	if( hres != D3D_OK ){
		DbgOut( "d3ddisp : RenderTriPhong : LightSpecular set error !!!\n" );
		_ASSERT( 0 );
		return 1;	
	}

	if( (g_usePS == 1) && (toonparams) ){
		hres = g_pEffect->SetValue( "mToonParams", toonparams, sizeof( float ) * 4 );
		if( hres != D3D_OK ){
			DbgOut( "d3ddisp : RenderTriPhong : toonparams set error !!!\n" );
			_ASSERT( 0 );
			return 1;
		}
	}

///////////////
	UINT cPasses, iPass;
	//UINT cPasses2, iPass2;

	
	int renderno;
	int befblno = -1;
	for( renderno = 0; renderno < mrenderblocknum; renderno++ ){
		RENDERBLOCK* currb;
		currb = mrenderblock + renderno;

		int blno;
		blno = currb->skinno;

		D3DXMATRIX* curskinmat = *(mskinmat + blno);
		int curskinnum = *(mskinmatnum + blno);

		char* curtexname = 0;
		int newrapstate;

//DbgOut( "d3ddisp render : RENDERBLOCK : no %d, materialno %d, skinno %d, startface %d, endface %d\r\n",
//	renderno, currb->materialno, currb->skinno, currb->startface, currb->endface );

		/***
		LPDIRECT3DTEXTURE9 curtex;
		curtex = (ptoon1 + currb->materialno)->tex;
		pd3dDevice->SetTexture( 0, curtex );//!!!!!!!!!
		***/

		CMQOMaterial* curmqomat;
		curmqomat = currb->mqomat;

		ret = curmqomat->SetCurTexname( switchno, swstate, srcenabletex, srcfirstjoint, srcframeno, srcmotid );
		_ASSERT( !ret );

		curtexname = curmqomat->curtexname;
		if( curmqomat->curtexname == 0 )
			curtexname = NULL;

		
		switch( curmqomat->texrule ){
		case TEXRULE_X:
		case TEXRULE_Y:
		case TEXRULE_Z:
			newrapstate = 0;
			break;
		case TEXRULE_CYLINDER:
			newrapstate = D3DWRAP_U;
			break;
		case TEXRULE_SPHERE:
			//newrapstate = D3DWRAP_U | D3DWRAP_V;
			newrapstate = D3DWRAP_U;
			break;
		case TEXRULE_MQ:
		default:
			newrapstate = 0;
			break;
		}
		pd3dDevice->SetRenderState( D3DRS_WRAP0, newrapstate );
		g_renderstate[ D3DRS_WRAP0 ] = newrapstate;


		LPDIRECT3DTEXTURE9 curtex = NULL;		
		curtex = g_texbnk->GetTexData( curtexname, curmqomat->transparent );

		pd3dDevice->SetTexture( 0, curtex );
		pd3dDevice->SetTexture( 1, NULL );
		pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
		pd3dDevice->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE ); 
		pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
		//pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
		pd3dDevice->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );//!!!!


		if( (lpsh->m_shader == COL_TOON0) && (g_usePS == 1) ){
			if( lptex != NULL ){
				if( curskinnum == 1 ){
					hres = g_pEffect->SetTechnique( "RenderSceneBone0Toon" );
					if( hres != D3D_OK ){
						DbgOut( "d3ddisp : RenderTriPhong : SetTechnique error !!!\n" );
						_ASSERT( 0 );
						return 1;
					}
				}else if( curskinnum == 2 ){
					hres = g_pEffect->SetTechnique( "RenderSceneBone1Toon" );
					if( hres != D3D_OK ){
						DbgOut( "d3ddisp : RenderTriPhong : SetTechnique error !!!\n" );
						_ASSERT( 0 );
						return 1;
					}
				}else{
					hres = g_pEffect->SetTechnique( "RenderSceneBone4Toon" );
					if( hres != D3D_OK ){
						DbgOut( "d3ddisp : RenderTriPhong : SetTechnique error !!!\n" );
						_ASSERT( 0 );
						return 1;
					}
				}
			}else{
				if( curskinnum == 1 ){
					hres = g_pEffect->SetTechnique( "RenderSceneBone0ToonNoTex" );
					if( hres != D3D_OK ){
						DbgOut( "d3ddisp : RenderTriPhong : SetTechnique error !!!\n" );
						_ASSERT( 0 );
						return 1;
					}
				}else if( curskinnum == 2 ){
					hres = g_pEffect->SetTechnique( "RenderSceneBone1ToonNoTex" );
					if( hres != D3D_OK ){
						DbgOut( "d3ddisp : RenderTriPhong : SetTechnique error !!!\n" );
						_ASSERT( 0 );
						return 1;
					}
				}else{
					hres = g_pEffect->SetTechnique( "RenderSceneBone4ToonNoTex" );
					if( hres != D3D_OK ){
						DbgOut( "d3ddisp : RenderTriPhong : SetTechnique error !!!\n" );
						_ASSERT( 0 );
						return 1;
					}
				}
			}
		}else{
			if( curskinnum == 1 ){
				hres = g_pEffect->SetTechnique( "RenderSceneBone0" );
				if( hres != D3D_OK ){
					DbgOut( "d3ddisp : RenderTriPhong : SetTechnique error !!!\n" );
					_ASSERT( 0 );
					return 1;
				}
			}else if( curskinnum == 2 ){
				hres = g_pEffect->SetTechnique( "RenderSceneBone1" );
				if( hres != D3D_OK ){
					DbgOut( "d3ddisp : RenderTriPhong : SetTechnique error !!!\n" );
					_ASSERT( 0 );
					return 1;
				}
			}else{
				hres = g_pEffect->SetTechnique( "RenderSceneBone4" );
				if( hres != D3D_OK ){
					DbgOut( "d3ddisp : RenderTriPhong : SetTechnique error !!!\n" );
					_ASSERT( 0 );
					return 1;
				}
			}
		}

		if( blno != befblno ){
			hres = g_pEffect->SetMatrixArray( "mWorldMatrixArray", curskinmat, curskinnum );
			if( hres != D3D_OK ){
				DbgOut( "d3ddisp : RenderTriPhong : worldmatrixarray set error !!!\n" );
				_ASSERT( 0 );
				return 1;
			}
		}

		/////////
		hres = g_pEffect->Begin(&cPasses, 0);
		if( hres != D3D_OK ){
			DbgOut( "d3ddisp : RenderTriPhong : effect Begin error !!!\n" );
			_ASSERT( 0 );
			return 1;
		}

		for (iPass = 0; iPass < cPasses; iPass++){
			hres = g_pEffect->BeginPass(iPass);
			if( hres != D3D_OK ){
				DbgOut( "d3ddisp : RenderTriPhong : effect BeginPass error !!!\n" );
				_ASSERT( 0 );
				return 1;
			}


			// The effect interface queues up the changes and performs them 
			// with the CommitChanges call. You do not need to call CommitChanges if 
			// you are not setting any parameters between the BeginPass and EndPass.
			// V( g_pEffect->CommitChanges() );

			int curnumprim;
			curnumprim = currb->endface - currb->startface;

			if( curnumprim > 0 ){
				pd3dDevice->SetVertexDeclaration( m_pskindecl );
				pd3dDevice->SetStreamSource( 0, *(m_ArrayVB + blno), 0, sizeof(SKINVERTEX) );
				pd3dDevice->SetIndices( m_IB );

				hres = pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST,
													0,
													0,
													m_numTLV,
													currb->startface * 3,
													curnumprim
													);
			}

			if( m_revArrayVB && (curnumprim > 0) ){
				pd3dDevice->SetVertexDeclaration( m_pskindecl );
				pd3dDevice->SetStreamSource( 0, *(m_revArrayVB + blno), 0, sizeof(SKINVERTEX) );		
				pd3dDevice->SetIndices( m_revIB );
				hres = pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST,
												0,
												0,
												m_numTLV,
												currb->startface * 3,
												curnumprim
												);

			}

			hres = g_pEffect->EndPass();
			if( hres != D3D_OK ){
				DbgOut( "d3ddisp : RenderTriPhong : effect EndPass error !!!\n" );
				_ASSERT( 0 );
				return 1;
			}

		}
		hres = g_pEffect->End();
		if( hres != D3D_OK ){
			DbgOut( "d3ddisp : RenderTriPhong : effect End error !!!\n" );
			_ASSERT( 0 );
			return 1;
		}


		befblno = blno;
				
	}	

	return ret;
}
