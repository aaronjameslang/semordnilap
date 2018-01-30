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
  if (word_check < 0) exit_code |= 1;
  if (word_check > 0) exit_code |= 8;
  if (drow_check < 0) exit_code |= 1;
  if (drow_check > 0) exit_code |= 4;
  return exit_code;
}

int main(int argc, char **argv) {
  const char *const word = argv[1];
  const char *const drow = strrev(word);
  const int word_check = spell_check(word, "en");
  const int drow_check = spell_check(drow, "en");
  const int exit_code = calculate_exit_code(word_check, drow_check);
  (void)argc;
  printf("%s -> %s\n", word, drow);
  exit(exit_code);
}
