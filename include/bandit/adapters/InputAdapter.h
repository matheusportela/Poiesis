// Interface to input handling.

#ifndef INPUT_ADAPTER_H_
#define INPUT_ADAPTER_H_

// All supported types of input.
namespace InputType
{
    enum Type
    {
        MousePress,
        MouseRelease,
        MouseDown,
        KeyPress,
        KeyRelease,
        KeyDown,
        QuitButtonPress,
    };
}

// All supported types of mouse input.
namespace MouseButton
{
    enum Button
    {
        Left,
        Middle,
        Right,
    };
}

// All supported types of keyboard input.
namespace KeyboardButton
{
    enum Button
    {
        LowercaseA,
        LowercaseB,
        LowercaseC,
        LowercaseD,
        LowercaseE,
        LowercaseF,
        LowercaseG,
        LowercaseH,
        LowercaseI,
        LowercaseJ,
        LowercaseK,
        LowercaseL,
        LowercaseM,
        LowercaseN,
        LowercaseO,
        LowercaseP,
        LowercaseQ,
        LowercaseR,
        LowercaseS,
        LowercaseT,
        LowercaseU,
        LowercaseV,
        LowercaseW,
        LowercaseX,
        LowercaseY,
        LowercaseZ,
        Number0,
        Number1,
        Number2,
        Number3,
        Number4,
        Number5,
        Number6,
        Number7,
        Number8,
        Number9,
        ArrowUp,
        ArrowDown,
        ArrowLeft,
        ArrowRight,
        LeftShift,
        RightShift,
        LeftCtrl,
        RightCtrl,
        Esc,
        Space,
    };
}

class InputAdapter
{
  public:
    virtual ~InputAdapter() {}
    
    // Processes all inputs that happened since the last invocation of this
    // method.
    virtual void ProcessInputs() = 0;

    // Checks whether the input type (with an optional button specifier)
    // occurred in the meanwhile.
    virtual bool CheckInputOccurred(InputType::Type inputType, int button = 0) = 0;
};

#endif // INPUT_ADAPTER_H_