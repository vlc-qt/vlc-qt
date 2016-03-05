echo EXPORTS > libvlc.def
for /f "usebackq tokens=4,* delims=_ " %%i in (`dumpbin /exports "libvlc.dll"`) do if %%i==libvlc echo %%i_%%j >> libvlc.def
lib /MACHINE:x64 /DEF:"libvlc.def" /OUT:"sdk\lib\libvlc.lib"

echo EXPORTS > libvlccore.def
for /f "usebackq tokens=4,* delims=_ " %%i in (`dumpbin /exports "libvlccore.dll"`) do if %%i==vlc echo %%i_%%j >> libvlccore.def
for /f "usebackq tokens=4,* delims=_ " %%i in (`dumpbin /exports "libvlccore.dll"`) do if %%i==var echo %%i_%%j >> libvlccore.def
lib /MACHINE:x64 /DEF:"libvlccore.def" /OUT:"sdk\lib\libvlccore.lib"
