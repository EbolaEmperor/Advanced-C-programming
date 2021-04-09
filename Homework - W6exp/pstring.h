#ifndef _PSTRING_H_
#define _PSTRING_H_

typedef struct {
	int length;
	char content[];
} PString;

//	create an object of PString with its content as s
PString* psCreate(const char* s);

//	release the object ps
void psFree(PString *ps);

//	print ps
void psPrint(const PString* ps);

//	read a word, which is seperated by space
PString* psReadWord();

//	read a line
PString* psReadLine();

//	returns the number of characters in the PString object, i.e. the length of the string
int psLength(const PString* ps);

//	clone a PString object
//	return the new one
PString* psClone(const PString *ps);

//	concat two PString into a new one
//	return the new one
PString* psConcat(const PString* ps1, const PString* ps2);

//	compare two PString objects
//	returns -1 if ps1 is < ps2; 0 if ps1 == ps2; 1 if ps1 > ps2
int psCompare(const PString* ps1, const PString* ps2);

//	find the location of ch in the ps
//	return the location of the first ch in ps, -1 if ch is not in ps
int psFindChar(const PString* ps, char ch);

//	find the first location of ps2 in ps1
//	return the location, NULL is not found
int psFindString(const PString* ps1, const PString* ps2);

//	get rid of the space at both end
//	return the new created string
PString* psTrim(const PString* ps);

//	turn every character in ps into lower case
//	return the new lowered string
PString* psLower(const PString* ps);

//	turn every character in ps into upper case
//	return the new uppered string
PString* psUpper(const PString* ps);

//	take a subset of the string ps. The subset is from begin to end.
//	For example, psSubstring(psCreate(“0123456789”), 3,5) returns a PString as “345”
//	return the new extracted string
PString* psSubstring(const PString* ps, int begin, int end);

//	replace every ch1 in ps with ch2
//	return the replaced string
PString* psReplace(const PString* ps, char ch1, char ch2);

//	return the char at the index
char psChar(const PString* ps, int index);

//	return 1 if the ps1 begins with ps2, 0 otherwise
int psBeginWith(const PString* ps1, const PString* ps2);

#endif