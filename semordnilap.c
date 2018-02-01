#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libsemordnilap.h"

int calculate_exit_code(const int word_check, const int drow_check) {
  int exit_code = 0;
  if (word_check < 0)
    exit_code |= 1;
  if (word_check > 0)
    exit_code |= 8;
  if (drow_check < 0)
    exit_code |= 1;
  if (drow_check > 0)
    exit_code |= 4;
  return exit_code;
}

void printfWordAndResult(const char *const word, struct Result result) {
  printf("%s%s -> %s%s\n", result.word_check == 0 ? "" : "*", word,
         result.drow_check == 0 ? "" : "*", result.drow);
}

int main(int argc, char **argv) {
  const char *const word = argv[1];
  struct Result result = calculateResult(word);
  const int exit_code =
      calculate_exit_code(result.word_check, result.drow_check);
  (void)argc;
  printfWordAndResult(word, result);
  exit(exit_code);
}
