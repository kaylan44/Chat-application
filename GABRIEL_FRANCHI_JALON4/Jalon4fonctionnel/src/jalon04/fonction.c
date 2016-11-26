#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Extract sub string from string
char *str_sub (const char *s, unsigned int start, unsigned int end)
{
   char *new_s = NULL;

   if (s != NULL && start < end)
   {
/* (1)*/
      new_s = malloc (sizeof (*new_s) * (end - start + 2));
      if (new_s != NULL)
      {
         int i;

/* (2) */
         for (i = start; i <= end; i++)
         {
/* (3) */
            new_s[i-start] = s[i];
         }
         new_s[i-start] = '\0';
      }
      else
      {
         fprintf (stderr, "Memoire insuffisante\n");
         exit (EXIT_FAILURE);
      }
   }
   return new_s;
}


// Découper une chaine
char **str_split (char *s, const char *ct)
{
   char **tab = NULL;

   if (s != NULL && ct != NULL)
   {
      int i;
      char *cs = NULL;
      size_t size = 1;

/* (1) */
      for (i = 0; (cs = strtok (s, ct)); i++)
      {
         if (size <= i + 1)
         {
            void *tmp = NULL;

/* (2) */
            size <<= 1;
            tmp = realloc (tab, sizeof (*tab) * size);
            if (tmp != NULL)
            {
               tab = tmp;
            }
            else
            {
               fprintf (stderr, "Memoire insuffisante\n");
               free (tab);
               tab = NULL;
               exit (EXIT_FAILURE);
            }
         }
/* (3) */
         tab[i] = cs;
         s = NULL;
      }
      tab[i] = NULL;
   }
   return tab;
}


void describe_string(char* buffer){
   int i = 0;
   while(buffer[i] != '\0'){

      printf("caract= %c \n",buffer[i]);
      i++;

   }

}

char* get_2_arg(char* buffer, int position){
    int i=position;
    char* pseudo=malloc(20);
    while(1){
        if((buffer[i] == ' ')  || (buffer[i] == '\n') || (buffer[i] == '\0')){
            pseudo[i-position]='\0';
            return pseudo;
        }
        else{
            pseudo[i-position]=buffer[i];
            i++;
        }
    }

}
