wav.exe: *.c *.h
	gcc file_output.c sound.c main.c -o wav.exe
