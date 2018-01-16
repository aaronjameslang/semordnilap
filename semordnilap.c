#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <enchant.h>

const char *const strrev(const char *const src) {
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

int main(int argc, char **argv) {
  /* TODO Spell check word? */
  const char *const word = argv[1];
  const char *const drow = strrev(word);
  const int check = spell_check(drow, "en");
  printf("%s -> %s\n", word, drow);
  exit(check);
}
