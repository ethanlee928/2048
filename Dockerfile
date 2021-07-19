FROM gcc:4.9
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp

RUN apt-get update && apt-get install -y software-properties-common wget

RUN apt-get install vim screen -y

