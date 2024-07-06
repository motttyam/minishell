#bin/bash

assert()
{
    # 引数 $1 をダブルクォートで囲んで表示
    # memo: %-30s は文字列を左寄せ30文字幅で表示するフォーマット
    printf '%-30s:' "\"$1\""

    # bashの出力をcmpに保存
    # -n オプションは echo 出力の最後に改行を追加しない。
    # -e オプションはエスケープシーケンスを解釈する。
    # 2>&- は標準エラー出力を閉じるための記法(エラーメッセージを無視)
    echo -n -e "$1" | bash > cmp 2>&-

    # 直前に実行したコマンド（bash）の終了ステータスを expected 変数に代入
    expected=$? 

    echo -n -e "$1" | ./../minishell >out 2>&-
    actual=$?

    # >/dev/null は、コマンドの出力を破棄するためのリダイレクト
    # /dev/null は「ブラックホール」とも呼ばれ、そこに送られたデータはすべて消えてしまいます。
    diff cmp out >/dev/null && echo -n 'diff OK' || echo -n 'diff NG'

    # まだ使わなさそうだから一旦封印
    # if ["$actual" = "$expected"]; then
    #     echo -n ' status OK'
    # else
    #     echo -n "status NG, expected $expected but got $actual"
    # fi
    echo
}

#Empty line(EOF)
assert ''