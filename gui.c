
#include "anki-importer-app.h"
#include "raygui.h"

void run_gui()
{
    InitWindow(400, 400, "main window");
    SetTargetFPS(60);
	char word[20];


	memset(&word, 0, 20);

    bool showMessageBox = false;

    while (!WindowShouldClose())
    {
        BeginDrawing();
			if (GuiTextInputBox((Rectangle){100, 180, 200, 200}, "Add", "Insert word to add:", "Submit", word ,10, NULL) > 0)
			{
				printf("result: %s\n", word);
				scraper_function(word);
			}
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
            if (GuiButton((Rectangle){ 24, 24, 120, 30 }, "#191#Generate")) 
			{
				showMessageBox = true;
			}
            if (showMessageBox)
            {
                int result = GuiMessageBox((Rectangle){ 85, 70, 250, 100 },
                    "#191#MessageBox", "File generated!", "Ok");
                if (result >= 0) showMessageBox = false;
            }
        EndDrawing();
    }
    CloseWindow();
}
