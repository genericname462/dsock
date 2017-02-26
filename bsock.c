/*

  Copyright (c) 2017 Martin Sustrik

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom
  the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.

*/

#include <stddef.h>

#include "dsockimpl.h"
#include "utils.h"

dsock_unique_id(bsock_type);

int bsend(int s, const void *buf, size_t len, int64_t deadline) {
    struct bsock_vfs *b = hquery(s, bsock_type);
    if(dsock_slow(!b)) return -1;
    struct iolist iol;
    iol.iol_base = (void*)buf;
    iol.iol_len = len;
    iol.iol_next = NULL;
    return b->bsendl(b, &iol, &iol, deadline);
}

int brecv(int s, void *buf, size_t len, int64_t deadline) {
    struct bsock_vfs *b = hquery(s, bsock_type);
    if(dsock_slow(!b)) return -1;
    struct iolist iol;
    iol.iol_base = buf;
    iol.iol_len = len;
    iol.iol_next = NULL;
    return b->brecvl(b, &iol, &iol, deadline);
}

int bsendl(int s, struct iolist *first, struct iolist *last, int64_t deadline) {
    struct bsock_vfs *b = hquery(s, bsock_type);
    if(dsock_slow(!b)) return -1;
    return b->bsendl(b, first, last, deadline);
}

int brecvl(int s, struct iolist *first, struct iolist *last, int64_t deadline) {
    struct bsock_vfs *b = hquery(s, bsock_type);
    if(dsock_slow(!b)) return -1;
    return b->brecvl(b, first, last, deadline);
}

