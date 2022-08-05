class LinkedList {

    class Node(value: Int) {

        public val value: Int
        var next: Node? = null
        
        init {
            this.value = value
        }
    }
    
    public val head = Node(-1)
    var last = head

    public fun add(value: Int) {
        val node = Node(value)
        last.next = node
        last = node
    }
}

fun main() {
    val list = LinkedList()
    for (k in 1..10) {
        list.add(k)
    }
    var node = list.head.next
    while (node != null) {
        print("${node.value} ")
        node = node.next
    }
    println("");
}
