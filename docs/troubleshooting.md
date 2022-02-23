# Troubleshooting

This document provides instructions for dealing with possible issues that might arise when trying to run Wanderer.

## There are black margins around my game viewport

### Option 1 (Windows)

If you're using a 16:9 monitor then this is likely solved by overriding the DPI-scaling settings for the executable in
Windows.

1. Navigate to the Wanderer executable.
1. Right-click the executable, select the `Properties` item.
1. Select the `Compatibility` tab.
1. In the `Settings` group, press the `Change high DPI settings` button.
1. In the `High DPI scaling override` group, enable the `Override high DPI scaling behaviour` checkbox.
1. Select the `Application` item in the dropdown.
1. That's it! The scaling should now be fixed the next time you Run the game.

### Option 2

If your monitor uses an uncommon resolution, the issue might be caused by the fact that the ratio between the logical
viewport size and the monitor size is not integral. This can be solved by disabling "Integer scaling" in the options.
However, this can introduce minor rendering artifacts.

### Option 3

An alternative to Option 2 is to override the logical viewport size manually. It is recommended to use a logical
viewport size with a width around 1000, and it should be an integral scale factor of the screen size.

```bash
./Wanderer -ls 960 600             # Terse syntax 
./Wanderer --logical-size 960 600  # Verbose syntax
```
