FROM srzzumix/googletest
RUN apt update && apt upgrade -y &&\
  apt install -y gcc libtbb-dev lcov make valgrind nginx &&\
  mkdir functions && mkdir tests 
COPY functions/* functions/
COPY tests/* tests/
COPY runner.sh .
COPY s21_matrix_oop.h .
COPY Makefile .
ENTRYPOINT sh runner.sh