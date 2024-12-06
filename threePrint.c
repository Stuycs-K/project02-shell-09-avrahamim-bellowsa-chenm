#include <stdio.h>

int main(){
char line_buff[255];
fgets(line_buff, 255, stdin);
printf("%s\n%s\n%s\n", line_buff, line_buff, line_buff);
return 0;
}
