// written by h. niemi
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

class commentread{

public:
double commentfloatread(FILE *stream);
int commentintread(FILE *stream);
int commentstrread(FILE *stream, char *buf);

};
