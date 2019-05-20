/* Copyright (c) 2019, Christian Kellner All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 *
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * * Neither the name of Feral Interactive nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * RISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#define _GNU_SOURCE 1
#include <config.h>

#include "gamemode_client.h"

#include <stdarg.h>
#include <stdio.h>

#define DO_TRACE 1

#ifdef NDEBUG
#define DEBUG(...)
#define LOG_ERROR
#else
#define DEBUG(...) fprintf (stderr, __VA_ARGS__)
#endif

#ifdef DO_TRACE
#define TRACE(...) fprintf (stderr, __VA_ARGS__)
#else
#define TRACE(...)
#endif

static int active = 0;

__attribute__((constructor))
static void
gamemode_auto_register (void)
{
  int r;

  TRACE ("GM: auto: requesting gamemode");

  r = gamemode_request_start ();

  if (r < 0)
    {
      DEBUG ("GameMode: auto: failed to register: %s",
             gamemode_error_string ());

      return;
    }

  TRACE ("GM: auto: gamemode requested successfully");
  active = 1;
}


__attribute__((destructor))
static void
gamemode_auto_unregister (void)
{
  int r;

  if (active == 0)
    return;

  TRACE ("GM: auto: un-register self");

  r = gamemode_request_end ();

  if (r < 0)
    {
      DEBUG ("GameMode: auto: failed to unregister: %s",
             gamemode_error_string ());
      return;
    }

  active = 0;
}
