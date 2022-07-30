/**
 * Simple stack implementation with `push`/`pop` methods.
 */
class Stack<T> {

    /** Inner deque for holding stack values. */
    private val tokens = ArrayDeque<T>()

    /** Push a value to the stack. */
    fun push(value: T) {
        tokens.addLast(value)
    }

    /** Removes top value from stack and returns it. */
    fun pop(): T {
        val last = tokens.removeLast()
        return last
    }
}

/** 
 * Evaluates postfix expression.
 */
fun evaluate(postfix: String): Int {
    val tokens = postfix.split(" ")
    val stack = Stack<Int>()
    for (token in tokens) {
        var value = token.toIntOrNull()
        if (value == null) {
            value = calculate(token, stack)
        }
        stack.push(value)
    }
    return stack.pop()
}

/**
 * Returns result of operator `op` applied
 * to the topmost two stack values.
 */
fun calculate(op: String, stack: Stack<Int>): Int {
    val y = stack.pop()
    val x = stack.pop()
    return when (op) {
        "+" -> x + y
        "-" -> x - y
        "*" -> x * y
        "/" -> x / y
        else -> 0
    }
}

fun main() {
    var postfix = "";
    while (postfix != "0") {
        print(">>> ")
        postfix = readLine()!!
        if (postfix != "") {
            val result = evaluate(postfix)
            println(result)
        }
    }
}
