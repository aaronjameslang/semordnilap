default: tags semordnilap test

semordnilap: semordnilap.c
	test -f /usr/lib64/libenchant.so                && gcc -Wall -I"/usr/include/enchant" semordnilap.c /usr/lib64/libenchant.so -o semordnilap # Fedora
	test -f /usr/lib/x86_64-linux-gnu/libenchant.so && gcc -Wall -I"/usr/include/enchant" semordnilap.c /usr/lib64/libenchant.so -o semordnilap # Ubuntu

test:
	roundup

tags: *.c
	ctags *.c
