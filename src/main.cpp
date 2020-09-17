#include <mbed.h>
#include <DebounceIn.hpp>

DigitalOut led2(LED2, 1);
DebounceIn btn(p31);

EventQueue mainEventQueue(64 * EVENTS_EVENT_SIZE);
Thread mainThread(osPriorityNormal, OS_STACK_SIZE, NULL, "MAIN.event.queue");

void toggleLed2() {
    led2 = !led2;

}

void btnFall() {
    printf("btnFall\n");
    toggleLed2();
}

void btnRise() {
    printf("btnRise\n");
}

int main() {
    printf("[Main] Boot start!\n");
    printf("[Main] Mbed OS v%u.%u.%u\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    mainThread.start(callback(&mainEventQueue, &EventQueue::dispatch_forever));

    // execute in the context of thread 'mainThread'
    btn.fall(mainEventQueue.event(btnFall));
    btn.rise(mainEventQueue.event(btnRise));

    printf("[Main] Boot complete!\n");

    return 0;
}