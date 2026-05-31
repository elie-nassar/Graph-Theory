#include "benchmark/benchmark.h"
#include "graph.hpp"
#include "coloring/proper_coloring.hpp"

static void BACKTRACKING(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    graph g = graph::random(18,30);
    state.ResumeTiming();
    proper_coloring_backtracking(g,3);
  }
}
BENCHMARK(BACKTRACKING);

static void SAT(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    graph g = graph::random(18,30);
    state.ResumeTiming();
    proper_coloring_sat(g,3);
  }
}
BENCHMARK(SAT);

static void INCLUSION_EXCLUSION(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    graph g = graph::random(18,30);
    state.ResumeTiming();
    proper_coloring_inclusion_exclusion(g,3);
  }
}
BENCHMARK(INCLUSION_EXCLUSION);

static void DP(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    graph g = graph::random(18,30);
    state.ResumeTiming();
    proper_coloring_dp(g,3);
  }
}
BENCHMARK(DP);

static void DP_MAX_INDEPENDANT_SETS(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    graph g = graph::random(18,30);
    state.ResumeTiming();
    proper_coloring_dp_max_independant_sets(g,3);
  }
}
BENCHMARK(DP_MAX_INDEPENDANT_SETS);

BENCHMARK_MAIN();