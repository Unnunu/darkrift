#!/usr/bin/env python3

def apply(config, args):
    config['baseimg'] = 'darkrift.z64'
    config['myimg'] = 'build/darkrift.z64'
    config['mapfile'] = 'build/darkrift.map'
    config['source_directories'] = ['.']
    config["make_command"] = ["ninja"]
    config["objdump_flags"] = ["-M", "reg-names=32"]
    config["expected_dir"] = f"expected/"
