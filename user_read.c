#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
ssize_t len = 10;
char buf[len];
 
int fp = open("/dev/axo", O_RDONLY);
if(fp < 0) printf("descrittore non valido\n");
else printf("File hello aperto; fd: %d \n", fp);

int result = read(fp, buf, len, 0);

if (result <0) printf("read error: %d\n", result);
else if (result == 0) printf("0 bytes\n");
else printf("numero bytes letti: %d\n", result);

printf("dati letti: %s\n", buf);

result = ioctl(fp, 1, buf);

}
