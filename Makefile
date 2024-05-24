target = _chess

cc = gcc
flags_base = -Wall -Wextra
flags_dbg = $(flags_base) -g3
flags_rel = $(flags_base) -Ofast -flto

lib = /home/manus/Documents/projects/libY/libY.a
src_dir = src/
obj_dir = obj/
chess_dir = chess/

src = $(wildcard $(src_dir)*c)
src_nd = $(notdir $(src))
obj = $(addprefix $(obj_dir),$(src_nd:.c=.o))
chess_lib = $(chess_dir)libChess.a

$(obj_dir)%.o : $(src_dir)%.c
	$(cc) $(flags) -c $^ -o $@

$(target) : $(obj)
	$(cc) $(flags) $(obj) $(chess_lib) $(lib) -o $@ -lraylib -lm

all: make -C $(chess_dir)
all: dbg

rm_obj:
	rm -f $(obj)

rm_target:
	rm -f $(target)

dir:
	mkdir -p $(obj_dir)

dbg: dir
dbg: flags = $(flags_dbg)
dbg: $(target)

rel: dir
rel: rm_obj rm_target
rel: flags = $(flags_rel)
rel: $(taget)

re_dbg: rm_obj rm_target dbg

chess_dbg:
	make dbg -C $(chess_dir)