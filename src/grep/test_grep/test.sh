#!/bin/bash

echo "Проверка Flags"
FILE="test_grep/t1.txt"
FILE2="test_grep/test.txt"
FILE3="test_grep/nofile.txt"
PATTERN_FILE="test_grep/patterns.reg"
PATTERN="fo"

FLAGS=("-v" "-i" "-e" "-c" "-l" "-n" "-h" "-s" "-o" "-vi" "-vc" "-vl" "-vn" "-vh" "-vs" "-vo" "-ic" "-il" "-in" "-ih" "-is" "-io" "-cl" "-cn" "-ch" "-cs" "-co" "-ln" "-lh" "-lh" "-ls" "-lo" "-nh" "-ns" "-no" "-hs" "-ho" "-so")


    echo "Тесты вывода программ grep и оригинального grep без флагов:"
    if diff -u <(./grep  $PATTERN "$FILE" "$FILE2" "$FILE3") <(grep $PATTERN "$FILE" "$FILE2" "$FILE3") >/dev/null; then
        echo "success"
    else
        echo "failed: "
        diff -u <(./grep  $PATTERN "$FILE" "$FILE2" "$FILE3") <(grep $PATTERN "$FILE" "$FILE2" "$FILE3")
    fi


for FLAG in "${FLAGS[@]}"; do
    echo "Тесты вывода программ grep и оригинального grep с флагом $FLAG:"
    if diff -u <(./grep "$FLAG" $PATTERN "$FILE" "$FILE2") <(grep "$FLAG" $PATTERN "$FILE" "$FILE2") >/dev/null; then
        echo "success"
    else
        echo "failed: "
        diff -u <(./grep "$FLAG" $PATTERN "$FILE" "$FILE2") <(grep "$FLAG" $PATTERN "$FILE" "$FILE2")
    fi
done


EFLAGS=("-ve" "-ie" "-ce" "-le" "-ne" "-he" "-se" "-oe")
for EFLAG in "${EFLAGS[@]}"; do
    echo "Тесты вывода программ grep и оригинального grep с флагом $EFLAG:"
    if diff -u <(./grep "$EFLAG" $PATTERN "$FILE" "$FILE2") <(grep "$EFLAG" $PATTERN "$FILE" "$FILE2") >/dev/null; then
        echo "success"
    else
        echo "failed: "
        diff -u <(./grep "$EFLAG" $PATTERN "$FILE" "$FILE2") <(grep "$EFLAG" $PATTERN "$FILE" "$FILE2")
    fi
done

FFLAGS=("-vf" "-if" "-cf" "-lf" "-nf" "-hf" "-sf" "-of")
for FFLAG in "${FFLAGS[@]}"; do
    echo "Тесты вывода программ grep и оригинального grep с флагом $FFLAG:"
    if diff -u <(./grep "$FFLAG" $PATTERN_FILE "$FILE" "$FILE2") <(grep "$FFLAG" $PATTERN_FILE "$FILE" "$FILE2") >/dev/null; then
        echo "success"
    else
        echo "failed: "
        diff -u <(./grep "$FFLAG" $PATTERN_FILE "$FILE" "$FILE2") <(grep "$FFLAG" $PATTERN_FILE "$FILE" "$FILE2")
    fi
done