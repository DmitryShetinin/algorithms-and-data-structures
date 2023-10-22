# `Класс DoublyLinkedList`

[push_front](https://github.com/DmitryShetinin/algorithms-and-data-structures/blob/main/lab1.cpp#L73) работает за: $$O(1)$$ потому что - в методе нет ни циклов, ни рекрсий, все команды в методе выполняются за константу, а значит и весь метод будет работать за O(1)
___

# `Класс DynamicArray`
[remove](https://github.com/DmitryShetinin/algorithms-and-data-structures/blob/main/lab1.cpp#L281) работает за: $$O(n)$$, потому что худший случай в данном методе мы получим когда `index != -1`, тогда вызовится метод removeAt в котором вызовится метод IndexTo который работает за $n/2$ но тк константы мы не учитываем то метод IndexTo будет работать за O(n). В итоге мы получаем что итоговая сложность равна O(n + size) то есть O(n)
(+ size получаем когда проходим цикл 
в самом методе remove)

___
# `Функция constructNumber`
[constructNumber](https://github.com/DmitryShetinin/algorithms-and-data-structures/blob/main/lab1.cpp#L468) работает за: $$O(n)$$ потому что в функции один цикл while который зависит от длины подаваемой в функцию строки.
