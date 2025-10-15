/* Main program segment */

/* Megaroids for the Macintosh is supplied courtesy of
Megamax, Inc. It was written by Mike Bunnell and Mitch
Bunnell, 1985. */
#include <qd.h>
#include <qdvars.h>
#include <win.h>
#include <menu.h>
#include <event.h>
#include <dialog.h>
#define LASTMENU 6
#define APPLEMENU 1
#define FILEMENU 256
#define STARTMENU 2
#define INFOMENU 3
#define HISCOREMENU 4
#define SCOREMENU 5
#define CURPAGEOPTION Ox936
#define NULL OL
#define TRUE 1
#define FALSE 0
#define SCORE-DIGITS 6

extern int hiscore[SCORE_DIGITSJ;
char score_string[SCORE-DIGITS+1];
menuhandle mymenus[LASTMENU+1];
rect screenrect, dragrect, prect;
boolean doneflag, temp;
eventrecord myevent;
int code, refnum;
windowrecord wrecord;
windowptr mywindow;
windowptr whichwindow;
int themenu, theitem;
char *progname = "megaroids";
#define SCREEN Ox7a700
#define SCREEN2 Ox72700
#define O_RDONLY 1
#define O_RDWR 3
#define O_BINARY 8192
#define MAXSIZE 10000 

char *free_info[] = {
"This program is free.",
, "You may make as many copies as you Like.",
, "It is not for resale",
NULL
};

char *Megamax_info[] = { "The Megamax C compiler is full K & R + common extensions",
"Its features include: ",
" full floating point, one pass compilation, optimized for",
" 68000, smart Linker (only Loads Library routines called)",
" Librarian, dynamic overlays, creates stand alone MAC",
" applications, in-Line assembly Language, batch facility,",
" nothing Left to buy, no License fees.",
"ALL for only 299.95 (ed. and quantity discounts available)",
"Megamax, Inc., P. O. Box 851521, Richardson, TX 75085-1521",
"Phone: (214) 987-4931 Dealer inquiries welcome.",
NULL
}; 

char *source_info[] = {
" ", "A commented source code Listing (bound hardcopy listing)",
"identical to this chapter is also available for $25 from: ",
"                    Megamax Inc.",",
"                    P. 0. Box 31294",
"                    Dallas, TX 75231-0294",
NULL
};

/* This routine was not in the Library. This is the
interface to the Macintosh Toolbox ROM routine. */ 

unpackbits (srcptr, destptr, count) 
char **srcptr, **destptr;
int count;
{
asm {
	  move.l    srcptr(A6), -(A7)
      move.l    destptr(A6), -(A7)
      move.l    count(A6), -(A7)
      dc.w     Oxa8d0 
	}
}
char *inbuf;
char destbuf[72];
bit srcbitmap;
#define START 116
#define LEFT 5

/* This routine reads in the high score and a Macpaint
formatted picture of the title screen out of the data
fork of the program. It stores the high score in
hiscore[] and stores the picture in the unused memory
between the two graphic screens. It does this to make use
of the space that is Lost when using the second screen
(The screen takes up about 22k but if you use this, you
Lose an even 32k). */
getpaintdoc (filename) 

char *fi Lename;
{
int f;
int i;
inbuf = (char *) (SCREEN2 + 21888);
/* space between screens */
f = open (filename, O_RDONLY | O_BINARY) ;
if (f != -1) {
read(f, score_string, SCORE_DIGITS);
score_string[SCORE-DIGITS] = 0;
for(i=0;i< SCORE_DIGITS ; i++) {
hiscore[i] = score_string[SCORE_DIGITS -1 -i] - '0';
}
read(f, inbuf, 512 - (SCORE_DIGITS));
/* read past header info */
read(f, inbuf, MAXSIZE);
/* read in the rest of the file*/
close (f);
/* second screen - the area that the Later expansion will go in */

srcbitmap.baseaddr = (qdptr) SCREEN2;
srcbitmap.rowbytes = 64;
srcbitmap.bounds.a.top = O;
srcbitmap.bounds.a.left = O;
srcbitmap.bounds.a.bottom = 342;
srcbitmap.bounds.a.right = 512; 
	}
}