##0 "hspdef.as"



































































##0 "ÉRÉsÅ[ Å` e3dhsp3_screenpos.as"



##0 "e3dhsp3.as"
#regcmd "_hsp3cmdinit@4","e3dhsp3.dll"
#cmd E3DInit $000
#cmd E3DBye $001
#cmd E3DSigLoad $002
#cmd E3DCreateSwapChain $003
#cmd E3DDestroySwapChain $004
#cmd E3DRender $005
#cmd E3DPresent $006
#cmd E3DBeginScene $007
#cmd E3DEndScene $008
#cmd E3DCreateBG $009
#cmd E3DSetBGU $00A
#cmd E3DSetBGV $00B
#cmd E3DDestroyBG $00C
#cmd E3DAddMotion $00D
#cmd E3DSetMotionKind $00E
#cmd E3DGetMotionKind $00F
#cmd E3DSetNewPose $010
#cmd E3DSetMotionStep $011
#cmd E3DChkConflict $012
#cmd E3DChkConflict2 $013
#cmd E3DCreateAfterImage $014
#cmd E3DDestroyAfterImage $015
#cmd E3DSetAlpha $016
#cmd E3DSetAlpha2 $017
#cmd E3DSetPos $018
#cmd E3DGetPos $019
#cmd E3DSetDir $01A
#cmd E3DRotateInit $01B
#cmd E3DRotateX $01C
#cmd E3DRotateY $01D
#cmd E3DRotateZ $01E
#cmd E3DTwist $01F
#cmd E3DPosForward $020
#cmd E3DCloseTo $021
#cmd E3DDirToTheOtherXZ $022
#cmd E3DDirToTheOther $023
#cmd E3DSeparateFrom $024
#cmd E3DGetCameraPos $025
#cmd E3DSetCameraPos $026
#cmd E3DGetCameraDeg $027
#cmd E3DSetCameraDeg $028
#cmd E3DSetCameraTarget $029
#cmd E3DChkInView $02A
#cmd E3DEnableDbgFile $02B
#cmd E3DSetProjection $02C
#cmd E3DGetKeyboardState $02D

#cmd E3DCos $02E
#cmd E3DSin $02F
#cmd E3DACos $030
#cmd E3DDot $031
#cmd E3DCross $032
#cmd E3DAtan $033
#cmd E3DAtan2 $034
#cmd E3DSqrt $035
#cmd E3DDrawText $036
#cmd E3DDrawBigText $037
#cmd E3DRand $038
#cmd E3DSeed $039
#cmd E3DGetFPS $03A
#cmd E3DWaitByFPS $03B
#cmd E3DCreateLight $03C
#cmd E3DSetDirectionalLight $03D
#cmd E3DSetPointLight $03E
#cmd E3DSetSpotLight $03F
#cmd E3DDestroyLight $040
#cmd E3DClearZ $041
#cmd E3DDestroyHandlerSet $042
#cmd E3DSetDispSwitch $043
#cmd E3DSetMotionFrameNo $044
#cmd E3DCreateSprite $045
#cmd E3DBeginSprite $046
#cmd E3DEndSprite $047
#cmd E3DRenderSprite $048
#cmd E3DGetSpriteSize $049
#cmd E3DSetSpriteRotation $04A
#cmd E3DSetSpriteARGB $04B
#cmd E3DDestroySprite $04C
#cmd E3DChkConfBillboard2 $04D
#cmd E3DChkConfBillboard $04E
#cmd E3DChkConfBySphere $04F
#cmd E3DChkConfBySphere2 $050
#cmd E3DCreateProgressBar $051
#cmd E3DSetProgressBar $052
#cmd E3DDestroyProgressBar $053
#cmd E3DLoadGroundBMP $054
#cmd E3DCameraPosForward $055
#cmd E3DSetBeforePos $056
#cmd E3DChkConfGround $057
#cmd E3DChkConfGround2 $058
#cmd E3DGetPartNoByName $059
#cmd E3DGetVertNumOfPart $05A
#cmd E3DGetVertPos $05B
#cmd E3DSetVertPos $05C
#cmd E3DSetPosOnGround $05D
#cmd E3DSetPosOnGroundPart $05E
#cmd E3DCreateBillboard $05F
#cmd E3DRenderBillboard $060
#cmd E3DSetBillboardPos $061
#cmd E3DSetBillboardOnGround $062
#cmd E3DDestroyBillboard $063

#cmd E3DLoadMQOFileAsGround $064
#cmd E3DSaveMQOFile $065
#cmd E3DGetBillboardInfo $066
#cmd E3DGetNearBillboard $067
#cmd E3DGetInvisibleFlag $068
#cmd E3DSetInvisibleFlag $069
#cmd E3DSetMovableArea $06A
#cmd E3DChkConfWall $06B
#cmd E3DChkConfWall2 $06C
#cmd E3DVec3Normalize $06D
#cmd E3DVec2CCW $06E
#cmd E3DVec3RotateY $06F
#cmd E3DLoadMQOFileAsMovableArea $070
#cmd E3DLoadSound $071
#cmd E3DPlaySound $072
#cmd E3DStopSound $073
#cmd E3DSetSoundLoop $074
#cmd E3DSetSoundVolume $075
#cmd E3DSetSoundTempo $076
#cmd E3DDestroySound $077
#cmd E3DSetSoundFrequency $078
#cmd E3DGetSoundVolume $079
#cmd E3DGetSoundFrequency $07A
#cmd E3DSet3DSoundListener $07B
#cmd E3DSet3DSoundListenerMovement $07C
#cmd E3DSet3DSoundDistance $07D
#cmd E3DSet3DSoundMovement $07E
#cmd E3DCreateNaviLine $07F
#cmd E3DDestroyNaviLine $080
#cmd E3DAddNaviPoint $081
#cmd E3DRemoveNaviPoint $082
#cmd E3DGetNaviPointPos $083
#cmd E3DSetNaviPointPos $084
#cmd E3DGetNaviPointOwnerID $085
#cmd E3DSetNaviPointOwnerID $086
#cmd E3DGetNextNaviPoint $087
#cmd E3DGetPrevNaviPoint $088
#cmd E3DGetNearestNaviPoint $089
#cmd E3DFillUpNaviLine $08A
#cmd E3DSetNaviLineOnGround $08B
#cmd E3DControlByNaviLine $08C
#cmd E3DSetDirQ $08D
#cmd E3DGetDirQ $08E
#cmd E3DSetWallOnGround $08F
#cmd E3DCreateNaviPointClearFlag $090
#cmd E3DDestroyNaviPointClearFlag $091
#cmd E3DInitNaviPointClearFlag $092
#cmd E3DSetNaviPointClearFlag $093
#cmd E3DGetOrder $094
#cmd E3DDestroyAllBillboard $095
#cmd E3DSetValidFlag $096
#cmd E3DSetDiffuse $097
#cmd E3DSetSpecular $098
#cmd E3DSetAmbient $099
#cmd E3DSetBlendingMode $09A
#cmd E3DSetRenderState $09B
#cmd E3DSetScale $09C
#cmd E3DGetScreenPos $09D
#cmd E3DGetScreenPos2 $09E
#cmd E3DCreateQ $09F
#cmd E3DDestroyQ $0A0
#cmd E3DInitQ $0A1
#cmd E3DSetQAxisAndDeg $0A2
#cmd E3DGetQAxisAndDeg $0A3
#cmd E3DRotateQX $0A4
#cmd E3DRotateQY $0A5
#cmd E3DRotateQZ $0A6
#cmd E3DMultQ $0A7
#cmd E3DNormalizeQ $0A8
#cmd E3DCopyQ $0A9

#cmd E3DGetBoneNoByName $0AA
#cmd E3DGetNextMP $0AB
#cmd E3DSetMPInfo $0AC
#cmd E3DIsExistMP $0AD
#cmd E3DGetMotionFrameLength $0AE
#cmd E3DSetMotionFrameLength $0AF
#cmd E3DAddMP $0B0
#cmd E3DDeleteMP $0B1
#cmd E3DFillUpMotion $0B2
#cmd E3DCopyMotionFrame $0B3
#cmd E3DGetMPInfo $0B4
#cmd E3DGetDirQ2 $0B5
#cmd E3DSetDirQ2 $0B6
#cmd E3DLookAtQ $0B7
#cmd E3DMultQVec $0B8
#cmd E3DTwistQ $0B9
#cmd E3DInitTwistQ $0BA
#cmd E3DGetTwistQ $0BB
#cmd E3DRotateQLocalX $0BC
#cmd E3DRotateQLocalY $0BD
#cmd E3DRotateQLocalZ $0BE
#cmd E3DGetBonePos $0BF
#cmd E3DCreateLine $0C0
#cmd E3DDestroyLine $0C1
#cmd E3DSetLineColor $0C2
#cmd E3DAddPoint2Line $0C3
#cmd E3DDeletePointOfLine $0C4
#cmd E3DSetPointPosOfLine $0C5
#cmd E3DGetPointPosOfLine $0C6
#cmd E3DGetNextPointOfLine $0C7
#cmd E3DGetPrevPointOfLine $0C8
#cmd E3DWriteDisplay2BMP $0C9
#cmd E3DCreateAVIFile $0CA
#cmd E3DWriteData2AVIFile $0CB
#cmd E3DCompleteAVIFile $0CC
#cmd E3DCameraLookAt $0CD
#cmd E3DCameraOnNaviLine $0CE
#cmd E3DCameraDirUp $0CF
#cmd E3DCameraDirDown $0D0
#cmd E3DCameraDirRight $0D1
#cmd E3DCameraDirLeft $0D2
#cmd E3DCreateFont $0D3
#cmd E3DDrawTextByFontID $0D4
#cmd E3DDrawTextByFontIDWithCnt $0D5
#cmd E3DDrawTextByFontIDWithCnt2 $0D6
#cmd E3DGetCharacterNum $0D7
#cmd E3DDestroyFont $0D8
#cmd E3DSlerpQ $0D9
#cmd E3DSquadQ $0DA
#cmd E3DSplineVec $0DB
#cmd E3DDbgOut $0DC



#cmd E3DGetDiffuse $0DD
#cmd E3DGetAmbient $0DE
#cmd E3DGetSpecular $0DF
#cmd E3DGetAlpha $0E0
#cmd E3DSaveQuaFile $0E1
#cmd E3DSaveSigFile $0E2
#cmd E3DSetMipMapParams $0E3
#cmd E3DPickVert $0E4
#cmd E3DGetCullingFlag $0E5
#cmd E3DGetOrgVertNo $0E6
#cmd E3DChkIM2Status $0E7
#cmd E3DLoadIM2File $0E8
#cmd E3DSaveIM2File $0E9
#cmd E3DGetJointNum $0EA
#cmd E3DGetJointInfo $0EB
#cmd E3DGetFirstJointNo $0EC
#cmd E3DGetDispObjNum $0ED
#cmd E3DGetDispObjInfo $0EE
#cmd E3DEnableTexture $0EF
#cmd E3DJointAddToTree $0F0
#cmd E3DJointRemoveFromParent $0F1
#cmd E3DJointRemake $0F2
#cmd E3DSigImport $0F3
#cmd E3DSigLoadFromBuf $0F4
#cmd E3DSigImportFromBuf $0F5
#cmd E3DAddMotionFromBuf $0F6
#cmd E3DCheckFullScreenParams $0F7
#cmd E3DGetMaxMultiSampleNum $0F8
#cmd E3DChkConfLineAndFace $0F9
#cmd E3DPickFace $0FA
#cmd E3DGetBBox $0FB
#cmd E3DGetVertNoOfFace $0FC
#cmd E3DGetSamePosVert $0FD
#cmd E3DRdtscStart $0FE
#cmd E3DRdtscStop $0FF
#cmd E3DSaveSig2Buf $100
#cmd E3DSaveQua2Buf $101
#cmd E3DCameraShiftLeft $102
#cmd E3DCameraShiftRight $103
#cmd E3DCameraShiftUp $104
#cmd E3DCameraShiftDown $105
#cmd E3DGetCameraQ $106
#cmd E3DInvQ $107
#cmd E3DSetCameraTwist $108


#cmd E3DIKRotateBeta $109
#cmd E3DIKRotateBeta2D $10A
#cmd E3DGetMotionType $10B
#cmd E3DSetMotionType $10C
#cmd E3DGetIKTransFlag $10D
#cmd E3DSetIKTransFlag $10E
#cmd E3DDestroyAllMotion $10F
#cmd E3DGetUserInt1OfPart $110
#cmd E3DSetUserInt1OfPart $111
#cmd E3DGetBSphere $112
#cmd E3DGetChildJoint $113
#cmd E3DDestroyMotionFrame $114
#cmd E3DGetKeyFrameNo $115
#cmd E3DConvScreenTo3D $116
#cmd E3DVec3Length $117
#cmd E3DSetUV $118
#cmd E3DGetUV $119
#cmd E3DPickBone $11A
#cmd E3DShiftBoneTree2D $11B
#cmd E3DGetDispSwitch $11C
#cmd E3DRotateBillboard $11D
#cmd E3DSetBillboardUV $11E
#cmd E3DCreateTexture $11F
#cmd E3DGetTextureInfo $120
#cmd E3DCopyTextureToTexture $121
#cmd E3DGetTextureFromDispObj $122
#cmd E3DSetTextureToDispObj $123
#cmd E3DRasterScrollTexture $124
#cmd E3DCopyTextureToBackBuffer $125
#cmd E3DDestroyTexture $126
#cmd E3DSetLightAmbient $127
#cmd E3DSetLightSpecular $128
#cmd E3DInvColTexture $129
#cmd E3DSaveGndFile $12A
#cmd E3DLoadGndFile $12B
#cmd E3DLoadGndFileFromBuf $12C
#cmd E3DCreateTextureFromBuf $12D
#cmd E3DLoadSoundFromBuf $12E
#cmd E3DTwistBone $12F
#cmd E3DSetStartPointOfSound $130

#cmd E3DGetBoneQ $131
#cmd E3DSetBoneQ $132
#cmd E3DIsSoundPlaying $133
#cmd E3DIKTranslate $134
#cmd E3DSetUVTile $135
#cmd E3DImportMQOFileAsGround $136
#cmd E3DLoadMQOFileAsMovableAreaFromBuf $137
#cmd E3DChkThreadWorking $138
#cmd E3DLoadMQOFileAsGroundThread $139
#cmd E3DSigLoadThread $13A
#cmd E3DSigLoadFromBufThread $13B
#cmd E3DLoadMQOFileAsMovableAreaThread $13C
#cmd E3DLoadMQOFileAsMovableAreaFromBufThread $13D
#cmd E3DLoadGroundBMPThread $13E
#cmd E3DLoadGndFileThread $13F
#cmd E3DLoadGndFileFromBufThread $140
#cmd E3DAddMotionThread $141
#cmd E3DAddMotionFromBufThread $142
#cmd E3DGetShaderType $143
#cmd E3DSetShaderType $144
#cmd E3DSetLightBlendMode $145
#cmd E3DGetLightBlendMode $146
#cmd E3DSetEmissive $147
#cmd E3DSetSpecularPower $148
#cmd E3DGetEmissive $149
#cmd E3DGetSpecularPower $14A
#cmd E3DGetInfElemNum $14B
#cmd E3DGetInfElem $14C
#cmd E3DSetInfElem $14D
#cmd E3DDeleteInfElem $14E
#cmd E3DSetInfElemDefault $14F
#cmd E3DNormalizeInfElem $150
#cmd E3DGetVisiblePolygonNum $151
#cmd E3DChkConfGroundPart $152
#cmd E3DChkConfGroundPart2 $153
#cmd E3DGetMidiMusicTime $154
#cmd E3DSetNextMotionFrameNo $155






























































































































































































































































































































































































































































##4 "hsptmp"

goto@hsp *_M0_exit
#deffunc waitbyfps int p1, var fps
e3dwaitbyfps p1@m0, fps@m0
await@hsp 0
return@hsp
*_m0_exit
dim@hsp keybuf, 256 

pointmax = 100 

screenw = 640 : screenh = 480
screen@hsp 0, screenw, screenh, 1
title@hsp "Easy3D for HSP2.6 sample"


e3denabledbgfile
e3dinit 0, -1, 0, 16, 0, scid1


camposx = 0.0 : camposy = 1500.0 : camposz = -6000.0
e3dsetcamerapos camposx, camposy, camposz	
camdegxz = 180.0 : camdegy = 0.0
e3dsetcameradeg camdegxz, camdegy



pathlen = 2048
sdim@hsp mediadir, pathlen
mediadir = dir_cur + "\\Media"
sdim@hsp pathbuf, pathlen, 2







e3dcreateprogressbar
e3dsetprogressbar 0



pathbuf.0 = mediadir + "\\groundplane1_p_small.sig"
e3dsigload pathbuf.0, hsid0
posx0 = 0.0 : posy0 = 0.0 : posz0 = 0.0
degx0 = 0.0 : degy0 = 0.0 : degz0 = 0.0
e3dsetpos hsid0, posx0, posy0, posz0
e3dsetdir hsid0, degx0, degy0, degz0
frameno0 = 0

e3dsetprogressbar 30



pathbuf.0 = mediadir + "\\ni_parts_6_bone.sig"
e3dsigload pathbuf.0, hsid1

pathbuf.0 = mediadir + "\\ni_parts4_idling.qua"
e3daddmotion hsid1, pathbuf.0, mk1_idling, max1_idling

e3dsetprogressbar 60

e3dsetmotionkind hsid1, mk1_idling
posx1 = 1000.0 : posy1 = 0.0 : posz1 = 0.0
degx1 = 0.0 : degy1 = 90.0 : degz1 = 0.0
e3dsetpos hsid1, posx1, posy1, posz1
e3dsetdir hsid1, degx1, degy1, degz1

frameno1 = 0
newmk1 = 0



pathbuf.0 = mediadir + "\\verttest7_2.sig"
e3dsigload pathbuf.0, hsid2
e3dgetpartnobyname hsid2, "\"obj1\"", partno2
e3dgetvertnumofpart hsid2, partno2, vertnum2



lightdirx1 = 0.0
lightdiry1 = 0.0
lightdirz1 = 1.0
lightr1 = 128
lightg1 = 128
lightb1 = 128


e3dcreatelight lid1
e3dsetdirectionallight lid1, lightdirx1, lightdiry1, lightdirz1, lightr1, lightg1, lightb1

lightposx2 = 0.0
lightposy2 = 500.0
lightposz2 = 0.0
lightdist2 = 2000.0
lightr2 = 255
lightg2 = 0
lightb2 = 0

pathbuf.0 = mediadir + "\\lake.bmp"
pathbuf.1 = mediadir + "\\cloud3.bmp"
e3dcreatebg scid1, pathbuf.0, pathbuf.1, 0.001, 0.0, 0
switchflag1 = 0



pathbuf.0 = mediadir + "\\circle.bmp"
e3dcreatesprite pathbuf.0, 1, spid1
e3dgetspritesize spid1, spw1, sph1

cenx1 = 0
ceny1 = 0


chkfps1 = 0

confstat = 0

e3ddestroyprogressbar


*main


e3dgetkeyboardstate keybuf

if@hsp keybuf.         $1B	 = 1 : goto@hsp *bye 


if@hsp endflag = 0 {
gosub@hsp *movechara1
}

e3dsetnewpose hsid1, frameno1

e3dchkinview scid1, hsid0
e3dchkinview scid1, hsid1
e3dchkinview scid1, hsid2

e3dbeginscene scid1


e3drender scid1, hsid0, 0, frameno0, 0
e3drender scid1, hsid1, 0, frameno1, 0
e3drender scid1, hsid2, 0, 0, 0


e3drender scid1, hsid1, 1, frameno1, 0

gosub@hsp *drawtext
gosub@hsp *drawindicator

e3dendscene

e3dpresent scid1

waitbyfps 100, chkfps1

goto@hsp *main


*bye
e3dbye
end@hsp

*movechara1
movecnt++
mvr = 2000.0

e3dcos movecnt, newx
e3dsin movecnt, newz
newx *= mvr
newz *= mvr

diffx = posx4 - newx
diffz = posz4 - newz

e3ddot diffx, 0.0, diffz, 0.0, 0.0, 1.0, dot
e3dacos dot, newdeg
e3dvec2ccw diffx, diffz, 0.0, 1.0, ccw

rotdegy = ccw * newdeg

posx4 = newx
posz4 = newz
e3dsetpos hsid1, posx4, posy4, posz4
e3dsetdir hsid1, 0.0, rotdegy, 0.0

return@hsp


*drawtext

textposx = 10 : textposy = 10
textr = 255 : textg = 255 : textb = 255
textscale = 1

textposx = 10 : textposy = 300
str5 = "chkfps1  " + chkfps1
e3ddrawtext textposx, textposy, textscale, textr, textg, textb, str5

textposx = 10 : textposy = 340
str8 = "cenx1  " + cenx1 + "  ceny1  " + ceny1
e3ddrawtext textposx, textposy, textscale, textr, textg, textb, str8

return@hsp

*drawindicator

e3dbeginsprite


e3dgetscreenpos scid1, hsid1, -1, cenx1, ceny1
x1 = cenx1 - (spw1 / 2)
y1 = ceny1 - (sph1 / 2)	
if@hsp ( (cenx1 != -1) & (ceny1 != -1) ) {
e3drendersprite spid1, 1.0, 1.0, x1, y1
}



vertno = 2	
e3dgetscreenpos scid1, hsid2, partno2, posx2, posy2, vertno, 0
scale = 0.1
sizediv = 1.0 / scale
x2 = posx2 - (spw1 / sizediv / 2)
y2 = posy2 - (spw1 / sizediv / 2)
if@hsp ( (posx2 != -1) & (posy2 != -1) ) {
e3drendersprite spid1, scale, scale, x2, y2
}

e3dendsprite
return@hsp

