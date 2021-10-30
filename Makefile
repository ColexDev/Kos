all: main
main: main.cpp
	g++ -I/usr/local/include main.cpp table.cpp progress_bar.cpp utils.cpp -L/usr/local/lib -Wl,-R/usr/local/lib -lncurses -o Kos
