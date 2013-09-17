clear:
	rm -f conv
convert: X Y atom convert.c
	gcc -Wall -pipe -o conv convert.c && ./conv 12
fractal: out
	gcc -Wall -pipe fractals.c -lGL -lGLU -lglut -L/usr/X11R6/lib -lXi -lXmu && ./a.out

