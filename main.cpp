#include "mbed.h"
#include <chrono>
#include <cstdio>

#define LED3 PB_5
#define LED2 PB_4
#define LED1 PB_3

#define BUTTON1 PA_1
#define BUTTON2 PA_2

#define TX PA_9
#define RX PA_10
#define BAUDRATE 9600

#define PERIOD_1 120
#define PERIOD_2 240

using namespace std::chrono_literals;
using namespace std::chrono;

static BufferedSerial uart(TX, RX, BAUDRATE);

FileHandle *mbed::mbed_override_console(int fd)
{
    return &uart;
}

static DigitalOut led3(LED3, PullUp);
static DigitalOut led2(LED2, PullUp);
static DigitalOut led1(LED1, PullUp);

static DigitalIn button1(BUTTON1, PullUp);
static DigitalIn button2(BUTTON2, PullUp);

int main()
{
    Timer timer;
    timer.start();
    unsigned long long elapsed = 0;
    float percent = 100.0;
    while (true) {
        elapsed = duration_cast<milliseconds>(timer.elapsed_time()).count();

        if (!button1) {
          if (percent > 0.0) {
            percent -= 0.1;
          } else
            percent = 0.0;
        }

        if (!button2) {
          if (percent < 100.0) {
            percent += 0.1;
          } else
            percent = 100.0;
        }

        printf("%f percent\n", percent);

        if (elapsed % PERIOD_1 >= PERIOD_1 * (percent / 100.0)) {
          led3 = 0;
        }
        else {
            led3 = 1;
        }
        if (elapsed % PERIOD_2 >= PERIOD_2 * (percent / 100.0)) {
          led2 = 0;
        }
        else {
            led2 = 1;
        }
    }
}

