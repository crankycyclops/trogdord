FROM ubuntu:22.04

ENV DEBIAN_FRONTEND="noninteractive" TZ="America/Los_Angeles"
RUN apt-get update && apt-get -y install sudo bash wget git g++ cmake libasio-dev sqlite3 libsqlite3-dev rapidjson-dev libhiredis-dev libxml2 libxml2-dev liblua5.3 liblua5.3-dev libinih1 libinih-dev redis-server software-properties-common
RUN cd /usr/include && wget https://raw.githubusercontent.com/doctest/doctest/v2.4.11/doctest/doctest.h

# Install the latest stable version of the core library
RUN add-apt-repository ppa:crankycyclops/trogdor-pp -y
RUN apt-get install libtrogdor libtrogdor-dev

WORKDIR /
COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

# test_trogdord needs to run as a non-root user because it relies on file
# permissions that don't apply to root.
RUN groupadd -r app && useradd -r -g app -d /home/app -s /sbin/nologin -c "Docker image user" app

ENTRYPOINT ["/entrypoint.sh"]