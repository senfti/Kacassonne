FROM ubuntu:18.04
RUN apt-get update
RUN apt-get install -y wget g++-8 gcc libzmq3-dev libwxgtk3.0-gtk3-dev libwxbase3.0-dev make
RUN ln -s /usr/bin/g++-8 /usr/bin/g++
RUN wget https://github.com/Kitware/CMake/releases/download/v3.19.1/cmake-3.19.1-Linux-x86_64.sh
RUN chmod 777 cmake-3.19.1-Linux-x86_64.sh
RUN ./cmake-3.19.1-Linux-x86_64.sh --skip-license
ADD build.sh /
CMD ["make", "Kacassonne"]