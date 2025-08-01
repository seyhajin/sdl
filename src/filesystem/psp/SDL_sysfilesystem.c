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

#ifdef SDL_FILESYSTEM_PSP

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
// System dependent filesystem routines

#include "../SDL_sysfilesystem.h"

#include <sys/stat.h>
#include <unistd.h>

char *SDL_SYS_GetBasePath(void)
{
    char *result = NULL;
    size_t len;
    char cwd[FILENAME_MAX];

    getcwd(cwd, sizeof(cwd));
    len = SDL_strlen(cwd) + 2;
    result = (char *)SDL_malloc(len);
    if (result) {
        SDL_snprintf(result, len, "%s/", cwd);
    }

    return result;
}

char *SDL_SYS_GetPrefPath(const char *org, const char *app)
{
    char *result = NULL;
    const char *base = SDL_GetBasePath();
    if (!base) {
        return NULL;
    }

    const size_t len = SDL_strlen(base) + SDL_strlen(org) + SDL_strlen(app) + 4;
    result = (char *)SDL_malloc(len);
    if (result) {
        if (*org) {
            SDL_snprintf(result, len, "%s%s/%s/", base, org, app);
        } else {
            SDL_snprintf(result, len, "%s%s/", base, app);
        }
        mkdir(result, 0755);
    }

    return result;
}

// TODO
char *SDL_SYS_GetUserFolder(SDL_Folder folder)
{
    SDL_Unsupported();
    return NULL;
}

#endif // SDL_FILESYSTEM_PSP
