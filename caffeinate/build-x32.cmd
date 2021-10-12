if %PROCESSOR_ARCHITECTURE%==AMD64 (set MSVCRTDLL=%SystemRoot%\SysWOW64\msvcrt.dll) else (set MSVCRTDLL=%SystemRoot%\System32\msvcrt.dll)
polib /MACHINE:X86 %MSVCRTDLL% /OUT:msvcrt32.lib
cc /x /Tx86-coff /Os /Ze caffeinate.c /ENTRY:wmain /SUBSYSTEM:CONSOLE /RELEASE /MACHINE:X86 /NODEFAULTLIB kernel32.lib user32.lib shell32.lib msvcrt32.lib /ocaffeinate-x32.exe