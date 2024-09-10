#!/bin/sh

# Проверка наличия аргумента
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <executable>"
    exit 1
fi

# Имя исполняемого файла
EXECUTABLE="$1"

# Получаем директорию, в которой находится исполняемый файл
DIR="$(dirname "$EXECUTABLE")"

# Выполнение команды и запись результата в benchmark.csv в той же директории
"$EXECUTABLE" --benchmark_format=csv > "$DIR/benchmark.csv"
