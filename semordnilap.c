#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<enchant.h>

void strrev(const char* const src, char* const dest)
{
    const int len = strlen(src);

      for (int i = 0; i < len; i += 1)
      {
          dest[len-i-1] = src[i];
      }

      dest[len] = '\0';
}

int spell_check(const char* const word, const char* const language) {
    EnchantBroker *enchantBroker = enchant_broker_init();
    EnchantDict *enchantDict = enchant_broker_request_dict (enchantBroker, language);
    const int check = enchant_dict_check (enchantDict, word, -1);
    return check;
}

int main(int argc, char **argv)
{
    const char* const word = argv[1]; // Should I spell check this?
          char* const drow = malloc(strlen(word) + 1);
    strrev(word, drow);
    const int check = spell_check(drow, "en");
    printf("%s -> %s\n", word, drow);
    exit(check);
}

