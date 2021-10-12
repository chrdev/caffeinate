set RELDIR=caffeinate-release
del /F /Q %RELDIR%.7z
rmdir /S /Q %RELDIR%
mkdir %RELDIR%
copy /y caffeinate\caffeinate-x??.exe %RELDIR%\
copy /y monitor-off\monitor-off-x??.exe %RELDIR%\
copy /y README.md %RELDIR%\
7z a -mx -myx -mqs -stl %RELDIR%.7z  %RELDIR%\
