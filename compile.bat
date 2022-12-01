@echo off
cls
gcc -O3 .\src\*.c .\src\pieces\*.c -I lib\GLFW\include\ -I . lib\GLFW\lib-mingw-w64\libglfw3.a -lopengl32 -lkernel32 -luser32 -lgdi32 -lws2_32 -o u_release.exe
.\u_release.exe
@echo on