
#include "anki-importer-app.h"
#include "raygui.h"

void run_gui()
{
	char word[20];

    InitWindow(800, 600, "Anki importer App");
	GuiLoadStyle("theme/style_amber.rgs");
    SetTargetFPS(60);

	memset(&word, 0, 20);
    while (!WindowShouldClose())
    {
        BeginDrawing();
			if (GuiTextInputBox((Rectangle){100, 180, 200, 200}, 
				"Add", "Insert word to add:", "Submit", word ,10, NULL) > 0)
				scraper_function(word);
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        EndDrawing();
    }
    CloseWindow();
}
