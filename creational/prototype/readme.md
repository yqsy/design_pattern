
<!-- TOC -->

- [1. 资料](#1-资料)

<!-- /TOC -->

<a id="markdown-1-资料" name="1-资料"></a>
# 1. 资料

* https://en.wikipedia.org/wiki/Prototype_pattern


案例模仿protobuf的Message,还包括了dispatch的代码

简单来说prototype就是利用已有的类型去创造同样的类型

例如在protobuf中的作用是,利用字符串在字典中找到相应的prototype,再创造一个新的对象去反序列化字节码

但是是否有必要死守这个设计模式,未必见得有必要

编程语言内置用类型创建类型的功能时,这设计模式就没用了.

