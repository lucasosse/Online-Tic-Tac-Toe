all: main.c menu.c rede.c tabuleiro.c
	@gcc main.c menu.c rede.c tabuleiro.c -I. -o main
