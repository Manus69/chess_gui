cc = /usr/bin/gcc-13
flags = -Wall -Wextra
exe = _chess
gui_dir = Gui
gui_src = $(wildcard $(gui_dir)/*.c)
eng_dir = Engine
eng_src = $(wildcard $(eng_dir)/*.c)
liby = ../libY/libY.a
libui = ../libUI/libUI.a

test :
	$(cc) $(flags) -g3 $(eng_src) $(gui_src) Chess.c $(libui) $(liby) -o $(exe) -lraylib -lm
