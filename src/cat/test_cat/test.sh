#!/bin/bash

echo "Проверка Flags"
FILE1="test_cat/a.txt"
FILE2="test_cat/b.txt"
FILE3="test_cat/c.txt"
FILE4="test_cat/d.txt"
FILE5="test_cat/e.txt"
FLAGS=("-b" "--number-nonblank" "-e" "-E" "-n" "--number" "-s" "--squeeze-blank" "-t" "-T" "-nb" "-ebts" "-etsnb")

for FLAG in "${FLAGS[@]}"; do
    echo "Тесты вывода программ cat и оригинального cat с флагом $FLAG:"
    if diff -u <(./cat "$FLAG" "$FILE1" "$FILE2" "$FILE3" "$FILE4" "$FILE5") <(cat "$FLAG" "$FILE1" "$FILE2" "$FILE3" "$FILE4" "$FILE5") >/dev/null; then
        echo "success"
    else
        echo "failed: "
        diff -u <(./cat "$FLAG" "$FILE1" "$FILE2" "$FILE3" "$FILE4" "$FILE5") <(cat "$FLAG" "$FILE1" "$FILE2" "$FILE3" "$FILE4" "$FILE5")
    fi
done

