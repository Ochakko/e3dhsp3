//-----------------------------------------------------------------------------
// File: DMUtil.cpp
//
// Desc: DirectMusic framework classes for playing DirectMusic segments and
//       DirectMusic scripts. Feel free to use this class as a starting point 
//       for adding extra functionality.
//
// Copyright (c) 1999-2001 Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------

//#include "stdafx.h"

//#define STRICT
#include <dmusicc.h>
#include <dmusici.h>
#include <dsound.h>
#include <dxerr9.h>
#include "DMUtil_ed.h"
#include "DXUtil.h"

#define DBGH
#include <dbg.h>

#include <crtdbg.h>



//-----------------------------------------------------------------------------
// Name: CMusicManager::CMusicManager()
// Desc: Constructs the class
//-----------------------------------------------------------------------------
CMusicManager::CMusicManager()
{
    m_pLoader       = NULL;
    m_pPerformance  = NULL;
    
    // Initialize COM
    //HRESULT hr = CoInitialize(NULL);
    //m_bCleanupCOM = SUCCEEDED(hr);
	m_bCleanupCOM = 1;

}




//-----------------------------------------------------------------------------
// Name: CMusicManager::~CMusicManager()
// Desc: Destroys the class
//-----------------------------------------------------------------------------
CMusicManager::~CMusicManager()
{
    SAFE_RELEASE( m_pLoader ); 

    if( m_pPerformance )
    {
        // If there is any music playing, stop it.
        m_pPerformance->Stop( NULL, NULL, 0, 0 );
        m_pPerformance->CloseDown();

        SAFE_RELEASE( m_pPerformance );
    }

    //if( m_bCleanupCOM )
    //    CoUninitialize();
}




//-----------------------------------------------------------------------------
// Name: CMusicManager::Initialize()
// Desc: Inits DirectMusic using a standard audio path
//-----------------------------------------------------------------------------
HRESULT CMusicManager::Initialize( HWND hWnd, DWORD dwPChannels, DWORD dwDefaultPathType )
{
    HRESULT hr;

    // Create loader object
    if( FAILED( hr = CoCreateInstance( CLSID_DirectMusicLoader, NULL, CLSCTX_INPROC, 
		IID_IDirectMusicLoader8, (void**)&m_pLoader ) ) ){
			DbgOut( "HS : MusicManager : Initialize : Create MusicLoader error !!!\n" );
			return DXTRACE_ERR( TEXT("CoCreateInstance"), hr );

		}
    // Create performance object
    if( FAILED( hr = CoCreateInstance( CLSID_DirectMusicPerformance, NULL, CLSCTX_INPROC, 
		IID_IDirectMusicPerformance8, (void**)&m_pPerformance ) ) ){
			DbgOut( "HS : MusicManager : Initialize : Create MusicPerformance error !!!\n" );
			return DXTRACE_ERR( TEXT("CoCreateInstance"), hr );
		}

    // Initialize the performance with the standard audio path.
    // This initializes both DirectMusic and DirectSound and 
    // sets up the synthesizer. Typcially its easist to use an 
    // audio path for playing music and sound effects.

    hr = m_pPerformance->InitAudio( NULL, NULL, hWnd, dwDefaultPathType, dwPChannels, DMUS_AUDIOF_ALL, NULL );
Sleep( 500 );//!!!!!!!!!!!!!!! 環境によっては、これがないと、音が鳴らないことがあるらしい。
	
	if( FAILED( hr ) ){
		DbgOut( "HS : MusicManager : Initialize : InitAudio error !!!\n" );

		if( hr == DSERR_NODRIVER )
        {
            DXTRACE( "Warning: No sound card found\n" );
            return hr;
        }

        return DXTRACE_ERR( TEXT("InitAudio"), hr );
    }

    return S_OK;
}


HRESULT CMusicManager::SetVolume( long lvol )
{
	HRESULT hr;
	hr = m_pPerformance->SetGlobalParam( GUID_PerfMasterVolume, (void*)&lvol, sizeof( long ) );
	if( FAILED( hr ) ){
		DbgOut( "mucismanager : perf : SetGlobalParam volume error !!!\n" );
		_ASSERT( 0 );
	}
	return hr;

}


//-----------------------------------------------------------------------------
// Name: CMusicManager::SetSearchDirectory()
// Desc: Sets the search directory.  If not called, the current working
//       directory is used to load content.
//-----------------------------------------------------------------------------
HRESULT CMusicManager::SetSearchDirectory( const TCHAR* strMediaPath )
{
	HRESULT hr;

    if( NULL == m_pLoader )
        return E_UNEXPECTED;

    // DMusic only takes wide strings
    WCHAR wstrMediaPath[MAX_PATH];
    DXUtil_ConvertGenericStringToWide( wstrMediaPath, strMediaPath );

    hr = m_pLoader->SetSearchDirectory( GUID_DirectMusicAllTypes, 
                                          wstrMediaPath, FALSE );
	if( hr != DS_OK ){
		DbgOut( "HS : MusicManager : SetSearchDirectory : loader SetSearchDirectory error \n" );
		return 1;
	}

//ScanDirectory
	hr = m_pLoader->ScanDirectory(
			CLSID_DirectMusicSegment, 
			//CLSID_DirectMusicStyle,
			L"*",
			NULL );
	if( (hr != S_OK) && (hr != S_FALSE) ){
		DbgOut( "HS : MusicManager : SetSearchDirectory : loader ScanDirectory error \n" );
		return 1;
	}

	return 0;
}




//-----------------------------------------------------------------------------
// Name: CMusicManager::GetDefaultAudioPath()
// Desc: 
//-----------------------------------------------------------------------------
IDirectMusicAudioPath8* CMusicManager::GetDefaultAudioPath()
{
    IDirectMusicAudioPath8* pAudioPath = NULL;
    if( NULL == m_pPerformance )
        return NULL;

    m_pPerformance->GetDefaultAudioPath( &pAudioPath );
    return pAudioPath;
}




//-----------------------------------------------------------------------------
// Name: CMusicManager::CollectGarbage()
// Desc: Tells the loader to cleanup any garbage from previously 
//       released objects.
//-----------------------------------------------------------------------------
VOID CMusicManager::CollectGarbage()
{
    if( m_pLoader )
        m_pLoader->CollectGarbage();
}




HRESULT CMusicManager::CreateSegmentFromBuf( CMusicSegment** ppSegment, char* buf, int bufsize,
		                           BOOL bDownloadNow, BOOL bIsMidiFile )
{



    HRESULT               hr;
    IDirectMusicSegment8* pSegment = NULL;

    DMUS_OBJECTDESC      ObjDesc; 
    ObjDesc.dwSize = sizeof(DMUS_OBJECTDESC);
    ObjDesc.guidClass = CLSID_DirectMusicSegment;
    ObjDesc.dwValidData = DMUS_OBJ_CLASS | DMUS_OBJ_MEMORY;
    ObjDesc.pbMemData = (BYTE*)buf;
    ObjDesc.llMemLength = bufsize;
 
    hr = m_pLoader->GetObject(
            &ObjDesc, IID_IDirectMusicSegment8, 
            (void**)&pSegment );
	if( FAILED( hr ) )
	{

		if( hr == DMUS_S_PARTIALLOAD ){
			//正常な場合もある
			DbgOut( "HS : musicmanager : CreateSegmentFromFile : LoadObjectFromFile : partialload \n" );
		}else{
			//error
			DbgOut( "HS : musicmanager : CreateSegmentFromFile : LoadObjectFromFile error \n" );
		}
        //if( hr == DMUS_E_LOADER_FAILEDOPEN )
        //    return hr;
        //return DXTRACE_ERR( TEXT("LoadObjectFromFile"), hr );

	}

    *ppSegment = new CMusicSegment( m_pPerformance, m_pLoader, pSegment );
	if (!*ppSegment){
		DbgOut( "HS : musicmanager : CreateSegmentFromFile : musicsegment alloc error \n" );

       return E_OUTOFMEMORY;
	}

    if( bIsMidiFile )
    {
        if( FAILED( hr = pSegment->SetParam( GUID_StandardMIDIFile, 
			0xFFFFFFFF, 0, 0, NULL ) ) ){
											 
				DbgOut( "HS : musicmanager : CreateSegmentFromFile : segment SetParam error %x\n", hr );
				DbgOut( "HS : SetParam err code UNSUPPORTED %x   TRACK NOT FOUND %x   POINTER %x\n",
					DMUS_E_SET_UNSUPPORTED, 
					DMUS_E_TRACK_NOT_FOUND, 
					E_POINTER 
				);


				return DXTRACE_ERR( TEXT("SetParam"), hr );
			}
    }

    if( bDownloadNow )
    {
		if( FAILED( hr = (*ppSegment)->Download() ) ){
			DbgOut( "HS : musicmanager : CreateSegmentFromFile : segment download error \n" );

            return DXTRACE_ERR( TEXT("Download"), hr );
		}
    }

    return S_OK;
}


//-----------------------------------------------------------------------------
// Name: CMusicManager::CreateSegmentFromFile()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CMusicManager::CreateSegmentFromFile( CMusicSegment** ppSegment, 
                                              TCHAR* strFileName, 
                                              BOOL bDownloadNow,
                                              BOOL bIsMidiFile )
{
    HRESULT               hr;
    IDirectMusicSegment8* pSegment = NULL;

    // DMusic only takes wide strings
    WCHAR wstrFileName[MAX_PATH];
    DXUtil_ConvertGenericStringToWide( wstrFileName, strFileName );

    if ( FAILED( hr = m_pLoader->LoadObjectFromFile( CLSID_DirectMusicSegment,
                                                     IID_IDirectMusicSegment8,
                                                     wstrFileName,
                                                     (LPVOID*) &pSegment ) ) )
    {
		if( hr == DMUS_S_PARTIALLOAD ){
			//正常な場合もある
			DbgOut( "HS : musicmanager : CreateSegmentFromFile : LoadObjectFromFile : partialload \n" );
		}else{
			//error
			DbgOut( "HS : musicmanager : CreateSegmentFromFile : LoadObjectFromFile error \n" );
		}
        //if( hr == DMUS_E_LOADER_FAILEDOPEN )
        //    return hr;
        //return DXTRACE_ERR( TEXT("LoadObjectFromFile"), hr );
    }

    *ppSegment = new CMusicSegment( m_pPerformance, m_pLoader, pSegment );
	if (!*ppSegment){
		DbgOut( "HS : musicmanager : CreateSegmentFromFile : musicsegment alloc error \n" );
        return E_OUTOFMEMORY;
	}

    if( bIsMidiFile )
    {
        if( FAILED( hr = pSegment->SetParam( GUID_StandardMIDIFile, 
			0xFFFFFFFF, 0, 0, NULL ) ) ){
											 
				DbgOut( "HS : musicmanager : CreateSegmentFromFile : segment SetParam error \n" );
				return DXTRACE_ERR( TEXT("SetParam"), hr );
			}
    }

    if( bDownloadNow )
    {
		if( FAILED( hr = (*ppSegment)->Download() ) ){
			DbgOut( "HS : musicmanager : CreateSegmentFromFile : segment download error \n" );
            return DXTRACE_ERR( TEXT("Download"), hr );
		}
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CMusicManager::CreateSegmentFromResource()
// Desc: 
//-----------------------------------------------------------------------------

HRESULT CMusicManager::CreateSegmentFromResource( CMusicSegment** ppSegment, 
                                                  TCHAR* strResource,
                                                  TCHAR* strResourceType,
                                                  BOOL bDownloadNow,
                                                  BOOL bIsMidiFile )
{
    HRESULT               hr;
    IDirectMusicSegment8* pSegment      = NULL;
    HRSRC                 hres          = NULL;
    void*                 pMem          = NULL;
    DWORD                 dwSize        = 0;
    DMUS_OBJECTDESC       objdesc;

    // Find the resource
    hres = FindResource( NULL,strResource,strResourceType );
    if( NULL == hres ) 
        return E_FAIL;

    // Load the resource
    pMem = (void*)LoadResource( NULL, hres );
    if( NULL == pMem ) 
        return E_FAIL;

    // Store the size of the resource
    dwSize = SizeofResource( NULL, hres ); 
    
    // Set up our object description 
    ZeroMemory(&objdesc,sizeof(DMUS_OBJECTDESC));
    objdesc.dwSize = sizeof(DMUS_OBJECTDESC);
    objdesc.dwValidData = DMUS_OBJ_MEMORY | DMUS_OBJ_CLASS;
    objdesc.guidClass = CLSID_DirectMusicSegment;
    objdesc.llMemLength =(LONGLONG)dwSize;
    objdesc.pbMemData = (BYTE*)pMem;
    
    if (FAILED ( hr = m_pLoader->GetObject( &objdesc,
                                            IID_IDirectMusicSegment8,
                                            (void**)&pSegment ) ) )
    {
        if( hr == DMUS_E_LOADER_FAILEDOPEN )
            return hr;
        return DXTRACE_ERR( TEXT("LoadObjectFromFile"), hr );
    }

    *ppSegment = new CMusicSegment( m_pPerformance, m_pLoader, pSegment );
    if( NULL == *ppSegment )
        return E_OUTOFMEMORY;

    if( bIsMidiFile )
    {
        // Do this to make sure that the default General MIDI set 
        // is connected appropriately to the MIDI file and 
        // all instruments sound correct.                  
        if( FAILED( hr = pSegment->SetParam( GUID_StandardMIDIFile, 
                                             0xFFFFFFFF, 0, 0, NULL ) ) )
            return DXTRACE_ERR( TEXT("SetParam"), hr );
    }

    if( bDownloadNow )
    {
        // The segment needs to be download first before playing.  
        // However, some apps may want to wait before calling this 
        // to because the download allocates memory for the 
        // instruments. The more instruments currently downloaded, 
        // the more memory is in use by the synthesizer.
        if( FAILED( hr = (*ppSegment)->Download() ) )
            return DXTRACE_ERR( TEXT("Download"), hr );
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CMusicManager::CreateScriptFromFile()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CMusicManager::CreateScriptFromFile( CMusicScript** ppScript, 
                                             TCHAR* strFileName )
{
    HRESULT               hr;
    IDirectMusicScript* pScript = NULL;

    // DMusic only takes wide strings
    WCHAR wstrFileName[MAX_PATH];
    DXUtil_ConvertGenericStringToWide( wstrFileName, strFileName );
    
    if ( FAILED( hr = m_pLoader->LoadObjectFromFile( CLSID_DirectMusicScript,
                                                     IID_IDirectMusicScript8,
                                                     wstrFileName,
                                                     (LPVOID*) &pScript ) ) )
													 return hr;
        //return DXTRACE_ERR_NOMSGBOX( TEXT("LoadObjectFromFile"), hr );

    if ( FAILED( hr = pScript->Init( m_pPerformance, NULL ) ) )
        return DXTRACE_ERR( TEXT("Init"), hr );

    *ppScript = new CMusicScript( m_pPerformance, m_pLoader, pScript );
    if (!*ppScript)
        return E_OUTOFMEMORY;

    return hr;
}




//-----------------------------------------------------------------------------
// Name: CMusicManager::CreateChordMapFromFile()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CMusicManager::CreateChordMapFromFile( IDirectMusicChordMap8** ppChordMap, 
                                               TCHAR* strFileName )
{
    // DMusic only takes wide strings
    WCHAR wstrFileName[MAX_PATH];
    DXUtil_ConvertGenericStringToWide( wstrFileName, strFileName );

    return m_pLoader->LoadObjectFromFile( CLSID_DirectMusicChordMap,
                                          IID_IDirectMusicChordMap8,
                                          wstrFileName, (LPVOID*) ppChordMap );
}




//-----------------------------------------------------------------------------
// Name: CMusicManager::CreateChordMapFromFile()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CMusicManager::CreateStyleFromFile( IDirectMusicStyle8** ppStyle, 
                                            TCHAR* strFileName )
{
    // DMusic only takes wide strings
    WCHAR wstrFileName[MAX_PATH];
    DXUtil_ConvertGenericStringToWide( wstrFileName, strFileName );

    return m_pLoader->LoadObjectFromFile( CLSID_DirectMusicStyle,
                                          IID_IDirectMusicStyle8,
                                          wstrFileName, (LPVOID*) ppStyle );
}




//-----------------------------------------------------------------------------
// Name: CMusicManager::GetMotifFromStyle()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CMusicManager::GetMotifFromStyle( IDirectMusicSegment8** ppMotif8, 
                                          TCHAR* strStyle, TCHAR* strMotif )
{       
    HRESULT              hr;
    IDirectMusicStyle8*  pStyle = NULL;
    IDirectMusicSegment* pMotif = NULL;

    if( FAILED( hr = CreateStyleFromFile( &pStyle, strStyle ) ) )
        return DXTRACE_ERR( TEXT("CreateStyleFromFile"), hr );

    if( pStyle )
    {
        // DMusic only takes wide strings
        WCHAR wstrMotif[MAX_PATH];
        DXUtil_ConvertGenericStringToWide( wstrMotif, strMotif );

        hr = pStyle->GetMotif( wstrMotif, &pMotif );
        SAFE_RELEASE( pStyle );

        if( FAILED( hr ) )
            return DXTRACE_ERR( TEXT("GetMotif"), hr );

        pMotif->QueryInterface( IID_IDirectMusicSegment8, (LPVOID*) ppMotif8 );
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CMusicSegment::CMusicSegment()
// Desc: Constructs the class
//-----------------------------------------------------------------------------

	//int serialno;
	//int is3d;
	//CMusicSegment* next;

	//IDirectSound3DBuffer*   m_pDS3DBuffer;//            = NULL;   // 3D sound buffer
	//DS3DBUFFER              m_dsBufferParams;//                  // 3D buffer properties

	//IDirectMusicAudioPath*  m_p3DAudioPath;
	//IDirectSound3DListener* m_pDSListener;// 3D listener object
	//DS3DLISTENER            m_dsListenerParams;// Listener properties



CMusicSegment::CMusicSegment( IDirectMusicPerformance8* pPerformance, 
                              IDirectMusicLoader8*      pLoader,
                              IDirectMusicSegment8*     pSegment )
{
    m_pPerformance          = pPerformance;
    m_pLoader               = pLoader;
    m_pSegment              = pSegment;
    m_pEmbeddedAudioPath    = NULL;
    m_bDownloaded           = FALSE;
    

	//m_pStereoAudioPath = NULL;
	m_pDSBuffer = NULL;


	/***
    // Try to pull out an audio path from the segment itself if there is one.
    // This embedded audio path will be used instead of the default
    // audio path if the app doesn't wish to use an overriding audio path.
    IUnknown* pConfig = NULL;
    if( SUCCEEDED( m_pSegment->GetAudioPathConfig( &pConfig ) ) )
    {
		HRESULT hr;
        hr = m_pPerformance->CreateAudioPath( pConfig, TRUE, &m_pEmbeddedAudioPath );
        SAFE_RELEASE( pConfig );

		if( hr != S_OK ){
			::MessageBox( NULL, "CreateAudioPath error !!!\n", "error", MB_OK );			
		}
    }else{
		::MessageBox( NULL, "GetAudioPathConfig error !!!\n", "error", MB_OK );	
	}
	***/

	//DbgOut( "HS : musicmanager : audiopath NULL set \n" );

}




//-----------------------------------------------------------------------------
// Name: CMusicSegment::~CMusicSegment()
// Desc: Destroys the class
//-----------------------------------------------------------------------------
CMusicSegment::~CMusicSegment()
{

			
	SAFE_RELEASE( m_pDSBuffer );
	//SAFE_RELEASE( m_pStereoAudioPath );

    if( m_pSegment )
    {
        // Tell the loader that this object should now be released
        if( m_pLoader )
            m_pLoader->ReleaseObjectByUnknown( m_pSegment );

        if( m_bDownloaded )
        {
            if( m_pEmbeddedAudioPath )
                m_pSegment->Unload( m_pEmbeddedAudioPath );
            else
                m_pSegment->Unload( m_pPerformance );
        }

        SAFE_RELEASE( m_pEmbeddedAudioPath ); 
        SAFE_RELEASE( m_pSegment ); 
    }

    m_pPerformance = NULL;
}


HRESULT CMusicSegment::SetStartPointOfSound( int musictime )
{

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// wav ファイルでは、GetLengthが常に１になっており、SetStartPointは、失敗する。
	// SetLengthしてみても、駄目。
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	HRESULT hr;

    if( m_pSegment == NULL || m_pPerformance == NULL )
        return CO_E_NOTINITIALIZED;


	hr = m_pSegment->SetStartPoint( musictime );
	if( FAILED( hr ) ){
		DbgOut( "MusicSegment : segment SetStartPoint error !!!\n" );
	//	return hr;
	}

	return S_OK;


/***
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// wav ファイルでは、GetLengthが常に１になっており、SetStartPointは、失敗する。
	// SetLengthしてみても、駄目。
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	
	HRESULT hr;

    if( m_pSegment == NULL || m_pPerformance == NULL )
        return CO_E_NOTINITIALIZED;

	REFERENCE_TIME curref;
	MUSIC_TIME curmt;
	hr = m_pPerformance->GetTime( &curref, &curmt );
	if( FAILED( hr ) ){
		return hr;
	}

//DbgOut( "CMusicSegment : SetStartPointOfSound : curmt %d, curref %d\r\n", curmt, curref );

	//MUSIC_TIME leng;
	//hr = m_pSegment->GetLength( &leng );
//DbgOut( "CMusicSegment : SetStartPointOfSound : length %d\r\n", leng );


	REFERENCE_TIME reftime = curref + (sec1000 * 10000);
	MUSIC_TIME setmt;

	hr = m_pPerformance->ReferenceToMusicTime( reftime, &setmt );
	if( FAILED( hr ) ){
		DbgOut( "MusicSegment : performance ReferenceToMusicTime error !!!\n" );
		return hr;
	}

	setmt -= curmt;//!!!!!!!!!!!

//DbgOut( "CMusicSegment : SetStartPointOfSound : setmp %d, reftime %d\r\n", setmt, reftime );

	hr = m_pSegment->SetStartPoint( setmt );
	if( FAILED( hr ) ){
		DbgOut( "MusicSegment : segment SetStartPoint error !!!\n" );
	//	return hr;
	}

	return S_OK;
***/	
}

HRESULT CMusicSegment::GetMusicTime( int* mtimeptr, double* rtimeptr )
{
	HRESULT hr;

    if( m_pSegment == NULL || m_pPerformance == NULL )
        return CO_E_NOTINITIALIZED;
	
	REFERENCE_TIME reftime;
	MUSIC_TIME mtime;
	hr = m_pPerformance->GetTime( &reftime, &mtime );
	if( hr != DS_OK ){
		DbgOut( "MusicSegment : performance GetTime error !!!\n" );
		return 1;
	}

	*rtimeptr = reftime;
	*mtimeptr = mtime;
	return 0;
}


//-----------------------------------------------------------------------------
// Name: CMusicSegment::Play()
// Desc: Plays the sound using voice management flags.  Pass in DSBPLAY_LOOPING
//       in the dwFlags to loop the sound
//-----------------------------------------------------------------------------
HRESULT CMusicSegment::Play( DWORD dwFlags, IDirectMusicAudioPath8* pAudioPath )
{
    if( m_pSegment == NULL || m_pPerformance == NULL )
        return CO_E_NOTINITIALIZED;

    if( !m_bDownloaded )
        return E_FAIL;

    // If an audio path was passed in then use it, otherwise
    // use the embedded audio path if there was one.
    if( pAudioPath == NULL && m_pEmbeddedAudioPath != NULL )
        pAudioPath = m_pEmbeddedAudioPath;
        
    // If pAudioPath is NULL then this plays on the default audio path.
    return m_pPerformance->PlaySegmentEx( m_pSegment, 0, NULL, dwFlags, 
                                          0, 0, NULL, pAudioPath );
}





//-----------------------------------------------------------------------------
// Name: CMusicSegment::Download()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CMusicSegment::Download( IDirectMusicAudioPath8* pAudioPath )
{
    HRESULT hr;
    
    if( m_pSegment == NULL )
        return CO_E_NOTINITIALIZED;

    // If no audio path was passed in, then download
    // to the embedded audio path if it exists 
    // else download to the performance
    if( pAudioPath == NULL )
    {
        if( m_pEmbeddedAudioPath )
            hr = m_pSegment->Download( m_pEmbeddedAudioPath );
        else    
            hr = m_pSegment->Download( m_pPerformance );
    }
    else
    {
        hr = m_pSegment->Download( pAudioPath );
    }
    
    if ( SUCCEEDED( hr ) )
        m_bDownloaded = TRUE;
        
    return hr;
}




//-----------------------------------------------------------------------------
// Name: CMusicSegment::Unload()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CMusicSegment::Unload( IDirectMusicAudioPath8* pAudioPath )
{
    HRESULT hr;
    
    if( m_pSegment == NULL )
        return CO_E_NOTINITIALIZED;

    // If no audio path was passed in, then unload 
    // from the embedded audio path if it exists 
    // else unload from the performance
    if( pAudioPath == NULL )
    {
        if( m_pEmbeddedAudioPath )
            hr = m_pSegment->Unload( m_pEmbeddedAudioPath );
        else    
            hr = m_pSegment->Unload( m_pPerformance );
    }
    else
    {
        hr = m_pSegment->Unload( pAudioPath );
    }
        
    if ( SUCCEEDED( hr ) )
        m_bDownloaded = FALSE;

    return hr;
}




//-----------------------------------------------------------------------------
// Name: CMusicSegment::IsPlaying()
// Desc: 
//-----------------------------------------------------------------------------
BOOL CMusicSegment::IsPlaying()
{
    if( m_pSegment == NULL || m_pPerformance == NULL )
        return CO_E_NOTINITIALIZED;

    return ( m_pPerformance->IsPlaying( m_pSegment, NULL ) == S_OK );
}




//-----------------------------------------------------------------------------
// Name: CMusicSegment::Stop()
// Desc: Stops the sound from playing
//-----------------------------------------------------------------------------
HRESULT CMusicSegment::Stop( DWORD dwFlags )
{
    if( m_pSegment == NULL || m_pPerformance == NULL )
        return CO_E_NOTINITIALIZED;

    return m_pPerformance->Stop( m_pSegment, NULL, 0, dwFlags );;
}




//-----------------------------------------------------------------------------
// Name: CMusicSegment::SetRepeats()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CMusicSegment::SetRepeats( DWORD dwRepeats )
{
    if( m_pSegment == NULL )
        return CO_E_NOTINITIALIZED;

    return m_pSegment->SetRepeats( dwRepeats );
}




//-----------------------------------------------------------------------------
// Name: CMusicSegment::GetStyle()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CMusicSegment::GetStyle( IDirectMusicStyle8** ppStyle, DWORD dwStyleIndex )
{
    // Get the Style from the Segment by calling the Segment's GetData() with
    // the data type GUID_StyleTrackStyle. 0xffffffff indicates to look at
    // tracks in all TrackGroups in the segment. The first 0 indicates to
    // retrieve the Style from the first Track  in the indicated TrackGroup.
    // The second 0 indicates to retrieve the Style from the beginning of the
    // segment, i.e. time 0 in Segment time. If this Segment was loaded from a
    // section file, there is only one Style and it is at time 0.
    return m_pSegment->GetParam( GUID_IDirectMusicStyle, 0xffffffff, dwStyleIndex, 
                                 0, NULL, (VOID*)ppStyle );
}

/***
int CMusicSegment::Set3DListener( float fDopplerFactor, float fRolloffFactor )
{
	DWORD dwApplyFlag = DS3D_IMMEDIATE;

	m_dsListenerParams.flDopplerFactor = fDopplerFactor;
	m_dsListenerParams.flRolloffFactor = fRolloffFactor;

	if( m_pDSListener )
		m_pDSListener->SetAllParameters( &m_dsListenerParams, dwApplyFlag );



	return 0;
}

int CMusicSegment::Set3DListenerMovement( D3DXVECTOR3* pvPosition, D3DXVECTOR3* pvVelocity, D3DXVECTOR3* pvOrientFront, D3DXVECTOR3* pvOrientTop )
{
	DWORD dwApplyFlag = DS3D_IMMEDIATE;

	m_dsListenerParams.vPosition = *pvPosition;
	m_dsListenerParams.vVelocity = *pvVelocity;
	m_dsListenerParams.vOrientFront = *pvOrientFront;
	m_dsListenerParams.vOrientTop = *pvOrientTop;

	if( m_pDSListener )
		m_pDSListener->SetAllParameters( &m_dsListenerParams, dwApplyFlag );

	return 0;
}
***/


//-----------------------------------------------------------------------------
// Name: CMusicScript::CMusicScript()
// Desc: Constructs the class
//-----------------------------------------------------------------------------
CMusicScript::CMusicScript( IDirectMusicPerformance8* pPerformance, 
                            IDirectMusicLoader8* pLoader,                   
                            IDirectMusicScript8* pScript )
{
    m_pPerformance = pPerformance;
    m_pLoader      = pLoader;
    m_pScript      = pScript;
}




//-----------------------------------------------------------------------------
// Name: CMusicScript::~CMusicScript()
// Desc: Destroys the class
//-----------------------------------------------------------------------------
CMusicScript::~CMusicScript()
{
    if( m_pLoader )
    {
        // Tell the loader that this object should now be released
        m_pLoader->ReleaseObjectByUnknown( m_pScript );
        m_pLoader = NULL;
    }

    SAFE_RELEASE( m_pScript ); 
    m_pPerformance = NULL;
}




//-----------------------------------------------------------------------------
// Name: CMusicScript::Play()
// Desc: Calls a routine in the script
//-----------------------------------------------------------------------------
HRESULT CMusicScript::CallRoutine( TCHAR* strRoutine )
{
    // DMusic only takes wide strings
    WCHAR wstrRoutine[MAX_PATH];
    DXUtil_ConvertGenericStringToWide( wstrRoutine, strRoutine );

    return m_pScript->CallRoutine( wstrRoutine, NULL );
}




//-----------------------------------------------------------------------------
// Name: CMusicScript::SetVariableNumber()
// Desc: Sets the value of a variable in the script
//-----------------------------------------------------------------------------
HRESULT CMusicScript::SetVariableNumber( TCHAR* strVariable, LONG lValue )
{
    // DMusic only takes wide strings
    WCHAR wstrVariable[MAX_PATH];
    DXUtil_ConvertGenericStringToWide( wstrVariable, strVariable );

    return m_pScript->SetVariableNumber( wstrVariable, lValue, NULL );
}




//-----------------------------------------------------------------------------
// Name: CMusicScript::GetVariableNumber()
// Desc: Gets the value of a variable in the script
//-----------------------------------------------------------------------------
HRESULT CMusicScript::GetVariableNumber( TCHAR* strVariable, LONG* plValue )
{
    // DMusic only takes wide strings
    WCHAR wstrVariable[MAX_PATH];
    DXUtil_ConvertGenericStringToWide( wstrVariable, strVariable );

    return m_pScript->GetVariableNumber( wstrVariable, plValue, NULL );
}



