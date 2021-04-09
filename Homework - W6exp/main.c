#include <stdio.h>
#include <string.h>
#include <pstring.h>

int main(int argc, char*argv[])
{
	FILE* fp = fopen(argv[1], "w");

	//	create && free
	int fs = 0;
	PString *s = psCreate("Hello");
	if ( psLength(s) == 5 ) {
		fs++;
	}
	psFree(s);
	fprintf(fp, "#01-%d\n", fs);
		
	//	readword & readline & print
	PString *s1 = psReadWord();
	psPrint(s1);
	PString *s2 = psCreate("Zhejiang");
	if ( psCompare(s1, s2) == 0 ) { 
		fs++;
	}
	psFree(s1);
	psFree(s2);
	fprintf(fp, "#02-%d\n", fs);

	//	clone 
	s1 = psCreate("aa");
	s2 = psClone(s1);
	if ( psCompare(s1, s2) == 0 ) { 
		fs++;	//10
	}
	psFree(s1);
	psFree(s2);
	fprintf(fp, "#03-%d\n", fs);
	
	//	concat
	s1 = psCreate("hello");
	s2 = psCreate("world");
	PString* s3 = psCreate("helloworld");
	PString* s4 = psConcat(s1, s2);
	if ( psCompare(s3, s4) == 0 ) {
		fs++;
	}
	psFree(s1);
	psFree(s4);
	fprintf(fp, "#04-%d\n", fs);
	
	//	compare
	s1 = psCreate("abc");
	s2 = psCreate("abd");
	if ( psCompare(s1, s2) <0 ) {
		fs++;
	}
	psFree(s1);
	psFree(s2);
	fprintf(fp, "#05-%d\n", fs);
	
	//	findchar
	s1 = psCreate("abc");
	if ( psFindChar(s1, 'b') == 1 ) {
		fs++;
	}
	psFree(s1);
	fprintf(fp, "#06-%d\n", fs);
	
	//	findstring
	s1 = psCreate("abcdefg");
	s2 = psCreate("de");
	if ( psFindString(s1, s2) ==3 ) {
		fs++;	
	}
	psFree(s1);
	psFree(s2);
	fprintf(fp, "#07-%d\n", fs);
	
	//	trim
	s1 = psCreate("o     ");
	s2 = psCreate("o");
	s3 = psTrim(s1);
	if ( psCompare(s3, s2) ==0 ) {
		fs++;	
	}
	psFree(s1);
	psFree(s2);
	psFree(s3);
	fprintf(fp, "#08-%d\n", fs);
	
	//	lower & upper
	s1 = psCreate("ZheJiang");
	s2 = psCreate("zhejiang");
	s3 = psLower(s1);
	if ( psCompare(s3, s2) ==0 ) {
		fs++;	
	}
	psFree(s1);
	psFree(s2);
	psFree(s3);
	fprintf(fp, "#09-%d\n", fs);
	
	//	substring
	s1 = psCreate("zhejiang");
	s2 = psCreate("jian");
	s3 = psSubstring(s1, 3,7);
	if ( psCompare(s3, s2) ==0 ) {
		fs++;	
	}
	psFree(s1);
	psFree(s2);
	psFree(s3);
	fprintf(fp, "#0A-%d\n", fs);
	
	//	replace
	s1 = psCreate("zhejieng");
	s2 = psCreate("zhajiang");
	s3 = psReplace(s1, 'e', 'a');
	if ( psCompare(s3, s2) ==0 ) {
		fs++;	
	}
	psFree(s1);
	psFree(s2);
	psFree(s3);
	fprintf(fp, "#0B-%d\n", fs);

	//	char
	s1 = psCreate("zhejieng");
	if ( psChar(s1, 1) =='h' ) {
		fs++;	
	}
	psFree(s1);
	fprintf(fp, "#0C-%d\n", fs);
	
	//	beginwith
	s1 = psCreate("zhejiang");
	s2 = psCreate("zhe");
	if ( psBeginWith(s1, s2) ==1 ) {
		fs++;	
	}
	psFree(s2);
	psFree(s1);
	fprintf(fp, "#0B-%d\n", fs);
	
	//	result
	fprintf(fp, "%d\n", fs);
	fclose(fp);
}
