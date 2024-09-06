#ifndef STRING_SYSTEM
#define STRING_SYSTEM

#include <stdbool.h>
#include <stddef.h>

/// @brief system_initialize関数
///
/// システムを初期化する.
/// この関数が呼ばれていない場合, 他の関数は即時終了する
void system_initialize();

/// @brief system_run関数
///
/// 文字列処理システムを起動する.
/// 効率のため, システム入力文字列の探索等は全て行う.
/// 一方で, 必要な結果を当ヘッダの使用者が選べるように, 別の関数に結果取得機能を実装した
/// @param str システム入力文字列
void system_run(const char* str);

/// @brief count_words関数
/// @return システム入力文字列中の英単語の数
size_t count_words();

/// @brief max_count_of_char関数
///
/// システム入力文字列中に最も頻繁に出現した文字と回数を得る
/// @param ptr_ch 最も頻繁に出現した文字を指すポインタ
/// @return 出現回数
size_t max_count_of_char(char* ptr_ch);

/// @brief reverse_string関数
///
/// 入力文字列の逆順文字列を取得する
/// @return 逆順文字列 
const char* reverse_string();

/// @brief system_shutdown関数
/// 
/// システムを終了する.
/// 使用していたメモリ等はきちんと解放する
void system_shutdown();

#endif