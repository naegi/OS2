;
;   crti.S give the prolog for the .init and the .fini section 
;
global _init
global _fini
_init:
	push ebp
	mov ebp, esp
	; gcc will nicely put the contents of crtbegin.o's .init section here.

_fini:
	push ebp
	mov ebp, esp
        ; gcc will nicely put the contents of crtbegin.o's .fini section here.
