/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
#define DICTIONARY_SIZE 6
#define TRANSFORM_INDEX_PUSH_1 1
#define TRANSFORM_INDEX_PUSH_2 2
#define TRANSFORM_INDEX_PUSH_3 3
#define A_UPPER 'A'
#define E_UPPER 'E'
#define I_UPPER 'I'
#define O_UPPER 'O'
#define U_UPPER 'U'
#define A_LOWER 'a'
#define E_LOWER 'e'
#define I_LOWER 'i'
#define O_LOWER 'o'
#define U_LOWER 'u'

void PrintMallocError();
void PrintWelcomeMessage();
void PrintWordMessage();
void PrintCharMessage();
int calc_target_word_len(char *word);
bool is_vowel_letter(char c);
void transform(char *str, char c, char *str_trns, char *source_strings[], char *target_strings[]);
void PrintTransformedWord(char *word);

/*-------------------------------------------------------------------------
  This program takes as input the length of a word, a word and a secret
  letter and converts the word into a transformed word using the provided
  secret.
 -------------------------------------------------------------------------*/
int main()
{
  char *source_strings[DICTIONARY_SIZE] = {"hebeabal", "woborld", "mabakebe", "ibit", "bebetteber", "plabacebe"};
  char *target_strings[DICTIONARY_SIZE] = {"rappao", "olam", "taaso", "oto", "tov", "makom"};
  int source_word_length = 0;
  int target_word_length = 0;
  char secret;
  PrintWelcomeMessage();
  scanf("%d", &source_word_length);
  char *source_word = malloc(source_word_length * sizeof(char));
  PrintWordMessage();
  scanf("%s", source_word);
  target_word_length = calc_target_word_len(source_word);
  char *target_word = malloc(target_word_length * sizeof(char));
  PrintCharMessage();
  scanf(" %c", &secret);
  transform(source_word, secret, target_word, source_strings, target_strings);
  PrintTransformedWord(target_word);
  free(source_word);
  free(target_word);
  return 0;
}

/*
  Function to switch transform the source word into a converted word using the provided secret letter.
  If the word matches a word from the supplied dictionary, it will be swapped with a word from the target
  dictionary.
*/
void transform(char *str, char c, char *str_trns, char *source_strings[], char *target_strings[])
{
  int i = 0;
  int j = 0;
  while (str[i])
  {
    if (is_vowel_letter(str[i]))
    {
      str_trns[j] = str[i];
      str_trns[j + TRANSFORM_INDEX_PUSH_1] = c;
      str_trns[j + TRANSFORM_INDEX_PUSH_2] = str[i];
      j += TRANSFORM_INDEX_PUSH_3;
    }
    else
    {
      str_trns[j] = str[i];
      j++;
    }
    i++;
  }
  str_trns[j] = 0;
  for (int h = 0; h < DICTIONARY_SIZE; h++)
  {
    if (!strcmp(str_trns, source_strings[h]))
    {
      strcpy(str_trns, target_strings[h]);
      return;
    }
  }
}

/*
  Function to calculate the length of the target word after conversion.
*/
int calc_target_word_len(char *word)
{
  int orig_len = (int)strlen(word);
  int count = (int)strlen(word);
  for (int i = 0; i < orig_len; i++)
  {
    if (is_vowel_letter(word[i]))
    {
      count += TRANSFORM_INDEX_PUSH_2;
    }
  }
  return count;
}

/*
  Function to check if the input letter is a vowel letter.
*/
bool is_vowel_letter(char c)
{
  switch (c)
  {
  case A_UPPER:
    return true;
    break;
  case E_UPPER:
    return true;
    break;
  case I_UPPER:
    return true;
    break;
  case O_UPPER:
    return true;
    break;
  case U_UPPER:
    return true;
    break;
  case A_LOWER:
    return true;
    break;
  case E_LOWER:
    return true;
    break;
  case I_LOWER:
    return true;
    break;
  case O_LOWER:
    return true;
    break;
  case U_LOWER:
    return true;
    break;
  default:
    return false;
    break;
  }
}

void PrintMallocError()
{
  printf("Malloc error.\n");
}

void PrintWelcomeMessage()
{
  printf("What is the length of your word?\n");
}

void PrintWordMessage()
{
  printf("Enter your word:\n");
}

void PrintCharMessage()
{
  printf("Enter your secret char:\n");
}

void PrintTransformedWord(char *word)
{
  printf("The transformed word is: %s\n", word);
}
