#!/bin/sh
bindir=$(pwd)
cd /home/mannmi/CLionProjects/opengl-2DMazeGame/OpenGL-Template-master/playground/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "xYES" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		/usr/bin/gdb -batch -command=$bindir/gdbscript --return-child-result /home/mannmi/CLionProjects/opengl-2DMazeGame/OpenGL-Template-master/cmake-build-debug/playground 
	else
		"/home/mannmi/CLionProjects/opengl-2DMazeGame/OpenGL-Template-master/cmake-build-debug/playground"  
	fi
else
	"/home/mannmi/CLionProjects/opengl-2DMazeGame/OpenGL-Template-master/cmake-build-debug/playground"  
fi
