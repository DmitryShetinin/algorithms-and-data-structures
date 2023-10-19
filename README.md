 #Оценка сложностей алгоритмов 
 
##Класс DoubleLinkedList
https://github.com/DmitryShetinin/algorithms-and-data-structures/blob/469447c57ba9c919889a24f91e1020bff2f50573/lab1.cpp#L32 - O(n) (потому что нам нужно пройти первую или вторую (в зависимости от индекса) листа, соответсвенно, чем больше n(в нашем случае node) тем больше времени потребуется для того чтобы пробежать весь DoubleLinkedList) (Также здесь я добавил мини оптимизацию, так например если брать индыкс который больше чем половины количества элементов, то лист будет начинать переберать элементы с конца (то есть с tail)   )

##Класс DynamicArray
https://github.com/vashasashenka/fluffy-journey/blob/main/alg1.py#L132 - O(n) (потому что, как и в методе выше, нам нужно пробежаться по всему DoubleLinkedList и вывести значение (чем больше n тем больше бегать, отсюда и О(n))

##Класс Stack
https://github.com/DmitryShetinin/algorithms-and-data-structures/blob/469447c57ba9c919889a24f91e1020bff2f50573/lab1.cpp#L56C10-L56C20 - O(1)(в методе представляется возможность добавлять Node в конец списка, сложность O(1) обосновывается тем что, у нас все действия в функции константные.)