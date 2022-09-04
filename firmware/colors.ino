

//convert 24 bit RGB to 16bit 5:6:5 RGB
unsigned int convertRGB(unsigned long rgb)
{
    return (((rgb & 0xf80000) >> 8) | ((rgb & 0xfc00) >> 5) | ((rgb & 0xf8) >> 3));
}


unsigned int colorTransition(unsigned long fromRGB, unsigned long toRGB, double percent)
{
    if(percent < 0.5)
    {
        percent = 1 - percent;
    }

    if(percent >= 1)
    {
        return fromRGB;
    }

    unsigned int fromR = (fromRGB >> 11) & 0x1F;
    unsigned int fromG = (fromRGB >>  5) & 0x3F;
    unsigned int fromB =  fromRGB        & 0x1F;

    unsigned int toR = (toRGB >> 11) & 0x1F;
    unsigned int toG = (toRGB >>  5) & 0x3F;
    unsigned int toB =  toRGB        & 0x1F;

    double diffR = fromR - toR;
    double diffG = fromG - toG;
    double diffB = fromB - toB;
    
    unsigned int r = (diffR * percent) + fromR;
    unsigned int g = (diffG * percent) + fromG;
    unsigned int b = (diffB * percent) + fromB;

    return (r << 11) | (g << 5) | b;
}