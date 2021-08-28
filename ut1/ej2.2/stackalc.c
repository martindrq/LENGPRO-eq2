// Compile with `gcc stackalc01.c -o stackalc01.exe`
#include <stdio.h>
#include <string.h>
#define MAX_INPUT 1024
#define MAX_CODE 30
#define MAX_STACK 100


// May be required or imported.
char *strsep(char **stringp, const char *delim) {
    char *rv = *stringp;
    if (rv) {
        *stringp += strcspn(*stringp, delim);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = 0; }
    return rv;
}

void eval(char *code[], int *pos, double stack[], int *top) {
  char *instr = code[*pos];
	if (strcmp("ADD", instr) == 0) {
		stack[(*top) - 1] = stack[(*top) - 1] + stack[*top];
		(*top)--;
	} else if (strcmp("SUB", instr) == 0) {
		stack[(*top) - 1] = stack[(*top) - 1] - stack[*top];
		(*top)--;
	} else if (strcmp("MULT", instr) == 0) {
		stack[(*top) - 1] = stack[(*top) - 1] * stack[*top];
		(*top)--;
	} else if (strcmp("DIV", instr) == 0) {
		stack[(*top) - 1] = stack[(*top) - 1] / stack[*top];
		(*top)--;
	}  else if (strcmp("EQ", instr) == 0) {
		stack[(*top) - 1] = stack[(*top) - 1] == stack[*top];
		(*top)--;
	} else if (strcmp("DIFF", instr) == 0) {
		stack[(*top) - 1] = stack[(*top) - 1] != stack[*top];
		(*top)--;
	} else if (strcmp("AND", instr) == 0) {
		stack[(*top) - 1] = stack[(*top) - 1] && stack[*top];
		(*top)--;
	} else if (strcmp("OR", instr) == 0) {
		stack[(*top) - 1] = stack[(*top) - 1] || stack[*top];
		(*top)--;
	} else if (strcmp("GT", instr) == 0) {
		stack[(*top) - 1] = stack[(*top) - 1] > stack[*top];
		(*top)--;
	} else if (strcmp("GTE", instr) == 0) {
		stack[(*top) - 1] = stack[(*top) - 1] >= stack[*top];
		(*top)--;
	} else if (strcmp("LT", instr) == 0) {
		stack[(*top) - 1] = stack[(*top) - 1] < stack[*top];
		(*top)--;
	} else if (strcmp("LTE", instr) == 0) {
		stack[(*top) - 1] = stack[(*top) - 1] <= stack[*top];
		(*top)--;
	} else if (strcmp("NOT", instr) == 0) {
		stack[(*top)] = !stack[*top];
	}
  
  else {
    char numeral[strlen(instr)];
	  strcpy(numeral, instr);
    float value;
		sscanf(numeral, "%f", &value);
    (*top)++;
    stack[*top] = value;
	}
}

void printStack(double stack[], int top) {
    for (int i = 0; i <= top; i++) {
        printf("%g ", stack[i]);
    }
    printf("\n");
}

void evalCode(char *code[], int codeLength, double stack[], int *top) {
  int pos = 0;
  for (int pos = 0; pos < codeLength; pos++) {
    eval(code, &pos, stack, top);
  }
  printStack(stack, *top);
}

int parseLine(char buffer[], char *code[]) {
  char *string, *found;
  int codeLength = 0;
  string = strdup(buffer);
  while ((found = strsep(&string, " ")) != NULL) {
    code[codeLength] = found;
    codeLength++;
  }
  return codeLength;
}

int main() {
  char *token;
  char buffer[MAX_INPUT];
  char *code[MAX_CODE];
  int codeLength = 0;
  double stack[MAX_STACK];
  int top = (-1);
	while (1) {
    if (fgets(buffer, MAX_INPUT, stdin) == NULL || strcmp(buffer, "\n") == 0) {
      break;
    }
    buffer[strcspn(buffer, "\n")] = 0; // Remove end-of-line
    codeLength = parseLine(buffer, code);
    evalCode(code, codeLength, stack, &top);
	}
  return 0; // End
}
