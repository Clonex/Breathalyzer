bool pressed[100] = {false};
bool btnPressed(int btn)
{
    if(digitalRead(btn) == LOW && pressed[btn] == false)
    {
        pressed[btn] = true;
        return true;
    }

    return false;
}

/**
 * Resets the button states if they arent PRESSED anymore.
 **/
void btnTick()
{
    if(digitalRead(BTN_UP) == HIGH)
    {
        pressed[BTN_UP] = false;
    }

    if(digitalRead(BTN_MID) == HIGH)
    {
        pressed[BTN_MID] = false;
    }

    if(digitalRead(BTN_DOWN) == HIGH)
    {
        pressed[BTN_DOWN] = false;
    }
}