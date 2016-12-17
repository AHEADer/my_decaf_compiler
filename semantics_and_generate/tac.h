#ifndef _H_tac
#define _H_tac

class Mips;

typedef enum {fpRelative, gpRelative} Segment;

class Location
{
protected:
    const char *variableName;
    Segment segment;
    int offset;

public:
    Location(Segment seg, int offset, const char* name);
    const char *GetName()   { return variableName;}
    Segment GetSegment()    { return segment;}
    int GetOffset()         { return offset;}
};

#endif