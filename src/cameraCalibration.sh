#!/usr/bin/env bash
set -e

DEVICE="/dev/video3"

echo "Configuring Logitech C270 on $DEVICE"

# ------------------------
# CAMERA CONTROLS (order matters!)
# ------------------------

# Disable auto exposure
v4l2-ctl -d "$DEVICE" --set-ctrl=auto_exposure=1

# Disable exposure-based FPS changes
v4l2-ctl -d "$DEVICE" --set-ctrl=exposure_dynamic_framerate=0

# Set manual exposure (only works AFTER auto_exposure=1)
v4l2-ctl -d "$DEVICE" --set-ctrl=exposure_time_absolute=667


# ------------------------
# USER CONTROLS
# ------------------------

# Disable auto white balance FIRST
v4l2-ctl -d "$DEVICE" --set-ctrl=white_balance_automatic=0

# Manual white balance (Kelvin)
v4l2-ctl -d "$DEVICE" --set-ctrl=white_balance_temperature=6500

# Image controls
v4l2-ctl -d "$DEVICE" --set-ctrl=brightness=170
v4l2-ctl -d "$DEVICE" --set-ctrl=contrast=35
v4l2-ctl -d "$DEVICE" --set-ctrl=saturation=45
v4l2-ctl -d "$DEVICE" --set-ctrl=sharpness=24


# Gain (analog amplification)
v4l2-ctl -d "$DEVICE" --set-ctrl=gain=131

# Power line flicker compensation (EU = 50 Hz)
v4l2-ctl -d "$DEVICE" --set-ctrl=power_line_frequency=1

# Disable backlight compensation
v4l2-ctl -d "$DEVICE" --set-ctrl=backlight_compensation=0


# ------------------------
# DONE
# ------------------------

echo "Camera configuration applied successfully."
echo "Current exposure-related status:"
v4l2-ctl -d "$DEVICE" --get-ctrl=auto_exposure,exposure_time_absolute