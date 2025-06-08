FROM ubuntu:latest
RUN apt-get update && apt-get install -y libstdc++6
RUN apt-get install -y libboost-all-dev
COPY ./gateway /apps
WORKDIR /apps
CMD ["./httpgateway"]

