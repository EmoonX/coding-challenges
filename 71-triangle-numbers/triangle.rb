# Calculate nth triangle/triangle number by the
# well known formula for sum of consecutive numbers.
def nth_triangle(n)
  return n * (n + 1) / 2
end

# Check if wrong argument count or negative number were passed
if ARGV.length != 1 or ARGV[0].to_i < 0
  puts("  Usage: ruby triangle.rb N")
  puts("         (n must be >= 0)")
  puts("     Ex: ruby triangle.rb 100")
  puts(" Output: 5050")
  Kernel.exit(1)
end

# Get and print nth triangle number by using first arg as `n`
n = ARGV[0].to_i
ans = nth_triangle(n)
puts(ans)
