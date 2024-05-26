#include "_private.h"

// #define TX_PATH "./assets/texture.png"
#define TX_PATH "/home/manus/Documents/projects/Chess/assets/texture.png"
#define FPS     (30)
#define WW_DFLT (1000)
#define WH_DFLT (1000)

static int _init(Gui * gui)
{
    InitWindow(gui->layout.window.width, gui->layout.window.height, "");
    SetWindowMonitor(0);
    SetTargetFPS(FPS);

    return OK;
}

static int _init_layout(Gui * gui)
{
    gui->layout = Layout_default(WW_DFLT, WH_DFLT);

    return OK;
}

static int _init_tx(Gui * gui, const char * path)
{
    Texture2D   texture;
    TxLayout    tx_layout;

    tx_layout = TxLayout_default();
    texture = LoadTexture(path);

    gui->tx.texture = texture;
    gui->tx.tx_layout = tx_layout;

    return texture.id > 0 ? OK : NOK;
}

static Gui * _error(Gui * gui)
{
    free(gui);

    return NULL;
}

Gui * Gui_start(void)
{
    Gui * gui;

    if (! (gui = malloc(sizeof(Gui)))) return NULL;

    if (_init_layout(gui) == NOK)       return _error(gui);
    if (_init(gui) == NOK)              return _error(gui);
    if (_init_tx(gui, TX_PATH) == NOK)  return _error(gui);

    return gui;
}

int Gui_stop(Gui * gui)
{
    UnloadTexture(gui->tx.texture);
    CloseWindow();

    return OK;
}

void Gui_reset(Gui * gui)
{
    Layout_deselect(& gui->layout);
}

void Gui_restore(Gui * gui)
{
    if (Layout_has_selection(& gui->layout)) Layout_restore_selection(& gui->layout);
}

Texture2D Gui_texture(const Gui * gui)
{
    return gui->tx.texture;
}

int Gui_data_size(const Gui * gui)
{
    return sizeof(* gui);
}

int Gui_Board_set_cstr(Gui * gui, const char * cstr)
{
    GuiBoard_place_from_cstr(& gui->layout.board, cstr);

    return OK;
}