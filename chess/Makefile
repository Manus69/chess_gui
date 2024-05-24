target = libChess.a

cc = gcc
flags_base = -Wall -Wextra
flags_dbg = $(flags_base) -g3
flags_rel = $(flags_base) -Ofast -Oflto

obj_dir = ./obj/
src = $(wildcard *.c)
objs = $(addprefix $(obj_dir),$(src:.c=.o))

$(obj_dir)%.o : %.c
	$(cc) $(flags) $^ -c -o $@

$(target) : $(objs)
	ar -rcsv $(target) $(objs)

.PHONY: dbg

all: dbg

dir:
	mkdir -p $(obj_dir)

dbg: dir
dbg: flags = $(flags_dbg)
dbg: $(target)

rm:
	rm -f $(objs) $(taget)

re_dbg: rm dbg
