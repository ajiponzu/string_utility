#include "string_system.h"
#include "dict.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// 英単語辞書が初期化されているか否か
static bool is_system_initialized = false;

/// システム入力文字列に含まれる英単語数
static size_t word_count;

/// システム入力文字列中の最も頻繫に出現した文字の出現回数
static size_t max_char_count;

/// システム入力文字列中の最も頻繫に出現した文字
static char max_freq_char;

/// 逆順文字列
static char* reversed_str;

void system_initialize() {
  if (is_system_initialized) {
    return;
  }

  bool is_loaded = load_dictionary();
  if (is_loaded) {
    return;
  }

  reversed_str = malloc(1);
  if (reversed_str == NULL) {
    return;
  }

  is_system_initialized = true;
}

void system_run(const char* str) {
  if (str == NULL) {
    return;
  }

  word_count = 0;
  max_char_count = 0;

  size_t length = strlen(str);
  char* buffer = malloc(length + 1);
  reversed_str = realloc(reversed_str, length + 1);

  strncpy(buffer, str, length + 1);
  strncpy(reversed_str, str, length + 1);

  size_t ch_counter[255] = { 0 };
  char* ptr_reversed = reversed_str + length;

  const char* separtor = " ";
  char* token = strtok(buffer, separtor);
  while (true) {
    puts(token);
    if (is_eword(token)) {
      word_count++;
    }

    while (*token != '\0') {
      int ch_code = (unsigned char)(*token);
      ch_counter[ch_code]++;

      if (ch_counter[ch_code] > max_char_count) {
        max_char_count = ch_counter[ch_code];
        max_freq_char = *token;
      }

      ptr_reversed--;
      *ptr_reversed = *token;
    
      token++;
    }
    
    token = strtok(NULL, separtor);

    if (token == NULL) {
      break;
    }

    ptr_reversed--;
    *ptr_reversed = ' ';
  }

  free(buffer);
}

size_t count_words() {
  return word_count;
}

size_t max_count_of_char(char* ptr_ch) {
  *ptr_ch = max_freq_char;

  return max_char_count;
}

const char* reverse_string() {
  return reversed_str;
}

void system_shutdown() {
  free(reversed_str);
  delete_dictionary();
}