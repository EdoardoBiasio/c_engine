sources=stb\
main\
shaders/shader\
shaders/model_shader\
vao\
math/vec\
utils/memory\
utils/logging\
texture\
utils/file\
mesh\
camera\
lights/point_light\
parsers/obj_parser\

source_dir=src
target_dir=build
debug_dir=debug
release_dir=release
obj_path=obj
sources_=$(patsubst %,$(source_dir)/%.c, $(sources))
debug_objects_=$(patsubst %,$(target_dir)/$(debug_dir)/$(obj_path)/%.o, $(sources))
release_objects_=$(patsubst %,$(target_dir)/$(release_dir)/$(obj_path)/%.o, $(sources))

include_files=shaders/shader.h\
includes.h\
vao.h\
math/vec.h\
color.h\
utils/memory.h\
utils/logging.h\
texture.h\
utils/file.h\
utils/optional.h\
mesh.h\
camera.h\
lights/lights.h\
parsers/obj_parser.h\

includes_files_=$(patsubst %, $(source_dir)/%, $(include_files))

CC=gcc
debug_flags=-Wall -Wextra -Wpedantic -Wshadow -Wundef -fsanitize=address -std=c11 -g -DBUILD_DEBUG
release_flags=-std=c11 -O3
linker=-framework OpenGL -lglfw -lglew -L/usr/local/lib/
includes=-I/usr/local/include/ -Iinclude/
target=cengine

$(target_dir)/$(debug_dir)/$(obj_path)/%.o: $(source_dir)/%.c $(includes_files_)
	$(CC) -c -o $@ $< $(includes) $(debug_flags)

$(target_dir)/$(release_dir)/$(obj_path)/%.o: $(source_dir)/%.c $(includes_files_)
	$(CC) -c -o $@ $< $(includes) $(release_flags)

$(target_dir)/$(debug_dir)/$(target): $(debug_objects_) 
	$(CC) $(debug_objects_) -o $(target_dir)/$(debug_dir)/$(target) $(debug_flags) $(linker) $(includes)

$(target_dir)/$(release_dir)/$(target): $(release_objects_)
	$(CC) $(release_objects_) -o $(target_dir)/$(release_dir)/$(target) $(release_flags) $(linker) $(includes)

.PHONY: run
run: $(target_dir)/$(debug_dir)/$(target)
	./$(target_dir)/$(debug_dir)/$(target)

.PHONY: run_release
run_release: $(target_dir)/$(release_dir)/$(target)
	./$(target_dir)/$(release_dir)/$(target)

.PHONY: clean
clean:
	rm $(debug_objects_)
	rm $(release_objects_)
	rm $(target_dir)/$(debug_dir)/$(target)
	rm $(target_dir)/$(release_dir)/$(target)