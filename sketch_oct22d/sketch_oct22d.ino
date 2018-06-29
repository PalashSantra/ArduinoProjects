#include <Playtune.h>

 

//copy paste content of converted midi file here.ie: Movie_Themes_-_James_Bond.c

 

Playtune pt;

void setup() {
pt.tune_initchan (10);
pt.tune_initchan (11);
pt.tune_initchan (12);
}

void loop () {
pt.tune_playscore (score); /* start playing */
while (pt.tune_playing) ; /* wait here until playing stops */
}
