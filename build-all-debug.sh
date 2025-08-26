#!/bin/bash

# This file is a part of Nitisa framework
# Copyright © 2021 Nitisa. All rights reserved.
# Author: Dmitriy Lysenko
# Site: http://nitisa.com
# Download: http://nitisa.com/downloads
# Documentation: http://nitisa.com/documentation
# License: http://nitisa.com/site/license

echo "Building Debug configuration"

echo "Building Nitisa library"
rm -f "$PWD/Nitisa/stdafx.h.gch"
./build.sh Nitisa Debug x86 dev Nitisa

echo "Building Standard library"
rm -f "$PWD/Packages/Standard/stdafx.h.gch"
./build.sh Standard Debug x86 dev Packages/Standard

echo "Building Platform library"
rm -f "$PWD/Packages/Platform/stdafx.h.gch"
./build.sh Platform Debug x86 dev Packages/Platform

echo "Building Extended library"
rm -f "$PWD/Packages/Extended/stdafx.h.gch"
./build.sh Extended Debug x86 dev Packages/Extended

echo "Building Charts library"
rm -f "$PWD/Packages/Charts/stdafx.h.gch"
./build.sh Charts Debug x86 dev Packages/Charts

echo "Building Ide library"
rm -f "$PWD/Packages/Ide/stdafx.h.gch"
./build.sh Ide Debug x86 dev Packages/Ide
