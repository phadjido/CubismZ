#!/usr/bin/env bash
set -Eeuo pipefail

echo "Downloading cavitation test data..."
wget https://www.hpclab.ceid.upatras.gr/cubismz/cavitation_data.tar.gz
tar xvfz cavitation_data.tar.gz
mv cavitation_data/* .
rm -rf cavitation_data
rm -f cavitation_data.tar.gz
