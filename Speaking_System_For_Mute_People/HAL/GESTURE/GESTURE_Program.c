#include "GESTURE_Config.h"
#include "GESTURE_Private.h"
#include "GESTURE_Interface.h"

/* Legacy gesture module retained for compatibility. */
void Gesture_Init(void)
{
    /* The main application performs all glove initialization. */
}

void Gesture_TriggerBinaryOutput(uint8_t matched_index)
{
    (void)matched_index;
    /* Gesture output is handled by GET_WORD_SOUND + SHOW. */
}
