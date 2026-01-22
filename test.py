#!/usr/bin/env python
import subprocess
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("source_file")
parser.add_argument("input")
parser.add_argument("expected_output")
args = parser.parse_args()

process = subprocess.run(["./bf-interpreter", args.source_file], input=args.input.encode(), stdout=subprocess.PIPE)
encoded_output = args.expected_output.encode()
if process.stdout == encoded_output:
    exit(0)
print(f"Expected {encoded_output}, got {process.stdout}")
exit(1)