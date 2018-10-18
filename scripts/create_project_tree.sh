#!/bin/sh


#  Create Structure of Directory for the Project               #
#  ---------------------------------------------------------   #
#  Create the folder structure for the Project                 #
#  
#  Setup:                                                      #
#     $ cd scripts/tree                                        #
#     $ chmod u+x create_project_tree.sh                       #
#     $ ln -s script/create_project_tree.sh ~/bin/project      #
#     $ echo "PATH=~/bin:\${PATH}" >> ~/.profile               #
#                                                              #
#  Usage:                                                      #
#     $ ./create_project_tree [directory] [devices] [platform] #

#####

#Devices debe ser un parametros $2 y plaform $3
DEVICES=atsam4s16c,atsam4sd32c,gr712rc,atmega328p,attiny85
PLATFORMS=gr712rc_commercial,gr712rc_ed31,atsam4s-xpro,sensor-mp-v1,arduino-mini

echo
if [ "$1" != "" ]  #if parameter exists, use as base folder
   then cd "$1"
   fi
pwd

echo
if [ "$2" != "" ]  #if parameter exists, use for devices
   then DEVICES=$2
   fi
pwd

echo
if [ "$3" != "" ]  #if parameter exists, use for devices
   then PLATFORMS=$3
   fi
pwd


eval "mkdir -p {documentation,resources,scripts}"

#Build SRC Hierarchi
eval "mkdir -p src/{mcal/{$DEVICES},platform/{$PLATFORMS},sys/start/{$DEVICES},util,os}"


#Esto podemos cambiarlo por una llamada a tree.

#basename "$PWD"

echo 
## Show the tree structure
ls -R | grep ":$" |   \
   sed -e 's/:$//' -e 's/[^-][^\/]*\//--/g' -e 's/^/   /' -e 's/-/|/'
# 1st sed: remove colons
# 2nd sed: replace higher level folder names with dashes
# 3rd sed: indent graph three spaces
# 4th sed: replace first dash with a vertical bar
if [ `ls -F -1 | grep "/" | wc -l` = 0 ]   # check if no folders
   then echo "   -> no sub-directories"
   fi
echo
exit
