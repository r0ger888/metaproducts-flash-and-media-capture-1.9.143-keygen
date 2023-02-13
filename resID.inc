include		windows.inc 
include		kernel32.inc 
include		user32.inc 
include     gdi32.inc  
include 	shell32.inc
include		winmm.inc
include		masm32.inc
include		msvcrt.inc
include		comctl32.inc
include		oleaut32.inc
include		ole32.inc
include		advapi32.inc
include		comdlg32.inc
include		msimg32.inc
include     /masm32/macros/macros.asm

includelib	kernel32.lib
includelib	user32.lib 
includelib 	gdi32.lib
includelib 	shell32.lib
includelib	winmm.lib
includelib 	masm32.lib
includelib	msvcrt.lib
includelib	comctl32.lib
includelib  oleaut32.lib
includelib  ole32.lib
includelib	advapi32.lib
includelib	comdlg32.lib
includelib 	msimg32.lib

include btnt.inc
include crc32.inc

include V2M_V15.inc
includelib V2M_V15.lib

externdef c theTune:byte 

DlgProc			PROTO	:DWORD,:DWORD,:DWORD,:DWORD

.const
IDD_MAIN	equ	1000
IDD_ABOUT	equ	2000
IDB_EXIT	equ	1001
IDB_ABOUT	equ	1002
IDC_NAME	equ	1003
IDC_SERIAL	equ	1004
IDB_PATCH	equ	1005

nHeight		equ	396
nWidth		equ	273

.data
WindowTitle	db	"-=: PRF oWNZ dA wORLD ! :=-",0
r3kt			RECT	<>
TxtFont		LOGFONT <8,0,0,0,FW_BOLD,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,0,'System'>
TxtFont2		LOGFONT <16,0,0,0,FW_BOLD,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,0,'MS Sans Serif'>
DELAY_VALUE			equ		6
Transparency		dd		?
TRANSPARENT_VALUE	equ 254
usrsize		dd  100h
Userbuff	db	100h dup(0)

Cpt1		db	"Keygen.Inc.Patch.By.Peryferiah.Klan",0
Msg1		db	"Patch succeeded!",0
Wrongsize	db	"Wrong size.",0
Badcrc		db 	"Wrong crc checksum.",0
Filebusy	db	"You need to run this keygen as admin to patch FMCapt.",13
			db  "Or if the app is running in background, pls close it.",0
Notfound	db	"FMCapt.dll not found.",0

TargetName   db "FMCapt.dll",0
BackupName   db "FMCapt.dll.BAK",0
TargetCRC32  dd 034736058h
TargetSize   dd 2270208

WBuffer1 	db 0A7h,0FCh
RawOffset1	dd 00171318h
WBuffer2	db 0DEh,06Ch,092h,08Dh,09Eh,069h
RawOffset2	dd 0017131Ah
WBuffer3	db 004h,091h,07Fh,018h,0BBh,0B4h,085h,02Ch,0E4h,0D8h 
RawOffset3	dd 00171320h
WBuffer4	db 058h,062h,0E8h,00Dh,012h,02Eh
RawOffset4	dd 0017132Ah
WBuffer5	db 040h,082h,053h,01Eh,07Eh,0D0h,042h,031h,03Dh,0E9h
RawOffset5  dd 00171330h
WBuffer6	db 003h,02Bh,06Eh,02Ah,06Fh,000h
RawOffset6	dd 0017133Ah
WBuffer7	db 097h,03Dh,005h,018h,07Bh,063h,0C8h,020h,07Fh,04Bh
RawOffset7	dd 00171340h
WBuffer8	db 0CAh,000h,05Ah,000h,02Ah,000h
RawOffset8	dd 0017134Ah
WBuffer9	db 085h,01Dh,06Bh,000h,009h,0E6h,015h,004h
RawOffset9	dd 00171350h

.data?
hInstance	dd	?
hFont			dd	?
hName			dd	?
hSerial			dd	?
hIMG			dd  ?
WndRect		RECT	<>
XndRect		RECT	<>
NameRect	RECT	<>
SerialRect	RECT	<>
hBrush		dd	?
PosX		dd  ?
PosY		dd  ?
xWnd		dd  ?
hTarget      HINSTANCE ?
BytesWritten db  ?