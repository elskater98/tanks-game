FROM ubuntu:18.04

#RUN useradd -ms /bin/bash user

RUN apt-get update && apt-get -y install sudo

# username: user
# password: user
RUN useradd -m user && echo "user:user" | chpasswd && adduser user sudo

RUN apt install -y pcmanfm featherpad xterm
#nautilus
#lxtask

RUN apt-get install build-essential -y
RUN apt install mesa-common-dev -y
RUN apt install libglu1-mesa-dev freeglut3-dev -y
RUN apt-get install libjpeg-dev -y
#RUN apt-get install -qqy x11-apps

USER user
WORKDIR /home/user

# binding env display with host port 0.0
ENV DISPLAY=host.docker.internal:0.0

CMD ["/bin/bash"]

# you will need some kind of xserver running (vcxsrv)

# docker run --rm -it -v (local):/home/user/ (image-name)