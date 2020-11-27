FROM gcc:9.3

RUN apt -y update && apt -y upgrade
RUN apt install -y cmake

WORKDIR /usr/src/app
COPY . .

RUN mkdir build
WORKDIR ./build
RUN cmake ..
RUN make

CMD ["/bin/bash"]
