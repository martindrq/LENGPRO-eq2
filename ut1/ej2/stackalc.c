// Compile with `gcc stackalc01.c -o stackalc01.exe`
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_INPUT 1024
#define MAX_CODE 30
#define MAX_STACK 100
#define VARIABLES_COUNT 5

// May be required or imported.
char *strsep(char **stringp, const char *delim)
{
  char *rv = *stringp;
  if (rv)
  {
    *stringp += strcspn(*stringp, delim);
    if (**stringp)
      *(*stringp)++ = '\0';
    else
      *stringp = 0;
  }
  return rv;
}

void eval(char *code[], int *pos, double stack[], int *top, double variables[])
{
  char *instr = code[*pos];

  //Arithmetic
  if (strcmp("ADD", instr) == 0)
  {
    stack[(*top) - 1] = stack[(*top) - 1] + stack[*top];
    (*top)--;
  }
  else if (strcmp("SUB", instr) == 0)
  {
    stack[(*top) - 1] = stack[(*top) - 1] - stack[*top];
    (*top)--;
  }
  else if (strcmp("MULT", instr) == 0)
  {
    stack[(*top) - 1] = stack[(*top) - 1] * stack[*top];
    (*top)--;
  }
  else if (strcmp("DIV", instr) == 0)
  {
    stack[(*top) - 1] = stack[(*top) - 1] / stack[*top];
    (*top)--;

    //Logic
  }
  else if (strcmp("EQ", instr) == 0)
  {
    stack[(*top) - 1] = stack[(*top) - 1] == stack[*top];
    (*top)--;
  }
  else if (strcmp("DIFF", instr) == 0)
  {
    stack[(*top) - 1] = stack[(*top) - 1] != stack[*top];
    (*top)--;
  }
  else if (strcmp("AND", instr) == 0)
  {
    stack[(*top) - 1] = stack[(*top) - 1] && stack[*top];
    (*top)--;
  }
  else if (strcmp("OR", instr) == 0)
  {
    stack[(*top) - 1] = stack[(*top) - 1] || stack[*top];
    (*top)--;
  }
  else if (strcmp("NOT", instr) == 0)
  {
    stack[(*top)] = !stack[*top];
  }

  //Comparable
  else if (strcmp("GT", instr) == 0)
  {
    stack[(*top) - 1] = stack[(*top) - 1] > stack[*top];
    (*top)--;
  }
  else if (strcmp("GTE", instr) == 0)
  {
    stack[(*top) - 1] = stack[(*top) - 1] >= stack[*top];
    (*top)--;
  }
  else if (strcmp("LT", instr) == 0)
  {
    stack[(*top) - 1] = stack[(*top) - 1] < stack[*top];
    (*top)--;
  }
  else if (strcmp("LTE", instr) == 0)
  {
    stack[(*top) - 1] = stack[(*top) - 1] <= stack[*top];
  }

  //Variables
  else if (strncmp("GET:", instr, 4) == 0)
  {
    if (isdigit(instr[4]) != 0)
    {
      int num = atoi(&(instr[4]));
      (*top)++;
      stack[*top] = variables[num];
    }
  }
  else if (strncmp("SET:", instr, 4) == 0)
  {
    if (isdigit(instr[4]) != 0)
    {
      int num = atoi(&(instr[4]));
      variables[num] = stack[*top];
      (*top)--;
    }
  }

  //Stack ops
  else if (strcmp("DUP", instr) == 0)
  {
    double value = stack[*top];
    (*top)++;
    stack[*top] = value;
  }
  else if (strcmp("POP", instr) == 0)
  {
    (*top)--;
  }

  else
  {
    char numeral[strlen(instr)];
    strcpy(numeral, instr);
    float value;
    sscanf(numeral, "%f", &value);
    (*top)++;
    stack[*top] = value;
  }
}

void printStack(double stack[], int top, double variables[])
{
  for (int i = 0; i <= top; i++)
  {
    printf("%g ", stack[i]);
  }
  printf("| 0=%g 1=%g 2=%g 3=%g 4=%g", variables[0], variables[1], variables[2], variables[3], variables[4]);
  printf("\n");
}

void evalCode(char *code[], int codeLength, double stack[], int *top, double variables[])
{
  int pos = 0;
  for (int pos = 0; pos < codeLength; pos++)
  {
    eval(code, &pos, stack, top, variables);
  }
  printStack(stack, *top, variables);
}

int parseLine(char buffer[], char *code[])
{
  char *string, *found;
  int codeLength = 0;
  string = strdup(buffer);
  while ((found = strsep(&string, " ")) != NULL)
  {
    code[codeLength] = found;
    codeLength++;
  }
  return codeLength;
}

int main()
{
  char *token;
  char buffer[MAX_INPUT];
  char *code[MAX_CODE];
  int codeLength = 0;
  double stack[MAX_STACK];
  double variables[VARIABLES_COUNT];
  int top = (-1);

  for (int i = 0; i <= VARIABLES_COUNT; i++)
  {
    variables[i] = NAN;
  }

  while (1)
  {
    if (fgets(buffer, MAX_INPUT, stdin) == NULL || strcmp(buffer, "\n") == 0)
    {
      break;
    }
    buffer[strcspn(buffer, "\n")] = 0; // Remove end-of-line
    codeLength = parseLine(buffer, code);
    evalCode(code, codeLength, stack, &top, variables);
  }
  return 0; // End
}
