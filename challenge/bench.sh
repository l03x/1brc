#!/usr/bin/env bash
# Run the 1BRC solution N times and print the average wall-clock time.
# Usage: ./bench.sh [runs]   (run from the challenge/ folder)
set -euo pipefail

RUNS=${1:-10}
JAVA=${JAVA:-java}
JAVAC=${JAVAC:-javac}

"$JAVAC" -d out/cli src/*.java

# One warmup run so the file is in the page cache for every timed run
"$JAVA" -cp out/cli Main >/dev/null

total=0
for i in $(seq 1 "$RUNS"); do
  start=$(date +%s%N)
  "$JAVA" -cp out/cli Main >/dev/null
  end=$(date +%s%N)
  ms=$(((end - start) / 1000000))
  total=$((total + ms))
  printf "run %2d: %d ms\n" "$i" "$ms"
done

printf "average over %d runs: %d ms\n" "$RUNS" $((total / RUNS))
