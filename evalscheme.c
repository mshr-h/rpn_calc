#include "evalscheme.h"
#include "shared.h"
#include "stack.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OP_NUM 13

char op[OP_NUM][6] = {
  "+", "-", "*", "/", "exp",
  "sin", "cos", "tan", "log", "log10",
  "sqrt", "pi", "e"
};

int checkScheme(char *scheme) {
  char tmp[SCHEME_SIZE];
  int i = 0, c, sp = 0;
  while((c=getWord(tmp, &scheme[i], SCHEME_SIZE)) && strlen(tmp)){
    if(!isOperation(tmp) && !isNumerics(tmp))
      return FALSE;
    if(strcmp(tmp, "+")==0)
      sp-=1;
    else if(strcmp(tmp, "-")==0)
      sp-=1;
    else if(strcmp(tmp, "*")==0)
      sp-=1;
    else if(strcmp(tmp, "/")==0)
      sp-=1;
    else if(strcmp(tmp, "exp")==0)
      sp-=1;
    else if(strcmp(tmp, "sin")==0)
      ;
    else if(strcmp(tmp, "cos")==0)
      ;
    else if(strcmp(tmp, "tan")==0)
      ;
    else if(strcmp(tmp, "sqrt")==0)
      ;
    else if(strcmp(tmp, "log")==0)
      ;
    else if(strcmp(tmp, "log10")==0)
      ;
    else if(strcmp(tmp, "pi")==0)
      sp++;
    else if(strcmp(tmp, "e")==0)
      sp++;
    else
      sp++;
    if((sp < 0) || (STACK_SIZE <= sp))
      return FALSE;
    i+=c;
  }
  if(sp == 1)
    return TRUE;
  else
    return FALSE;
}

char *evalScheme(char *scheme) {
  char tmp[SCHEME_SIZE];
  int i = 0, c;
  STACK_TYPE a, b, r;

  if(!checkScheme(scheme)) {
    strcpy(scheme, "syntax error");
    return scheme;
  }

  initStack();
  while((c=getWord(tmp, &scheme[i], SCHEME_SIZE)) && strlen(tmp)){
    if(strcmp(tmp, "+")==0) {
      b = pop(); a = pop();
      r = a + b;
    }
    else if(strcmp(tmp, "-")==0) {
      b = pop(); a = pop();
      r = a - b;
    }
    else if(strcmp(tmp, "*")==0) {
      b = pop(); a = pop();
      r = a * b;
    }
    else if(strcmp(tmp, "/")==0) {
      b = pop(); a = pop();
      if(b == 0) {
        sprintf(scheme, "NaN");
        return scheme;
      }
      r = a / b;
    }
    else if(0 == strcmp(tmp, "exp")) {
      b = pop(); a = pop();
      r = pow(a, b);
    }
    else if(strcmp(tmp, "sin")==0)
      r = sin(pop());
    else if(strcmp(tmp, "cos")==0)
      r = cos(pop());
    else if(strcmp(tmp, "tan")==0)
      r = tan(pop());
    else if(strcmp(tmp, "sqrt")==0)
      r = sqrt(pop());
    else if(strcmp(tmp, "log")==0)
      r = log(pop());
    else if(strcmp(tmp, "log10")==0)
      r = log10(pop());
    else if(strcmp(tmp, "pi")==0)
      r = M_PI;
    else if(strcmp(tmp, "e")==0)
      r = M_E;
    else
      r = atof(tmp);
    push(r);
    i+=c;
  }
  sprintf(scheme, "%.5Lf", pop());
  return scheme;
}

int getWord(char* dst, const char* str, int limit) {
    int i, j, len = strlen(str);
    for(i=0; i<len && isspace(str[i]); i++);
    for(j=0; j<limit && (j+i)<len && !isspace(str[i+j]); j++)
      dst[j]=str[i+j];
    dst[j]='\0';
    return i+j;
}

int isOperation(char *s) {
  int i;
  for (i = 0; i < OP_NUM; i++) {
    if(!strcmp(s,  op[i]))
      return TRUE;
  }
  return FALSE;
}

int isNumerics(char *s) {
  for (; *s != '\0'; s++) {
    if((!isdigit(*s)) && (*s != '.'))
      return FALSE;
  }
  return TRUE;
}
