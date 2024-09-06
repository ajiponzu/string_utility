#include "dict.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK 64
#define DICT_FILE_PATH "words.txt"

/// 辞書に登録された単語の個数.
/// 辞書ファイルの行数に等しい（末尾に改行がある場合を除く）
#define WORDS_COUNT 466549

/// 英単語辞書.
/// 一度読み込んだらプログラム終了時まで変更されない
static char* ewords_dictionary[WORDS_COUNT];

bool load_dictionary() {
  FILE* fp = fopen(DICT_FILE_PATH, "r");
  if (fp == NULL) {
    fprintf(stderr, "Dictionary: not found!\n");
    return false;
  }

  size_t count = 0;
  while (true) {
    ewords_dictionary[count] = malloc(CHUNK);

    if (fgets(ewords_dictionary[count], CHUNK, fp) == NULL) {
      break;
    }

    size_t length = strlen(ewords_dictionary[count]);
    ewords_dictionary[count][length-1] = '\0';

    count++;
  }

  fclose(fp);

  return true;
}

bool is_eword(char* str) {
  int left = 0;
  int right = WORDS_COUNT;

  while (left <= right) {
    int center = (left + right) / 2;

    char* ewords = ewords_dictionary[center];
    int compared = strcmp(str, ewords);
    if (compared == 0) {
      return true;
    }

    if (compared < 0) {
      right = center - 1;
    }

    if (compared > 0) {
      left = center + 1;
    }
  }

  return false;
}

void delete_dictionary() {
  for (size_t index = 0; index < WORDS_COUNT; index++) {
    free(ewords_dictionary[index]);
  }
}
