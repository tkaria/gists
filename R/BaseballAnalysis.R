## Demo for CS 194-16: Introduction to Data Science
## Berkeley, Spring 2011
## --------------------------
## Michael E. Driscoll
## mike@metamarketsgroup.com
## --------------------------
##
## This file was found at:
##
## http://metamx-mdriscol-adhoc.s3.amazonaws.com/gameday/README.R
## 
## This is some sample code for analyzing and visualizing ~ 700k
## pitches tracked by the Pitch FX system during the 2009 Major League
## Baseball Season.  More information about this data and its fields
## can be found at:
##
##   http://webusers.npl.illinois.edu/~a-nathan/pob/tracking.htm
##
## Thanks to Dennis Murphy who cleaned this data and made it readable in R.
##
## The R data files can found at (pitch09.Rda is the largest at ~ 40Mb):
##
##   http://metamx-mdriscol-adhoc.s3.amazonaws.com/gameday/pitch09.Rda  
##   http://metamx-mdriscol-adhoc.s3.amazonaws.com/gameday/hitchart09.Rda
##   http://metamx-mdriscol-adhoc.s3.amazonaws.com/gameday/players09.Rda
##   http://metamx-mdriscol-adhoc.s3.amazonaws.com/gameday/atbat09.Rda
##
##
## ---------------------------------------------------------------------------

## Code for doing some exploratory data analysis and visualization

## install & load ggplot2 library
install.packages('ggplot2', dependencies=TRUE) ## only if you don't have ggplot2 installed
library(ggplot2)

## let's load up the pitch data environment from S3
load(url('http://metamx-mdriscol-adhoc.s3.amazonaws.com/gameday/players09.Rda'))
## or, if you already downloaded the files, use the following line to load the data
# load('players09.Rda')

## this takes a long time - it's a 40MB file - and loads the 'pitch09' data frame
load(url('http://metamx-mdriscol-adhoc.s3.amazonaws.com/gameday/pitch09.Rda'))
# load('pitch09.Rda')

## let's examine some basic structure of the data frame and its columns
head(pitch09)
str(pitch09)
summary(pitch09)
class(pitch09$home_team)
unique(pitch09$home_team)

## let's find the ID that corresponds with Tim Lincecum of SF
subset(players09,last_name=='Lincecum',)

## okay, so we've got the id for Lincecum, let's put that in a new frame
## let's also just take the few data fields we care most about
lincecum <- subset(pitch09, pitcher==453311, select=c('pitcher','pitch_type', 'pfx_x', 'pfx_z', 'start_speed'))
lincecum$pitch_type <- as.character(lincecum$pitch_type)

## now let's plot a single dimension:  speed
library(ggplot2)
qplot(start_speed, data=lincecum)

## interesting, looks like a bimodal distribution here
## let's tabulate pitches by pitch type
table(lincecum$pitch_type)

## now let's constrain to just changeups, curves, fastballs, and sliders
## and add a second dimension to the plot, pitch type, and see how it looks
lincecum_sub <- subset(lincecum, pitch_type %in% c('CH','CU','FF','SL'))
qplot(start_speed, data=lincecum_sub, binwidth=1) + facet_grid(pitch_type ~ .)

## let's look at another couple of dimensions, x and y
qplot(pfx_x, pfx_z, data=lincecum)

## how does it break down by pitch_type?
qplot(pfx_x, pfx_z, data=lincecum_sub) + facet_grid(. ~ pitch_type) 

## what about speed, can we incorporate this as a color?
qplot(pfx_x, pfx_z, data=lincecum_sub, color=start_speed) + facet_grid(. ~ pitch_type)

## let's add an alpha parameter of 50% to make points slightly transparent
qplot(pfx_x, pfx_z, data=lincecum_sub, color=start_speed, alpha=0.5) + facet_grid(. ~ pitch_type) 

## now let's look at sabathia
sabathia <- subset(pitch09, pitcher==282332, select=c('pitcher','pitch_type', 'pfx_x', 'pfx_z', 'start_speed'))
sabathia_sub <- subset(sabathia, pitch_type %in% c('CH','CU','FF','SL'))

## let's combine sabathia and lincecum's data
sabathia_sub$pitcher_name = 'sabathia'
lincecum_sub$pitcher_name = 'lincecum'
combined <- rbind(sabathia_sub, lincecum_sub)


## let's graph the combination of these two
qplot(pfx_x, pfx_z, data=combined, color=start_speed, alpha=I(0.5)) + facet_grid(pitcher_name ~ pitch_type) 

## let's save a sample of the data into a smaller data frame
pitch_sample <- combined
save(pitch_sample, file='pitch_sample.Rda')

