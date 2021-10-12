nasm -f win64 -o monitor-off-x64.obj monitor-off-x64.asm
polink /SUBSYSTEM:WINDOWS /MACHINE:X64 /ENTRY:main /RELEASE /OUT:monitor-off-x64.exe monitor-off-x64.obj kernel32.lib user32.lib
