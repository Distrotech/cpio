#! /bin/sh

test -d m4 || mkdir m4
test -d scripts || mkdir scripts
autoreconf -f -i -s
