#include "benchmark/benchmark.h"
#include "graph.hpp"
#include "coloring/dominator_coloring.hpp"

static void BACKTRACKING(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    graph g = graph::random(18,30);
    state.ResumeTiming();
    dominator_coloring_backtracking(g,3);
  }
}
BENCHMARK(BACKTRACKING);

static void SAT(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    graph g = graph::random(18,30);
    state.ResumeTiming();
    dominator_coloring_sat(g,3);
  }
}
BENCHMARK(SAT);

BENCHMARK_MAIN();