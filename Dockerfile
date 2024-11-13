FROM ros:noetic

ENV DEBIAN_FRONTEND=noninteractive
ENV PATH_TO_SOURCE=home/multisense_ws
SHELL ["/bin/bash", "-c"]

# install ros package
RUN apt-get update
RUN apt-get install -y ros-noetic-desktop-full
RUN apt-get install -y git python3-rosinstall build-essential cmake
RUN rm -rf /var/lib/apt/lists/*
RUN echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
RUN source ~/.bashrc
RUN apt-get update
RUN rosdep update

RUN mkdir -p ${PATH_TO_SOURCE}/src
WORKDIR ${PATH_TO_SOURCE}/src
RUN apt-get install -y ros-noetic-catkin python3-catkin-tools
RUN git clone --recurse-submodules https://github.com/carnegierobotics/multisense_ros.git multisense
WORKDIR /
RUN rosdep install --from-paths ${PATH_TO_SOURCE}/src --ignore-src -r -y

RUN apt-get install net-tools
RUN apt-get install -y vim

WORKDIR ${PATH_TO_SOURCE}
RUN source /opt/ros/noetic/setup.bash \
    && catkin_make \
    && source devel/setup.bash
RUN apt-get install -y iproute2 iputils-ping emacs
RUN apt-get update

WORKDIR /
RUN apt-get install -y software-properties-common &&\
    add-apt-repository universe && apt update && sudo apt install -y curl &&\
    curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg &&\
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
RUN apt-get update && apt-get install -y ros-galactic-desktop
RUN echo "source /opt/ros/galactic/setup.bash" >> ~/.bashrc

# RUN echo "ifconfig enx48225455e16f 10.66.171.20 netmask 255.255.255.0 broadcast 10.66.171.255 mtu 7200" >> ~/.bashrc # MUST DO FOR BRINGUP 10.66.171.20
RUN apt-get install -y python3-colcon-common-extensions
WORKDIR /home
#RUN echo "    PasswordAuthentication yes" >> /etc/ssh/ssh_config
RUN echo "alias cb='source /opt/ros/galactic/setup.bash && source /opt/ros/noetic/setup.bash && colcon build && . install/setup.bash'" >> ~/.bashrc
RUN echo "alias  b='source /opt/ros/galactic/setup.bash && source /opt/ros/noetic/setup.bash && catkin_make && source devel/setup.bash'" >> ~/.bashrc
RUN echo "alias c='clear'" >> ~/.bashrc
RUN echo "export ROS_DOMAIN_ID=38" >> ~/.bashrc

WORKDIR /home
RUN git clone https://github.com/MacksCohn/Docker_for_Multisense.git
# # launch ros package
# CMD ["ros2", "launch", "demo_nodes_cpp", "talker_listener_launch.py"]
#
# ADD TO BASHRC
# export CURRENT_CONTAINER="CONTAINER_NAME_HERE"
# export BUILD_NAME="build/test:latest"
# #To build with docker, run the following to set a name (in the directory with the Dockerfile) sudo docker build -t BUILD_NAME_HERE:VERSION_HERE creates an image, one time use if Dockerfile is unchanged
# #Save changes to imag
# alias save='sudo docker commit $CURRENT_CONTAINER $BUILD_NAME'
# #Enter containers bash
# alias enter='sudo docker exec -it $CURRENT_CONTAINER bash'
# #Open the container with network access and file access
# alias run='sudo docker run -it -d --dns 10.0.0.1 --net=host --name $CURRENT_CONTAINER --privileged $BUILD_NAME'
# #Close the container and prune it
# alias close='sudo docker kill $CURRENT_CONTAINER && sudo docker container prune -f'
# #Faster prune command
# alias prune='sudo docker container prune -f'
# to build, sudo docker build -t name/version .
# alias build='sudo docker build -t $BUILD_NAME .'
