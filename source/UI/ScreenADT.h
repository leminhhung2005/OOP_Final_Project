// Screen Abstract class

#pragma once

#include "header.h"
#include "Login.h"
#include "../Manage/ManageUser.h"

class Screen
{
protected:
    Login login;
    ManageUser &manageUser;

public:
    Screen(ManageUser &userManager) : manageUser(userManager),login(userManager)
    {
    }

    virtual void display() = 0;

    virtual int handleInput(int keyInput) = 0;

    virtual ~Screen() = default;
};