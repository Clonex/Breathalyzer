struct animation {
    int tick;
    int duration;
    void (*callback)(float);
};

int animationCount = 0;
animation animations[10] = {};

animation *Animation(void (*f)(float), int duration)
{
    struct animation anim;
    anim.callback = (*f);
    anim.tick = 0;
    anim.duration = duration;
    animations[animationCount] = anim;
    animationCount++;
    return &anim;
}

void animationTick()
{
    for(int i = 0; i < animationCount; i++)
    {
        animation *anim = &animations[i];
        float progress = (float) anim->tick / (float) anim->duration;
        anim->callback(progress);
        anim->tick++;
        if(progress >= 1)
        {
            removeAnimation(i);
            i--;
        }
    }
}

void removeAnimation(int targetI)
{
    for(int i = targetI + 1; i < animationCount; i++)
    {
        animations[i - 1] = animations[i];
    }
    animationCount--;
}

