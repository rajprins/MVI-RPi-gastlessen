/*
 * dos2unix.c
 *
 * Doel  : converteren van textbestand in DOS-indeling naar UNIX-indeling
 *
 * Door  : Roy Prins, Origin Nederland BV.
 * Datum : 23-07-2000
 *
 */

#include <stdio.h>
#include <fcntl.h>

#define START 0
#define CRFOUND 1

#define RBYTES 4096

char CR = '\r';
char rbuf[RBYTES];
FILE *rfp;

print_argmsg()
{
   printf("\n  Gebruik: dos2unix bronbestand [ > doelbestand]\n");
   exit(-1);
}

print_rmsg(file)
char *file;
{
   printf("Leesfout op bronbestand %s\n", file);
   fclose(rfp);
   exit(-1);
}

print_wmsg(file)
char *file;
{
   printf("schrijffout op doelbestand %s\n", file);
   fclose(rfp);
   exit(-1);
}

main(argc, argv)
int argc;
char *argv[];
{

   int rlen, len, i;
   int state = START;
   char c;

   printf("DOS-UNIX text conversie utility.\n");
   printf("Copyright (C) 2000 Roy Prins, Origin BV.\n"); 

   if (argc < 2)
      print_argmsg();

   if (!(rfp=fopen(argv[1], "rb")))
   {
      printf("Kan bronbestand %s niet openen\n", argv[1]);		
      exit(-1);
   }

   #ifdef ON_DOS
      /* set mode van stdout naar binary */
      if ((setmode(fileno(stdout), O_BINARY)) == 1)
      {
         printf("kan stdout niet omzetten naar binary mode\n");
         exit(-1);
      }
   #endif

   do /* condition: while (rlen == RBYTES) */
   {
      if ((rlen=fread(rbuf, 1, RBYTES, rfp)) == -1)
         print_rmsg(argv[1]);

      if (rlen == 0)
         /*bestandsgrootte is 0*/
         break;

      len = rlen;
      i = 0;
      while (len--)
      {
         c = rbuf[i++];
	      switch (c)
	      {
   		   case '\r':
	   		   if (state == CRFOUND)
                  if (fwrite(&CR, 1, 1, stdout) < 1)
                     print_wmsg(argv[2]);
				   state = CRFOUND; 
				   break;
            case '\n':
               if (state == CRFOUND)
               {
                  if (fwrite(&c, 1, 1, stdout) < 1)
                     print_wmsg(argv[2]);
                     state = START;
				   }
				   break;
   			default:
               if (state == CRFOUND)
               {
                  state = START;
                  if (fwrite(&CR, 1, 1, stdout) < 1)
                     print_wmsg(argv[2]);
   				}

               if (c == 0x1a)
               goto eof;

               if (fwrite(&c, 1, 1, stdout) < 1)
                  print_wmsg(argv[2]);
                  break;
         };
      };
   } while (rlen == RBYTES);

   eof:
      fclose(rfp);
      exit(0);
}
