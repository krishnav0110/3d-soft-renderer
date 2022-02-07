set VScompiler = "C:/Program Files (x86)/Microsoft Visual Studio/2019/BuildTools/VC/Tools/MSVC/14.28.29910/bin/Hostx64/x64/cl.exe"

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" amd64_x86

cd obj
cl ../src/*.c /c /I../include/ /DCOMPILING_DLL

cd ..
link obj/*.obj /dll user32.lib gdi32.lib kernel32.lib

cl app.c /Iinclude/ /linkcamera.lib