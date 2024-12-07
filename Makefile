all:
	@gcc main.c time.c verify.c menu.c io.c -o main
clean:
	@rm -f main bookinfo/*