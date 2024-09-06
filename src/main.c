#include "string_system.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK 128

/// @brief input_string関数
///
/// 標準入力から文字列をメモリ資源のある限り読みこむ.
/// 読み込んだ文字列の長さを得る.
/// 何も入力されなかった, またはエラーが起きた際は0を得る
/// @param length 読み込んだ文字列の長さ
/// @return 入力文字列
static char* input_string(size_t* length) {
  char* input = malloc(CHUNK);
  if (input == NULL) {
    fprintf(stderr, "Error input_string: memory allocation\n");
    return NULL;
  }

  char* realloc_buffer;
  size_t size = CHUNK;
  *length = 0;

  while (fgets(input + *length, CHUNK, stdin) != NULL) {
    *length = strlen(input);
    if (input[*length - 1] == '\n') {
      input[*length - 1] = '\0';
      (*length)--;
      return input;
    }

    size += CHUNK;
    realloc_buffer = realloc(input, size);
    if (realloc_buffer == NULL) {
      free(input);
      return NULL;
    }
    input = realloc_buffer;
  }

  if (*length == 0) {
    free(input);
    return NULL;
  }

  return input;
}

int main(void) {
  fprintf(stdout, "input> ");

  size_t length;
  char* str = input_string(&length);
  if (length == 0) {
    fprintf(stderr, "Not input\n");
    return EXIT_FAILURE;
  }

  system_initialize();
  system_run(str);

  size_t word_count = count_words();

  char max_freq_char = 0;
  size_t max_char_count = max_count_of_char(&max_freq_char);

  const char* reversed = reverse_string();

  fprintf(stdout, "** String Info **\nlength: %zu\nwords: %zu\n", length, word_count);
  fprintf(stdout, "max_freq: %c, count: %zu\n", max_freq_char, max_char_count);
  fprintf(stdout, "reversed: %s\n", reversed);

  system_shutdown();
  free(str);

  return EXIT_SUCCESS;
}