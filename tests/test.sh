assert() {
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
        echo "---- bash output ----"
        cat cmp_output.txt
        echo "---- minishell output ----"
        cat out_output.txt
        echo
        echo
    fi

    # まだ使わなさそうだから一旦封印
    # if ["$actual" = "$expected"]; then
    #     echo -n ' status OK'
    # else
    #     echo -n "status NG, expected $expected but got $actual"
    # fi
}

#Empty line(EOF)
assert ''
assert 'echo hello'
assert 'pwd'