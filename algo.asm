include biglib.inc
includelib biglib.lib

include base64.asm

GenKey        PROTO    :DWORD

.data
ExpN db "9D10290DC2383F759A334C46B09C74B47DE20EBE47CD4FE92F1BA7E1D4145D818"
	 db "363BDCB1A1D9726D64EF95266EB10BC995BF7A1DAFDDD9CB09",0
ExpD db "58CC1629CD3077D04949CF49F7F7BC937EC81B85C09A771F629EC41F897729D21"
	 db "039A0A2CFDA81FBDDC862E31E784CE382B647CCC29078C0DF1",0

ProgLabel   db "FM11",0
OneByte     db 01h,0 
LicType     db "10000",0
StartKey    db "dqma",0
EndKey      db "amqd",0
CustomStr   db "QuickMafz",0 ; 2 + 2 is 4 minus 1 that'z 3 QuickMafz !
NoName      db "insert ur name.",0
TooLong     db "name too long.",0
FinalBuffer db 256 dup(0)
NameBuffer  db 256 dup(0)

.data?
_N            dd ?
_D            dd ?
_C    		  dd ?
_M			  dd ?
RSAEnk        db 256 dup(?)
Base64Bfr     db 256 dup(?)

.code
GenKey proc hWin:DWORD

    ; get the whole name string.
    invoke GetDlgItemText,hWin,IDC_NAME,offset NameBuffer,sizeof NameBuffer
    .if eax == 0
		invoke SetDlgItemText,hWin,IDC_SERIAL,offset NoName
	.elseif eax > 30
		invoke SetDlgItemText,hWin,IDC_SERIAL,offset TooLong
	.elseif
   
    ; initialize the string for RSA-470 decryption
    mov byte ptr [RSAEnk],7
    invoke lstrcat,offset RSAEnk,offset ProgLabel  ; FM11
    invoke lstrcat,offset RSAEnk,offset OneByte    ; 01h
    invoke lstrcat,offset RSAEnk,offset NameBuffer ; ur name
    invoke lstrcat,offset RSAEnk,offset OneByte    ; 01h
    invoke lstrcat,offset RSAEnk,offset LicType    ; 10000 (Unlimited site license)
    invoke lstrcat,offset RSAEnk,offset OneByte    ; 01h
    invoke lstrcat,offset RSAEnk,offset CustomStr  ; any string :p
    invoke _BigCreate,0
    mov _N,eax
    invoke _BigCreate,0
    mov _D,eax
    invoke _BigCreate,0
    mov _C,eax
    invoke _BigCreate,0
    mov _M,eax
   
    ; decrypting string to 470 bits of RSA
    invoke _BigIn,offset ExpN,16,_N
    invoke _BigIn,offset ExpD,16,_D
    invoke lstrlen,offset RSAEnk
    invoke _BigInBytes,offset RSAEnk,eax,256,_M
    invoke _BigPowMod,_M,_D,_N,_C
    invoke _BigOutBytes,_C,256,offset RSAEnk
   
    ; then encode them with base64
    push offset Base64Bfr
    push eax
    push offset RSAEnk
    call Base64Enk
   
    ; "dqma" + final string made of RSA-470 & Base64 + "amqd"
    invoke lstrcat,offset FinalBuffer,offset StartKey
    invoke lstrcat,offset FinalBuffer,offset Base64Bfr
    invoke lstrcat,offset FinalBuffer,offset EndKey
   
    ; final result in the textbox :p
    invoke SetDlgItemText,hWin,IDC_SERIAL,offset FinalBuffer
   
    ; clear RSA buffers.
    call Clean
   
    .endif
    ret
    
GenKey endp

Clean proc

    invoke RtlZeroMemory,offset FinalBuffer,sizeof FinalBuffer
    invoke RtlZeroMemory,offset RSAEnk,sizeof RSAEnk
    invoke RtlZeroMemory,offset Base64Bfr,sizeof Base64Bfr
    invoke RtlZeroMemory,offset NameBuffer,sizeof NameBuffer
    invoke _BigDestroy,_N
    invoke _BigDestroy,_D
    invoke _BigDestroy,_C
    invoke _BigDestroy,_M
    ret
   
Clean endp
