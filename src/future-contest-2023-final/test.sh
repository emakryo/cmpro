#!/bin/bash

cd tools
cargo run --release --bin tester bash -c "cd ..; cargo run" < in/0000.txt > out.txt
pbcopy < out.txt
cd -