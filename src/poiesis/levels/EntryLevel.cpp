#include "poiesis/levels/EntryLevel.h"

void EntryLevel::Start()
{
    LOG_I("[EntryLevel] Starting");

    Engine::GetInstance().PlayMusic(CFG_GETP("BACKGROUND_MUSIC"),
        REPEAT_CONTINUOUSLY);
    
    EntityFactory::CreateButton(CFG_GETP("EXIT_BUTTON_IMAGE"),
        Rectangle(800, 600, 150, 50),
        std::bind(&EntryLevel::ExitButtonCallback, this));

    // Creating systems.
    Engine::GetInstance().AddSystem(std::make_shared<RenderingSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<InputSystem>());
    Engine::GetInstance().AddSystem(std::make_shared<DebugSystem>());

    canCreateStartButton = true;
}

void EntryLevel::Update()
{
    if (!PreloadImages())
    {
        if (!Engine::GetInstance().GetGraphicsAdapter()->IsFontLoaded(CFG_GETP("FONT_FILE")))
            Engine::GetInstance().GetGraphicsAdapter()->LoadFont(CFG_GETP("FONT_FILE"), CFG_GETI("DEBUG_MESSAGE_SIZE"));

        Engine::GetInstance().GetGraphicsAdapter()->Write("Loading",
            CFG_GETP("FONT_FILE"), 835, 500);
    }
    else if (canCreateStartButton)
    {
        EntityFactory::CreateButton(CFG_GETP("START_BUTTON_IMAGE"),
            Rectangle(800, 500, 150, 50),
            std::bind(&EntryLevel::StartButtonCallback, this));

        canCreateStartButton = false;
    }
}

void EntryLevel::Finish()
{
    LOG_I("[EntryLevel] Finishing");
    Engine::GetInstance().ClearEntities();
    Engine::GetInstance().ClearSystems();
}

void EntryLevel::StartButtonCallback()
{
    LOG_I("[EntryLevel] Clicked on start button");
    SetFinished();
    Engine::GetInstance().SetNextLevel(std::make_shared<Level2>());
}

void EntryLevel::ExitButtonCallback()
{
    LOG_I("[EntryLevel] Clicked on exit button");
    SetFinished();
}

bool EntryLevel::PreloadImages()
{
    LOG_D("[EntryLevel] Preloading images");

    return PreloadAnimation(CFG_GETP("CELL_ANIMATION"), CFG_GETI("CELL_ANIMATION_NUM_FRAMES"));
}

bool EntryLevel::PreloadAnimation(std::string filename, int numFrames)
{
    std::string frameNumberStr;
    std::string frameFilename;

    for (int i = 0; i < numFrames; ++i)
    {
        frameNumberStr = std::to_string(i);
        frameFilename = filename + std::string(4 - frameNumberStr.length(), '0') + frameNumberStr + ".png";
        if (PreloadImage(frameFilename))
            return false;
    }

    return true;
}

bool EntryLevel::PreloadImage(std::string filename)
{
    if (!Engine::GetInstance().GetGraphicsAdapter()->IsLoaded(filename))
    {
        Engine::GetInstance().GetGraphicsAdapter()->LoadImage(filename);
        return true;
    }

    return false;
}