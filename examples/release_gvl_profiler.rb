require 'lowlevel-toolkit'
require "net/http"

def counter_loop(counter = 0) = (counter += 1 while counter < 150_000_000)

pp(LowlevelToolkit.release_gvl_profiler(filename_prefix: "output") do
  counter_loop # Doesn't show up, GVL not released
  Net::HTTP.start("www.google.com", open_timeout: 5, read_timeout: 5, write_timeout: 5) { |it| it.get("/") }
  big_data = File.read("/dev/zero", 300_000_000)
  Dir.children("/usr/lib")
  Zlib::Deflate.deflate(big_data[0, 100_000_000])
end)
