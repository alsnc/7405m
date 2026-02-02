#include "main.h"
#include "autonselector.h"
#include "pros/adi.hpp"
#include "pros/rtos.hpp"
#include "pros/screen.hpp"

static int auton = -1;       
static int alliance = -1;    
static bool selectingAuton = false;    
static bool autonSelected = false;     
static const char* selectedAutonLabel = "None";  //labeling stuff


struct Button {
    int x0, y0, x1, y1;
    const char* label; 
};

//alliance buttons
static Button allianceButtons[] = {
    {50, 60, 230, 140, "Red"},
    {250, 60, 430, 140, "Blue"}
};
#define NUM_ALLIANCE (sizeof(allianceButtons)/sizeof(allianceButtons[0]))

//auton buttonsss
static Button autonBlueButtons[] = {
    {20, 40, 200, 100, "Bottom Goal"},
    {220, 40, 400, 100, "Top Goal"},
    {20, 140, 200, 200, "Bottom Control Goal"},
    {220, 140, 400, 200, "null"}
};

static Button autonRedButtons[] = {
    {20, 40, 200, 100, "Bottom Goal"},
    {220, 40, 400, 100, "Top Goal"},
    {20, 140, 200, 200, "Bottom Control Goal"},
    {220, 140, 400, 200, "null"}
};


//get the array length/number of buttons
#define NUMRED_AUTON (sizeof(autonRedButtons)/sizeof(autonRedButtons[0]))
#define NUMBLUE_AUTON (sizeof(autonBlueButtons)/sizeof(autonBlueButtons[0]))

//back button
static Button backButton = {180, 190, 300, 230, "Back"};

static int getTextYCenter(const Button &btn) {
    int h = btn.y1 - btn.y0;
    return btn.y0 + h / 2 - 10;
}

static void drawButtonBorder(const Button &btn) {
    pros::screen::set_pen(pros::c::COLOR_YELLOW);
    pros::screen::draw_rect(btn.x0, btn.y0, btn.x1, btn.y1);
}

static void drawButton(const Button &btn, int fillColor) {
    pros::screen::set_pen(fillColor); 
    pros::screen::fill_rect(btn.x0, btn.y0, btn.x1, btn.y1);

    pros::screen::set_pen(pros::c::COLOR_WHITE);
    pros::screen::print(TEXT_MEDIUM, btn.x0 + 10, getTextYCenter(btn), btn.label);

    drawButtonBorder(btn);
}


static void drawAllianceScreen() {
    selectingAuton = false;
    autonSelected = false;
    selectedAutonLabel = "None";

    pros::screen::set_pen(pros::c::COLOR_BLACK);
    pros::screen::fill_rect(0, 0, 480, 240);

    drawButton(allianceButtons[0], pros::c::COLOR_RED);
    drawButton(allianceButtons[1], pros::c::COLOR_BLUE);
}

static void drawAutonScreen() {
    selectingAuton = true;
    autonSelected = false;

    pros::screen::set_pen(pros::c::COLOR_BLACK);
    pros::screen::fill_rect(0, 0, 480, 240);

    //alliance label
    pros::screen::set_pen(alliance == 0 ? pros::c::COLOR_RED : pros::c::COLOR_BLUE);
    const char* allianceLabel = alliance == 0 ? "Red Alliance" : "Blue Alliance";
    pros::screen::print(TEXT_MEDIUM, 140, 10, allianceLabel);

    //auton buttons for alliance
    if (alliance == 0) {
        for (int i = 0; i < NUMRED_AUTON; i++)
            drawButton(autonRedButtons[i], pros::c::COLOR_RED);
    } else {
        for (int i = 0; i < NUMBLUE_AUTON; i++)
            drawButton(autonBlueButtons[i], pros::c::COLOR_BLUE);
    }

    //back
    drawButton(backButton, pros::c::COLOR_WHITE);
}

static void drawAutonSelectedScreen() {
    selectingAuton = false;
    autonSelected = true;

    pros::screen::set_pen(pros::c::COLOR_BLACK);
    pros::screen::fill_rect(0, 0, 480, 240);

    //confirmation label
    pros::screen::set_pen(pros::c::COLOR_WHITE);
    pros::screen::print(TEXT_LARGE, 100, 60, "Selected Auton:");
    pros::screen::print(TEXT_LARGE, 100, 100, selectedAutonLabel);

    // Show only the back button
    drawButton(backButton, pros::c::COLOR_WHITE);
}

static void touchHandler() {
    pros::screen_touch_status_s_t status = pros::screen::touch_status();
    int x = status.x;
    int y = status.y;

    if (!selectingAuton && !autonSelected) {
        //alliance selection
        for (int i = 0; i < NUM_ALLIANCE; i++) {
            if (x >= allianceButtons[i].x0 && x <= allianceButtons[i].x1 &&
                y >= allianceButtons[i].y0 && y <= allianceButtons[i].y1) {
                alliance = i;
                drawAutonScreen();
                return;
            }
        }
    } else if (selectingAuton) {
        //auton buttons
        if (alliance == 0) { //red
            for (int i = 0; i < NUMRED_AUTON; i++) {
                if (x >= autonRedButtons[i].x0 && x <= autonRedButtons[i].x1 &&
                    y >= autonRedButtons[i].y0 && y <= autonRedButtons[i].y1) {
                    auton = i + 4;   
                    selectedAutonLabel = autonRedButtons[i].label; 
                    drawAutonSelectedScreen();
                    return;
                }
            }
        } else { //blue
            for (int i = 0; i < NUMBLUE_AUTON; i++) {
                if (x >= autonBlueButtons[i].x0 && x <= autonBlueButtons[i].x1 &&
                    y >= autonBlueButtons[i].y0 && y <= autonBlueButtons[i].y1) {
                    auton = i;       
                    selectedAutonLabel = autonBlueButtons[i].label; 
                    drawAutonSelectedScreen();
                    return;
                }
            }
        }

        //return to alliance screen
        if (x >= backButton.x0 && x <= backButton.x1 &&
            y >= backButton.y0 && y <= backButton.y1) {
            drawAllianceScreen();
            return;
        }
    } else if (autonSelected) {
        //back button is active
        if (x >= backButton.x0 && x <= backButton.x1 &&
            y >= backButton.y0 && y <= backButton.y1) {
            drawAutonScreen(); //go back to auton options
            auton = -1;        //clear previous selection
            selectedAutonLabel = "None";
            return;
        }
    }
}

void autonSelectorStart() {
    pros::delay(50);
    drawAllianceScreen(); 
    pros::screen::touch_callback(touchHandler, TOUCH_RELEASED);
}

int getSelectedAuton() { return auton; }
int getSelectedAlliance() { return alliance; }
const char* getSelectedAutonLabel() { return selectedAutonLabel; }  