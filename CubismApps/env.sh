#!/usr/bin/env bash
# File       : env.sh
# Created    : Wed Nov 29 2017 07:32:11 PM (+0100)
# Author     : Fabian Wermelinger
# Description: Setup environment variables
# Copyright 2017 ETH Zurich. All Rights Reserved.
TOOLS="$(pwd -P)/Tools/build/bin"
THIRDTOOLS="$(pwd -P)/ThirdParty/build/bin"
export PATH=${TOOLS}:${THIRDTOOLS}:${PATH}
