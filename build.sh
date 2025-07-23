#!/usr/bin/bash

export __GLX_VENDOR_LIBRARY_NAME=nvidia
export LIBGL_ALWAYS_INDIRECT=0
export WLR_NO_HARDWARE_CURSORS=1
export GBM_BACKEND=nvidia-drm
export EGL_PLATFORM=wayland

cmake --build build
