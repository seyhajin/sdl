/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include "SDL_internal.h"

#ifndef SDL_evdev_h_
#define SDL_evdev_h_

#ifdef SDL_INPUT_LINUXEV

struct input_event;

extern bool SDL_EVDEV_Init(void);
extern void SDL_EVDEV_Quit(void);
extern void SDL_EVDEV_SetVTSwitchCallbacks(void (*release_callback)(void *), void *release_callback_data,
                                           void (*acquire_callback)(void *), void *acquire_callback_data);
extern int SDL_EVDEV_GetDeviceCount(int device_class);
extern void SDL_EVDEV_Poll(void);
extern Uint64 SDL_EVDEV_GetEventTimestamp(struct input_event *event);

#endif // SDL_INPUT_LINUXEV

#endif // SDL_evdev_h_
