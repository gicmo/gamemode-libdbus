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

#include "gamemode_client.h"

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
  int r;

  printf ("Running [pid: %u]\n", (uint32_t) getpid ());
  printf ("Requesting gamemode\n");

  r = gamemode_request_start ();

  if (r < 0)
    {
      fprintf (stderr, "Failed to request gamemode: [%d] %s\n",
               r, gamemode_error_string ());
      return -1;
    }

  r = gamemode_query_status ();

  printf ("GameMode status: %d\n", r);
  printf ("Press any key to stop\n");

  (void) getchar();

  printf ("Stopping gamemode request\n");
  r = gamemode_request_end ();

  if (r < 0)
    fprintf (stderr, "Failed to end gamemode: [%d] %s\n",
             r, gamemode_error_string ());

  printf ("GameMode status: %d\n", r);

  return r;
}
