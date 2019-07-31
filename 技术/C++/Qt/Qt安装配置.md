# Qt 安装配置

## Project ERROR: Xcode not set up properly. You may need to confirm the license agreement by running /

### >= Xcode 8

Step 1:
Open the file:

> Qt_install_folder/5.7/clang_64/mkspecs/features/mac/default_pre.prf

Step 2:
Replace:

> isEmpty($$list($$system("/usr/bin/xcrun -find xcrun 2>/dev/null")))

With:

> isEmpty($$list($$system("/usr/bin/xcrun -find xcodebuild 2>/dev/null")))


### ~> Xcode 8
Before Xcode 8, this problem occurs when command line tools are installed after Xcode is installed. What happens is theXcode-selectdeveloper directory gets pointed to/Library/Developer/CommandLineTools.

Step 1:

PointXcode-selectto the correct Xcode Developer directory with the command:

> sudo xcode-select -switch /Applications/Xcode.app/Contents/Developer

Step 2:

Confirm the license agreement with the command:

> xcodebuild -license

This will prompt you to read through the license agreement.

Enteragreeto accept the terms.


