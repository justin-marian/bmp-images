CFLAGS += -c -g -Wall -Wextra -Wpedantic -O \
                -Wformat=2 -Wno-unused-parameter \
                -Wnested-externs -Wmissing-include-dirs \
                -Wold-style-definition -Wredundant-decls \
                -Wshadow -Wwrite-strings -Wstrict-prototypes \
                -Wjump-misses-init -Wlogical-op -Werror

PATH_TO_FILES += ../src/
PATH_TO_INSTR += $(PATH_TO_FILES)/include/api/
PATH_TO_CMD += $(PATH_TO_FILES)/cmd/

FILES += $(PATH_TO_INSTR)/instr.c $(PATH_TO_FILES)/bmp_image.c \
		 $(PATH_TO_CMD)/cmd_insert.c $(PATH_TO_CMD)/cmd_draw.c $(PATH_TO_CMD)/cmd_fill.c \

build: bmp
	@rm -rf *.o

bmp: bmp_obj_files
	@gcc *.o -o bmp

bmp_obj_files: $(FILES)
	@gcc $(CFLAGS) $(FILES)

clean:
	@find . -type f -name "*.o" -exec rm -rf {} \;
	@rm -rf output bmp