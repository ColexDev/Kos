main:
	g++ -I/usr/local/include src/main.cpp src/cell.cpp src/file.cpp src/table.cpp src/progress_bar.cpp src/utils.cpp -L/usr/local/lib -Wl,-R/usr/local/lib -lncurses -o kos
