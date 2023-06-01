/*
 * unix2dos.c
 *
 * Doel  : converteren van textbestand in UNIX-indeling naar DOS-indeling
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

char rbuf[RBYTES];
FILE *rfp;

print_argmsg()
{
   printf("\n  Gebruik: unix2dos bronbestand [ > doelbestand]\n");
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
   char c;

   printf("UNIX-DOS text conversie utility.\n");
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
   if ((setmode(fileno(stdout), O_BINARY)) == 1) {
      printf("kan stdout niet omzetten naar binary mode\n");
      exit(-1);
   }
   #endif

   do /* condition: while (rlen == RBYTES) */
   {
      if ((rlen=fread(rbuf, 1, RBYTES, rfp)) == -1)
      print_rmsg(argv[1]);

      if (rlen == 0)
         break;

      len = rlen;
      i = 0;

      while (len--)
      {
         c = rbuf[i++];
         switch (c)
         {
            case '\n':
               if (fwrite("\r\n", 1, 2, stdout) < 2)
                  print_wmsg(argv[2]);
                  break;
            default:
               if (fwrite(&c, 1, 1, stdout) < 1)
                  print_wmsg(argv[2]);
                  break;
         };
      };
   } while (rlen == RBYTES);

   fclose(rfp);
   exit(0);
}
