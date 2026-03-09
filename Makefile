output.png: main output.ppm
	magick output.ppm output.png

output.ppm: main
	./main

main: main.c
	cc -Wall -Wextra main.c -o main -lm

clean:
	rm -f main output.ppm output.png
