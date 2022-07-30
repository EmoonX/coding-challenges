class Stack {

    val tokens = ArrayDeque<String>()

    fun push(value: String) {
        tokens.addLast(value)
    }

    fun pop(): String {
        val last = tokens.removeLast()
        return last
    }
}

fun calculate(postfix: String): String? {
    val tokens = postfix.split(" ")
    val stack = Stack()
    for (token in tokens) {
        stack.push(token)
    }
    return stack.pop()
}

fun main() {
    var postfix = "";
    while (postfix != "0") {
        print(">>> ")
        postfix = readLine()!!
        val result = calculate(postfix)
        if (result != "") {
            println(result)
        }
    }
}
