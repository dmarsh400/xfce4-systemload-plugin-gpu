[![License](https://img.shields.io/badge/License-BSD%202--Clause-blue.svg)](https://gitlab.xfce.org/panel-plugins/xfce4-systemload-plugin/-/blob/master/COPYING)
[![License](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://gitlab.xfce.org/panel-plugins/xfce4-systemload-plugin/-/blob/master/COPYING)

# xfce4-systemload-plugin-gpu

xfce4-systemload-plugin displays current CPU load, memory in use, network utilization, swap space, system uptime, and **GPU utilization** in xfce4-panel.

## Features

- **CPU Load**: Monitor processor utilization
- **Memory Usage**: Track RAM consumption
- **Network Traffic**: Display network I/O rates
- **Swap Usage**: Monitor swap space utilization
- **System Uptime**: Show system uptime
- **GPU Monitoring**: Real-time AMD GPU utilization (GPU0/GPU1) via ROCm
- **VRAM Monitoring**: Real-time AMD GPU memory usage (VRAM0/VRAM1) via ROCm

## GPU Support

This enhanced version includes integrated GPU monitoring for AMD GPUs using ROCm:

- **GPU0/GPU1 Support**: Monitor multiple AMD GPUs simultaneously
- **VRAM0/VRAM1 Support**: Monitor VRAM usage for multiple AMD GPUs
- **ROCm Integration**: Uses `rocm-smi --showuse` and `rocm-smi --showmeminfo` for accurate readings
- **Real-time Updates**: Live GPU utilization and VRAM usage tracking
- **Configurable**: Enable/disable individual GPU and VRAM monitors
- **Visual Indicators**: Distinct colors for each GPU (GPU0: dark red, GPU1: purple) and VRAM (VRAM0: dark red, VRAM1: dark purple)

### Requirements for GPU Monitoring

- AMD GPU with ROCm installed
- `rocm-smi` command available (typically at `/opt/rocm-*/bin/rocm-smi`)

## Installation

From source:

    % sudo apt install meson ninja-build build-essential libxfce4panel-2.0-dev
    % cd xfce4-systemload-plugin-gpu
    % meson setup build --wipe --prefix=/usr
    % meson compile -C build
    % sudo meson install -C build
    % xfce4-panel -r

This fork installs as a separate XFCE panel module (`systemload-gpu`) so it can coexist with the distro `xfce4-systemload-plugin` package.

## Usage

1. Add the "System Load Monitor (GPU)" plugin to your Xfce panel
2. Right-click the plugin → Properties to configure which monitors to display
3. Enable GPU0/GPU1 and VRAM0/VRAM1 monitoring as desired
4. Customize colors and labels for each monitor type

## Troubleshooting

- If Meson reports stale build metadata after an OS upgrade:

    % meson setup build --wipe --prefix=/usr

- If Meson cannot find Ninja, verify the executable in your PATH:

    % which ninja
    % ninja --version

- If panel options still look like the stock plugin, restart the panel and re-add this plugin:

    % xfce4-panel -r

## Configuration

- **Monitor Selection**: Enable/disable CPU, Memory, Network, Swap, GPU0, GPU1, VRAM0, VRAM1
- **Colors**: Customize colors for each monitor type
- **Labels**: Show/hide text labels for each monitor
- **Update Interval**: Adjust refresh rate (default: 500ms)

## Requirements

- **Xfce4 panel**
- **GTK3**
- **libxfce4panel**
- **libxfce4ui**
- **libxfce4util**
- **xfconf**
- **AMD GPU + ROCm** (for GPU monitoring)

## Screenshots

### System Load Monitor with GPU Support
![Enhanced System Load Monitor](Screenshot%20for%20Github.png)

*Shows the enhanced system load monitor displaying CPU, Memory, Network, Swap, GPU0/GPU1 utilization, and VRAM0/VRAM1 usage with persistent labels, colors, and monitor toggles.*

## License

BSD-2-Clause (original) + GPL-2.0-or-later (enhancements)

## Development

This is an enhanced version of the official XFCE system load plugin with integrated GPU monitoring. For a standalone GPU graph plugin, see [xfce4-gpugraph-plugin](https://github.com/dmarsh400/xfce4-gpugraph-plugin).

### Homepage

[Xfce4-systemload-plugin documentation](https://docs.xfce.org/panel-plugins/xfce4-systemload-plugin/start)

### Changelog

See [NEWS](https://gitlab.xfce.org/panel-plugins/xfce4-systemload-plugin/-/blob/master/NEWS) for details on changes and fixes made in the current release.

### Source Code Repository

[Xfce4-systemload-plugin source code](https://gitlab.xfce.org/panel-plugins/xfce4-systemload-plugin)

### Download a Release Tarball

[Xfce4-systemload-plugin archive](https://archive.xfce.org/src/panel-plugins/xfce4-systemload-plugin)
    or
[Xfce4-systemload-plugin tags](https://gitlab.xfce.org/panel-plugins/xfce4-systemload-plugin/-/tags)

### Installation

From source code repository: 

    % cd xfce4-systemload-plugin
    % meson setup build
    % meson compile -C build
    % meson install -C build

From release tarball:

    % tar xf xfce4-systemload-plugin-<version>.tar.xz
    % cd xfce4-systemload-plugin-<version>
    % meson setup build
    % meson compile -C build
    % meson install -C build

### Uninstallation

    % ninja uninstall -C build

### Reporting Bugs

Visit the [reporting bugs](https://docs.xfce.org/panel-plugins/xfce4-systemload-plugin/bugs) page to view currently open bug reports and instructions on reporting new bugs or submitting bugfixes.

