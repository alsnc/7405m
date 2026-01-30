#pragma once
#include "pros/apix.h"

// Initialize auton selector (called in initialize())
void autonSelectorStart();

// Return which auton is selected (-1 if none)
int getSelectedAuton();
int getSelectedAlliance();

// Cancel the selection (resets back to -1)
void cancelSelection();


//variables
//extern int auton;       
//extern int alliance;