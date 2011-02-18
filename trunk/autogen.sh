#!/bin/sh

#touch NEWS README AUTHORS COPYING ChangeLog
autoreconf --force --install "$@"
