
#include "anki-importer-app.h"
#include "raygui.h"

void run_gui()
{
    InitWindow(400, 200, "main window");
    SetTargetFPS(60);

    bool showMessageBox = false;

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
            if (GuiButton((Rectangle){ 24, 24, 120, 30 }, "#191#Button")) 
				showMessageBox = true;
            if (showMessageBox)
            {
                int result = GuiMessageBox((Rectangle){ 85, 70, 250, 100 },
                    "#191#MessageBox", "Message", "OK");
                if (result >= 0) showMessageBox = false;
            }
        EndDrawing();
    }
    CloseWindow();
}
