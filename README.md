## ADD TO BASHRC
```bash
export CURRENT_CONTAINER="CONTAINER_NAME_HERE"
export BUILD_NAME="BUILD_NAME_HERE/VERSION"

alias save='sudo docker commit $CURRENT_CONTAINER $BUILD_NAME'  #Save changes to image
alias enter='sudo docker exec -it $CURRENT_CONTAINER bash'    #Enter containers bash
alias run='sudo docker run -it -d --dns 10.0.0.1 --net=host --name $CURRENT_CONTAINER --privileged $BUILD_NAME'   # Open the container with network access and file access
alias close='sudo docker kill $CURRENT_CONTAINER && sudo docker container prune -f'   # Close the container and prune it
alias prune='sudo docker container prune -f'          # Faster prune command
alias build='sudo docker build -t $BUILD_NAME .'      # for building
```
***********************************************************************************
## TO USE THIS DOCKER
In the first terminal RUN the following commands
```bash
build
enter
cd pipe/
cb
ros2 run ros-to-ros2-pipe ros-to-ros2-pipe
```
In a separate terminal, RUN:
```bash
enter
cd multisense_ws
b
```
**Before you run this, connect the multisense head**
> it should show up as an ethernet connection in ifconfig
> To give it a proper ip address, the final line of the dockerfile should have added the instruction to the bashrc
> So, just source your ~/.bashrc 
```bash
source ~/.bashrc
```
> then run the following command
```bash
RUN roslaunch multisense_bringup multisense.launch
```
if the local machine is also put on the same ROS_DOMAIN_ID=38, the multisense should now show up in rviz2
```