	curhs->m_gpd.m_gpe.pos = D3DXVECTOR3( posx, posy, posz );
	curhs->m_gpd.m_gpe.e3dpos = curhs->m_gpd.m_gpe.pos;
	curhs->m_gpd.CalcMatWorld();


	CQuaternion newq;
	newq.SetParams( srcqptr->w, srcqptr->x, srcqptr->y, srcqptr->z );

	D3DXVECTOR3 neweul;
	ret = qToEuler( 0, &newq, &neweul );
	_ASSERT( !ret );
	ret = modifyEuler( &neweul, &curhs->m_gpd.m_gpe.e3drot );
	_ASSERT( !ret );
	curhs->m_gpd.m_gpe.e3drot = neweul;
	curhs->m_twist = srcqptr->twist;

	curhs->m_gpd.CalcMatWorld();
