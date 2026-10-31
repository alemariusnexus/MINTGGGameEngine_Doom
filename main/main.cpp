/* MINTGGGameEngine_Doom - A port of Doom to MINTGGGameEngine
 *
 * Copyright (C) 2026 David Lerch
 * SPDX-License-Identifier: GPL-3.0-or-later
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <MINTGGGameEngine.h>

#include <list>

#include "doomgeneric/doomgeneric/doomgeneric.h"
#include "doomgeneric/doomgeneric/doomkeys.h"

LOG_USE_TAG("main")


struct KeyDef
{
    const char* id;
    unsigned char doomKey;
    gpionum_t gpio;
};

struct KeyEvent
{
    unsigned char doomKey;
    bool pressed;
};


static const KeyDef KeyDefs[] = {
    //  ID          DOOMKEY             GPIO
    {   "left",     KEY_LEFTARROW,      -1      },
    {   "right",    KEY_RIGHTARROW,     -1      },
    {   "up",       KEY_UPARROW,        -1      },
    {   "down",     KEY_DOWNARROW,      -1      },
    {   "enter",    KEY_ENTER,          -1      },
    {   "escape",   KEY_ESCAPE,         -1      },
    {   "fire",     KEY_FIRE,           -1      },
    {   "use",      KEY_USE,            -1      }
};


timer_mstick_t StartTime;

std::list<KeyEvent> keyQueue;
Mutex keyQueueMtx;

char** ProgramArgs;


void onButtonEvent(const InputButtonEvent& evt)
{
    unsigned char doomKey;
    bool doomKeyFound = false;
    for (const auto& def : KeyDefs) {
        if (def.id == evt.getID()) {
            doomKey = def.doomKey;
            doomKeyFound = true;
            break;
        }
    }
    if (!doomKeyFound) {
        return;
    }

    KeyEvent devt = {
        .doomKey = doomKey,
        .pressed = evt.isPressed()
    };

    {
        Mutex::Lock lk(keyQueueMtx);
        keyQueue.push_back(devt);
    }
}

void gameSetup()
{
    const std::string args[] = {
        "MINTGGGameEngine_Doom",
        "-iwad", game.storage().resolvePath("/sdcard/doom1.wad"),
        "-gfxmode", "rgb565"
    };

    //engine.setPrintFrameStatistics(true);

    for (const auto& def : KeyDefs) {
        game.input().defineButton(def.id, def.gpio);
    }

    game.input().addButtonEventCallback(&onButtonEvent);

    game.screen().fill(Color::BLACK, false);

    game.setBackgroundSkipped(true);

    StartTime = TimerGetTickcountMs();

    const int argc = static_cast<int>(sizeof(args) / sizeof(std::string));
    ProgramArgs = argc >= 0 ? static_cast<char**>(malloc(argc*sizeof(char*))) : nullptr;
    for (int i = 0 ; i < argc ; i++) {
        ProgramArgs[i] = static_cast<char*>(malloc(args[i].length() + 1));
        strcpy(ProgramArgs[i], args[i].data());
    }

    doomgeneric_Create(argc, ProgramArgs);
}

void gameLoop(float dt)
{
    doomgeneric_Tick();
}

void onCollision(const GameObjectCollision& coll)
{
}



void DG_Init()
{
    // Nothing to do here. Setup is done in gameSetup().
}

void DG_DrawFrame()
{
    BitmapRenderer renderer;

    auto screenBuf = reinterpret_cast<uint8_t*>(static_cast<ScreenRPiTC358762&>(game.screen()).getBuffer().getBuffer());

    BitmapRenderer::Transfer transfer = {
        .src = {
            .buffer = DG_ScreenBuffer,
            .alpha = nullptr,
            .width = DOOMGENERIC_RESX,
            .height = DOOMGENERIC_RESY,
            .blockOffsetX = 0,
            .blockOffsetY = 0,
            .blockWidth = DOOMGENERIC_RESX,
            .blockHeight = DOOMGENERIC_RESY,
            .pixelFormat = PixelFormat::RGB565,
            .alphaStorage = AlphaStorage::Bit1,
            .byteOrder = ByteOrder::Native
        },

        .dest = {
            .buffer = screenBuf,
            .alpha = nullptr,
            .width = game.screen().getWidth(),
            .height = game.screen().getHeight(),
            .blockOffsetX = 80,
            .blockOffsetY = 40,
            .pixelFormat = game.screen().getNativePixelFormat(),
            .alphaStorage = AlphaStorage::Bit1,
            .byteOrder = game.screen().getNativeByteOrder()
        }
    };

    const int16_t scaleFactor = std::max<int16_t>(1, std::min(
        static_cast<int16_t>(game.screen().getWidth() / DOOMGENERIC_RESX),
        static_cast<int16_t>(game.screen().getHeight() / DOOMGENERIC_RESY)
        ));

    BitmapRenderer::TransformSimple transform = {
        .scaleX = scaleFactor,
        .scaleY = scaleFactor,
        .rotation = Rotation::Rot0,
        .mirror = FlipDir::None
    };

    renderer.render(transfer, transform);
}

void DG_SleepMs(uint32_t ms)
{
    DelayTaskMs(ms);
}

uint32_t DG_GetTicksMs()
{
    return static_cast<uint32_t>(TimerGetTickcountMs() - StartTime);
}

int DG_GetKey(int* pressed, unsigned char* key)
{
    Mutex::Lock lk(keyQueueMtx);
    if (keyQueue.empty()) {
        return 0;
    }
    const KeyEvent& evt = keyQueue.front();
    *key = evt.doomKey;
    *pressed = evt.pressed;
    keyQueue.pop_front();
    return 1;
}

void DG_SetWindowTitle(const char* title)
{
    LogInfo("Window Title: %s", title);

#ifdef MINTGGGAMEENGINE_PORT_DESKTOP
    MainWindow::instance()->setWindowTitle(title);
#endif
}
