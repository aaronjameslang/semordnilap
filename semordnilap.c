#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <enchant.h>

char *strrev(const char *const src) {
  const int len = strlen(src);
  char *const dest = malloc(len + 1);
  int i = 0;

  for (; i < len; i += 1) {
    dest[len - i - 1] = src[i];
  }

  dest[len] = '\0';

  return dest;
}

int spell_check(const char *const word, const char *const language) {
  EnchantBroker *enchantBroker = enchant_broker_init();
  EnchantDict *enchantDict =
      enchant_broker_request_dict(enchantBroker, language);
  const int check = enchant_dict_check(enchantDict, word, -1);
  return check;
}

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

struct Result {
  const char *drow;
  int word_check;
  int drow_check;
};

struct Result calculateResult(const char *const word) {
  struct Result result;
  result.drow = strrev(word);
  result.word_check = spell_check(word, "en");
  result.drow_check = spell_check(result.drow, "en");
  return result;
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
