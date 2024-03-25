#!/bin/bash

set -u

for i in {0..9}; do
	base_dir="level0$i"
	mkdir "$base_dir"
	touch "$base_dir/flag"
	touch "$base_dir/source.c"
	touch "$base_dir/README.md"
done
