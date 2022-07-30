fun calculate(postfix: String): String {
    return postfix
}

fun main() {
    var postfix = "";
    while (postfix != "0") {
        print(">>> ")
        postfix = readLine()!!
        val result = calculate(postfix)
        println(result)
    }
}
