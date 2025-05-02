require "benchmark/ips"
require "lowlevel-toolkit"

def run_benchmark(config_name)
  Benchmark.ips do |x|
    x.config(time: 10, warmup: 2)

    x.report("#{RUBY_VERSION} #{config_name}", "Object.new")
    x.save! "newobj_overhead-results.json"
    x.compare!
  end
end

LowlevelToolkit.newobj_overhead { run_benchmark("tracepoint ✅") }
run_benchmark("tracepoint ❌")
