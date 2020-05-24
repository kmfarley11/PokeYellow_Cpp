FROM ubuntu:18.04

# generic (dev) setup
# "Acquire" stuff necessary if running via wsl in windows 10
RUN apt-get -o Acquire::Check-Valid-Until=false -o Acquire::Check-Date=false update

ARG dev_pkgs="build-essential cmake libsdl2-dev libsdl2-image-dev wget"
ARG misc_pkgs="vim tmux"
RUN apt-get install -y $dev_pkgs $misc_pkgs

# local files
#COPY PokeYellow_Cpp /

# tasks
ENV PROJ_DIR=/PokeYellow_Cpp
#ARG build_dir=$repo_dir/build

CMD mkdir -p $PROJ_DIR 
#CMD mkdir -p $build_dir
#CMD cd $build_dir
#CMD cmake $proj_dir
#CMD make
