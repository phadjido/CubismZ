#!/usr/bin/env bash
set -Eeuo pipefail

echo "Downloading cavitation test data..."
curl https://polybox.ethz.ch/index.php/s/di7qQoWc6eAhCXk/download > tmp.tar.xz
tar xJf tmp.tar.xz
mv data_005000/* .
rm -rf data_005000
rm -f tmp.tar.xz
