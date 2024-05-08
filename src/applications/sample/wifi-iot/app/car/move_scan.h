#define LEFT 0
#define RIGHT 1
#define FRONT 2
#define RESTART 1
#define CONTINUE 0

struct scan_message
{
    float front;
    float left;
    float right;
};

struct scan_message step_scan(char restart);

struct scan_message scan(void);

float get_distance(short direction);