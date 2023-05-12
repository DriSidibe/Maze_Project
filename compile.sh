gcc $1 -o $2 $(sdl2-config --cflags --libs)
$($2)
