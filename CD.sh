#!/bin/bash

menu_choiece=""
current_cd=""
title_file="title.cdb"
tracks_file="tracks.cdb"
temp_file=./tmp/cdb.$$
trap 'rm -f $temp_file' EXIT

get_return() {
   echo -e "Press retrun \c"
   read x
   return 0
}
get_confirm() {
   echo -e "Are you sure? \c"
   while true
   do
      read x
      case "$x" in
         y | yes | Y | Yes | YES ) return 0;;
         n | no | N | No | NO )
            echo
            echo "Cancelled"
            return 1;;
           *) echo "Please enter yes or no";;
      esac
   done
}

set_menu_choice() {
  clear
  echo "Options :-"
  echo 
  echo "  a) Add new CD"
  echo "  f) Find CD"
  echo "  c) Count the CDs and tracks in the catalog"
  if [ "$cdcatnum" != "" ]; then
    echo "  l) List tracks on $cdtile"
    echo "  r) Remove $cdtile"
    echo "  u) Update track information for $cdtile"
  fi
  echo "  q) Quit"
  echo
  echo -e "Please enter choice then press return \c"
  read menu_choice
  return
}

insert_tile() {
  echo $* >> $tile_file
  return 
}
insert_track() {
  echo $* >> $track_file
  return
}
add_record_tracks() {
  echo "Enter track information for this CD"
  echo "When no more tracks enter q"
  cdtrack=1
  cdtile=""
  while [ "$cdtitle" != "q" ]
  do
    echo -e "Track $cdtrack, track title?\c"
    read tmp
    cdtt
}