BITS 64
DEFAULT REL

global main

extern GetDoubleClickTime
extern Sleep
extern SendMessageW
extern ExitProcess

section .text
main:
	sub rsp,0x28
	
	call GetDoubleClickTime
	mov rcx,rax
	call Sleep
	
	mov rcx,0xFFFF ;HWND_BROADCAST
	mov rdx,0x0112 ;WM_SYSCOMMAND
	mov r8, 0xF170 ;SC_MONITORPOWER
	mov r9, 0x0002 ;MONITOR_OFF
	call SendMessageW
	
	mov rcx, rax
	call ExitProcess
	