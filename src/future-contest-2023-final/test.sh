#!/bin/bash
set -e

cd tools

for intxt in $(ls in/); do
cargo run --release --bin tester bash -c "cd ..; cargo run" < in/$intxt > out.txt
done
# pbcopy < out.txt
cd -