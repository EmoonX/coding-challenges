fun main() {
    println("   1")
    var lastRow = Array(1, {1})
    for (i in 1..5) {
        val row = Array(i+1, {0})
        for (j in 0..i) {
            if (j == 0 || j == i) {
                print("   1")
                row[j] = 1
            } else {
                val k = lastRow[j-1] + lastRow[j]
                print("%4d".format(k))
                row[j] = k
            }
        }
        lastRow = row
        println()
    }
}
