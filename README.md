# cdecl
Translates C declarations into pseudo-English. Algorithm taken from [1]. 

Pass arguments using double quotes. Sample usage:

```
$ ./cdecl "volatile const short * const a()"
```

You probably will have to edit the Makefile. This is something I wrote on my way to work. Might not be as polished as I wished.

[1] 'Expert C Programming' by Peter van der Linden
