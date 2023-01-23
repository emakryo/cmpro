#!/bin/bash
set -e

cd tools

# export RUST_BACKTRACE=1
# for intxt in $(ls in/); do
# cargo run --release --bin tester bash -c "cd ..; cargo run" < in/$intxt > out.txt
# done
cargo run --release --bin tester bash -c "cd ..; cargo run" < in/0000.txt > out.txt
pbcopy < out.txt
cd -