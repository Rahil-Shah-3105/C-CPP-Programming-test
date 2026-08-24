#include <stdio.h> 
#include <stdlib.h> 


void enter_string(char* message, char* s, size_t s_size) 
{
fprintf(stderr, ">>> Entering enter_string(message=%s,s=%s,s_size=%zu)\n", message, s, s_size);
  printf("%s", message);
  fgets(s, s_size, stdin);   
fprintf(stderr, "<<< Exiting enter_string(message=%s,s=%s,s_size=%zu)\n", message, s, s_size);
}

int get_score(char* s) 
{
fprintf(stderr, ">>> Entering get_score(s=%s)\n", s);
  char *end;
  for (end = s; *end != '\0'; ++end);
  --end;

  if (end == s) 
  {
      printf("wrong Input\n");
      return -1;
  }

  int score = 0;
  char c;
  for(char* p = s; p != end; ++p)
  {
    c = *p;
    if(c == ' ') continue;

    c &= ~0x20;

    if(c >= 'A' && c <= 'Z')
    {
      score += c - '@';
    }  
    else
    {
      printf("wrong Input\n");
      return -1;
    }
  }
fprintf(stderr, "<<< Exiting get_score(s=%s)\n", s);
  return score * 5 / (end - s);
}

int main()
{
fprintf(stderr, ">>> Entering main()\n");
  int p,s1,s2;
  char name[1000];

  while(1)
  {
    do 
    {
      enter_string("Enter The First Name: ", name, sizeof(name));
      s1 = get_score(name);
	fprintf(stderr, "main(): s1 → %d\n", s1);
    } while (s1 == -1);

    do 
    {
      enter_string("Enter The Second Name: ", name, sizeof(name));
      s2 = get_score(name);
	fprintf(stderr, "main(): s2 → %d\n", s2);
    } while (s2 == -1);

    if(s2 > s1)
    {
      p = (s1 * 100) / s2;
	fprintf(stderr, "main(): p → %d\n", p);
    }
    else
    {
      p = (s2 * 100) / s1;
    }

    printf("The love Percentage is : %d %% \n",p);
    printf("\n pls Follow me  🌟 if you like this code 😊\n");
  } 
fprintf(stderr, "<<< Exiting main()\n");
  return 0;
}


/* created by NemoNet aka The Young Programmer 🏅
in collaboration with tigertv 🐯 
pls kindly follow me on github OR
give me a star 🌟  */
