struct scan_message
{
    float front;
    float left;
    float right;
};
#define LEFT 0
#define RIGHT 1
#define FRONT 2
struct scan_message step_scan(void);