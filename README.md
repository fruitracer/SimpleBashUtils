# SimpleBashUtils

## Образовательный проект, в котором реализованы утилиты Bash: cat, grep

## Оглавление
1. [Утилита Cat](#утилита-cat)
2. [Утилита Grep](#утилита-grep)
3. [Как запустить](#как-запустить)

## Утилита Cat
Cat - утилита UNIX, выводящая последовательно указанные файлы (или устройства), таким образом, объединяя их в единый поток.

#### Имеет флаги (опции):
- `b` (`--number-nonblank`) - нумерует только непустые строки.
- `e` - отображает символы конца строки как $.
- `n` (`--number`)- нумерует все выходные строки.
- `s` (--squeeze-blank)- сжимает несколько смежных пустых строк.
- `t` - отображает табы как ^I.
- `v` - отображает непечатаемые символы так, чтобы они были видимы.

## Утилита Grep
Grep - утилита UNIX, которая находит на вводе строки, отвечающие заданному регулярному выражению, и выводит их, если вывод не отменён специальным ключом.

#### Имеет флаги (опции)
- `e` - шаблон.
- `i` - Игнорирует различия регистра.
- `v` - Инвертирует смысл поиска соответствий.
- `с` - Выводит только количество совпадающих строк.
- `l` - Выводит только совпадающие файлы.
- `n` - Предваряет каждую строку вывода номером строки из файла ввода.
- `h` - Выводит совпадающие строки, не предваряя их именами файлов.
- `s` - Подавляет сообщения об ошибках о несуществующих или нечитаемых файлах.
- `f` - Получает регулярные выражения из файла.
- `o` - Печатает только совпадающие (непустые) части совпавшей строки.

## Как запустить

* Сборка программ настроена с помощью Makefile с соответствующими целями: cat, grep.
* Чтобы собрать проект необходимо в папке `cat` или `grep` запустить команду : `make cat` / `make grep`.
* Далее для cat можно использовать команду `./cat [OPTION] [FILE]`.
* Для grep `./grep [options] template [file_name]`.
* Для запуска тестов используется команда: `make test`.
