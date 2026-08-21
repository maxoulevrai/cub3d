#!/usr/bin/env sh

set -eu

display=${DISPLAY:-:99}

if pgrep -f "Xvfb ${display}" >/dev/null 2>&1; then
	exit 0
fi

Xvfb "${display}" -screen 0 1280x720x24 >/tmp/cub3d-xvfb.log 2>&1 &