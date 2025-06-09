FROM ubuntu:latest
RUN apt-get update && apt-get install -y libstdc++6 && apt-get install -y libboost-all-dev
COPY ./monitor /apps
WORKDIR /apps
CMD ["bash"]
CMD ["./monitor.service"]

