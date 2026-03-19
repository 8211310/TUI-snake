#include <string.h>
#include "String.h"

titleString createString(char* str){
	titleString output;
	output.str = str;
	output.len = strlen(str);
	return output;
}


//#define DEBUG
#ifdef DEBUG
#include <stdio.h>
int main(){
	titleString a = createString("ABCDDC");
	printf("The string is %s, length: %d",a.str, a.len);
	return 0;
}
#endif
