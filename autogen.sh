#!/bin/sh

set -e

touch NEWS README AUTHORS COPYING ChangeLog
autoreconf --force --install
