import kotlin.system.exitProcess

/**
 * Draws `i`th Pascal's row using the `i-1`th as basis.
 * Returns `i`th row array as result.
 */
fun drawRow(i: Int, row: ArrayList<Long>) {
    var prev = 0L
    for (j in 0..i) {
        if (j == i) {
            // Last value is always 1
            print("  1")
            row.add(1)
        } else {
            // j-th value equals sum of the top two values; actual
            // "cell" length depends on # of digits (but always >= 3)
            val k = prev + row[j]
            prev = row[j]
            row[j] = k
            val len = maxOf(k.toString().length, 2) + 1
            val formatStr = "%%%dd".format(len)
            print(formatStr.format(k))
        }
    }
}

fun main(args: Array<String>) {
    // Get n value from command line
    if (args.size != 1 || args[0].toInt() < 0) {
        println(" Usage: kotlin pascal.jar N")
        println("        (n must be >= 0)")
        println("    Ex: kotlin pascal.jar 42")
        exitProcess(1)
    }
    val n = args[0].toInt()
    
    // Print Pascal's triangle rows (from 0th to nth)
    val row = ArrayList<Long>()
    for (i in 0..n) {
        print("%2d ->".format(i))
        drawRow(i, row)
        println()
    }
}
