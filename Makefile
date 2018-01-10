default: tags semordnilap test

semordnilap: semordnilap.c
	gcc -Wall -I"/usr/include/enchant" semordnilap.c /usr/lib64/libenchant.so -o semordnilap

test:
	roundup

tags: *.c
	ctags *.c
