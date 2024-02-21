// written by h. niemi
#include <cstring>

double commentfloatread(FILE *stream);
int commentintread(FILE *stream);
int commentstrread(FILE *stream, char *buf);


double commentfloatread(FILE *stream)
{
	char cache1[500];
	int check;
	double value;
	int out_flag;
	int err;

	value = 0.0;
	out_flag = 0;
	while(!out_flag)
	{
		err = fscanf(stream,"%s", cache1);

		if(cache1[0]=='#')
			while((check = fgetc(stream)) != '\n' && check != EOF);
		else
		{
			value = atof(cache1);
			out_flag = 1;
		}
	}

	return value;
}


int commentintread(FILE *stream)
{
	char cache1[500];
	int value, check;
	int out_flag;
	int err;

	value = 0;
	out_flag = 0;
	while(!out_flag)
	{
		err = fscanf(stream,"%s", cache1);

		if(cache1[0]=='#')
			while((check = fgetc(stream)) != '\n' && check != EOF);
		else
		{
			value = atoi(cache1);
			out_flag = 1;
		}
	}

	return value;
}


int commentstrread(FILE *stream, char *buf)
{
	char cache1[500];
	int check;
	int out_flag;
	int err;

	out_flag = 0;
	while(!out_flag)
	{
		err = fscanf(stream,"%s", cache1);

		if(cache1[0]=='#')
			while((check = fgetc(stream)) != '\n' && check != EOF);
		else
		{
			strcpy(buf, cache1);
			out_flag = 1;
		}
	}

	return 0;
}

// Recognize empty line
// {
// 	char buf[BUFLEN], *p;
// 	int counter = 0;
// 	while( !feof(stdin) ){
// 		fgets(buf, BUFLEN, stdin);
// 		p=buf;
// 		while(*p==' ' || *p=='\t') p++; // skip whitespaces
// 		if(*p=='\r') p++;
// 		if(*p=='\n') counter++;
// 	}
// 	printf("%d\n", counter);
// 	return 0;
// }
