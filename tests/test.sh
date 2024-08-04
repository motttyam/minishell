#bin/bash

assert()
{
    # 引数 $1 をダブルクォートで囲んで表示
    printf '%-30s:' "\"$1\""

    # bashの出力をcmpに保存
    printf "$1\n" | bash > cmp_output.txt 2> cmp_error.txt
    expected=$?

    # minishellの出力をoutに保存
    printf "$1\n" | ./minishell > out_output.txt 2> out_error.txt
    actual=$?

    # 出力の差分を確認
    if diff cmp_output.txt out_output.txt >/dev/null; then
        printf "diff OK\n"
        echo
        echo
    else
        printf "diff NG\n"
        # エラーメッセージの内容を表示
        echo " - Output mismatch:"
        echo "---------------- bash output ----------------"
        cat cmp_output.txt
        echo "---------------- minishell output ----------------"
        cat out_output.txt
        echo
        echo
    fi

    # # まだ使わなさそうだから一旦封印
    # if ["$actual" = "$expected"]; then
    #     echo -n ' status OK'
    # else
    #     echo -n "status NG, expected $expected but got $actual"
    # fi
}

minishell ()
{
    printf '%-30s:' "\"$1\""
    printf "$1\n" | ./minishell > out_output.txt 2> out_error.txt
    actual=$?
    echo
    echo
    echo "---------------- minishell output ----------------"
    cat out_output.txt
    if [ -s out_error.txt ]; then
        echo
        echo
        echo "---- minishell error ----"
        cat out_error.txt
    else
        echo "---------------- minishell error ----------------"
        echo "No errors"
    fi
}

cmd ()
{
    command="$1"
    if [ "$MODE" = "assert" ]; then
        assert "$command"
    elif [ "$MODE" = "minishell" ]; then
        minishell "$command"
    else
        echo "Unknown mode: $MODE"
    fi
}

MODE=${1:-assert}

clear


# =====================================================================
# final tests
# =====================================================================


# =====================================================================
# Normal tests
# =====================================================================
# cmd ''
# cmd ' '
# cmd 'EOF'

# # =====================================================================
# # Command tests
# # =====================================================================
# cmd 'ls'
# cmd 'pwd'
# cmd 'whoami'
# cmd 'date'
# cmd 'uname -a'
# cmd 'echo "Hello, World!"'
# cmd 'cat /etc/hosts'

# # =====================================================================
# # Error handling tests　
# # =====================================================================
# cmd 'nonexistentcommand'
# cmd 'cat nonexistentfile'

# # =====================================================================
# # Pipe tests
# # =====================================================================
# cmd 'ls | grep "test"'  # "ls"コマンドの結果から"test"を含む行を検索
# cmd 'cat /etc/hosts | wc -l'  # /etc/hostsファイルの行数をカウント
# cmd 'echo "Hello" | tr "H" "h"'  # "Hello"の"H"を"h"に変換
# cmd 'seq 1 5 | paste -sd+ - | bc'  # 1から5までの数値を生成し、足し算して結果を表示
# cmd 'echo "HELLO world" | tr "A-Z" "a-z" | tr " " "_"'  # 大文字を小文字に変換し、スペースをアンダースコアに変換
# cmd 'ls -l | grep "^d" | wc -l'  # ディレクトリの数をカウント
# cmd 'cat /etc/passwd | cut -d ":" -f 1 | sort'  # /etc/passwdファイルのユーザー名を抽出してソート
# cmd 'ps aux | awk \'{print $1}\' | sort | uniq''  # 実行中のプロセスのユーザー名を一意に抽出
# cmd 'echo "This is a test" | cut -d " " -f 2,3 | tr " " "-"'  # 2番目と3番目の単語を抽出し、スペースをハイフンに変換
# cmd 'df -h | grep "/dev/sd" | awk \'{print $5}\'''  # ディスク使用量のパーセンテージを表示
# cmd 'ls -l | awk \'{print $9, $5}\' | column -t''  # ファイル名とサイズを表示
# cmd 'head -n 5 /etc/passwd | tail -n 1 | cut -d ":" -f 7'  # /etc/passwdファイルの5行目のシェルを表示

# # テスト項目として除外
# cmd 'echo "one two three four five" | tr " " "\n" | sort'  # 単語をソート
# cmd 'find . -type f | xargs wc -l | grep total'  # 現在のディレクトリ以下のファイルの行数を合計


# # =====================================================================
# # # Input_Redirect tests:　<
# # =====================================================================
# ## Basic Test ###
# cmd 'cat < README.md'                  # ファイルの内容を読み込み
# cmd 'cat < ls'                         # ファイルが存在しない場合のエラー
# cmd 'sort < README.md'                 # ファイルをソート
# cmd 'wc -l < README.md'                # ファイルの行数を数える
# cmd 'grep "main" < srcs/minishell.c'   # 特定の文字列を含む行を検索
# cmd 'head -n 5 < README.md'            # 最初の5行を表示
# cmd 'tail -n 5 < README.md'            # 最後の5行を表示
# cmd 'tr "a-z" "A-Z" < README.md'       # 小文字を大文字に変換
# cmd 'cut -d" " -f1 < README.md'        # スペースで区切られた最初のフィールドを抽出
# cmd 'cat < /dev/null'                  # 空のデバイスファイルを読み込み
# cmd 'cat < /etc/passwd'                # システムファイルの内容を読み込み

# ## Additional Test ###
# echo -e "apple\nbanana\ncherry" > fruits.txt
# cmd 'sort < fruits.txt'                # テキストファイルをソート
# cmd 'uniq < fruits.txt'                # 重複行を削除
# cmd 'grep "banana" < fruits.txt'       # 特定の行を検索
# cmd 'sed "s/apple/APPLE/" < fruits.txt' # パターン置換

# # テスト用の一時ファイルを削除
# rm -f fruits.txt

# # bashとexecveの仕様が異なるため、NGになるかも
# cmd 'awk "{print $1}" < README.md'     # 各行の最初のフィールドを抽出

# # =====================================================================
# # Output_Redirect tests: >　
# # =====================================================================
# cmd 'echo "test" > tmpfile1'           # 新しいファイルに書き込み
# cmd 'echo "another line" > tmpfile1'   # 上書き
# cmd 'cat tmpfile1'                     # 内容を表示
# cmd 'ls > tmpfile2'                    # ディレクトリリストをファイルに書き込み
# cmd 'wc -l > tmpfile3 < README.md'     # ファイルの行数を別のファイルに書き込み
# cmd 'date > tmpfile4'                  # 現在の日付と時刻をファイルに書き込み
# cmd 'uname -a > tmpfile5'              # システム情報をファイルに書き込み
# cmd 'ps aux > tmpfile6'                # プロセス情報をファイルに書き込み
# cmd 'df -h > tmpfile7'                 # ディスク使用量をファイルに書き込み
# cmd 'who > tmpfile8'                   # ログインユーザー情報をファイルに書き込み
# cmd 'echo "Hello World" > tmpfile9'    # テキストをファイルに書き込み
# cmd 'cat /etc/passwd > tmpfile10'      # システムファイルの内容をファイルに書き込み

# # =====================================================================
# # # Redirection tests: >>
# # =====================================================================
# cmd 'echo "test" > tmpfile100'          # 新しいファイルに書き込み
# cmd 'echo "another line" >> tmpfile100' # 追記
# cmd 'cat tmpfile100'                    # 内容を表示

# # 追加のテスト項目
# cmd 'echo "Line 1" > tmpfile101'        # 新しいファイルに書き込み
# cmd 'echo "Line 2" >> tmpfile101'       # 追記
# cmd 'echo "Line 3" >> tmpfile101'       # さらに追記
# cmd 'cat tmpfile101'                    # 内容を表示

# cmd 'date >> tmpfile102'                # 現在の日付と時刻を追記
# cmd 'echo "Adding more lines" >> tmpfile102' # 文字列を追記
# cmd 'cat tmpfile102'                    # 内容を表示

# cmd 'ls -l >> tmpfile103'               # ディレクトリリストを追記
# cmd 'df -h >> tmpfile103'               # ディスク使用量を追記
# cmd 'cat tmpfile103'                    # 内容を表示

# cmd 'ps aux >> tmpfile104'              # プロセス情報を追記
# cmd 'who >> tmpfile104'                 # ログインユーザー情報を追記
# cmd 'cat tmpfile104'                    # 内容を表示

# cmd 'echo "First append test" >> tmpfile105'  # 初回の追記
# cmd 'echo "Second append test" >> tmpfile105' # 二回目の追記
# cmd 'echo "Third append test" >> tmpfile105'  # 三回目の追記
# cmd 'cat tmpfile105'                          # 内容を表示

# # # =====================================================================
# # # Redirection tests: <<
# # # =====================================================================
# cmd 'cat <<EOF > tmpfile4
# line 1
# line 2
# EOF'                                  # ヒアドキュメントを使用してファイルに書き込み
# cmd 'cat tmpfile4'                    # 内容を表示

# # =====================================================================
# # Pipe and Redirection tests: <
# # =====================================================================
# cmd 'cat < README.md | grep "one"'      # ファイルから読み込み、grepでフィルタリング
# cmd 'tr "a-z" "A-Z" < README.md | grep "ONE"'  # 小文字を大文字に変換してgrep
# cmd 'head -n 10 < README.md | tail -n 5'    # 最初の10行から最後の5行を表示
# cmd 'grep "one" < README.md | wc -l'    # 特定のパターンを含む行数をカウント
# cmd 'sed "s/old/new/g" < README.md | grep "new"'  # 文字列を置換してgrep
# cmd 'cut -d" " -f1 < README.md | sort | uniq'  # スペースで区切られた最初のフィールドを抽出してソートし、重複行を削除

# # =====================================================================
# # Pipe and Redirection tests: >
# # =====================================================================
# cmd 'cat README.md > tmpfile1000 | ls'
# cmd 'cat README.md > tmpfile1000 | pwd | cat -e'
# cmd 'echo "test line" | cat > tmpfile1'      # パイプの出力をファイルに書き込み
# cmd 'ls -l | grep "README" > tmpfile2'       # ディレクトリリストのフィルタリング結果をファイルに書き込み
# cmd 'date | awk "{print \$1}" > tmpfile3'    # 日付の最初のフィールドをファイルに書き込み
# cmd 'uname -a | cut -d" " -f1 > tmpfile4'    # システム情報の最初のフィールドをファイルに書き込み
# cmd 'ps aux | head -n 5 > tmpfile5'          # プロセスリストの最初の5行をファイルに書き込み
# cmd 'df -h | grep "/dev/sda1" > tmpfile6'    # ディスク使用量情報をファイルに書き込み
# cmd 'who | sort > tmpfile7'                  # ログインユーザー情報をソートしてファイルに書き込み
# cmd 'cat /etc/passwd | awk -F: "{print \$1}" > tmpfile8'  # ユーザー名を抽出してファイルに書き込み
# cmd 'echo "Start of file" > tmpfile9'        # テキストを新規ファイルに書き込み
# cmd 'echo "Another line" > tmpfile9'         # 上書き
# cmd 'dmesg | tail -n 10 > tmpfile10'         # カーネルメッセージの最後の10行をファイルに書き込み
# cmd 'cat /etc/hosts | grep "localhost" > tmpfile12'  # /etc/hosts ファイルから localhost エントリをファイルに書き込み


# # =====================================================================
# # Pipe and Redirection tests: >>
# # =====================================================================
# cmd 'cat README.md >> tmpfile1001 | uname >>tmpfile1001 -a | ls'
# cmd 'cat README.md >> tmpfile1002 | pwd | cat -e'
# cmd 'echo "appending line" | cat >> tmpfile1'  # パイプの出力をファイルに追記
# cmd 'ls -a | grep "hidden" >> tmpfile3'        # ディレクトリリストのフィルタリング結果をファイルに追記

# # =====================================================================
# # Pipe and Redirection tests: <<
# # =====================================================================
# cmd 'cat <<EOF | grep "pattern" > tmpfile4
# line 1
# pattern line
# EOF'                                          # ヒアドキュメントから読み込み、grepでフィルタリングしてファイルに書き込み

# cmd 'cat <<EOF | sort > tmpfile5
# banana
# apple
# cherry
# EOF'                                          # ヒアドキュメントから読み込み、ソートしてファイルに書き込み

# =====================================================================
# # Built-in command tests　 未開放
# # =====================================================================
# cmd 'cd /'
# cmd 'pwd'
# cmd 'cd -'

# # =====================================================================
# # Special characters tests　 未開放
# # =====================================================================
# cmd 'echo *'
# cmd 'echo ?'
# cmd 'echo [a-z]'


# # =====================================================================
# # Corner case tests　
# # =====================================================================
# cmd 'echo ""'
# cmd 'echo -n "No newline"'
# cmd 'echo $((2+2))'
# cmd 'echo `date`'
# cmd 'echo $(date)'
# cmd 'echo ${HOME}'
# cmd 'echo $((2*3+1))'

# # =====================================================================
# # Environment variable tests  未開放
# # =====================================================================
# cmd 'export TEST_VAR="Hello"'
# cmd 'echo $TEST_VAR'
# cmd 'unset TEST_VAR'

# # =====================================================================
# # Quoting and escaping tests　 未開放
# # =====================================================================
# cmd 'echo "This is a test"'
# cmd 'echo "This is a \"test\""'
# cmd 'echo '\''This is a test'\'''
# cmd "echo 'This is a test'"


# # =====================================================================
# # Clean up
# # =====================================================================
# cmd 'rm -f tmp*'
