FROM nodered/node-red-docker
MAINTAINER Marcel mc-b Bernet <marcel.bernet@ch-open.ch>

EXPOSE 5683/udp

RUN cd /data && npm install coap-cli && npm install node-red-contrib-coap
