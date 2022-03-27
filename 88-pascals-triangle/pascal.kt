import kotlin.system.exitProcess

/**
 *  Draws `i`th Pascal's row using `i-1`th as basis.
 *  Returns `i`th row array as result.
 */
fun drawRow(i: Int, lastRow: Array<Long>): Array<Long> {
    val row = Array(i+1, {0L})
    for (j in 0..i) {
        if (j == 0 || j == i) {
            // First and last values are always 1
            print("  1")
            row[j] = 1L
        } else {
            // j-th value equals sum of the top two values; actual
            // "cell" length depends on # of digits (but always >= 3)
            val k = lastRow[j-1] + lastRow[j]
            val len = maxOf(k.toString().length, 2) + 1
            val formatStr = "%%%dd".format(len)
            print(formatStr.format(k))
            row[j] = k
        }
    }
    println()
    return row
}

fun main(args: Array<String>) {
    // Get n value from command line
    if (args.size != 1 || args[0].toInt() < 0) {
        println(" Usage: kotlin pascal.jar N")
        println("        (n must be >= 0)")
        println("    Ex: kotlin pascal.jar 42")
        exitProcess(1)
    }
    var n = args[0].toInt();
    
    // Print Pascal's triangle rows (from 0th to nth)
    println(" 0 ->  1")
    var lastRow = Array(1, {1L})
    for (i in 1..n) {
        print("%2d ->".format(i))
        lastRow = drawRow(i, lastRow)
    }
}
