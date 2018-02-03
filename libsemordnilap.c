#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libsemordnilap.h"
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

struct Result calculateResult(const char *const word) {
  struct Result result;
  result.drow = strrev(word);
  result.word_check = spell_check(word, "en");
  result.drow_check = spell_check(result.drow, "en");
  return result;
}
