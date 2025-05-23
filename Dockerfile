FROM gcc:12.2.0

# Устанавливаем русскую локаль
RUN apt-get update && apt-get install -y locales && \
    sed -i -e 's/# ru_RU.UTF-8 UTF-8/ru_RU.UTF-8 UTF-8/' /etc/locale.gen && \
    dpkg-reconfigure --frontend=noninteractive locales && \
    update-locale LANG=ru_RU.UTF-8

# Устанавливаем переменные окружения для локали
ENV LANG=ru_RU.UTF-8
ENV LANGUAGE=ru_RU:ru
ENV LC_ALL=ru_RU.UTF-8

# Создаем рабочую директорию
WORKDIR /app

# Копируем исходный код в контейнер
COPY src/main.cpp .

# Компилируем программу
RUN g++ -o guess_number main.cpp

# Команда для запуска программы при старте контейнера
CMD ["./guess_number"]