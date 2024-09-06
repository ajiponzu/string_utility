#ifndef DICT
#define DICT

#include <stdbool.h>

/// @brief load_dictionary関数
///
/// 英単語辞書を登録する.
/// @return 辞書の登録に成功したか否か
bool load_dictionary();

/// @brief is_eword関数
///
/// 英単語辞書に存在する場合はtrue, 存在しない場合はfalseを得る
/// @param str 英単語候補
/// @return 英単語か否か
bool is_eword(char *str);

/// @brief delete_dictionary関数
///
/// 辞書を削除する
void delete_dictionary();

#endif
