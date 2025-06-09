//
// Created by User on 6/9/2025.
//

#ifndef BATTLEPREPSCREEN_H
#define BATTLEPREPSCREEN_H

#include "Screen.h"

class BattlePrepScreen final: public Screen {
public:
    void init() override;
    ScreenType update() override;
    void draw() override;
    void cleanup() override;
};
#endif //BATTLEPREPSCREEN_H