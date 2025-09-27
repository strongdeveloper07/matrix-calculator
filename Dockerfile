FROM gcc:12.2.0

# Установка необходимых инструментов
RUN apt-get update && apt-get install -y \
    doxygen \
    graphviz \
    make \
    && rm -rf /var/lib/apt/lists/*

# Создаем рабочую директорию в контейнере
WORKDIR /app

# Копируем ТОЛЬКО исходные файлы (не бинарники)
COPY src/ ./src/
COPY Makefile ./
COPY Doxyfile ./

# Собираем приложение ВНУТРИ контейнера
RUN make all

# Генерируем документацию
RUN doxygen Doxyfile

# Команда по умолчанию при запуске контейнера - запуск тестов
CMD ["./test_app"]