# Docker image for trogdord.
# To build: docker build --build-arg TROGDORD_VER=<trogdord version> -t crankycyclops/trogdord:<trogdord version> .

FROM ubuntu:22.04

ARG TROGDORD_VER

# Make the version argument mandatory (build will fail if it's not present)
RUN test -n "$TROGDORD_VER"

ENV TROGDORD_VER=${TROGDORD_VER}

# Pre-configure environment and install build dependencies
ENV DEBIAN_FRONTEND="noninteractive" TZ="UTC"
RUN apt-get update
RUN apt-get dist-upgrade -y
RUN apt-get install software-properties-common -y

RUN add-apt-repository ppa:crankycyclops/trogdor-pp -y

# Pin the version
RUN echo "Package: trogdord" > /etc/apt/preferences.d/trogdord.pref
RUN echo "Pin: version $TROGDORD_VER.*" >> /etc/apt/preferences.d/trogdord.pref
RUN echo "Pin-Priority: 1002" >> /etc/apt/preferences.d/trogdord.pref

RUN apt-get update
RUN apt-get install trogdord -y

# Create a non-root user to execute trogdord
RUN groupadd -r trogdord -g 999 && useradd -u 999 -r -g trogdord -d /home/trogdord -s /sbin/nologin -c "trogdord" trogdord

# Make sure volumes that get mounted here by docker-compose will be owned by trogdord
RUN mkdir -p /var/trogdord && chown trogdord:trogdord /var/trogdord && chmod u+s /var/trogdord && chmod g+s /var/trogdord
RUN mkdir -p /var/trogdord/state && chown trogdord:trogdord /var/trogdord/state && chmod u+s /var/trogdord/state && chmod g+s /var/trogdord/state

WORKDIR /

USER trogdord
ENTRYPOINT ["/usr/bin/trogdord"]
