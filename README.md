# main memory database|利用T*-tree做索引的内存中的数据库

T*-tree是一种类似于T-tree的二叉树，它的节点的结构体中比T-tree多一个指向继承者位的指针。因此T*-tree有快速查找索引的优点，也利于遍历某个范围的数据。

### Prerequisites

```
gcc 8.2.1
cmake 3.14.1
cJSON(.c, .h)
uthash(.c, .h)

```


## Usage
```
**SELECT**

SELECT [JSON / KEYVALUE]
FIND
FIND [numbers]
INSERT
INSERT [numbers] [value] or INSERT [JSON1] [JSON2] [JSON3] [JSON4]
DELETE
DELETE [numbers]
PRINT
PRINT :print all data stored in t\*ttee,PRINT FROM [number1] TO [number2] ,print data range from number1 to number2.
```

### initial database test

\*.del is dummy file for test.
```
key-value键值对是随机生成的，有100W条有序/无序的，1000万条有序/无序的。
```
## segmentfault博文链接

* [T-Tree、T*-Tree的理解与简单内存数据库的实现 V1.0](https://segmentfault.com/a/1190000018502294?share_user=1030000018424139)-这里写了关于内存数据库最初版本的详细解释。
* [通过TCP与简易内存数据库进行数据交互的实现 V1.1](https://segmentfault.com/a/1190000018561636?share_user=1030000018424139)-这里写了简单的socket编程来实现client端和server端的简单通信。


## Deployment

Add additional notes about how to deploy this on a live system


## Built With

* [gcc](https://gcc.gnu.org/) - GCC, the GNU Compiler Collection
* [uthash](https://github.com/troydhanson/uthash) - Any C structure can be stored in a hash table using uthash. Just add a UT_hash_handle to the structure and choose one or more fields in your structure to act as the key. Then use these macros to store, retrieve or delete items from the hash table.
* [cJSON](https://github.com/DaveGamble/cJSON) - Ultralightweight JSON parser in ANSI C.


## Authors

* **Slarsar Zhang** - *Initial work* - [github](https://github.com/slarsar)


## Acknowledgments

* Hat tip to anyone whose code was used; ttree.c,ttree.h:Dan Kruchinin <dkruchinin@acm.org>
