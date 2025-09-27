# Базовый образ с компилятором C++
FROM gcc:12.2.0

# Установка необходимых инструментов
RUN apt-get update && apt-get install -y \
    doxygen \
    graphviz \
    make \
    && rm -rf /var/lib/apt/lists/*

# Создаем рабочую директорию в контейнере
WORKDIR /app

# Копируем ВСЕ файлы из текущей папки в контейнер
COPY . .

# Собираем приложение с помощью Makefile
RUN make all

# Генерируем документацию
RUN doxygen Doxyfile

# Команда по умолчанию при запуске контейнера - запуск тестов
CMD ["./test_app"]