all: 
	gcc hy457_crypto.c -o run	
clean:
	rm -rf run hy457_crypto hy457_crypto.o outputEncrypted.txt outputDecrypted.txt
