/* 

Light switching logic

    Initial state:  LED_off
    Press:          turn on last pattern (rgb/white)
    Double Press:   no effect
    Long   Press:   no effect
    Rotate:         no effect
    
    Initial state:  White_Pattern
    Press:          Change to (LED_off)
    Double Press:   Change to (Select_white_pattern)
    Long   Press:   Change to (RGB_Pattern)
    Rotate:         Change intensity - <send update message>

    Initial state:  RGB_Pattern
    Press:          Change to (LED_off)
    Double Press:   Change to (Select_RGB_pattern)
    Long   Press:   Change to (White_Pattern)
    Rotate:         Change intensity - <send update message>

    Initial state:  Select_RGB_pattern
    Press:          Change to (RGB_Pattern) -   <save settings>
    Double Press:   No effect
    Long   Press:   No effect
    Rotate:         Change pattern - <update local RGB ring>

    Initial state:  Select_white_pattern
    Press:          Change to (White_Pattern) - <save settings>
    Double Press:   No effect
    Long   Press:   No effect
    Rotate:         Change pattern - <send update message>
 */