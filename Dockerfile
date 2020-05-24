FROM ubuntu:18.04

# generic (dev) setup
# "Acquire" stuff necessary if running via wsl in windows 10
RUN apt-get -o Acquire::Check-Valid-Until=false -o Acquire::Check-Date=false update

ARG dev_pkgs="build-essential cmake libsdl2-dev libsdl2-image-dev wget"
ARG misc_pkgs="vim tmux"
RUN apt-get install -y ${dev_pkgs} ${misc_pkgs}

# if sharing source with container
ENV PROJ_NAME=PokeYellow_Cpp
ENV MOUNT_DIR=/${PROJ_NAME}
# if separate source from container
ENV COPY_DIR=/${PROJ_NAME}_COPY

# local files
CMD mkdir -p ${COPY_DIR}
#COPY $PWD/* ${COPY_DIR}/
COPY $PWD/ ${COPY_DIR}/

# other setup tasks
CMD mkdir -p ${MOUNT_DIR}

