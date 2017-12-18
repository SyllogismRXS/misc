FROM ubuntu:16.04

MAINTAINER Kevin DeMarco

#ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && \
    apt-get install -y git sudo build-essential apt-utils aptdaemon

# Create user, allow sudo without password, point to id_rsa
RUN adduser --uid 1000 --disabled-password --gecos '' syllo && \
    adduser syllo sudo && \
    echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

USER syllo
WORKDIR /home/syllo

RUN git clone https://github.com/afrl-rq/OpenUxAS.git
WORKDIR ./OpenUxAS

RUN chmod +x ./install_prerequisites.sh
RUN bash -c "./install_prerequisites.sh"
RUN ninja -C build
