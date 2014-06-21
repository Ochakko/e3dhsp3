bool XAudioWave::Load( const char *pFileName )
{
	Stop();
	Release();

	FILE *fp = fopen( pFileName, "rb" );
	if( !fp ){
		DbgOut( "wave : Load : fopen error !!!\r\n" );
		_ASSERT( 0 );
		return false;
	}

	unsigned char Header[4];
	ZeroMemory( Header, sizeof( unsigned char ) * 4 );
	fread( Header, 4, 1, fp );

	// RIFF
	if( memcmp( Header, "RIFF", 4 ) != 0 ){
		DbgOut( "wave : Load : RIFF error !!!\r\n" );
		_ASSERT( 0 );
		fclose( fp );
		return false;
	}

	// File Size
	fread( Header, 4, 1, fp );
	int FileSize = ( ( (int)Header[3] ) << 24 ) + ( ( (int)Header[2] ) << 16 ) + ( ( (int)Header[1] ) << 8 ) + (int)Header[0];

	// WAVE
	fread( Header, 4, 1, fp );
	if( memcmp( Header, "WAVE", 4 ) != 0 ){
		DbgOut( "wave : Load : WAVE header error !!!\r\n" );
		_ASSERT( 0 );
		fclose( fp );
		return false;
	}

	// fmt
	fread( Header, 4, 1, fp );
	if( memcmp( Header, "fmt ", 4 ) != 0 ){
		DbgOut( "wave : Load : fmt error !!!\r\n" );
		_ASSERT( 0 );
		fclose( fp );
		return false;
	}

	// Linear PCM
	fread( Header, 4, 1, fp );
	int FMTChunkBytes = ( ( (int)Header[3] ) << 24 ) + ( ( (int)Header[2] ) << 16 ) + ( ( (int)Header[1] ) << 8 ) + (int)Header[0];

	// http://www.web-sky.org/program/other/wave.php
	// WAVE_FORMAT_UNKNOWN	0x0000	Microsoft Corporation
	// WAVE_FORMAT_PCM	0x0001	Microsoft PCM format
	// WAVE_FORMAT_MS_ADPCM	0x0002	Microsoft ADPCM
	// WAVE_FORMAT_IEEE_FLOAT	0x0003	Micrososft 32 bit float format
	// WAVE_FORMAT_VSELP	0x0004	Compaq Computer Corporation
	// WAVE_FORMAT_IBM_CVSD	0x0005	IBM Corporation
	// WAVE_FORMAT_ALAW	0x0006	Microsoft Corporation
	// WAVE_FORMAT_MULAW	0x0007	Microsoft Corporation
	// WAVE_FORMAT_OKI_ADPCM	0x0010	OKI
	// WAVE_FORMAT_IMA_ADPCM	0x0011	Intel Corporation
	// WAVE_FORMAT_MEDIASPACE_ADPCM	0x0012	Videologic
	// WAVE_FORMAT_SIERRA_ADPCM	0x0013	Sierra Semiconductor Corp
	// WAVE_FORMAT_G723_ADPCM	0x0014	Antex Electronics Corporation
	// WAVE_FORMAT_DIGISTD	0x0015	DSP Solutions, Inc.
	// WAVE_FORMAT_DIGIFIX	0x0016	DSP Solutions, Inc.
	// WAVE_FORMAT_DIALOGIC_OKI_ADPCM	0x0017	Dialogic Corporation
	// WAVE_FORMAT_MEDIAVISION_ADPCM	0x0018	Media Vision, Inc.
	// WAVE_FORMAT_CU_CODEC	0x0019	Hewlett-Packard Company
	// WAVE_FORMAT_YAMAHA_ADPCM	0x0020	Yamaha Corporation of America
	// WAVE_FORMAT_SONARC	0x0021	Speech Compression
	// WAVE_FORMAT_DSPGROUP_TRUESPEECH	0x0022	DSP Group, Inc
	// WAVE_FORMAT_ECHOSC1	0x0023	Echo Speech Corporation
	// WAVE_FORMAT_AUDIOFILE_AF36	0x0024	Audiofile, Inc.
	// WAVE_FORMAT_APTX	0x0025	Audio Processing Technology
	// WAVE_FORMAT_AUDIOFILE_AF10	0x0026	Audiofile, Inc.
	// WAVE_FORMAT_PROSODY_1612	0x0027	Aculab plc
	// WAVE_FORMAT_LRC	0x0028	Merging Technologies S.A.
	// WAVE_FORMAT_DOLBY_AC2	0x0030	Dolby Laboratories
	// WAVE_FORMAT_GSM610	0x0031	Microsoft Corporation
	// WAVE_FORMAT_MSNAUDIO	0x0032	Microsoft Corporation
	// WAVE_FORMAT_ANTEX_ADPCME	0x0033	Antex Electronics Corporation
	// WAVE_FORMAT_CONTROL_RES_VQLPC	0x0034	Control Resources Limited
	// WAVE_FORMAT_DIGIREAL	0x0035	DSP Solutions, Inc.
	// WAVE_FORMAT_DIGIADPCM	0x0036	DSP Solutions, Inc.
	// WAVE_FORMAT_CONTROL_RES_CR10	0x0037	Control Resources Limited
	// WAVE_FORMAT_NMS_VBXADPCM	0x0038	Natural MicroSystems
	// WAVE_FORMAT_ROLAND_RDAC	0x0039	Roland
	// WAVE_FORMAT_ECHOSC3	0x003A	Echo Speech Corporation
	// WAVE_FORMAT_ROCKWELL_ADPCM	0x003B	Rockwell International
	// WAVE_FORMAT_ROCKWELL_DIGITALK	0x003C	Rockwell International
	// WAVE_FORMAT_XEBEC	0x003D	Xebec Multimedia Solutions Limited
	// WAVE_FORMAT_G721_ADPCM	0x0040	Antex Electronics Corporation
	// WAVE_FORMAT_G728_CELP	0x0041	Antex Electronics Corporation
	// WAVE_FORMAT_MSG723	0x0042	Microsoft Corporation
	// WAVE_FORMAT_MPEG	0x0050	Microsoft Corporation
	// WAVE_FORMAT_RT24	0x0052	InSoft Inc.
	// WAVE_FORMAT_PAC	0x0053	InSoft Inc.
	// WAVE_FORMAT_MPEGLAYER3	0x0055	MPEG 3 Layer 1
	// WAVE_FORMAT_LUCENT_G723	0x0059	Lucent Technologies
	// WAVE_FORMAT_CIRRUS	0x0060	Cirrus Logic
	// WAVE_FORMAT_ESPCM	0x0061	ESS Technology
	// WAVE_FORMAT_VOXWARE	0x0062	Voxware Inc
	// WAVE_FORMAT_CANOPUS_ATRAC	0x0063	Canopus, Co., Ltd.
	// WAVE_FORMAT_G726_ADPCM	0x0064	APICOM
	// WAVE_FORMAT_G722_ADPCM	0x0065	APICOM
	// WAVE_FORMAT_DSAT	0x0066	Microsoft Corporation
	// WAVE_FORMAT_DSAT_DISPLAY	0x0067	Microsoft Corporation
	// WAVE_FORMAT_VOXWARE_BYTE_ALIGNED	0x0069	Voxware Inc.
	// WAVE_FORMAT_VOXWARE_AC8	0x0070	Voxware Inc.
	// WAVE_FORMAT_VOXWARE_AC10	0x0071	Voxware Inc.
	// WAVE_FORMAT_VOXWARE_AC16	0x0072	Voxware Inc.
	// WAVE_FORMAT_VOXWARE_AC20	0x0073	Voxware Inc.
	// WAVE_FORMAT_VOXWARE_RT24	0x0074	Voxware Inc.
	// WAVE_FORMAT_VOXWARE_RT29	0x0075	Voxware Inc.
	// WAVE_FORMAT_VOXWARE_RT29HW	0x0076	Voxware Inc.
	// WAVE_FORMAT_VOXWARE_VR12	0x0077	Voxware Inc.
	// WAVE_FORMAT_VOXWARE_VR18	0x0078	Voxware Inc.
	// WAVE_FORMAT_VOXWARE_TQ40	0x0079	Voxware Inc.
	// WAVE_FORMAT_SOFTSOUND	0x0080	Softsound, Ltd.
	// WAVE_FORMAT_VOXARE_TQ60	0x0081	Voxware Inc.
	// WAVE_FORMAT_MSRT24	0x0082	Microsoft Corporation
	// WAVE_FORMAT_G729A	0x0083	AT&T Laboratories
	// WAVE_FORMAT_MVI_MV12	0x0084	Motion Pixels
	// WAVE_FORMAT_DF_G726	0x0085	DataFusion Systems (Pty) (Ltd)
	// WAVE_FORMAT_DF_GSM610	0x0086	DataFusion Systems (Pty) (Ltd)
	// WAVE_FORMAT_ONLIVE	0x0089	OnLive! Technologies, Inc.
	// WAVE_FORMAT_SBC24	0x0091	Siemens Business Communications Systems
	// WAVE_FORMAT_DOLBY_AC3_SPDIF	0x0092	Sonic Foundry
	// WAVE_FORMAT_ZYXEL_ADPCM	0x0097	ZyXEL Communications, Inc.
	// WAVE_FORMAT_PHILIPS_LPCBB	0x0098	Philips Speech Processing
	// WAVE_FORMAT_PACKED	0x0099	Studer Professional Audio AG
	// WAVE_FORMAT_RHETOREX_ADPCM	0x0100	Rhetorex, Inc.
	// IBM_FORMAT_MULAW	0x0101	IBM mu-law format
	// IBM_FORMAT_ALAW	0x0102	IBM a-law format
	// IBM_FORMAT_ADPCM	0x0103	IBM AVC Adaptive Differential PCM format
	// WAVE_FORMAT_VIVO_G723	0x0111	Vivo Software
	// WAVE_FORMAT_VIVO_SIREN	0x0112	Vivo Software
	// WAVE_FORMAT_DIGITAL_G723	0x0123	Digital Equipment Corporation
	// WAVE_FORMAT_CREATIVE_ADPCM	0x0200	Creative Labs, Inc
	// WAVE_FORMAT_CREATIVE_FASTSPEECH8	0x0202	Creative Labs, Inc
	// WAVE_FORMAT_CREATIVE_FASTSPEECH10	0x0203	Creative Labs, Inc
	// WAVE_FORMAT_QUARTERDECK	0x0220	Quarterdeck Corporation
	// WAVE_FORMAT_FM_TOWNS_SND	0x0300	Fujitsu Corporation
	// WAVE_FORMAT_BZV_DIGITAL	0x0400	Brooktree Corporation
	// WAVE_FORMAT_VME_VMPCM	0x0680	AT&T Labs, Inc.
	// WAVE_FORMAT_OLIGSM	0x1000	Ing C. Olivetti & C., S.p.A.
	// WAVE_FORMAT_OLIADPCM	0x1001	Ing C. Olivetti & C., S.p.A.
	// WAVE_FORMAT_OLICELP	0x1002	Ing C. Olivetti & C., S.p.A.
	// WAVE_FORMAT_OLISBC	0x1003	Ing C. Olivetti & C., S.p.A.
	// WAVE_FORMAT_OLIOPR	0x1004	Ing C. Olivetti & C., S.p.A.
	// WAVE_FORMAT_LH_CODEC	0x1100	Lernout & Hauspie
	// WAVE_FORMAT_NORRIS	0x1400	Norris Communications, Inc.
	// WAVE_FORMAT_SOUNDSPACE_MUSICOMPRESS	0x1500	AT&T Labs, Inc.
	// WAVE_FORMAT_DVM	0x2000	FAST Multimedia AG
	// WAVE_FORMAT_INTERWAV_VSC112	0x7150	?????
	// WAVE_FORMAT_EXTENSIBLE	0xFFFE

	fread( Header, 2, 1, fp );
	int FormatID = ( ( (int)Header[1] ) << 8 ) + (int)Header[0];
	if( FormatID != 0x0001 && FormatID != 0xFFFE ){ // 0x0001: WAVE_FORMAT_PCM 0xFFFE: WAVE_FORMAT_EXTENSIBLE
		DbgOut( "wave : Load : FormatID error !!!\r\n" );
		_ASSERT( 0 );

		fclose( fp );
		return false;
	}

	// Number of Channels
	fread( Header, 2, 1, fp );
	int NumChannels = ( ( (int)Header[1] ) << 8 ) + (int)Header[0];

/////////
	if( flag3d && (NumChannels >= 2) ){
		::MessageBox( NULL, "３Dサウンドはモノラルのみです。", "エラー", MB_OK );
		_ASSERT( 0 );
		fclose( fp );
		return false;
	}
	m_audioState.emitter.ChannelCount = NumChannels;


	// Sampling Rate
	fread( Header, 4, 1, fp );
	int SamplingRate = ( ( (int)Header[3] ) << 24 ) + ( ( (int)Header[2] ) << 16 ) + ( ( (int)Header[1] ) << 8 ) + (int)Header[0];

	// Data Speed
	fread( Header, 4, 1, fp );
	int DataSpeed = ( ( (int)Header[3] ) << 24 ) + ( ( (int)Header[2] ) << 16 ) + ( ( (int)Header[1] ) << 8 ) + (int)Header[0];

	// Block Size
	fread( Header, 2, 1, fp );
	int BlockSize = ( ( (int)Header[1] ) << 8 ) + (int)Header[0];

	// Bits / Sample
	fread( Header, 2, 1, fp );
	int BitsPerSample = ( ( (int)Header[1] ) << 8 ) + (int)Header[0];

	// Skip
	if( FMTChunkBytes - 16 > 0 ) fseek( fp, FMTChunkBytes - 16, SEEK_CUR );

	// skip chunks
	for( int i = 0; ; ++i ){
		fread( Header, 4, 1, fp );

		if( memcmp( Header, "data", 4 ) == 0 ){
			break;
		}

		fread( Header, 4, 1, fp );

		int Size = ( ( (int)Header[3] ) << 24 ) + ( ( (int)Header[2] ) << 16 ) + ( ( (int)Header[1] ) << 8 ) + (int)Header[0];
		fseek( fp, Size, SEEK_CUR );
		DbgOut( "wave : load : skip Size %d\r\n", Size );
	}


	// data
	// WaveSize (byte)
	fread( Header, 4, 1, fp );
	WaveSize = ( ( (int)Header[3] ) << 24 ) + ( ( (int)Header[2] ) << 16 ) + ( ( (int)Header[1] ) << 8 ) + (int)Header[0];
	DbgOut( "wave : load : WaveSize %d\r\n", WaveSize );


	if( WaveSize > XAUDIO2_MAX_BUFFER_BYTES ) {
		DbgOut( "wave : Load : WaveSize Overflow error !!!\r\n" );
		_ASSERT( 0 );

		fclose( fp );
		return false;
	}

	pData = new unsigned char[WaveSize];

	fread( pData, sizeof( char ), WaveSize, fp );

	fclose( fp );

	// PCM audio
//	WAVEFORMATEX WaveFormatEx;

	m_WaveFormatEx.wFormatTag = 1; // PCM audio
	m_WaveFormatEx.nChannels = NumChannels;
	m_WaveFormatEx.nSamplesPerSec = SamplingRate;
	m_WaveFormatEx.wBitsPerSample = BitsPerSample;
	m_WaveFormatEx.nBlockAlign = m_WaveFormatEx.nChannels * m_WaveFormatEx.wBitsPerSample / 8;
	m_WaveFormatEx.nAvgBytesPerSec = m_WaveFormatEx.nSamplesPerSec * m_WaveFormatEx.nBlockAlign;
	m_WaveFormatEx.cbSize = WaveSize;//!!!!! 0

	pStatusCallBack->pXAudioWave = this;


    XAUDIO2_SEND_DESCRIPTOR sendDescriptors;
    sendDescriptors.Flags = XAUDIO2_SEND_USEFILTER; // LPF direct-path
	sendDescriptors.pOutputVoice = XAudio::GetInstance().pMasteringVoice;
    const XAUDIO2_VOICE_SENDS sendList = { 1, &sendDescriptors };

	if( FAILED( XAudio::GetInstance().GetXAudio2()->CreateSourceVoice(
			&pSourceVoice, &m_WaveFormatEx, 0, XAUDIOFREQMAX, pStatusCallBack, &sendList ) ) ){
		DbgOut( "wave : Load : CreateSourceVoice error !!!\r\n" );
		_ASSERT( 0 );

		return false;
	}

//	if( !pXAudioFadeEffect->Init( pSourceVoice, NumChannels ) ) return false;

	int ret;
	HRESULT hr;
//	IXAPO* pFadeAPO = NULL;
//	ret = pXAudioFadeEffect->CreateEffect( NumChannels, &pFadeAPO );
	ret = pXAudioFadeEffect->CreateEffect( NumChannels, &m_pFadeAPO );
	if( ret || !m_pFadeAPO ){
		DbgOut( "wave : Load : CreateEffect error !!!\r\n" );
		_ASSERT( 0 );
		return false;
	}

DbgOut( "wave : Load : NumChannels %d\r\n", NumChannels );

	XAUDIO2_EFFECT_CHAIN Chain;
	ZeroMemory( &Chain, sizeof( XAUDIO2_EFFECT_CHAIN ) );
	XAUDIO2_EFFECT_DESCRIPTOR Descriptor[2];
	ZeroMemory( Descriptor, sizeof( XAUDIO2_EFFECT_DESCRIPTOR ) * 2 );
	XAUDIO2_EFFECT_DESCRIPTOR FadeDescriptor;
	ZeroMemory( &FadeDescriptor, sizeof( XAUDIO2_EFFECT_DESCRIPTOR ) );

	if( flagreverb ){
		hr = XAudio2CreateReverb( &pRevEffect );
		if( (hr != 0) || !pRevEffect ){
			DbgOut( "wave : Load : CreateReverb error !!!\r\n" );
			_ASSERT( 0 );
			return false;
		}

		Descriptor[0].InitialState = true;
		Descriptor[0].OutputChannels = NumChannels;
		Descriptor[0].pEffect = m_pFadeAPO;

		Descriptor[1].InitialState = true;
		//Descriptor[1].OutputChannels = 1;
		Descriptor[1].OutputChannels = NumChannels;
		Descriptor[1].pEffect = pRevEffect;

		Chain.EffectCount = 2;
		Chain.pEffectDescriptors = &(Descriptor[0]);
	}else{
		FadeDescriptor.InitialState = true;
		FadeDescriptor.OutputChannels = NumChannels;
		FadeDescriptor.pEffect = m_pFadeAPO;

		Chain.EffectCount = 1;
		Chain.pEffectDescriptors = &FadeDescriptor;
	}
	
	hr = pSourceVoice->SetEffectChain( &Chain );
	if( hr != S_OK ){
		DbgOut( "wave : load : source SetEffectChain error !!!\r\n" );
		_ASSERT( 0 );
		return false;
	}



	FadeEffectParams Param;
	ZeroMemory( &Param, sizeof( FadeEffectParams ) );
	Param.IsFade = false;
	if( FAILED( pSourceVoice->SetEffectParameters( 0, &Param, sizeof( FadeEffectParams ) ) ) ){
		DbgOut( "wave : Load : SetEffectParameters error !!!\r\n" );
		_ASSERT( 0 );

		return false;
	}

	if( flagreverb ){
		XAUDIO2FX_REVERB_PARAMETERS reverbParameters;
		reverbParameters.ReflectionsDelay = XAUDIO2FX_REVERB_DEFAULT_REFLECTIONS_DELAY;
		reverbParameters.ReverbDelay = XAUDIO2FX_REVERB_DEFAULT_REVERB_DELAY;
		reverbParameters.RearDelay = XAUDIO2FX_REVERB_DEFAULT_REAR_DELAY;
		reverbParameters.PositionLeft = XAUDIO2FX_REVERB_DEFAULT_POSITION;
		reverbParameters.PositionRight = XAUDIO2FX_REVERB_DEFAULT_POSITION;
		reverbParameters.PositionMatrixLeft = XAUDIO2FX_REVERB_DEFAULT_POSITION_MATRIX;
		reverbParameters.PositionMatrixRight = XAUDIO2FX_REVERB_DEFAULT_POSITION_MATRIX;
		reverbParameters.EarlyDiffusion = XAUDIO2FX_REVERB_DEFAULT_EARLY_DIFFUSION;
		reverbParameters.LateDiffusion = XAUDIO2FX_REVERB_DEFAULT_LATE_DIFFUSION;
		reverbParameters.LowEQGain = XAUDIO2FX_REVERB_DEFAULT_LOW_EQ_GAIN;
		reverbParameters.LowEQCutoff = XAUDIO2FX_REVERB_DEFAULT_LOW_EQ_CUTOFF;
		reverbParameters.HighEQGain = XAUDIO2FX_REVERB_DEFAULT_HIGH_EQ_GAIN;
		reverbParameters.HighEQCutoff = XAUDIO2FX_REVERB_DEFAULT_HIGH_EQ_CUTOFF;
		reverbParameters.RoomFilterFreq = XAUDIO2FX_REVERB_DEFAULT_ROOM_FILTER_FREQ;
		reverbParameters.RoomFilterMain = XAUDIO2FX_REVERB_DEFAULT_ROOM_FILTER_MAIN;
		reverbParameters.RoomFilterHF = XAUDIO2FX_REVERB_DEFAULT_ROOM_FILTER_HF;
		reverbParameters.ReflectionsGain = XAUDIO2FX_REVERB_DEFAULT_REFLECTIONS_GAIN;
		reverbParameters.ReverbGain = XAUDIO2FX_REVERB_DEFAULT_REVERB_GAIN;
		reverbParameters.DecayTime = XAUDIO2FX_REVERB_DEFAULT_DECAY_TIME;
		reverbParameters.Density = XAUDIO2FX_REVERB_DEFAULT_DENSITY;
		reverbParameters.RoomSize = XAUDIO2FX_REVERB_DEFAULT_ROOM_SIZE;
		reverbParameters.WetDryMix = XAUDIO2FX_REVERB_DEFAULT_WET_DRY_MIX;

		hr = pSourceVoice->SetEffectParameters( 1, &reverbParameters, sizeof( reverbParameters ) );
		if( hr != 0 ){
			DbgOut( "wave : Load : SetEffectParameters 1 error !!!\r\n" );

			_ASSERT( 0 );
			return false;
		}
	}

	//SetBufferEnd( Callback_BufferEnd );

	DbgOut( "wave : load : %s success \r\n", pFileName );

	return true;
}
