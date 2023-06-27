FROM ubuntu:20.04

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential protobuf-c-compiler libprotobuf-c-dev git cmake && \
    rm -rf /var/lib/apt/lists/*

# clone repo
RUN git clone https://github.com/tugayozel/gNB-e2sm-emu.git /gNB-e2sm-emu
WORKDIR /gNB-e2sm-emu

# checkout mrn-base
RUN git checkout mrn-base

# synch submodules
RUN chmod +x submodule-sync.sh
RUN ./submodule-sync.sh

# build the emulator
RUN chmod +x build.sh
RUN ./build.sh

ENTRYPOINT ["/bin/bash"]