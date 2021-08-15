all:
	clang++ -I include -o app src/main.cpp -L libs -lstdc++ -framework AppKit -lpdfium
