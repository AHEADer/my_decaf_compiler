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

class Instruction {
protected:
    char printed[128];

public:
    virtual ~Instruction() {}
    virtual void Print();
    virtual void EmitSpecific(Mips *mips) = 0;
    virtual void Emit(Mips *mips);
};

#endif